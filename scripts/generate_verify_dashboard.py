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


def run_one_test(path: pathlib.Path, *, tle: float, oj_jobs: int) -> dict[str, Any]:
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

    compile_started_at = time.perf_counter()
    with tempfile.TemporaryDirectory(prefix="verify-dashboard-", dir=cache_dir) as tempdir_str:
        tempdir = pathlib.Path(tempdir_str)
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
    max-width: 1200px;
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
.table-wrap {{
    border: 1px solid var(--line);
    border-radius: 22px;
    overflow: hidden;
    background: rgba(255, 253, 248, 0.9);
    box-shadow: 0 16px 40px rgba(76, 52, 24, 0.08);
}}
table {{
    width: 100%;
    border-collapse: collapse;
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
.path {{
    font-family: "Iosevka Web", "SFMono-Regular", monospace;
    font-size: 13px;
}}
.muted {{
    color: var(--muted);
}}
.status-ok {{ color: var(--ok); font-weight: 700; }}
.status-bad {{ color: var(--bad); font-weight: 700; }}
.status-warn {{ color: var(--warn); font-weight: 700; }}
.bar {{
    width: 160px;
    height: 10px;
    background: #eadfce;
    border-radius: 999px;
    overflow: hidden;
    margin-top: 6px;
}}
.bar > span {{
    display: block;
    height: 100%;
    border-radius: 999px;
    background: linear-gradient(90deg, #d97706, var(--accent));
}}
details {{
    margin-top: 10px;
}}
summary {{
    cursor: pointer;
    color: var(--accent);
}}
.case-table {{
    margin-top: 12px;
    border: 1px solid var(--line);
    border-radius: 14px;
    overflow: hidden;
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
    padding: 14px;
    border-radius: 14px;
    overflow: auto;
}}
@media (max-width: 860px) {{
    .controls {{
        grid-template-columns: 1fr;
    }}
    th:nth-child(3),
    td:nth-child(3),
    th:nth-child(6),
    td:nth-child(6) {{
        display: none;
    }}
    .bar {{
        width: 120px;
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
    <div class="table-wrap">
        <table>
            <thead>
                <tr>
                    <th><button data-sort="path">test</button></th>
                    <th><button data-sort="status">status</button></th>
                    <th><button data-sort="compileWallSec">compile</button></th>
                    <th><button data-sort="slowestSec">slowest</button></th>
                    <th><button data-sort="averageSec">average</button></th>
                    <th><button data-sort="maxMemoryMb">memory</button></th>
                    <th>details</th>
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
let currentSort = "slowestSec";
const openDetails = new Map();

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

function detailStateKey(path, kind) {{
    return `${{path}}::${{kind}}`;
}}

function rememberOpenDetails() {{
    rows.querySelectorAll("details[data-entry-path][data-detail-kind]").forEach((detail) => {{
        openDetails.set(detailStateKey(detail.dataset.entryPath, detail.dataset.detailKind), detail.open);
    }});
}}

function detailOpenAttr(path, kind) {{
    return openDetails.get(detailStateKey(path, kind)) ? " open" : "";
}}

function bindDetailState() {{
    rows.querySelectorAll("details[data-entry-path][data-detail-kind]").forEach((detail) => {{
        detail.addEventListener("toggle", () => {{
            openDetails.set(detailStateKey(detail.dataset.entryPath, detail.dataset.detailKind), detail.open);
        }});
    }});
}}

function render() {{
    rememberOpenDetails();
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

    const peak = Math.max(0.000001, ...filtered.map((entry) => entry.run.parsed.slowestSec ?? 0));
    rows.innerHTML = filtered.map((entry) => {{
        const slowest = entry.run.parsed.slowestSec;
        const barWidth = slowest == null ? 0 : (slowest / peak) * 100;
        return `
            <tr>
                <td>
                    <div class="path">${{esc(entry.path)}}</div>
                    <div class="muted">${{esc(entry.problem)}}</div>
                </td>
                <td><span class="${{statusClass(entry)}}">${{statusLabel(entry)}}</span></td>
                <td>${{fmtSec(entry.compiler.wallSec)}}</td>
                <td>
                    <div>${{fmtSec(slowest)}}</div>
                    <div class="bar"><span style="width:${{barWidth}}%"></span></div>
                </td>
                <td>${{fmtSec(entry.run.parsed.averageSec)}}</td>
                <td>${{fmtMb(entry.run.parsed.maxMemoryMb)}}</td>
                <td>
                    <div class="muted">${{entry.run.parsed.caseCount}} cases / cached ${{entry.testcases.cachedCaseCount}}</div>
                    <details data-entry-path="${{esc(entry.path)}}" data-detail-kind="case"${{detailOpenAttr(entry.path, "case")}}>
                        <summary>case detail</summary>
                        ${{buildCaseTable(entry)}}
                    </details>
                    <details data-entry-path="${{esc(entry.path)}}" data-detail-kind="raw"${{detailOpenAttr(entry.path, "raw")}}>
                        <summary>raw log</summary>
                        <pre>${{esc(entry.run.output)}}</pre>
                    </details>
                </td>
            </tr>
        `;
    }}).join("");

    const summary = report.summary ?? {{}};
    const failed = summary.failed ?? report.tests.filter((entry) => !entry.run.ok && entry.phase !== "pending" && entry.phase !== "running").length;
    summaryGenerated.textContent = `generated: ${{report.generatedAt}}`;
    summaryTotal.textContent = `tests: ${{report.tests.length}}`;
    summaryProgress.textContent = `done: ${{summary.done ?? 0}} / running: ${{summary.running ?? 0}} / pending: ${{summary.pending ?? 0}}`;
    summaryFailed.textContent = `failed: ${{failed}}`;
    bindDetailState();
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
    if not tests:
        print(f"json: {args.json_path.relative_to(ROOT)}")
        print(f"html: {args.html_path.relative_to(ROOT)}")
        return 0

    worker_count = min(args.jobs, len(tests))
    next_index = 0
    futures: dict[concurrent.futures.Future[dict[str, Any]], int] = {}

    def submit_one(executor: concurrent.futures.Executor, index: int) -> None:
        report_tests[index]["phase"] = "running"
        future = executor.submit(run_one_test, tests[index], tle=args.tle, oj_jobs=args.oj_jobs)
        futures[future] = index

    try:
        with concurrent.futures.ThreadPoolExecutor(max_workers=worker_count) as executor:
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
