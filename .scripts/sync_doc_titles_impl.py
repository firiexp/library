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
    r"/\*\*\n \* @brief (?P<title>[^\n]+)\n \*/\n?",
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
        for path in (ROOT / root).rglob("*.cpp"):
            if (ROOT / expected_docs_path(path.relative_to(ROOT).as_posix())).exists():
                files.add(path.relative_to(ROOT).as_posix())
    return files


def expected_docs_path(relpath: str) -> str:
    path = Path(relpath)
    return (Path("_md") / path.parent / f"{path.stem}.md").as_posix()


def expected_documentation_of(relpath: str) -> str:
    return f"//{relpath}"


def render_block(title: str) -> str:
    return (
        "/**\n"
        f" * @brief {title}\n"
        " */\n"
    )


def replace_block(text: str, relpath: str, title: str) -> tuple[str, bool]:
    new_block = render_block(title)
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


def split_front_matter(text: str) -> tuple[list[str], str] | None:
    lines = text.splitlines(keepends=True)
    if not lines or lines[0].strip() != "---":
        return None
    for i in range(1, len(lines)):
        if lines[i].strip() == "---":
            return lines[1:i], "".join(lines[i + 1 :])
    return None


def replace_front_matter(text: str, relpath: str, title: str) -> tuple[str, bool]:
    parsed = split_front_matter(text)
    if parsed is None:
        front_matter = (
            "---\n"
            f"title: {title}\n"
            f"documentation_of: {expected_documentation_of(relpath)}\n"
            "---\n"
        )
        return front_matter + text, True
    front_matter_lines, body = parsed
    target = expected_documentation_of(relpath)
    updated_lines: list[str] = []
    changed = False
    found_title = False
    found_documentation_of = False
    for line in front_matter_lines:
        if line.startswith("title:"):
            found_title = True
            new_line = f"title: {title}\n"
            updated_lines.append(new_line)
            changed |= line != new_line
            continue
        if line.startswith("documentation_of:"):
            found_documentation_of = True
            new_line = f"documentation_of: {target}\n"
            updated_lines.append(new_line)
            changed |= line != new_line
            continue
        updated_lines.append(line)
    if not found_title:
        updated_lines.insert(0, f"title: {title}\n")
        changed = True
    if not found_documentation_of:
        insert_at = 0
        for i, line in enumerate(updated_lines):
            if line.startswith("title:"):
                insert_at = i + 1
                break
        updated_lines.insert(insert_at, f"documentation_of: {target}\n")
        changed = True
    updated = "---\n" + "".join(updated_lines) + "---\n" + body
    return updated, changed


def parse_front_matter_value(text: str, key: str) -> str | None:
    parsed = split_front_matter(text)
    if parsed is None:
        return None
    front_matter_lines, _ = parsed
    for line in front_matter_lines:
        if line.startswith(f"{key}:"):
            return line.split(":", 1)[1].strip()
    return None


def check_file(relpath: str, title: str) -> list[str]:
    problems: list[str] = []
    path = ROOT / relpath
    if not path.exists():
        return [f"missing file: {relpath}"]
    doc_path = expected_docs_path(relpath)
    md_path = ROOT / doc_path
    if not md_path.exists():
        problems.append(f"missing md: {doc_path}")

    text = path.read_text()
    match = MANAGED_BLOCK_RE.search(text)
    if not match:
        problems.append(f"missing managed block: {relpath}")
        return problems

    if "@docs" in text:
        problems.append(f"deprecated @docs remains: {relpath}")

    current_title = match.group("title")
    if current_title != title:
        problems.append(f"title mismatch: {relpath}")

    if md_path.exists():
        md_text = md_path.read_text()
        md_title = parse_front_matter_value(md_text, "title")
        if md_title != title:
            problems.append(f"md title mismatch: {doc_path}")
        documentation_of = parse_front_matter_value(md_text, "documentation_of")
        if documentation_of != expected_documentation_of(relpath):
            problems.append(f"documentation_of mismatch: {doc_path}")
    return problems


def collect_problems(titles: dict[str, str], doc_files: set[str]) -> list[str]:
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
    return problems


def main() -> int:
    parser = argparse.ArgumentParser(description="sync @brief comments and documentation_of from meta/doc_titles.yml")
    parser.add_argument("--write", action="store_true", help="rewrite source and markdown files to match meta/doc_titles.yml")
    args = parser.parse_args()

    titles = load_titles(TITLE_FILE)
    doc_files = collect_doc_files()
    problems = collect_problems(titles, doc_files)

    if args.write:
        changed = 0
        for relpath, title in sorted(titles.items()):
            path = ROOT / relpath
            if path.exists():
                updated, is_changed = replace_block(path.read_text(), relpath, title)
                if is_changed:
                    path.write_text(updated)
                    changed += 1

            md_path = ROOT / expected_docs_path(relpath)
            if md_path.exists():
                updated_md, is_changed_md = replace_front_matter(md_path.read_text(), relpath, title)
                if is_changed_md:
                    md_path.write_text(updated_md)
                    changed += 1
        print(f"updated {changed} files")
        problems = collect_problems(titles, doc_files)

    if problems:
        for problem in problems:
            print(problem, file=sys.stderr)
        return 1

    print(f"ok: {len(titles)} title entries")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
