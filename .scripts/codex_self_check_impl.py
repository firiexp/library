#!/usr/bin/env python3

from __future__ import annotations

import re
import subprocess
import sys
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


def main() -> int:
    ok = run_sync_doc_titles()
    problems = check_library_files() + check_markdown_files()
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
