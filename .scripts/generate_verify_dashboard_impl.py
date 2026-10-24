#!/usr/bin/env python3

from __future__ import annotations

import argparse
import concurrent.futures
import functools
import html
import json
import os
import pathlib
import platform
import re
import subprocess
import sys
import tempfile
import threading
import time
from datetime import datetime, timezone
from typing import Any


ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / ".scripts"))
from verification_impl import STATE, command, read_json, resolve, select, unlimited_stack, write_json
DEFAULT_JSON_PATH = ROOT / ".competitive-verifier" / "measure-dashboard.json"
DEFAULT_HTML_PATH = ROOT / ".competitive-verifier" / "measure-dashboard.html"
DEFAULT_DOCS_STATIC_DIR = ROOT / ".competitive-verifier" / "docs" / "static"
DEFAULT_DOCS_STATIC_JSON_PATH = DEFAULT_DOCS_STATIC_DIR / DEFAULT_JSON_PATH.name
DEFAULT_DOCS_STATIC_HTML_PATH = DEFAULT_DOCS_STATIC_DIR / DEFAULT_HTML_PATH.name
DASHBOARD_ASSET_DIR = ROOT / "scripts" / "measure_dashboard_assets"
DEFAULT_WORKERS = 1
PROBLEM_DEFINE_RE = re.compile(r'^\s*#\s*define\s+PROBLEM\b', re.MULTILINE)
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
        description="Measure PROBLEM tests with assertions disabled and generate a browser dashboard; skip STANDALONE tests.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "paths",
        nargs="*",
        help="PROBLEM test paths; if omitted, scan test/*.test.cpp for PROBLEM definitions",
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
        help="testcase time limit",
    )
    parser.add_argument(
        "-j",
        "--jobs",
        type=int,
        default=DEFAULT_WORKERS,
        help="number of tests to measure in parallel",
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
    parser.add_argument("--no-download", action="store_true", help="require existing testcase caches")
    return parser.parse_args()


def list_test_paths(paths: list[str]) -> list[pathlib.Path]:
    if paths:
        return [ROOT / pathlib.Path(path) for path in paths]
    return sorted(path for path in (ROOT / "test").glob("*.test.cpp") if PROBLEM_DEFINE_RE.search(path.read_text()))


def relative_test_path(path: pathlib.Path) -> str:
    return str(path.resolve().relative_to(ROOT))


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


def sanitize_public_value(value: Any) -> Any:
    if isinstance(value, str):
        value = value.replace(str(ROOT), ".")
        return value.replace(str(pathlib.Path.home()), "~")
    if isinstance(value, list):
        return [sanitize_public_value(item) for item in value]
    if isinstance(value, dict):
        return {key: sanitize_public_value(item) for key, item in value.items()}
    return value


@functools.lru_cache(maxsize=1)
def get_environment_info() -> dict[str, Any]:
    compiler = subprocess.run(
        ["g++", "--version"],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=False,
    )
    revision = subprocess.run(
        ["git", "rev-parse", "HEAD"],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=False,
    )
    compiler_line = compiler.stdout.splitlines()[0] if compiler.stdout else None
    revision_text = revision.stdout.strip() if revision.returncode == 0 else None
    return {
        "gitRevision": revision_text,
        "compiler": compiler_line,
        "platform": platform.platform(),
        "processor": platform.processor() or None,
        "logicalCpuCount": os.cpu_count(),
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
    current_paths = {relative_test_path(path) for path in list_test_paths([])}
    measured_paths = {
        entry.get("path")
        for entry in entries
        if isinstance(entry, dict) and isinstance(entry.get("path"), str)
    }
    missing_paths = sorted(current_paths - measured_paths)
    public_entries = sanitize_public_value(entries)
    return {
        "generatedAt": datetime.now(timezone.utc).astimezone().isoformat(timespec="seconds"),
        "root": ".",
        "testCount": len(entries),
        "inventory": {
            "currentTestCount": len(current_paths),
            "measuredTestCount": len(measured_paths & current_paths),
            "unmeasuredCount": len(missing_paths),
            "unmeasuredPaths": missing_paths,
            "stale": bool(missing_paths),
        },
        "generationEnvironment": get_environment_info(),
        "summary": {
            **phase_counts,
            "ok": ok_count,
            "failed": failed_count,
        },
        "tests": public_entries,
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
    print(f"json: {json_path}")
    print(f"html: {html_path}")
    if json_path == DEFAULT_JSON_PATH and html_path == DEFAULT_HTML_PATH:
        print(f"docs json: {DEFAULT_DOCS_STATIC_JSON_PATH.relative_to(ROOT)}")
        print(f"docs html: {DEFAULT_DOCS_STATIC_HTML_PATH.relative_to(ROOT)}")


def parse_verification_result(result, standalone=None):
    cases = result.get("testcases") or []
    if standalone is not None:
        cases = [{"name": "standalone", "status": "AC" if standalone["returncode"] == 0 else "TLE" if standalone["returncode"] == 124 else "RE",
                  "elapsed": standalone["elapsed"], "memory": standalone["memory"]}]
    slowest = max(cases, key=lambda case: case["elapsed"], default=None)
    with_memory = [case for case in cases if case.get("memory") is not None]
    heaviest = max(with_memory, key=lambda case: case["memory"], default=None)
    return {
        "cases": [{"name": case["name"], "status": case["status"], "timeSec": case["elapsed"]} for case in cases],
        "caseCount": len(cases), "timedCaseCount": len(cases),
        "passedCaseCount": sum(case["status"] == "AC" for case in cases),
        "slowestSec": slowest["elapsed"] if slowest else None,
        "slowestCase": slowest["name"] if slowest else None,
        "averageSec": sum(case["elapsed"] for case in cases) / len(cases) if cases else None,
        "maxMemoryMb": heaviest["memory"] if heaviest else None,
        "maxMemoryCase": heaviest["name"] if heaviest else None,
        "summary": result["status"],
    }


def run_one_test(path: pathlib.Path, *, tle: float, compile_slots: threading.Semaphore) -> dict[str, Any]:
    relative_path = relative_test_path(path)
    resolved = select(_resolved, [relative_path])
    verification = resolved["files"][relative_path]["verification"][0]
    compile_command = verification.pop("compile")
    directory = ROOT / compile_command[3]
    (directory / "run.json").unlink(missing_ok=True)
    with compile_slots:
        compiled = command(compile_command, capture=True)
    compile_info = read_json(directory / "compile.json")
    entry = make_empty_entry(path)
    entry["phase"] = "done"
    entry["problem"] = verification.get("problem")
    entry["compiler"] = {"command": compile_command[5:], "wallSec": compile_info["elapsed"]}
    if compiled.returncode:
        entry["phase"] = "error"
        entry["run"].update({"returnCode": compiled.returncode, "output": compiled.stdout})
        return entry
    with tempfile.TemporaryDirectory(prefix="measure-", dir=STATE) as temporary:
        temporary = pathlib.Path(temporary)
        input_path, result_path = temporary / "input.json", temporary / "result.json"
        write_json(input_path, resolved)
        args = ["competitive-verifier", "verify", "--verify-json", str(input_path), "--output", str(result_path),
                "--check-error", "--no-download", "--tle", str(tle)]
        started = time.perf_counter()
        completed = command(args, capture=True)
        elapsed = time.perf_counter() - started
        results = read_json(result_path, {}).get("files", {}).get(relative_path, {}).get("verifications", [])
    result = results[0] if results else {"status": "failure"}
    standalone = read_json(directory / "run.json") if verification["type"] == "command" else None
    parsed = parse_verification_result(result, standalone)
    entry["testcases"] = {"directory": None, "cachedCaseCount": parsed["caseCount"]}
    entry["run"] = {"command": verification["command"], "returnCode": completed.returncode, "wallSec": elapsed,
                    "ok": completed.returncode == 0 and result["status"] == "success", "parsed": parsed,
                    "output": compiled.stdout + completed.stdout}
    return entry


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
            "inventory": report.get("inventory", {}),
            "generationEnvironment": report.get("generationEnvironment", {}),
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
    global _resolved
    unlimited_stack()
    _resolved = resolve(min(8, max(1, os.cpu_count() or 1)), tle=args.tle, release=True)
    problem_tests = []
    for path in tests:
        relative_path = relative_test_path(path)
        verifications = _resolved["files"].get(relative_path, {}).get("verification", [])
        if not verifications:
            raise ValueError(f"unknown test path: {relative_path}")
        if verifications[0]["type"] == "command":
            print(f"skip {relative_path}: STANDALONE requires assertions; use scripts/run_verify.py")
        else:
            problem_tests.append(path)
    tests = problem_tests
    if not tests:
        print("no PROBLEM tests selected")
        return 0
    if not args.no_download:
        with tempfile.TemporaryDirectory(prefix="measure-download-", dir=STATE) as temporary:
            input_path = pathlib.Path(temporary) / "input.json"
            write_json(input_path, select(_resolved, [relative_test_path(path) for path in tests]))
            downloaded = command(["competitive-verifier", "download", "--verify-json", str(input_path)])
            if downloaded.returncode:
                return downloaded.returncode
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
            compile_slots=compile_slots,
        )
        futures[future] = index

    try:
        with concurrent.futures.ThreadPoolExecutor(max_workers=worker_count) as executor:
            print(
                f"parallel tests={worker_count}, compile slots={compile_worker_count}, sequential cases/test",
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
    return int(any(not entry["run"]["ok"] for entry in report_tests if entry["path"] in {relative_test_path(path) for path in tests}))


if __name__ == "__main__":
    raise SystemExit(main())
