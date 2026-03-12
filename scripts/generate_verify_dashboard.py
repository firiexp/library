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
    bootstrap_json = json.dumps(report, ensure_ascii=False)
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
}}
.controls {{
    display: grid;
    grid-template-columns: minmax(240px, 1fr) auto auto;
    gap: 12px;
    margin-bottom: 18px;
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
th, td {{
    padding: 12px 14px;
    text-align: left;
    border-bottom: 1px solid var(--line);
    vertical-align: top;
}}
th button {{
    border: 0;
    background: transparent;
    font: inherit;
    color: inherit;
    padding: 0;
    cursor: pointer;
}}
tbody tr:hover {{
    background: rgba(154, 52, 18, 0.04);
}}
.dashboard-row {{
    cursor: pointer;
    transition: background-color 120ms ease, box-shadow 120ms ease;
}}
.dashboard-row.is-selected {{
    background: rgba(154, 52, 18, 0.1);
    box-shadow: inset 4px 0 0 var(--accent);
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
}}
.expander.is-open {{
    background: var(--accent);
    border-color: var(--accent);
    color: #fff7ed;
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
.status-ok {{ color: var(--ok); font-weight: 700; }}
.status-bad {{ color: var(--bad); font-weight: 700; }}
.status-warn {{ color: var(--warn); font-weight: 700; }}
.empty-state {{
    padding: 24px 18px;
    color: var(--muted);
}}
.detail-row > td {{
    padding: 0;
    border-bottom: 1px solid var(--line);
}}
.detail-panel {{
    margin: 0;
    padding: 22px 20px 20px;
    background: rgba(255, 249, 240, 0.96);
}}
.detail-head {{
    display: grid;
    grid-template-columns: minmax(0, 1fr) auto;
    gap: 16px;
    align-items: start;
    margin-bottom: 16px;
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
    }}
    .result-meta {{
        flex-direction: column;
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
        <div class="chip" id="summary-generated">generated: {generated_at}</div>
        <div class="chip" id="summary-total"></div>
        <div class="chip" id="summary-progress"></div>
        <div class="chip" id="summary-failed"></div>
        <div class="chip" id="summary-visible"></div>
    </div>
    <div class="controls">
        <input id="filter" type="search" placeholder="test path / url で絞り込み">
        <select id="status-filter">
            <option value="all">all</option>
            <option value="ok">ok only</option>
            <option value="failed">failed only</option>
        </select>
        <select id="sort-key">
            <option value="slowestSec">sort: slowest</option>
            <option value="averageSec">sort: average</option>
            <option value="compileWallSec">sort: compile</option>
            <option value="path">sort: path</option>
        </select>
    </div>
    <div class="result-meta">
        <div class="muted" id="result-count"></div>
        <div class="muted">test row をクリックすると detail を展開する</div>
    </div>
    <div class="table-wrap">
        <table class="dashboard-table">
            <thead>
                <tr>
                    <th><button data-sort="path">test</button></th>
                    <th><button data-sort="status">status</button></th>
                    <th><button data-sort="compileWallSec">compile</button></th>
                    <th><button data-sort="slowestSec">slowest</button></th>
                    <th><button data-sort="averageSec">average</button></th>
                    <th><button data-sort="maxMemoryMb">memory</button></th>
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
const filterInput = document.getElementById("filter");
const statusFilter = document.getElementById("status-filter");
const sortKey = document.getElementById("sort-key");
const summaryGenerated = document.getElementById("summary-generated");
const summaryTotal = document.getElementById("summary-total");
const summaryProgress = document.getElementById("summary-progress");
const summaryFailed = document.getElementById("summary-failed");
const summaryVisible = document.getElementById("summary-visible");
const resultCount = document.getElementById("result-count");
let currentSort = "slowestSec";
let selectedPath = null;
let currentDetailTab = "case";

function fmtSec(value) {{
    return value == null ? "-" : `${{value.toFixed(6)}} s`;
}}

function fmtMb(value) {{
    return value == null ? "-" : `${{value.toFixed(3)}} MB`;
}}

function esc(value) {{
    return String(value)
        .replaceAll("&", "&amp;")
        .replaceAll("<", "&lt;")
        .replaceAll(">", "&gt;")
        .replaceAll('"', "&quot;");
}}

function renderProblem(problem) {{
    if (!problem) return `<span class="muted">problem url is unavailable</span>`;
    const url = esc(problem);
    return `<a class="problem-link muted" href="${{url}}" target="_blank" rel="noreferrer noopener">${{url}}</a>`;
}}

function statusClass(entry) {{
    if (entry.phase === "running" || entry.phase === "pending") return "status-warn";
    if (entry.phase === "error") return "status-bad";
    if (entry.run.ok) return "status-ok";
    if (entry.run.parsed.caseCount > 0) return "status-warn";
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

function normalized(entry, key) {{
    if (key === "path") return entry.path;
    if (key === "status") return statusLabel(entry);
    if (key === "compileWallSec") return entry.compiler.wallSec ?? -1;
    if (key === "slowestSec") return entry.run.parsed.slowestSec ?? -1;
    if (key === "averageSec") return entry.run.parsed.averageSec ?? -1;
    if (key === "maxMemoryMb") return entry.run.parsed.maxMemoryMb ?? -1;
    return -1;
}}

function buildCaseTable(entry) {{
    const cases = entry.run.parsed.cases;
    if (!cases.length) return "<div class=\\"muted\\">case detail is unavailable</div>";
    return `
        <h3 class="detail-block-title">case detail</h3>
        <table class="case-table">
            <thead>
                <tr><th>case</th><th>time</th><th>status</th></tr>
            </thead>
            <tbody>
                ${{cases.map((testcase) => `
                    <tr>
                        <td class="path">${{esc(testcase.name)}}</td>
                        <td>${{fmtSec(testcase.timeSec ?? null)}}</td>
                        <td>${{esc(testcase.status ?? "-")}}</td>
                    </tr>
                `).join("")}}
            </tbody>
        </table>
    `;
}}

function buildRawLog(entry) {{
    if (!entry.run.output) return "<div class=\\"muted\\">raw log is unavailable</div>";
    return `
        <h3 class="detail-block-title">raw log</h3>
        <pre>${{esc(entry.run.output)}}</pre>
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
    rows.querySelectorAll("tr[data-entry-path]").forEach((row) => {{
        const select = () => {{
            selectedPath = selectedPath === row.dataset.entryPath ? null : row.dataset.entryPath;
            render();
        }};
        row.addEventListener("click", select);
        row.addEventListener("keydown", (event) => {{
            if (event.key === "Enter" || event.key === " ") {{
                event.preventDefault();
                select();
            }}
        }});
    }});
}}

function buildDetailPanel(entry) {{
    const chips = [
        `<div class="chip ${{statusClass(entry)}}">status: ${{statusLabel(entry)}}</div>`,
        `<div class="chip">compile: ${{fmtSec(entry.compiler.wallSec)}}</div>`,
        `<div class="chip">slowest: ${{fmtSec(entry.run.parsed.slowestSec)}}</div>`,
        `<div class="chip">average: ${{fmtSec(entry.run.parsed.averageSec)}}</div>`,
        `<div class="chip">memory: ${{fmtMb(entry.run.parsed.maxMemoryMb)}}</div>`,
        `<div class="chip">cases: ${{entry.run.parsed.caseCount}} / cached ${{entry.testcases.cachedCaseCount}}</div>`,
    ].join("");
    const content = currentDetailTab === "raw" ? buildRawLog(entry) : buildCaseTable(entry);
    return `
        <div class="detail-panel">
            <div class="detail-head">
                <div>
                    <div class="eyebrow">expanded test</div>
                    <h2 class="detail-title">${{esc(entry.path)}}</h2>
                    <div>${{renderProblem(entry.problem)}}</div>
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
}}

function render() {{
    const query = filterInput.value.trim().toLowerCase();
    const filtered = report.tests
        .filter((entry) => {{
            const haystack = `${{entry.path}} ${{entry.problem}}`.toLowerCase();
            if (query && !haystack.includes(query)) return false;
            if (statusFilter.value === "ok" && !entry.run.ok) return false;
            if (statusFilter.value === "failed" && entry.run.ok) return false;
            return true;
        }})
        .sort((lhs, rhs) => {{
            const a = normalized(lhs, currentSort);
            const b = normalized(rhs, currentSort);
            if (typeof a === "string" || typeof b === "string") {{
                return String(a).localeCompare(String(b));
            }}
            return b - a;
        }});
    ensureSelection(filtered);

    if (!filtered.length) {{
        rows.innerHTML = `<tr><td colspan="6"><div class="empty-state">current filter に一致する test はない</div></td></tr>`;
    }} else {{
        rows.innerHTML = filtered.map((entry) => {{
            const slowest = entry.run.parsed.slowestSec;
            const isSelected = selectedPath === entry.path;
            return `
                <tr class="dashboard-row${{isSelected ? " is-selected" : ""}}" data-entry-path="${{esc(entry.path)}}" tabindex="0" aria-selected="${{isSelected ? "true" : "false"}}">
                    <td>
                        <div class="test-main">
                            <div class="test-head">
                                <span class="expander${{isSelected ? " is-open" : ""}}">${{isSelected ? "−" : "+"}}</span>
                                <div class="path">${{esc(entry.path)}}</div>
                            </div>
                            <div>${{renderProblem(entry.problem)}}</div>
                        </div>
                    </td>
                    <td><span class="${{statusClass(entry)}}">${{statusLabel(entry)}}</span></td>
                    <td>${{fmtSec(entry.compiler.wallSec)}}</td>
                    <td>
                        <div>${{fmtSec(slowest)}}</div>
                        <div class="muted">${{esc(entry.run.parsed.slowestCase ?? "-")}}</div>
                    </td>
                    <td>${{fmtSec(entry.run.parsed.averageSec)}}</td>
                    <td>${{fmtMb(entry.run.parsed.maxMemoryMb)}}</td>
                </tr>
                ${{isSelected ? `<tr class="detail-row"><td colspan="6">${{buildDetailPanel(entry)}}</td></tr>` : ""}}
            `;
        }}).join("");
    }}

    const summary = report.summary ?? {{}};
    const failed = summary.failed ?? report.tests.filter((entry) => !entry.run.ok && entry.phase !== "pending" && entry.phase !== "running").length;
    summaryGenerated.textContent = `generated: ${{report.generatedAt}}`;
    summaryTotal.textContent = `tests: ${{report.tests.length}}`;
    summaryProgress.textContent = `done: ${{summary.done ?? 0}} / running: ${{summary.running ?? 0}} / pending: ${{summary.pending ?? 0}}`;
    summaryFailed.textContent = `failed: ${{failed}}`;
    summaryVisible.textContent = `visible: ${{filtered.length}}`;
    resultCount.textContent = filtered.length ? `displaying ${{filtered.length}} / ${{report.tests.length}} tests` : "displaying 0 tests";
    bindSelection();
    bindDetailTabs();
}}

let refreshLock = false;
async function refreshReport() {{
    if (refreshLock) return;
    refreshLock = true;
    try {{
        const response = await fetch(`${{jsonUrl}}?t=${{Date.now()}}`, {{ cache: "no-store" }});
        if (!response.ok) return;
        report = await response.json();
        render();
    }} catch (_error) {{
    }} finally {{
        refreshLock = false;
    }}
}}

document.querySelectorAll("[data-sort]").forEach((button) => {{
    button.addEventListener("click", () => {{
        currentSort = button.dataset.sort;
        sortKey.value = currentSort;
        render();
    }});
}});
filterInput.addEventListener("input", render);
statusFilter.addEventListener("change", render);
sortKey.addEventListener("change", () => {{
    currentSort = sortKey.value;
    render();
}});
render();
refreshReport();
setInterval(refreshReport, 2000);
</script>
</body>
</html>
"""


def main() -> int:
    args = parse_args()
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
