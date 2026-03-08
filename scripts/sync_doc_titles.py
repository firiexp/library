#!/usr/bin/env python3

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path


ROOT = Path(__file__).resolve().parents[1]
TITLE_FILE = ROOT / "meta" / "doc_titles.yml"
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


COMMENT_BLOCK_RE = re.compile(r"/\*\*\n(?: \*.*\n)*? \*/\n?", re.MULTILINE)
MANAGED_BLOCK_RE = re.compile(
    r"/\*\*\n \* @brief (?P<title>[^\n]+)\n \* @docs (?P<docs>_md/[^\n]+)\n \*/\n?",
    re.MULTILINE,
)


def load_titles(path: Path) -> dict[str, str]:
    titles: dict[str, str] = {}
    for lineno, raw in enumerate(path.read_text().splitlines(), 1):
        line = raw.strip()
        if not line or line.startswith("#"):
            continue
        if ": " not in line:
            raise ValueError(f"{path}:{lineno}: invalid line")
        key, value = line.split(": ", 1)
        try:
            parsed = json.loads(value)
        except json.JSONDecodeError as exc:
            raise ValueError(f"{path}:{lineno}: invalid JSON string") from exc
        if not isinstance(parsed, str):
            raise ValueError(f"{path}:{lineno}: title must be a string")
        titles[key] = parsed
    return titles


def collect_doc_files() -> set[str]:
    files: set[str] = set()
    for root in CORE_DIRS:
        for path in (ROOT / root).glob("*.cpp"):
            if (ROOT / "_md" / f"{path.stem}.md").exists():
                files.add(path.relative_to(ROOT).as_posix())
    return files


def expected_docs_path(relpath: str) -> str:
    return f"_md/{Path(relpath).stem}.md"


def render_block(relpath: str, title: str) -> str:
    return (
        "/**\n"
        f" * @brief {title}\n"
        f" * @docs {expected_docs_path(relpath)}\n"
        " */\n"
    )


def replace_block(text: str, relpath: str, title: str) -> tuple[str, bool]:
    new_block = render_block(relpath, title)
    matches = [m for m in COMMENT_BLOCK_RE.finditer(text) if "@brief" in m.group(0) or "@docs" in m.group(0)]
    if len(matches) > 1:
        raise ValueError(f"{relpath}: multiple managed comment blocks found")
    if matches:
        match = matches[0]
        old = match.group(0)
        if old.endswith("\n"):
            replacement = new_block
        else:
            replacement = new_block.rstrip("\n")
        updated = text[: match.start()] + replacement + text[match.end() :]
        return updated, updated != text

    stripped = text.rstrip("\n")
    suffix = "\n\n" if stripped else ""
    updated = stripped + suffix + new_block
    return updated, True


def check_file(relpath: str, title: str) -> list[str]:
    problems: list[str] = []
    path = ROOT / relpath
    if not path.exists():
        return [f"missing file: {relpath}"]
    doc_path = expected_docs_path(relpath)
    if not (ROOT / doc_path).exists():
        problems.append(f"missing md: {doc_path}")

    text = path.read_text()
    match = MANAGED_BLOCK_RE.search(text)
    if not match:
        problems.append(f"missing managed block: {relpath}")
        return problems

    current_title = match.group("title")
    current_docs = match.group("docs")
    if current_title != title:
        problems.append(f"title mismatch: {relpath}")
    if current_docs != doc_path:
        problems.append(f"docs mismatch: {relpath} -> {current_docs}")
    return problems


def main() -> int:
    parser = argparse.ArgumentParser(description="sync @brief/@docs comments from meta/doc_titles.yml")
    parser.add_argument("--write", action="store_true", help="rewrite source files to match meta/doc_titles.yml")
    args = parser.parse_args()

    titles = load_titles(TITLE_FILE)
    doc_files = collect_doc_files()

    problems: list[str] = []
    for relpath in sorted(titles):
        if relpath not in doc_files:
            problems.append(f"title entry without matching md-backed file: {relpath}")
    for relpath in sorted(doc_files):
        text = (ROOT / relpath).read_text()
        if "@docs" in text and relpath not in titles:
            problems.append(f"file has @docs but no title entry: {relpath}")
    for relpath, title in sorted(titles.items()):
        problems.extend(check_file(relpath, title))

    if args.write:
        changed = 0
        for relpath, title in sorted(titles.items()):
            path = ROOT / relpath
            if not path.exists():
                continue
            updated, is_changed = replace_block(path.read_text(), relpath, title)
            if is_changed:
                path.write_text(updated)
                changed += 1
        print(f"updated {changed} files")

    if problems:
        for problem in problems:
            print(problem, file=sys.stderr)
        return 1

    print(f"ok: {len(titles)} title entries")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
