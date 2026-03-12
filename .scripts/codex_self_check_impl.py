#!/usr/bin/env python3

from __future__ import annotations

import re
import subprocess
import sys
from importlib import util as importlib_util
from pathlib import Path


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
        for path in sorted((ROOT / dirname).glob("*.cpp")):
            relpath = path.relative_to(ROOT).as_posix()
            text = path.read_text()
            for name, pattern in FORBIDDEN_LIBRARY_PATTERNS:
                for match in pattern.finditer(text):
                    lineno = line_of(text, match.start())
                    problems.append(f"{relpath}:{lineno}: {name}")
    return problems


def strip_fenced_code(text: str) -> str:
    return FENCED_CODE_RE.sub("", text)


def check_markdown_files() -> list[str]:
    problems: list[str] = []
    for path in sorted((ROOT / "_md").glob("*.md")):
        relpath = path.relative_to(ROOT).as_posix()
        text = strip_fenced_code(path.read_text())
        for match in BACKTICK_COMPLEXITY_RE.finditer(text):
            lineno = line_of(text, match.start())
            problems.append(f"{relpath}:{lineno}: complexity should use MathJax, not backticks")
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


def main() -> int:
    ok = run_sync_doc_titles()
    problems = check_library_files() + check_markdown_files() + check_measure_dashboard_html()
    if problems:
        for problem in problems:
            print(problem, file=sys.stderr)
        ok = False
    if not ok:
        return 1
    print("ok: codex self-check")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
