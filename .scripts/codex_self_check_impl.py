#!/usr/bin/env python3

from __future__ import annotations

import argparse
import re
import shutil
import subprocess
import sys
from importlib import util as importlib_util
from pathlib import Path
from urllib.parse import urlparse


ROOT = Path(__file__).resolve().parents[1]
CORE_DIRS = (
    "datastructure",
    "graph",
    "math",
    "string",
    "tree",
    "geometry",
    "flow",
    "fps",
    "util",
)
FORBIDDEN_LIBRARY_PATTERNS = (
    ("standard include", re.compile(r"^\s*#include\s*<[^>]+>", re.MULTILINE)),
    ("template alias ll", re.compile(r"^\s*using\s+ll\s*=\s*(?:long\s+long|std::int64_t|int64_t)\s*;", re.MULTILINE)),
    ("template alias uint", re.compile(r"^\s*using\s+uint\s*=\s*(?:unsigned(?:\s+int)?|std::uint32_t|uint32_t)\s*;", re.MULTILINE)),
    ("template alias ull", re.compile(r"^\s*using\s+ull\s*=\s*(?:unsigned\s+long\s+long|std::uint64_t|uint64_t)\s*;", re.MULTILINE)),
)
BACKTICK_COMPLEXITY_RE = re.compile(r"`(?:O|Θ)\([^`\n]*\)`")
FENCED_CODE_RE = re.compile(r"```.*?```", re.DOTALL)
PROBLEM_DEFINE_RE = re.compile(r'^\s*#define\s+PROBLEM\s+"([^"]+)"\s*$', re.MULTILINE)
TEST_FILE_NAME_RE = re.compile(r"^[a-z0-9_]+\.test\.cpp$")
SCRIPT_IMPL_RE = re.compile(
    r'^IMPL = __file__\.rsplit\("/", 2\)\[0\] \+ "/\.scripts/([^"]+)"$',
    re.MULTILINE,
)
ALLOWED_JUDGE_HOSTS = {
    "judge.u-aizu.ac.jp",
    "judge.yosupo.jp",
    "onlinejudge.u-aizu.ac.jp",
    "yukicoder.me",
}


def line_of(text: str, pos: int) -> int:
    return text.count("\n", 0, pos) + 1


def run_sync_doc_titles() -> bool:
    proc = subprocess.run(
        [sys.executable, str(ROOT / "scripts" / "sync_doc_titles.py")],
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if proc.stdout:
        print(proc.stdout, end="")
    if proc.stderr:
        stream = sys.stderr if proc.returncode else sys.stdout
        print(proc.stderr, end="", file=stream)
    return proc.returncode == 0


def check_library_files() -> list[str]:
    problems: list[str] = []
    for dirname in CORE_DIRS:
        for path in sorted((ROOT / dirname).rglob("*.cpp")):
            relpath = path.relative_to(ROOT).as_posix()
            text = path.read_text()
            for name, pattern in FORBIDDEN_LIBRARY_PATTERNS:
                for match in pattern.finditer(text):
                    if name == "standard include" and match.group(0).strip() == "#include <immintrin.h>":
                        continue
                    lineno = line_of(text, match.start())
                    problems.append(f"{relpath}:{lineno}: {name}")
    return problems


def strip_fenced_code(text: str) -> str:
    return FENCED_CODE_RE.sub("", text)


def check_markdown_files() -> list[str]:
    problems: list[str] = []
    for path in sorted((ROOT / "_md").rglob("*.md")):
        relpath = path.relative_to(ROOT).as_posix()
        text = strip_fenced_code(path.read_text())
        for match in BACKTICK_COMPLEXITY_RE.finditer(text):
            lineno = line_of(text, match.start())
            problems.append(f"{relpath}:{lineno}: complexity should use MathJax, not backticks")
    return problems


def check_test_files() -> list[str]:
    problems: list[str] = []
    for path in sorted((ROOT / "test").rglob("*.test.cpp")):
        relpath = path.relative_to(ROOT).as_posix()
        if not TEST_FILE_NAME_RE.fullmatch(path.name):
            problems.append(f"{relpath}: test file name must use lowercase letters, digits, and underscores")

        matches = PROBLEM_DEFINE_RE.findall(path.read_text())
        if len(matches) != 1:
            problems.append(f"{relpath}: expected exactly one #define PROBLEM URL")
            continue

        url = matches[0]
        parsed = urlparse(url)
        if parsed.scheme not in {"http", "https"} or parsed.hostname not in ALLOWED_JUDGE_HOSTS:
            problems.append(f"{relpath}: unsupported judge URL: {url}")
    return problems


def check_script_wrappers() -> list[str]:
    problems: list[str] = []
    for path in sorted((ROOT / "scripts").glob("*.py")):
        relpath = path.relative_to(ROOT).as_posix()
        match = SCRIPT_IMPL_RE.search(path.read_text())
        if match is None:
            problems.append(
                f"{relpath}: keep Python implementation under .scripts to avoid oj-verify docs dependency scans"
            )
            continue
        impl_path = ROOT / ".scripts" / match.group(1)
        if not impl_path.is_file():
            problems.append(f"{relpath}: missing implementation: {impl_path.relative_to(ROOT).as_posix()}")
    return problems


def check_measure_dashboard_html() -> list[str]:
    problems: list[str] = []
    module_path = ROOT / "scripts" / "generate_verify_dashboard.py"
    spec = importlib_util.spec_from_file_location("generate_verify_dashboard", module_path)
    if spec is None or spec.loader is None:
        return [f"{module_path.relative_to(ROOT).as_posix()}: failed to load module spec"]
    module = importlib_util.module_from_spec(spec)
    spec.loader.exec_module(module)

    report = {
        "generatedAt": "2026-03-12T00:00:00+09:00",
        "root": str(ROOT),
        "testCount": 1,
        "summary": {"pending": 0, "running": 0, "done": 1, "error": 0, "ok": 1, "failed": 0},
        "tests": [],
    }
    html_text = module.render_html(report, json_path=ROOT / ".verify-helper" / "measure-dashboard.json")

    ids = re.findall(r'id="([^"]+)"', html_text)
    duplicates = sorted({element_id for element_id in ids if ids.count(element_id) > 1})
    for element_id in duplicates:
        problems.append(f"measure dashboard html: duplicate id={element_id}")

    required_ids = (
        "rows",
        "filter",
        "status-filter",
        "sort-key",
        "sort-direction",
        "summary-live",
        "summary-failed",
        "summary-visible",
    )
    for element_id in required_ids:
        if f'id="{element_id}"' not in html_text:
            problems.append(f"measure dashboard html: missing id={element_id}")

    for column in module.SORT_COLUMNS:
        key = column["key"]
        label = column["label"]
        if f'data-sort="{key}"' not in html_text:
            problems.append(f"measure dashboard html: missing data-sort={key}")
        if f'<option value="{key}">{label}</option>' not in html_text:
            problems.append(f"measure dashboard html: missing mobile sort option={key}")

    required_inline_tokens = (
        'data-detail-tab="case"',
        'data-detail-tab="raw"',
        "data-case-filter",
        "data-case-sort",
    )
    for token in required_inline_tokens:
        if token not in html_text:
            problems.append(f"measure dashboard html: missing token {token}")
    return problems


def check_measure_dashboard_screenshots() -> list[str]:
    if shutil.which("chromium-browser") is None:
        print("skip: measure dashboard screenshots (chromium-browser not found)")
        return []

    command = [sys.executable, str(ROOT / "scripts" / "capture_measure_dashboard_screenshots.py")]
    proc = subprocess.run(
        command,
        cwd=ROOT,
        capture_output=True,
        text=True,
    )
    if proc.returncode != 0:
        detail = (proc.stderr or proc.stdout).strip()
        if "snap-confine is packaged without necessary permissions" in detail:
            print("skip: measure dashboard screenshots (chromium sandbox restriction)")
            return []
        suffix = f": {detail}" if detail else ""
        return [f"measure dashboard screenshots: capture failed{suffix}"]

    output_dir = ROOT / ".verify-helper" / "measure-dashboard-regression"
    expected = (
        output_dir / "desktop-top.png",
        output_dir / "desktop-scroll.png",
        output_dir / "mobile-top.png",
        output_dir / "skeleton-top.png",
    )
    problems: list[str] = []
    for path in expected:
        if not path.exists():
            problems.append(f"measure dashboard screenshots: missing output {path.relative_to(ROOT).as_posix()}")
    return problems


def main() -> int:
    parser = argparse.ArgumentParser(description="Run fast repository policy and generated-output checks.")
    parser.add_argument(
        "--full",
        action="store_true",
        help="also run the dashboard screenshot regression check",
    )
    args = parser.parse_args()

    ok = run_sync_doc_titles()
    problems = (
        check_library_files()
        + check_markdown_files()
        + check_test_files()
        + check_script_wrappers()
        + check_measure_dashboard_html()
    )
    if args.full:
        problems += check_measure_dashboard_screenshots()
    if problems:
        for problem in problems:
            print(problem, file=sys.stderr)
        ok = False
    if not ok:
        return 1
    mode = "full" if args.full else "fast"
    print(f"ok: codex self-check ({mode})")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
