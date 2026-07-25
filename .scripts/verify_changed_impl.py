#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
import pathlib
import re
import shlex
import subprocess
import sys


ROOT = pathlib.Path(__file__).resolve().parent.parent
CORE_DIRS = {
    "datastructure",
    "flow",
    "fps",
    "geometry",
    "graph",
    "math",
    "string",
    "tree",
    "util",
}
GLOBAL_VERIFY_INPUTS = {
    pathlib.Path(".verify-helper/config.toml"),
    pathlib.Path("requirements-dev.txt"),
}
INCLUDE_RE = re.compile(r'^\s*#\s*include\s*"([^"]+)"', re.MULTILINE)
DEFAULT_JOBS = min(8, max(1, os.cpu_count() or 1))


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Select verification tests affected by working-tree or branch changes and optionally run them.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "paths",
        nargs="*",
        help="changed files to analyze; omit to inspect staged, unstaged, and untracked files",
    )
    parser.add_argument(
        "--base",
        help="also include committed changes in BASE...HEAD; cannot be combined with explicit paths",
    )
    parser.add_argument("--list", action="store_true", help="only list affected tests")
    parser.add_argument("--all", action="store_true", help="select every verification test without generating docs")
    parser.add_argument("-j", "--jobs", type=int, default=DEFAULT_JOBS, help="oj-verify dependency and oj test jobs")
    parser.add_argument("--tle", type=float, default=60.0, help="oj test time limit")
    parser.add_argument("--skip-self-check", action="store_true", help="skip the fast repository self-check")
    parser.add_argument(
        "--full-self-check",
        action="store_true",
        help="include dashboard screenshot regression in the self-check",
    )
    args = parser.parse_args()
    if args.paths and args.base:
        parser.error("--base cannot be combined with explicit paths")
    if args.jobs <= 0:
        parser.error("--jobs must be positive")
    return args


def normalize_repo_path(raw_path: str | pathlib.Path) -> pathlib.Path:
    path = pathlib.Path(raw_path)
    absolute = path if path.is_absolute() else ROOT / path
    try:
        return absolute.resolve(strict=False).relative_to(ROOT)
    except ValueError as exc:
        raise ValueError(f"path is outside the repository: {raw_path}") from exc


def git_paths(command: list[str]) -> set[pathlib.Path]:
    completed = subprocess.run(command, cwd=ROOT, capture_output=True, check=False)
    if completed.returncode != 0:
        detail = completed.stderr.decode(errors="replace").strip()
        raise RuntimeError(detail or f"command failed: {shlex.join(command)}")
    return {
        normalize_repo_path(raw.decode(errors="surrogateescape"))
        for raw in completed.stdout.split(b"\0")
        if raw
    }


def collect_changed_paths(args: argparse.Namespace) -> set[pathlib.Path]:
    if args.paths:
        return {normalize_repo_path(path) for path in args.paths}

    changed = git_paths(["git", "diff", "--name-only", "-z", "HEAD"])
    changed |= git_paths(["git", "ls-files", "--others", "--exclude-standard", "-z"])
    if args.base:
        changed |= git_paths(["git", "diff", "--name-only", "-z", f"{args.base}...HEAD"])
    return changed


def resolve_include(source: pathlib.Path, include: str) -> pathlib.Path | None:
    candidates = [source.parent / include, ROOT / include]
    for candidate in candidates:
        resolved = candidate.resolve(strict=False)
        try:
            relative = resolved.relative_to(ROOT)
        except ValueError:
            continue
        if resolved.exists():
            return relative

    resolved = candidates[0].resolve(strict=False)
    try:
        return resolved.relative_to(ROOT)
    except ValueError:
        return None


def collect_quoted_dependencies(test_path: pathlib.Path) -> set[pathlib.Path]:
    dependencies: set[pathlib.Path] = set()
    pending = [test_path]
    while pending:
        relative = pending.pop()
        if relative in dependencies:
            continue
        dependencies.add(relative)

        source = ROOT / relative
        if not source.is_file():
            continue
        text = source.read_text(errors="replace")
        for include in INCLUDE_RE.findall(text):
            dependency = resolve_include(source, include)
            if dependency is not None and dependency not in dependencies:
                pending.append(dependency)
    return dependencies


def collect_test_dependencies() -> dict[pathlib.Path, set[pathlib.Path]]:
    tests = sorted(path.relative_to(ROOT) for path in (ROOT / "test").rglob("*.test.cpp"))
    return {test: collect_quoted_dependencies(test) for test in tests}


def select_affected_tests(
    changed: set[pathlib.Path],
    dependencies: dict[pathlib.Path, set[pathlib.Path]],
    *,
    select_all: bool,
) -> list[pathlib.Path]:
    if select_all or changed & GLOBAL_VERIFY_INPUTS:
        return sorted(dependencies)
    return sorted(test for test, test_dependencies in dependencies.items() if changed & test_dependencies)


def uncovered_library_paths(
    changed: set[pathlib.Path],
    dependencies: dict[pathlib.Path, set[pathlib.Path]],
) -> list[pathlib.Path]:
    covered = set().union(*dependencies.values()) if dependencies else set()
    return sorted(
        path
        for path in changed
        if path.suffix == ".cpp" and path.parts and path.parts[0] in CORE_DIRS and path not in covered
    )


def print_selection(changed: set[pathlib.Path], selected: list[pathlib.Path], uncovered: list[pathlib.Path]) -> None:
    print(f"changed inputs: {len(changed)}")
    for path in sorted(changed):
        print(f"  {path.as_posix()}")
    print(f"affected verification tests: {len(selected)}")
    for path in selected:
        print(f"  {path.as_posix()}")
    sys.stdout.flush()
    for path in uncovered:
        print(f"warning: no verification test includes {path.as_posix()}", file=sys.stderr)


def run_command(command: list[str]) -> int:
    print("$", shlex.join(command), flush=True)
    completed = subprocess.run(command, cwd=ROOT, check=False)
    return completed.returncode


def main() -> int:
    args = parse_args()
    try:
        changed = collect_changed_paths(args)
    except (RuntimeError, ValueError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        return 2

    dependencies = collect_test_dependencies()
    selected = select_affected_tests(changed, dependencies, select_all=args.all)
    uncovered = uncovered_library_paths(changed, dependencies)
    print_selection(changed, selected, uncovered)

    if args.list:
        return 1 if uncovered else 0

    if not args.skip_self_check:
        self_check = [sys.executable, "scripts/codex_self_check.py"]
        if args.full_self_check:
            self_check.append("--full")
        result = run_command(self_check)
        if result != 0:
            return result

    if uncovered:
        return 1
    if not selected:
        print("ok: no judge verification is affected")
        return 0

    return run_command(
        [
            "oj-verify",
            "run",
            "-j",
            str(args.jobs),
            "--tle",
            str(args.tle),
            *(path.as_posix() for path in selected),
        ]
    )


if __name__ == "__main__":
    raise SystemExit(main())
