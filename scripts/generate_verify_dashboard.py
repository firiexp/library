#!/usr/bin/env python3

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import html
import json
import os
import pathlib
import shlex
import subprocess
import sys
import tempfile
import threading
import time
from datetime import datetime, timezone
from typing import Any

import onlinejudge
import onlinejudge.service.library_checker
import onlinejudge_verify.languages.list

ROOT = pathlib.Path(__file__).resolve().parent.parent
DEFAULT_JSON_PATH = ROOT / ".verify-helper" / "measure-dashboard.json"
DEFAULT_HTML_PATH = ROOT / ".verify-helper" / "measure-dashboard.html"
DEFAULT_WORKERS = max(1, os.cpu_count() or 1)
_problem_locks_guard = threading.Lock()
_problem_locks: dict[str, threading.Lock] = {}


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Measure verification tests, update json incrementally, and generate a browser dashboard.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "paths",
        nargs="*",
        help="verification test paths; if omitted, scan test/*.test.cpp",
    )
    parser.add_argument(
        "--json",
        dest="json_path",
        type=pathlib.Path,
        default=DEFAULT_JSON_PATH,
        help="output json path",
    )
    parser.add_argument(
        "--html",
        dest="html_path",
        type=pathlib.Path,
        default=DEFAULT_HTML_PATH,
        help="output html path",
    )
    parser.add_argument(
        "--tle",
        type=float,
        default=60.0,
        help="oj test --tle value",
    )
    parser.add_argument(
        "-j",
        "--jobs",
        type=int,
        default=DEFAULT_WORKERS,
        help="number of tests to measure in parallel",
    )
    parser.add_argument(
        "--oj-jobs",
        type=int,
        default=1,
        help="oj test -j value for each measured test",
    )
    parser.add_argument(
        "--compile-jobs",
        type=int,
        default=1,
        help="number of compilations to run in parallel",
    )
    parser.add_argument(
        "--keep-going",
        action="store_true",
        help="continue even if some tests fail to compile or run",
    )
    parser.add_argument(
        "--render-only",
        action="store_true",
        help="read existing json and regenerate html without running measurements",
    )
    return parser.parse_args()


def list_test_paths(paths: list[str]) -> list[pathlib.Path]:
    if paths:
        return [ROOT / pathlib.Path(path) for path in paths]
    return sorted((ROOT / "test").glob("*.test.cpp"))


def run_command(command: list[str], *, cwd: pathlib.Path) -> subprocess.CompletedProcess[str]:
    return subprocess.run(
        command,
        cwd=cwd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
    )


def parse_oj_test_output(output: str) -> dict[str, Any]:
    cases: list[dict[str, Any]] = []
    current_case: dict[str, Any] | None = None
    slowest_sec = None
    slowest_case = None
    max_memory_mb = None
    max_memory_case = None
    summary = None

    for raw_line in output.splitlines():
        line = raw_line.strip()
        if not line.startswith("["):
            continue

        if line.startswith("[INFO] time: "):
            if current_case is not None:
                value = line[len("[INFO] time: ") :].removesuffix(" sec")
                current_case["timeSec"] = float(value)
            continue

        if line.startswith("[INFO] slowest: "):
            body = line[len("[INFO] slowest: ") :]
            value, _, rest = body.partition(" sec")
            slowest_sec = float(value)
            if "(for " in rest and rest.endswith(")"):
                slowest_case = rest.split("(for ", 1)[1][:-1]
            continue

        if line.startswith("[INFO] max memory: "):
            body = line[len("[INFO] max memory: ") :]
            value, _, rest = body.partition(" MB")
            max_memory_mb = float(value)
            if "(for " in rest and rest.endswith(")"):
                max_memory_case = rest.split("(for ", 1)[1][:-1]
            continue

        if line.startswith("[SUCCESS] test success: "):
            summary = line[len("[SUCCESS] ") :]
            continue

        if line.startswith("[INFO] ") and ":" not in line and "cases found" not in line and "online-judge-tools" not in line:
            case_name = line[len("[INFO] ") :]
            current_case = {"name": case_name}
            cases.append(current_case)
            continue

        if current_case is not None and line.startswith("["):
            prefix, _, body = line.partition("] ")
            status = body.strip()
            if prefix in ("[SUCCESS", "[FAILURE", "[ERROR"):
                current_case["status"] = status

    timed_cases = [case["timeSec"] for case in cases if "timeSec" in case]
    return {
        "cases": cases,
        "caseCount": len(cases),
        "timedCaseCount": len(timed_cases),
        "passedCaseCount": sum(case.get("status") == "AC" for case in cases),
        "slowestSec": slowest_sec,
        "slowestCase": slowest_case,
        "averageSec": (sum(timed_cases) / len(timed_cases)) if timed_cases else None,
        "maxMemoryMb": max_memory_mb,
        "maxMemoryCase": max_memory_case,
        "summary": summary,
    }


def build_cache_dir(problem_url: str) -> pathlib.Path:
    digest = hashlib.md5(problem_url.encode()).hexdigest()
    return ROOT / ".verify-helper" / "cache" / digest


def get_problem_lock(problem_url: str) -> threading.Lock:
    with _problem_locks_guard:
        lock = _problem_locks.get(problem_url)
        if lock is None:
            lock = threading.Lock()
            _problem_locks[problem_url] = lock
        return lock


def make_empty_entry(path: pathlib.Path) -> dict[str, Any]:
    relative_path = path.resolve().relative_to(ROOT)
    return {
        "path": str(relative_path),
        "phase": "pending",
        "problem": None,
        "compiler": {
            "command": [],
            "wallSec": None,
        },
        "testcases": {
            "directory": None,
            "cachedCaseCount": 0,
        },
        "run": {
            "command": [],
            "returnCode": None,
            "wallSec": None,
            "ok": False,
            "parsed": {
                "cases": [],
                "caseCount": 0,
                "timedCaseCount": 0,
                "passedCaseCount": 0,
                "slowestSec": None,
                "slowestCase": None,
                "averageSec": None,
                "maxMemoryMb": None,
                "maxMemoryCase": None,
                "summary": None,
            },
            "output": "",
        },
    }


def make_report(entries: list[dict[str, Any]]) -> dict[str, Any]:
    phase_counts = {
        "pending": 0,
        "running": 0,
        "done": 0,
        "error": 0,
    }
    ok_count = 0
    failed_count = 0
    for entry in entries:
        phase = entry.get("phase", "pending")
        phase_counts[phase] = phase_counts.get(phase, 0) + 1
        if phase == "done" and entry["run"]["ok"]:
            ok_count += 1
        elif phase in ("done", "error"):
            failed_count += 1
    return {
        "generatedAt": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        "root": str(ROOT),
        "testCount": len(entries),
        "summary": {
            **phase_counts,
            "ok": ok_count,
            "failed": failed_count,
        },
        "tests": entries,
    }


def write_report(report: dict[str, Any], *, json_path: pathlib.Path, html_path: pathlib.Path) -> None:
    json_path.parent.mkdir(parents=True, exist_ok=True)
    html_path.parent.mkdir(parents=True, exist_ok=True)
    json_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n")
    html_path.write_text(render_html(report, json_path=json_path))


def ensure_testcases(problem_url: str, *, testcase_dir: pathlib.Path) -> None:
    if testcase_dir.exists() and any(testcase_dir.iterdir()):
        return

    testcase_dir.mkdir(parents=True, exist_ok=True)
    command = ["oj", "download", "--system", "-d", str(testcase_dir), "--silent", problem_url]
    if os.environ.get("DROPBOX_TOKEN"):
        command += ["--dropbox-token", os.environ["DROPBOX_TOKEN"]]
    if os.environ.get("YUKICODER_TOKEN"):
        command += ["--yukicoder-token", os.environ["YUKICODER_TOKEN"]]

    completed = run_command(command, cwd=ROOT)
    if completed.returncode != 0:
        raise RuntimeError(f"failed to download testcases: {problem_url}\n{completed.stdout}")
    if not any(testcase_dir.iterdir()):
        raise RuntimeError(f"downloaded testcase directory is empty: {testcase_dir}")


def run_one_test(path: pathlib.Path, *, tle: float, oj_jobs: int, compile_slots: threading.Semaphore) -> dict[str, Any]:
    relative_path = path.resolve().relative_to(ROOT)
    language = onlinejudge_verify.languages.list.get(relative_path)
    if language is None:
        raise RuntimeError(f"unsupported language: {relative_path}")

    attributes = language.list_attributes(relative_path, basedir=ROOT)
    problem_url = attributes.get("PROBLEM")
    if not problem_url:
        raise RuntimeError(f"PROBLEM is not specified: {relative_path}")

    cache_dir = build_cache_dir(problem_url)
    testcase_dir = cache_dir / "test"
    cache_dir.mkdir(parents=True, exist_ok=True)

    problem = onlinejudge.dispatch.problem_from_url(problem_url)
    judge_command = None
    with get_problem_lock(problem_url):
        ensure_testcases(problem_url, testcase_dir=testcase_dir)
        if isinstance(problem, onlinejudge.service.library_checker.LibraryCheckerProblem):
            judge_command = str(problem.download_checker_binary())

    environments = language.list_environments(relative_path, basedir=ROOT)
    if not environments:
        raise RuntimeError(f"no compiler environment found: {relative_path}")
    environment = environments[0]

    with tempfile.TemporaryDirectory(prefix="verify-dashboard-", dir=cache_dir) as tempdir_str:
        tempdir = pathlib.Path(tempdir_str)
        with compile_slots:
            compile_started_at = time.perf_counter()
            environment.compile(relative_path, basedir=ROOT, tempdir=tempdir)
            compile_wall_sec = time.perf_counter() - compile_started_at

        execute = environment.get_execute_command(relative_path, basedir=ROOT, tempdir=tempdir)
        command = ["oj", "test", "-c", shlex.join(execute), "-d", str(testcase_dir), "--tle", str(tle)]
        if judge_command is not None:
            command += ["--judge-command", judge_command]
        if oj_jobs != 1:
            command += ["-j", str(oj_jobs)]

        run_started_at = time.perf_counter()
        completed = run_command(command, cwd=ROOT)
        run_wall_sec = time.perf_counter() - run_started_at

    parsed = parse_oj_test_output(completed.stdout)
    testcase_count = len(list(testcase_dir.glob("*.in")))
    return {
        "path": str(relative_path),
        "phase": "done",
        "problem": problem_url,
        "compiler": {
            "command": [str(environment.CXX), *environment.CXXFLAGS, "-I", str(ROOT), "-o", "a.out", str(relative_path)],
            "wallSec": compile_wall_sec,
        },
        "testcases": {
            "directory": str(testcase_dir.relative_to(ROOT)),
            "cachedCaseCount": testcase_count,
        },
        "run": {
            "command": command,
            "returnCode": completed.returncode,
            "wallSec": run_wall_sec,
            "ok": completed.returncode == 0,
            "parsed": parsed,
            "output": completed.stdout,
        },
    }


def render_html(report: dict[str, Any], *, json_path: pathlib.Path) -> str:
    bootstrap_json = json.dumps(
        {
            "generatedAt": report.get("generatedAt"),
            "root": report.get("root"),
            "testCount": report.get("testCount", 0),
            "summary": report.get("summary", {}),
            "tests": [],
        },
        ensure_ascii=False,
    )
    json_filename = html.escape(json_path.name)
    generated_at = html.escape(report["generatedAt"])
    title = "verify measurement dashboard"
    return f"""<!doctype html>
<html lang="ja">
<head>
<meta charset="utf-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<title>{title}</title>
<style>
:root {{
    --bg: #f6f3ee;
    --panel: #fffdf8;
    --panel-2: #f0e7d8;
    --panel-3: #f7efe2;
    --line: #d8ccb8;
    --text: #1f1d1a;
    --muted: #685f54;
    --ok: #1a7f45;
    --bad: #b42318;
    --warn: #b7791f;
    --accent: #9a3412;
    --controls-top: 12px;
    --table-sticky-top: 96px;
}}
* {{ box-sizing: border-box; }}
body {{
    margin: 0;
    font-family: "Iosevka Web", "IBM Plex Sans JP", sans-serif;
    color: var(--text);
    background:
        radial-gradient(circle at top left, #f0d9b5 0, transparent 35%),
        linear-gradient(180deg, #f9f5ed 0%, var(--bg) 100%);
}}
main {{
    max-width: 1280px;
    margin: 0 auto;
    padding: 32px 20px 80px;
}}
h1 {{
    margin: 0;
    font-size: clamp(28px, 5vw, 48px);
    line-height: 1.05;
    letter-spacing: -0.03em;
}}
.lede {{
    margin: 10px 0 0;
    color: var(--muted);
}}
.meta {{
    display: flex;
    gap: 12px;
    flex-wrap: wrap;
    margin: 22px 0 28px;
}}
.chip {{
    border: 1px solid var(--line);
    background: rgba(255, 253, 248, 0.75);
    padding: 8px 12px;
    border-radius: 999px;
    font-size: 14px;
    min-height: 40px;
    display: inline-flex;
    align-items: center;
    gap: 8px;
    font-variant-numeric: tabular-nums;
}}
.chip-label {{
    font-weight: 700;
}}
.chip-meta {{
    color: var(--muted);
    min-width: 12ch;
}}
.live-dot {{
    width: 10px;
    height: 10px;
    border-radius: 999px;
    background: currentColor;
    flex: none;
}}
.chip.is-ok {{
    color: var(--ok);
    border-color: rgba(26, 127, 69, 0.22);
    background: rgba(26, 127, 69, 0.08);
}}
.chip.is-warn {{
    color: var(--warn);
    border-color: rgba(183, 121, 31, 0.24);
    background: rgba(183, 121, 31, 0.11);
}}
.chip.is-bad {{
    color: var(--bad);
    border-color: rgba(180, 35, 24, 0.24);
    background: rgba(180, 35, 24, 0.09);
}}
.chip.is-active {{
    color: var(--accent);
    border-color: rgba(154, 52, 18, 0.3);
    background: rgba(154, 52, 18, 0.1);
}}
.chip-action {{
    font: inherit;
    color: inherit;
    cursor: pointer;
    transition: transform 120ms ease, box-shadow 120ms ease;
}}
.chip-action:hover {{
    transform: translateY(-1px);
    box-shadow: 0 6px 16px rgba(76, 52, 24, 0.08);
}}
.chip-action:focus-visible {{
    outline: 2px solid rgba(154, 52, 18, 0.35);
    outline-offset: 2px;
}}
.chip-action:disabled {{
    cursor: not-allowed;
    opacity: 0.7;
    transform: none;
    box-shadow: none;
}}
.controls {{
    display: grid;
    grid-template-columns: minmax(260px, 1.3fr) repeat(2, minmax(180px, 0.7fr)) minmax(220px, auto);
    gap: 12px;
    margin-bottom: 18px;
    position: sticky;
    top: var(--controls-top);
    z-index: 24;
    padding: 12px;
    border: 1px solid rgba(216, 204, 184, 0.85);
    border-radius: 18px;
    background: rgba(255, 249, 240, 0.9);
    backdrop-filter: blur(10px);
    box-shadow: 0 14px 28px rgba(76, 52, 24, 0.08);
}}
.control-field {{
    display: grid;
    gap: 6px;
    align-content: start;
}}
.control-label {{
    color: var(--muted);
    font-size: 11px;
    font-weight: 700;
    letter-spacing: 0.08em;
    text-transform: uppercase;
}}
.control-cluster {{
    display: grid;
    grid-template-columns: minmax(0, 1fr) auto;
    gap: 8px;
}}
.controls input,
.controls select {{
    width: 100%;
    border: 1px solid var(--line);
    border-radius: 12px;
    padding: 10px 12px;
    background: var(--panel);
    color: var(--text);
}}
.controls input:focus-visible,
.controls select:focus-visible,
.expander:focus-visible,
.detail-tab:focus-visible,
.detail-toolbar select:focus-visible,
.problem-link:focus-visible,
.sort-button:focus-visible,
.log-block > summary:focus-visible {{
    outline: 2px solid rgba(154, 52, 18, 0.35);
    outline-offset: 2px;
}}
.control-hint {{
    align-self: end;
    padding: 0 4px 4px 0;
    text-align: right;
}}
.desktop-only {{
    display: block;
}}
.mobile-only {{
    display: none;
}}
.result-meta {{
    display: flex;
    justify-content: space-between;
    gap: 12px;
    flex-wrap: wrap;
    margin-bottom: 12px;
}}
.table-wrap {{
    border: 1px solid var(--line);
    border-radius: 22px;
    overflow-x: auto;
    overflow-y: hidden;
    background: rgba(255, 253, 248, 0.9);
    box-shadow: 0 16px 40px rgba(76, 52, 24, 0.08);
}}
table {{
    width: 100%;
    min-width: 920px;
    border-collapse: collapse;
    table-layout: fixed;
}}
thead {{
    background: var(--panel-2);
}}
thead th {{
    position: sticky;
    top: var(--table-sticky-top);
    z-index: 12;
    background: var(--panel-2);
}}
th, td {{
    padding: 12px 14px;
    text-align: left;
    border-bottom: 1px solid var(--line);
    vertical-align: top;
}}
th {{
    vertical-align: middle;
}}
th.is-active {{
    color: var(--accent);
}}
.sort-button {{
    border: 0;
    background: transparent;
    font: inherit;
    color: inherit;
    padding: 0;
    cursor: pointer;
    display: inline-flex;
    align-items: center;
    justify-content: space-between;
    gap: 6px;
    font-weight: 600;
    width: 100%;
    min-height: 28px;
    line-height: 1.2;
}}
.sort-label {{
    min-width: 0;
}}
.sort-indicator {{
    width: 1.25em;
    flex: none;
    text-align: center;
    color: var(--accent);
}}
.num {{
    text-align: right;
    white-space: nowrap;
    font-variant-numeric: tabular-nums;
}}
.dashboard-table th.num .sort-button {{
    justify-content: flex-end;
    width: 100%;
}}
.metric-sub {{
    margin-top: 4px;
    font-size: 12px;
}}
tbody tr:hover {{
    background: rgba(154, 52, 18, 0.04);
}}
.dashboard-row {{
    transition: background-color 120ms ease, box-shadow 120ms ease;
}}
.dashboard-row.is-selected {{
    background: rgba(154, 52, 18, 0.1);
    box-shadow: inset 4px 0 0 var(--accent), inset 0 -1px 0 rgba(154, 52, 18, 0.18);
}}
.dashboard-row.is-selected:hover {{
    background: rgba(154, 52, 18, 0.12);
}}
.dashboard-row:focus-visible {{
    outline: 2px solid rgba(154, 52, 18, 0.35);
    outline-offset: -2px;
}}
.test-main {{
    display: grid;
    gap: 6px;
}}
.test-head {{
    display: flex;
    align-items: center;
    gap: 8px;
}}
.expander {{
    display: inline-flex;
    align-items: center;
    justify-content: center;
    width: 20px;
    height: 20px;
    border: 1px solid var(--line);
    border-radius: 999px;
    color: var(--accent);
    font-size: 11px;
    font-weight: 700;
    background: rgba(255, 253, 248, 0.82);
    flex: none;
    cursor: pointer;
}}
.expander.is-open {{
    background: var(--accent);
    border-color: var(--accent);
    color: #fff7ed;
}}
.expander:hover {{
    transform: translateY(-1px);
}}
.path {{
    font-family: "Iosevka Web", "SFMono-Regular", monospace;
    font-size: 13px;
    overflow-wrap: anywhere;
}}
.problem-link {{
    color: inherit;
    text-decoration: underline;
    text-decoration-color: rgba(154, 52, 18, 0.35);
    text-underline-offset: 0.15em;
}}
.problem-link:hover {{
    color: var(--accent);
}}
.muted {{
    color: var(--muted);
    overflow-wrap: anywhere;
}}
.status-badge {{
    display: inline-flex;
    align-items: center;
    border-radius: 999px;
    padding: 4px 10px;
    font-size: 12px;
    font-weight: 700;
    letter-spacing: 0.04em;
    background: rgba(104, 95, 84, 0.08);
}}
.status-ok {{ color: var(--ok); font-weight: 700; }}
.status-bad {{ color: var(--bad); font-weight: 700; }}
.status-warn {{ color: var(--warn); font-weight: 700; }}
.empty-state {{
    padding: 24px 18px;
    color: var(--muted);
}}
.detail-row > td {{
    padding: 0;
    border-bottom: 1px solid rgba(154, 52, 18, 0.18);
    background: rgba(255, 249, 240, 0.6);
}}
.detail-panel {{
    margin: 0;
    padding: 22px 20px 20px;
    background: rgba(255, 249, 240, 0.96);
    border-top: 0;
    box-shadow: inset 4px 0 0 rgba(154, 52, 18, 0.16);
}}
.detail-head {{
    display: grid;
    grid-template-columns: minmax(0, 1fr) auto;
    gap: 16px;
    align-items: start;
    margin-bottom: 16px;
}}
.detail-head-main {{
    display: grid;
    gap: 10px;
}}
.eyebrow {{
    color: var(--accent);
    font-size: 12px;
    font-weight: 700;
    letter-spacing: 0.08em;
    text-transform: uppercase;
}}
.detail-title {{
    margin: 6px 0 0;
    font-size: clamp(20px, 3vw, 30px);
    line-height: 1.1;
}}
.detail-head-side {{
    min-width: min(100%, 260px);
}}
.detail-problem-full {{
    margin-top: 6px;
    font-size: 12px;
}}
.detail-chips {{
    display: flex;
    gap: 10px;
    flex-wrap: wrap;
}}
.detail-tabs {{
    display: inline-flex;
    gap: 8px;
    flex-wrap: wrap;
    margin-bottom: 14px;
}}
.detail-toolbar {{
    display: flex;
    gap: 10px;
    flex-wrap: wrap;
    align-items: center;
    margin-bottom: 12px;
}}
.detail-toolbar select {{
    border: 1px solid var(--line);
    border-radius: 999px;
    background: var(--panel);
    color: var(--text);
    padding: 8px 12px;
    font: inherit;
}}
.detail-tab {{
    border: 1px solid var(--line);
    border-radius: 999px;
    background: var(--panel);
    color: var(--muted);
    padding: 9px 14px;
    font: inherit;
    cursor: pointer;
}}
.detail-tab.is-active {{
    background: var(--accent);
    border-color: var(--accent);
    color: #fff7ed;
}}
.detail-content {{
    border: 1px solid var(--line);
    border-radius: 18px;
    background: var(--panel-3);
    padding: 18px;
}}
.detail-block-title {{
    margin: 0 0 12px;
    font-size: 15px;
}}
.case-table {{
    width: 100%;
    border: 1px solid var(--line);
    border-radius: 14px;
    overflow: hidden;
    background: rgba(255, 253, 248, 0.88);
    table-layout: auto;
}}
.case-table th,
.case-table td {{
    padding: 8px 10px;
    font-size: 13px;
}}
.case-row.is-hot {{
    background: rgba(183, 121, 31, 0.08);
}}
.case-row.is-failed {{
    background: rgba(180, 35, 24, 0.08);
}}
.case-name {{
    display: grid;
    gap: 6px;
}}
.case-tags {{
    display: flex;
    flex-wrap: wrap;
    gap: 6px;
}}
.case-tag {{
    display: inline-flex;
    align-items: center;
    border-radius: 999px;
    padding: 2px 8px;
    font-size: 11px;
    font-weight: 700;
    letter-spacing: 0.04em;
    background: rgba(104, 95, 84, 0.1);
    color: var(--muted);
}}
.case-tag.is-hot {{
    background: rgba(183, 121, 31, 0.15);
    color: var(--warn);
}}
.case-tag.is-failed {{
    background: rgba(180, 35, 24, 0.14);
    color: var(--bad);
}}
.log-block {{
    border: 1px solid var(--line);
    border-radius: 16px;
    background: rgba(255, 253, 248, 0.72);
    padding: 12px 14px;
}}
.log-block + .log-block {{
    margin-top: 12px;
}}
.log-block > summary {{
    cursor: pointer;
    font-weight: 700;
    color: var(--accent);
}}
pre {{
    white-space: pre-wrap;
    word-break: break-word;
    background: #201d18;
    color: #f8f3ea;
    padding: 12px 14px;
    border-radius: 14px;
    overflow: auto;
}}
.dashboard-table > thead > tr > th:nth-child(1),
.dashboard-table > tbody > tr > td:nth-child(1) {{
    width: 34%;
}}
.dashboard-table > thead > tr > th:nth-child(2),
.dashboard-table > tbody > tr > td:nth-child(2) {{
    width: 10%;
}}
.dashboard-table > thead > tr > th:nth-child(3),
.dashboard-table > tbody > tr > td:nth-child(3),
.dashboard-table > thead > tr > th:nth-child(4),
.dashboard-table > tbody > tr > td:nth-child(4),
.dashboard-table > thead > tr > th:nth-child(5),
.dashboard-table > tbody > tr > td:nth-child(5),
.dashboard-table > thead > tr > th:nth-child(6),
.dashboard-table > tbody > tr > td:nth-child(6) {{
    width: 12%;
}}
@media (max-width: 860px) {{
    main {{
        padding-inline: 14px;
    }}
    .controls {{
        grid-template-columns: 1fr;
        top: 10px;
        padding: 10px;
    }}
    .desktop-only {{
        display: none;
    }}
    .mobile-only {{
        display: block;
    }}
    .control-cluster {{
        grid-template-columns: 1fr;
    }}
    .result-meta {{
        flex-direction: column;
    }}
    .table-wrap {{
        overflow: visible;
        border: 0;
        border-radius: 0;
        background: transparent;
        box-shadow: none;
    }}
    .dashboard-table {{
        min-width: 0;
        display: block;
    }}
    .dashboard-table thead {{
        display: none;
    }}
    .dashboard-table tbody {{
        display: block;
    }}
    .dashboard-table tr {{
        display: block;
    }}
    .dashboard-table td {{
        display: block;
        width: 100%;
    }}
    .dashboard-row {{
        margin-bottom: 12px;
        border: 1px solid var(--line);
        border-radius: 22px;
        background: rgba(255, 253, 248, 0.92);
        box-shadow: 0 12px 28px rgba(76, 52, 24, 0.08);
    }}
    .dashboard-row td {{
        display: grid;
        grid-template-columns: 88px minmax(0, 1fr);
        gap: 12px;
        align-items: start;
        padding: 8px 14px;
        border-bottom: 1px solid rgba(216, 204, 184, 0.7);
        text-align: left;
        white-space: normal;
    }}
    .dashboard-row td::before {{
        content: attr(data-label);
        color: var(--muted);
        font-size: 11px;
        font-weight: 700;
        letter-spacing: 0.08em;
        text-transform: uppercase;
    }}
    .dashboard-row td:first-child {{
        display: block;
        padding-top: 14px;
        padding-bottom: 12px;
    }}
    .dashboard-row td:first-child::before {{
        content: none;
    }}
    .dashboard-row td:last-child {{
        border-bottom: 0;
        padding-bottom: 14px;
    }}
    .dashboard-row .metric-sub {{
        text-align: left;
    }}
    .detail-row {{
        margin: -6px 0 14px;
    }}
    .detail-row > td {{
        display: block;
        padding: 0;
        border-bottom: 0;
    }}
    .detail-head {{
        grid-template-columns: 1fr;
    }}
    .detail-panel {{
        padding: 18px 14px 16px;
    }}
}}
</style>
</head>
<body>
<main>
    <h1>Verify Measurement Dashboard</h1>
    <p class="lede">`oj test` を再実行しながら JSON を逐次更新し、テストごとの最遅ケースとケース別実行時間を一覧する。</p>
    <div class="meta">
        <button class="chip chip-action" id="summary-live" type="button"></button>
        <div class="chip" id="summary-generated">generated: {generated_at}</div>
        <div class="chip" id="summary-total"></div>
        <div class="chip" id="summary-progress"></div>
        <button class="chip chip-action" id="summary-failed" type="button"></button>
        <div class="chip" id="summary-visible"></div>
    </div>
    <div class="controls" id="controls">
        <label class="control-field" for="filter">
            <span class="control-label">filter</span>
            <input id="filter" type="search" placeholder="test path / url で絞り込み">
        </label>
        <label class="control-field" for="status-filter">
            <span class="control-label">status</span>
            <select id="status-filter">
                <option value="all">all</option>
                <option value="ok">ok only</option>
                <option value="failed">failed only</option>
            </select>
        </label>
        <div class="control-field mobile-only">
            <span class="control-label">sort</span>
            <div class="control-cluster">
                <select id="sort-key">
                    <option value="slowestSec">slowest</option>
                    <option value="averageSec">average</option>
                    <option value="compileWallSec">compile</option>
                    <option value="path">path</option>
                    <option value="status">status</option>
                    <option value="maxMemoryMb">memory</option>
                </select>
                <select id="sort-direction">
                    <option value="desc">desc</option>
                    <option value="asc">asc</option>
                </select>
            </div>
        </div>
        <div class="control-hint muted desktop-only">header click で sort / expander で detail 開閉</div>
    </div>
    <div class="result-meta">
        <div class="muted" id="result-count"></div>
        <div class="muted desktop-only" id="sort-summary"></div>
    </div>
    <div class="table-wrap">
        <table class="dashboard-table">
            <thead>
                <tr>
                    <th><button class="sort-button" type="button" data-sort="path" data-label="test"><span class="sort-label">test</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                    <th><button class="sort-button" type="button" data-sort="status" data-label="status"><span class="sort-label">status</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                    <th class="num"><button class="sort-button" type="button" data-sort="compileWallSec" data-label="compile"><span class="sort-label">compile</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                    <th class="num"><button class="sort-button" type="button" data-sort="slowestSec" data-label="slowest"><span class="sort-label">slowest</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                    <th class="num"><button class="sort-button" type="button" data-sort="averageSec" data-label="average"><span class="sort-label">average</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                    <th class="num"><button class="sort-button" type="button" data-sort="maxMemoryMb" data-label="memory"><span class="sort-label">memory</span><span class="sort-indicator" aria-hidden="true"></span></button></th>
                </tr>
            </thead>
            <tbody id="rows"></tbody>
        </table>
    </div>
</main>
<script>
const jsonUrl = {json.dumps(json_filename)};
let report = {bootstrap_json};
const rows = document.getElementById("rows");
const controls = document.getElementById("controls");
const filterInput = document.getElementById("filter");
const statusFilter = document.getElementById("status-filter");
const sortKey = document.getElementById("sort-key");
const sortDirection = document.getElementById("sort-direction");
const summaryLive = document.getElementById("summary-live");
const summaryGenerated = document.getElementById("summary-generated");
const summaryTotal = document.getElementById("summary-total");
const summaryProgress = document.getElementById("summary-progress");
const summaryFailed = document.getElementById("summary-failed");
const summaryVisible = document.getElementById("summary-visible");
const resultCount = document.getElementById("result-count");
const sortSummary = document.getElementById("sort-summary");
let currentSort = "slowestSec";
let currentSortDirection = "desc";
let selectedPath = null;
let currentDetailTab = "case";
let currentCaseFilter = "all";
let currentCaseSort = "timeDesc";
let pendingReport = null;
function fmtSec(value) {{
    return value == null ? "-" : `${{value.toFixed(6)}} s`;
}}

function fmtSecCompact(value) {{
    if (value == null) return "-";
    if (value < 1) {{
        const ms = value * 1000;
        const digits = ms >= 100 ? 0 : ms >= 10 ? 1 : 2;
        return `${{ms.toFixed(digits)}} ms`;
    }}
    const digits = value >= 100 ? 0 : value >= 10 ? 2 : 3;
    return `${{value.toFixed(digits)}} s`;
}}

function fmtMb(value) {{
    return value == null ? "-" : `${{value.toFixed(3)}} MB`;
}}

function fmtMbCompact(value) {{
    if (value == null) return "-";
    if (value >= 1024) return `${{(value / 1024).toFixed(2)}} GB`;
    if (value >= 100) return `${{value.toFixed(0)}} MB`;
    if (value >= 10) return `${{value.toFixed(1)}} MB`;
    return `${{value.toFixed(2)}} MB`;
}}

function esc(value) {{
    return String(value)
        .replaceAll("&", "&amp;")
        .replaceAll("<", "&lt;")
        .replaceAll(">", "&gt;")
        .replaceAll('"', "&quot;");
}}

function compactProblemLabel(problem) {{
    try {{
        const url = new URL(problem);
        const segments = url.pathname.split("/").filter(Boolean);
        const tail = segments.slice(-2).join(" / ");
        return tail ? `${{url.hostname}} / ${{tail}}` : url.hostname;
    }} catch (_error) {{
        return problem;
    }}
}}

function renderProblem(problem, {{ compact = true, muted = true }} = {{}}) {{
    if (!problem) return `<span class="muted">problem url is unavailable</span>`;
    const url = esc(problem);
    const label = esc(compact ? compactProblemLabel(problem) : problem);
    const className = muted ? "problem-link muted" : "problem-link";
    return `<a class="${{className}}" href="${{url}}" title="${{url}}" target="_blank" rel="noreferrer noopener">${{label}}</a>`;
}}

function statusClass(entry) {{
    if (entry.phase === "running" || entry.phase === "pending") return "status-warn";
    if (entry.phase === "error") return "status-bad";
    if (entry.run.ok) return "status-ok";
    if (entry.run.parsed.caseCount > 0) return "status-bad";
    return "status-bad";
}}

function statusLabel(entry) {{
    if (entry.phase === "pending") return "PENDING";
    if (entry.phase === "running") return "RUNNING";
    if (entry.phase === "error") return "ERROR";
    if (entry.run.ok) return "OK";
    if (entry.run.parsed.caseCount > 0) return "FAILED";
    return "ERROR";
}}

function isFailedEntry(entry) {{
    return entry.phase === "error" || (entry.phase === "done" && !entry.run.ok);
}}

function normalized(entry, key) {{
    if (key === "path") return entry.path;
    if (key === "status") return statusLabel(entry);
    if (key === "compileWallSec") return entry.compiler.wallSec ?? -1;
    if (key === "slowestSec") return entry.run.parsed.slowestSec ?? -1;
    if (key === "averageSec") return entry.run.parsed.averageSec ?? -1;
    if (key === "maxMemoryMb") return entry.run.parsed.maxMemoryMb ?? -1;
    return -1;
}}

function defaultSortDirection(key) {{
    return key === "path" || key === "status" ? "asc" : "desc";
}}

function sortLabel(key) {{
    if (key === "path") return "path";
    if (key === "status") return "status";
    if (key === "compileWallSec") return "compile";
    if (key === "averageSec") return "average";
    if (key === "maxMemoryMb") return "memory";
    return "slowest";
}}

function applyChipState(element, ...states) {{
    element.className = ["chip", ...states.filter(Boolean)].join(" ");
}}

function syncStickyOffset() {{
    if (!controls) return;
    const top = Number.parseFloat(window.getComputedStyle(controls).top) || 0;
    const gap = 14;
    document.documentElement.style.setProperty("--controls-top", `${{top}}px`);
    document.documentElement.style.setProperty("--table-sticky-top", `${{Math.round(top + controls.offsetHeight + gap)}}px`);
}}

function syncSortUi() {{
    if (sortKey) sortKey.value = currentSort;
    if (sortDirection) sortDirection.value = currentSortDirection;
    document.querySelectorAll("[data-sort]").forEach((button) => {{
        const active = button.dataset.sort === currentSort;
        const indicator = button.querySelector(".sort-indicator");
        const header = button.closest("th");
        if (header) {{
            header.classList.toggle("is-active", active);
            header.setAttribute("aria-sort", active ? (currentSortDirection === "asc" ? "ascending" : "descending") : "none");
        }}
        button.setAttribute("aria-pressed", active ? "true" : "false");
        button.title = active
            ? `${{button.dataset.label}} (${{
                currentSortDirection === "asc" ? "ascending" : "descending"
            }})`
            : `sort by ${{button.dataset.label}}`;
        if (indicator) indicator.textContent = active ? (currentSortDirection === "asc" ? "↑" : "↓") : "";
    }});
    if (sortSummary) {{
        sortSummary.textContent = `sort: ${{sortLabel(currentSort)}} / ${{currentSortDirection}}`;
    }}
}}

function buildCaseTable(entry) {{
    const cases = entry.run.parsed.cases.map((testcase) => {{
        const isSlowest = testcase.name === entry.run.parsed.slowestCase;
        const isMaxMemory = testcase.name === entry.run.parsed.maxMemoryCase;
        const isFailed = testcase.status != null && testcase.status !== "AC";
        return {{
            ...testcase,
            isSlowest,
            isMaxMemory,
            isFailed,
            isHot: isSlowest || isMaxMemory || isFailed,
        }};
    }});
    if (!cases.length) return "<div class=\\"muted\\">case detail is unavailable</div>";
    const filteredCases = cases
        .filter((testcase) => {{
            if (currentCaseFilter === "failed") return testcase.isFailed;
            if (currentCaseFilter === "hot") return testcase.isHot;
            return true;
        }})
        .sort((lhs, rhs) => {{
            if (currentCaseSort === "timeAsc") return (lhs.timeSec ?? Number.POSITIVE_INFINITY) - (rhs.timeSec ?? Number.POSITIVE_INFINITY);
            if (currentCaseSort === "nameAsc") return lhs.name.localeCompare(rhs.name);
            return (rhs.timeSec ?? -1) - (lhs.timeSec ?? -1);
        }});
    return `
        <h3 class="detail-block-title">case detail</h3>
        <div class="detail-toolbar">
            <select data-case-filter>
                <option value="all"${{currentCaseFilter === "all" ? " selected" : ""}}>cases: all</option>
                <option value="hot"${{currentCaseFilter === "hot" ? " selected" : ""}}>cases: hot only</option>
                <option value="failed"${{currentCaseFilter === "failed" ? " selected" : ""}}>cases: failed only</option>
            </select>
            <select data-case-sort>
                <option value="timeDesc"${{currentCaseSort === "timeDesc" ? " selected" : ""}}>sort: time desc</option>
                <option value="timeAsc"${{currentCaseSort === "timeAsc" ? " selected" : ""}}>sort: time asc</option>
                <option value="nameAsc"${{currentCaseSort === "nameAsc" ? " selected" : ""}}>sort: case name</option>
            </select>
            <div class="muted">showing ${{filteredCases.length}} / ${{cases.length}} cases</div>
        </div>
        <table class="case-table">
            <thead>
                <tr><th>case</th><th class="num">time</th><th>status</th></tr>
            </thead>
            <tbody>
                ${{filteredCases.length ? filteredCases.map((testcase) => `
                    <tr class="case-row${{testcase.isHot ? " is-hot" : ""}}${{testcase.isFailed ? " is-failed" : ""}}">
                        <td>
                            <div class="case-name">
                                <div class="path">${{esc(testcase.name)}}</div>
                                <div class="case-tags">
                                    ${{testcase.isSlowest ? '<span class="case-tag is-hot">slowest</span>' : ""}}
                                    ${{testcase.isMaxMemory ? '<span class="case-tag is-hot">max memory</span>' : ""}}
                                    ${{testcase.isFailed ? '<span class="case-tag is-failed">failed</span>' : ""}}
                                </div>
                            </div>
                        </td>
                        <td class="num" title="${{fmtSec(testcase.timeSec ?? null)}}">${{fmtSecCompact(testcase.timeSec ?? null)}}</td>
                        <td>${{esc(testcase.status ?? "-")}}</td>
                    </tr>
                `).join("") : '<tr><td colspan="3"><div class="empty-state">current case filter に一致する case はない</div></td></tr>'}}
            </tbody>
        </table>
    `;
}}

function buildRawLog(entry) {{
    if (!entry.run.output) return "<div class=\\"muted\\">raw log is unavailable</div>";
    const lines = entry.run.output.split("\\n");
    const failureIndex = lines.findIndex((line) => line.startsWith("[FAILURE]") || line.startsWith("[ERROR]"));
    const excerpt = failureIndex >= 0
        ? lines.slice(Math.max(0, failureIndex - 2), Math.min(lines.length, failureIndex + 12)).join("\\n").trim()
        : "";
    const summary = entry.run.parsed.summary ?? (entry.run.ok ? "test success" : statusLabel(entry));
    return `
        <h3 class="detail-block-title">raw log</h3>
        <div class="detail-toolbar">
            <div class="chip ${{statusClass(entry)}}">summary: ${{esc(summary ?? "-")}}</div>
            <div class="muted">${{failureIndex >= 0 ? "first failure excerpt を先に表示する" : "full log のみ利用できる"}}</div>
        </div>
        ${{excerpt ? `
            <details class="log-block" open>
                <summary>first failure excerpt</summary>
                <pre>${{esc(excerpt)}}</pre>
            </details>
        ` : ""}}
        <details class="log-block"${{excerpt ? "" : " open"}}>
            <summary>full log</summary>
            <pre>${{esc(entry.run.output)}}</pre>
        </details>
    `;
}}

function findEntry(path) {{
    return report.tests.find((entry) => entry.path === path) ?? null;
}}

function ensureSelection(filtered) {{
    if (!filtered.length || selectedPath == null) return null;
    if (filtered.some((entry) => entry.path === selectedPath)) return findEntry(selectedPath);
    selectedPath = null;
    return null;
}}

function bindSelection() {{
    rows.querySelectorAll("[data-expand-path]").forEach((button) => {{
        const select = () => {{
            selectedPath = selectedPath === button.dataset.expandPath ? null : button.dataset.expandPath;
            render();
        }};
        button.addEventListener("click", select);
    }});
}}

function buildDetailPanel(entry) {{
    const chips = [
        `<div class="chip ${{statusClass(entry)}}">status: ${{statusLabel(entry)}}</div>`,
        `<div class="chip">compile: ${{fmtSecCompact(entry.compiler.wallSec)}}</div>`,
        `<div class="chip">slowest: ${{fmtSecCompact(entry.run.parsed.slowestSec)}}</div>`,
        `<div class="chip">average: ${{fmtSecCompact(entry.run.parsed.averageSec)}}</div>`,
        `<div class="chip">memory: ${{fmtMbCompact(entry.run.parsed.maxMemoryMb)}}</div>`,
        `<div class="chip">cases: ${{entry.run.parsed.caseCount}} / cached ${{entry.testcases.cachedCaseCount}}</div>`,
    ].join("");
    const content = currentDetailTab === "raw" ? buildRawLog(entry) : buildCaseTable(entry);
    return `
        <div class="detail-panel">
            <div class="detail-head">
                <div class="detail-head-main">
                    <div>
                        <div class="eyebrow">expanded test</div>
                        <h2 class="detail-title">${{esc(entry.path)}}</h2>
                        <div>${{renderProblem(entry.problem, {{ compact: true, muted: false }})}}</div>
                        <div class="detail-problem-full muted">${{renderProblem(entry.problem, {{ compact: false }})}}</div>
                    </div>
                </div>
                <div class="detail-head-side">
                    <div class="detail-chips">${{chips}}</div>
                </div>
            </div>
            <div class="detail-tabs">
                <button class="detail-tab${{currentDetailTab === "case" ? " is-active" : ""}}" type="button" data-detail-tab="case">case detail</button>
                <button class="detail-tab${{currentDetailTab === "raw" ? " is-active" : ""}}" type="button" data-detail-tab="raw">raw log</button>
            </div>
            <div class="detail-content">${{content}}</div>
        </div>
    `;
}}

function bindDetailTabs() {{
    rows.querySelectorAll("[data-detail-tab]").forEach((button) => {{
        button.addEventListener("click", (event) => {{
            event.stopPropagation();
            currentDetailTab = button.dataset.detailTab;
            render();
        }});
    }});
    rows.querySelectorAll("[data-case-filter]").forEach((select) => {{
        select.addEventListener("change", () => {{
            currentCaseFilter = select.value;
            render();
        }});
    }});
    rows.querySelectorAll("[data-case-sort]").forEach((select) => {{
        select.addEventListener("change", () => {{
            currentCaseSort = select.value;
            render();
        }});
    }});
}}

function updateLiveChip() {{
    const meta = pendingReport != null ? "update pending" : "auto";
    summaryLive.innerHTML = `<span class="live-dot" aria-hidden="true"></span><span class="chip-label">live</span><span class="chip-meta">${{meta}}</span>`;
    applyChipState(summaryLive, "chip-action", pendingReport != null ? "is-active" : "is-ok");
    summaryLive.disabled = false;
    summaryLive.title = pendingReport != null
        ? "apply pending update now"
        : (refreshLock ? "refresh in progress" : "refresh now");
}}

function render() {{
    if (selectedPath == null && pendingReport != null) {{
        report = pendingReport;
        pendingReport = null;
    }}
    const query = filterInput.value.trim().toLowerCase();
    const totalTests = report.testCount ?? report.tests.length;
    const filtered = report.tests
        .filter((entry) => {{
            const haystack = `${{entry.path}} ${{entry.problem}}`.toLowerCase();
            if (query && !haystack.includes(query)) return false;
            if (statusFilter.value === "ok" && !entry.run.ok) return false;
            if (statusFilter.value === "failed" && !isFailedEntry(entry)) return false;
            return true;
        }})
        .sort((lhs, rhs) => {{
            const a = normalized(lhs, currentSort);
            const b = normalized(rhs, currentSort);
            const direction = currentSortDirection === "asc" ? 1 : -1;
            if (typeof a === "string" || typeof b === "string") {{
                return direction * String(a).localeCompare(String(b));
            }}
            return direction * (a - b);
        }});
    ensureSelection(filtered);
    syncSortUi();
    syncStickyOffset();

    if (!filtered.length) {{
        const emptyMessage = report.tests.length === 0 && totalTests > 0
            ? "loading dashboard data..."
            : "current filter に一致する test はない";
        rows.innerHTML = `<tr><td colspan="6"><div class="empty-state">${{emptyMessage}}</div></td></tr>`;
    }} else {{
        rows.innerHTML = filtered.map((entry) => {{
            const slowest = entry.run.parsed.slowestSec;
            const isSelected = selectedPath === entry.path;
            const detailRow = isSelected
                ? `
                <tr class="detail-row">
                    <td colspan="6">${{buildDetailPanel(entry)}}</td>
                </tr>
                `
                : "";
            return `
                <tr class="dashboard-row${{isSelected ? " is-selected" : ""}}" data-entry-path="${{esc(entry.path)}}" aria-selected="${{isSelected ? "true" : "false"}}">
                    <td>
                        <div class="test-main">
                            <div class="test-head">
                                <button class="expander${{isSelected ? " is-open" : ""}}" type="button" data-expand-path="${{esc(entry.path)}}" aria-expanded="${{isSelected ? "true" : "false"}}">${{isSelected ? "−" : "+"}}</button>
                                <div class="path">${{esc(entry.path)}}</div>
                            </div>
                            <div>${{renderProblem(entry.problem)}}</div>
                        </div>
                    </td>
                    <td data-label="status"><span class="status-badge ${{statusClass(entry)}}">${{statusLabel(entry)}}</span></td>
                    <td class="num" data-label="compile" title="${{fmtSec(entry.compiler.wallSec)}}">${{fmtSecCompact(entry.compiler.wallSec)}}</td>
                    <td class="num" data-label="slowest" title="${{fmtSec(slowest)}}">
                        <div>${{fmtSecCompact(slowest)}}</div>
                        <div class="muted metric-sub">${{esc(entry.run.parsed.slowestCase ?? "-")}}</div>
                    </td>
                    <td class="num" data-label="average" title="${{fmtSec(entry.run.parsed.averageSec)}}">${{fmtSecCompact(entry.run.parsed.averageSec)}}</td>
                    <td class="num" data-label="memory" title="${{fmtMb(entry.run.parsed.maxMemoryMb)}}">${{fmtMbCompact(entry.run.parsed.maxMemoryMb)}}</td>
                </tr>
                ${{detailRow}}
            `;
        }}).join("");
    }}

    const summary = report.summary ?? {{}};
    const pending = summary.pending ?? 0;
    const running = summary.running ?? 0;
    const done = summary.done ?? 0;
    const failed = summary.failed ?? report.tests.filter((entry) => isFailedEntry(entry)).length;
    summaryGenerated.textContent = `generated: ${{report.generatedAt}}`;
    summaryTotal.textContent = `tests: ${{totalTests}}`;
    summaryProgress.textContent = `done: ${{done}} / running: ${{running}} / pending: ${{pending}}`;
    summaryFailed.textContent = statusFilter.value === "failed" ? `failed: ${{failed}} (filtered)` : `failed: ${{failed}}`;
    summaryVisible.textContent = `visible: ${{filtered.length}}`;
    updateLiveChip();
    applyChipState(summaryTotal);
    applyChipState(summaryProgress, running > 0 || pending > 0 ? "is-warn" : "is-ok");
    applyChipState(summaryFailed, "chip-action", failed > 0 ? "is-bad" : "is-ok", statusFilter.value === "failed" ? "is-active" : "");
    applyChipState(summaryVisible, query || statusFilter.value !== "all" ? "is-active" : "");
    summaryFailed.disabled = failed === 0 && statusFilter.value !== "failed";
    summaryFailed.title = statusFilter.value === "failed" ? "clear failed filter" : "show failed tests only";
    resultCount.textContent = filtered.length
        ? `displaying ${{filtered.length}} / ${{totalTests}} tests`
        : (report.tests.length === 0 && totalTests > 0 ? `loading 0 / ${{totalTests}} tests` : "displaying 0 tests");
    bindSelection();
    bindDetailTabs();
}}

let refreshLock = false;
async function refreshReport() {{
    if (refreshLock) return;
    refreshLock = true;
    updateLiveChip();
    try {{
        const response = await fetch(`${{jsonUrl}}?t=${{Date.now()}}`, {{ cache: "no-store" }});
        if (!response.ok) return;
        const nextReport = await response.json();
        if (selectedPath != null) {{
            pendingReport = nextReport;
            updateLiveChip();
        }} else {{
            report = nextReport;
            pendingReport = null;
            render();
        }}
    }} catch (_error) {{
    }} finally {{
        refreshLock = false;
        if (selectedPath != null || pendingReport != null) {{
            updateLiveChip();
        }} else if (!document.hidden) {{
            updateLiveChip();
        }}
    }}
}}

document.querySelectorAll("[data-sort]").forEach((button) => {{
    button.addEventListener("click", () => {{
        if (currentSort === button.dataset.sort) {{
            currentSortDirection = currentSortDirection === "asc" ? "desc" : "asc";
        }} else {{
            currentSort = button.dataset.sort;
            currentSortDirection = defaultSortDirection(currentSort);
        }}
        render();
    }});
}});
filterInput.addEventListener("input", render);
statusFilter.addEventListener("change", render);
summaryFailed.addEventListener("click", () => {{
    statusFilter.value = statusFilter.value === "failed" ? "all" : "failed";
    render();
}});
summaryLive.addEventListener("click", () => {{
    if (pendingReport != null) {{
        report = pendingReport;
        pendingReport = null;
        render();
        return;
    }}
    refreshReport();
}});
sortKey.addEventListener("change", () => {{
    currentSort = sortKey.value;
    render();
}});
sortDirection.addEventListener("change", () => {{
    currentSortDirection = sortDirection.value;
    render();
}});
window.addEventListener("resize", syncStickyOffset);
render();
refreshReport();
setInterval(refreshReport, 2000);
</script>
</body>
</html>
"""


def main() -> int:
    args = parse_args()
    if args.render_only:
        if not args.json_path.exists():
            raise FileNotFoundError(f"json report not found: {args.json_path}")
        report = json.loads(args.json_path.read_text())
        write_report(report, json_path=args.json_path, html_path=args.html_path)
        print(f"json: {args.json_path.relative_to(ROOT)}")
        print(f"html: {args.html_path.relative_to(ROOT)}")
        return 0

    tests = list_test_paths(args.paths)
    report_tests = [make_empty_entry(path) for path in tests]
    write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)

    if args.jobs <= 0:
        raise ValueError("--jobs must be positive")
    if args.oj_jobs <= 0:
        raise ValueError("--oj-jobs must be positive")
    if args.compile_jobs <= 0:
        raise ValueError("--compile-jobs must be positive")
    if not tests:
        print(f"json: {args.json_path.relative_to(ROOT)}")
        print(f"html: {args.html_path.relative_to(ROOT)}")
        return 0

    worker_count = min(args.jobs, len(tests))
    compile_worker_count = min(args.compile_jobs, worker_count)
    compile_slots = threading.Semaphore(compile_worker_count)
    next_index = 0
    futures: dict[concurrent.futures.Future[dict[str, Any]], int] = {}

    def submit_one(executor: concurrent.futures.Executor, index: int) -> None:
        report_tests[index]["phase"] = "running"
        future = executor.submit(
            run_one_test,
            tests[index],
            tle=args.tle,
            oj_jobs=args.oj_jobs,
            compile_slots=compile_slots,
        )
        futures[future] = index

    try:
        with concurrent.futures.ThreadPoolExecutor(max_workers=worker_count) as executor:
            print(
                f"parallel tests={worker_count}, compile slots={compile_worker_count}, oj jobs/test={args.oj_jobs}",
                flush=True,
            )
            while next_index < len(tests) and len(futures) < worker_count:
                submit_one(executor, next_index)
                next_index += 1
            write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)

            while futures:
                done, _ = concurrent.futures.wait(
                    futures,
                    return_when=concurrent.futures.FIRST_COMPLETED,
                )
                for future in done:
                    index = futures.pop(future)
                    path = tests[index]
                    try:
                        entry = future.result()
                        report_tests[index] = entry
                        status = "ok" if entry["run"]["ok"] else "failed"
                        slowest = entry["run"]["parsed"]["slowestSec"]
                        print(f"{entry['path']}: {status}, slowest={slowest}")
                    except Exception as exc:
                        if not args.keep_going:
                            for pending in futures:
                                pending.cancel()
                            raise
                        relative_path = path.resolve().relative_to(ROOT)
                        entry = make_empty_entry(path)
                        entry["phase"] = "error"
                        entry["run"]["output"] = str(exc)
                        print(f"{relative_path}: error: {exc}", file=sys.stderr)
                        report_tests[index] = entry

                while next_index < len(tests) and len(futures) < worker_count:
                    submit_one(executor, next_index)
                    next_index += 1
                write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)
    except Exception:
        write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)
        raise

    print(f"json: {args.json_path.relative_to(ROOT)}")
    print(f"html: {args.html_path.relative_to(ROOT)}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
