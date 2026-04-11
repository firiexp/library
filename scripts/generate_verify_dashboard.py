#!/usr/bin/env python3

from __future__ import annotations

import argparse
import concurrent.futures
import hashlib
import html
import json
import os
import pathlib
import resource
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
DEFAULT_DOCS_STATIC_DIR = ROOT / ".verify-helper" / "docs" / "static"
DEFAULT_DOCS_STATIC_JSON_PATH = DEFAULT_DOCS_STATIC_DIR / DEFAULT_JSON_PATH.name
DEFAULT_DOCS_STATIC_HTML_PATH = DEFAULT_DOCS_STATIC_DIR / DEFAULT_HTML_PATH.name
DASHBOARD_ASSET_DIR = ROOT / "scripts" / "measure_dashboard_assets"
DEFAULT_WORKERS = max(1, os.cpu_count() or 1)
_problem_locks_guard = threading.Lock()
_problem_locks: dict[str, threading.Lock] = {}
_library_checker_lock = threading.Lock()
SORT_COLUMNS = [
    {"key": "path", "label": "test", "defaultDirection": "asc", "numeric": False},
    {"key": "status", "label": "status", "defaultDirection": "asc", "numeric": False},
    {"key": "compileWallSec", "label": "compile", "defaultDirection": "desc", "numeric": True},
    {"key": "slowestSec", "label": "slowest", "defaultDirection": "desc", "numeric": True},
    {"key": "averageSec", "label": "average", "defaultDirection": "desc", "numeric": True},
    {"key": "maxMemoryMb", "label": "memory", "defaultDirection": "desc", "numeric": True},
]


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


def relative_test_path(path: pathlib.Path) -> str:
    return str(path.resolve().relative_to(ROOT))


def run_command(command: list[str], *, cwd: pathlib.Path) -> subprocess.CompletedProcess[str]:
    def set_unlimited_stack() -> None:
        soft, hard = resource.getrlimit(resource.RLIMIT_STACK)
        target = hard if hard != resource.RLIM_INFINITY else resource.RLIM_INFINITY
        if soft != target:
            resource.setrlimit(resource.RLIMIT_STACK, (target, hard))

    return subprocess.run(
        command,
        cwd=cwd,
        text=True,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        check=False,
        preexec_fn=set_unlimited_stack,
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
    relative_path = relative_test_path(path)
    return {
        "path": relative_path,
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


def load_existing_entries(json_path: pathlib.Path) -> list[dict[str, Any]]:
    if not json_path.exists():
        return []
    report = json.loads(json_path.read_text())
    tests = report.get("tests")
    if not isinstance(tests, list):
        return []
    return tests


def prune_missing_entries(entries: list[dict[str, Any]]) -> list[dict[str, Any]]:
    pruned: list[dict[str, Any]] = []
    for entry in entries:
        if not isinstance(entry, dict):
            continue
        path = entry.get("path")
        if not isinstance(path, str):
            continue
        if not (ROOT / path).exists():
            continue
        pruned.append(entry)
    return pruned


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


def write_one_report(report: dict[str, Any], *, json_path: pathlib.Path, html_path: pathlib.Path) -> None:
    json_path.parent.mkdir(parents=True, exist_ok=True)
    html_path.parent.mkdir(parents=True, exist_ok=True)
    json_path.write_text(json.dumps(report, ensure_ascii=False, indent=2) + "\n")
    html_path.write_text(render_html(report, json_path=json_path))


def write_report(report: dict[str, Any], *, json_path: pathlib.Path, html_path: pathlib.Path) -> None:
    write_one_report(report, json_path=json_path, html_path=html_path)
    if json_path == DEFAULT_JSON_PATH and html_path == DEFAULT_HTML_PATH:
        write_one_report(
            report,
            json_path=DEFAULT_DOCS_STATIC_JSON_PATH,
            html_path=DEFAULT_DOCS_STATIC_HTML_PATH,
        )


def print_output_paths(*, json_path: pathlib.Path, html_path: pathlib.Path) -> None:
    print(f"json: {json_path.relative_to(ROOT)}")
    print(f"html: {html_path.relative_to(ROOT)}")
    if json_path == DEFAULT_JSON_PATH and html_path == DEFAULT_HTML_PATH:
        print(f"docs json: {DEFAULT_DOCS_STATIC_JSON_PATH.relative_to(ROOT)}")
        print(f"docs html: {DEFAULT_DOCS_STATIC_HTML_PATH.relative_to(ROOT)}")


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
    relative_path = pathlib.Path(relative_test_path(path))
    language = onlinejudge_verify.languages.list.get(relative_path)
    if language is None:
        raise RuntimeError(f"unsupported language: {relative_path}")

    attributes = language.list_attributes(relative_path, basedir=ROOT)
    problem_url = attributes.get("PROBLEM")
    if not problem_url:
        raise RuntimeError(f"PROBLEM is not specified: {relative_path}")
    error_tolerance = attributes.get("ERROR")

    cache_dir = build_cache_dir(problem_url)
    testcase_dir = cache_dir / "test"
    cache_dir.mkdir(parents=True, exist_ok=True)

    problem = onlinejudge.dispatch.problem_from_url(problem_url)
    judge_command = None
    if isinstance(problem, onlinejudge.service.library_checker.LibraryCheckerProblem):
        with get_problem_lock(problem_url):
            ensure_testcases(problem_url, testcase_dir=testcase_dir)
        checker_path = None
        try:
            candidate = problem._get_problem_directory_path() / "checker"
            if candidate.exists():
                checker_path = candidate
        except RuntimeError:
            checker_path = None
        if checker_path is None:
            with _library_checker_lock:
                checker_path = problem.download_checker_binary()
        judge_command = str(checker_path)
    else:
        with get_problem_lock(problem_url):
            ensure_testcases(problem_url, testcase_dir=testcase_dir)

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
        if error_tolerance:
            command += ["-e", str(error_tolerance)]
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


def render_sort_key_options() -> str:
    return "\n".join(
        f'                    <option value="{column["key"]}">{column["label"]}</option>'
        for column in SORT_COLUMNS
    )


def render_sort_header_cells() -> str:
    cells = []
    for column in SORT_COLUMNS:
        class_name = ' class="num"' if column["numeric"] else ""
        cells.append(
            f'                    <th{class_name}><button class="sort-button" type="button" '
            f'data-sort="{column["key"]}" data-label="{column["label"]}">'
            f'<span class="sort-label">{column["label"]}</span>'
            f'<span class="sort-indicator" aria-hidden="true"></span></button></th>'
        )
    return "\n".join(cells)


def load_dashboard_asset(name: str) -> str:
    return (DASHBOARD_ASSET_DIR / name).read_text()


def render_template(template: str, replacements: dict[str, str]) -> str:
    for key, value in replacements.items():
        template = template.replace(f"__{key}__", value)
    return template


def render_html(report: dict[str, Any], *, json_path: pathlib.Path, bootstrap_full_report: bool = False) -> str:
    bootstrap_json = json.dumps(
        {
            "generatedAt": report.get("generatedAt"),
            "root": report.get("root"),
            "testCount": report.get("testCount", 0),
            "summary": report.get("summary", {}),
            "tests": report.get("tests", []) if bootstrap_full_report else [],
        },
        ensure_ascii=False,
    )
    json_filename = json_path.name
    generated_at = html.escape(report["generatedAt"])
    title = "verify measurement dashboard"
    sort_key_options = render_sort_key_options()
    sort_header_cells = render_sort_header_cells()
    script = render_template(
        load_dashboard_asset("dashboard.js"),
        {
            "BOOTSTRAP_JSON": bootstrap_json,
            "JSON_URL": json.dumps(json_filename),
            "SORT_COLUMNS_JSON": json.dumps(SORT_COLUMNS, ensure_ascii=False),
        },
    )
    return render_template(
        load_dashboard_asset("dashboard.html"),
        {
            "GENERATED_AT": generated_at,
            "SCRIPT": script,
            "SORT_HEADER_CELLS": sort_header_cells,
            "SORT_KEY_OPTIONS": sort_key_options,
            "STYLE": load_dashboard_asset("dashboard.css"),
            "TITLE": html.escape(title),
        },
    )


def main() -> int:
    args = parse_args()
    if args.render_only:
        if not args.json_path.exists():
            raise FileNotFoundError(f"json report not found: {args.json_path}")
        entries = prune_missing_entries(load_existing_entries(args.json_path))
        write_report(make_report(entries), json_path=args.json_path, html_path=args.html_path)
        print_output_paths(json_path=args.json_path, html_path=args.html_path)
        return 0

    tests = list_test_paths(args.paths)
    onlinejudge_verify.languages.list.get(pathlib.Path("dummy.cpp"))
    if args.paths:
        report_tests = prune_missing_entries(load_existing_entries(args.json_path))
        index_by_path = {
            entry.get("path"): index
            for index, entry in enumerate(report_tests)
            if isinstance(entry, dict) and isinstance(entry.get("path"), str)
        }
        for path in tests:
            relative_path = relative_test_path(path)
            index = index_by_path.get(relative_path)
            if index is None:
                index_by_path[relative_path] = len(report_tests)
                report_tests.append(make_empty_entry(path))
            else:
                report_tests[index] = make_empty_entry(path)
    else:
        report_tests = [make_empty_entry(path) for path in tests]
        index_by_path = {entry["path"]: index for index, entry in enumerate(report_tests)}
    write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)

    if args.jobs <= 0:
        raise ValueError("--jobs must be positive")
    if args.oj_jobs <= 0:
        raise ValueError("--oj-jobs must be positive")
    if args.compile_jobs <= 0:
        raise ValueError("--compile-jobs must be positive")
    if not tests:
        print_output_paths(json_path=args.json_path, html_path=args.html_path)
        return 0

    worker_count = min(args.jobs, len(tests))
    compile_worker_count = min(args.compile_jobs, worker_count)
    compile_slots = threading.Semaphore(compile_worker_count)
    next_index = 0
    futures: dict[concurrent.futures.Future[dict[str, Any]], int] = {}

    def submit_one(executor: concurrent.futures.Executor, index: int) -> None:
        report_index = index_by_path[relative_test_path(tests[index])]
        report_tests[report_index]["phase"] = "running"
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
                    test_index = futures.pop(future)
                    path = tests[test_index]
                    report_index = index_by_path[relative_test_path(path)]
                    try:
                        entry = future.result()
                        report_tests[report_index] = entry
                        status = "ok" if entry["run"]["ok"] else "failed"
                        slowest = entry["run"]["parsed"]["slowestSec"]
                        print(f"{entry['path']}: {status}, slowest={slowest}")
                    except Exception as exc:
                        if not args.keep_going:
                            for pending in futures:
                                pending.cancel()
                            raise
                        relative_path = relative_test_path(path)
                        entry = make_empty_entry(path)
                        entry["phase"] = "error"
                        entry["run"]["output"] = str(exc)
                        print(f"{relative_path}: error: {exc}", file=sys.stderr)
                        report_tests[report_index] = entry

                while next_index < len(tests) and len(futures) < worker_count:
                    submit_one(executor, next_index)
                    next_index += 1
                write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)
    except Exception:
        write_report(make_report(report_tests), json_path=args.json_path, html_path=args.html_path)
        raise

    print_output_paths(json_path=args.json_path, html_path=args.html_path)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
