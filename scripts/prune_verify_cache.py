#!/usr/bin/env python3

from __future__ import annotations

import argparse
import shutil
from dataclasses import dataclass
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
DEFAULT_CACHE_DIR = ROOT / ".verify-helper" / "cache"


@dataclass(frozen=True)
class CacheEntry:
    path: Path
    size: int
    modified_at: float


def directory_stats(path: Path) -> tuple[int, float]:
    size = 0
    modified_at = path.stat().st_mtime
    for child in path.rglob("*"):
        try:
            stat = child.stat()
        except FileNotFoundError:
            continue
        modified_at = max(modified_at, stat.st_mtime)
        if child.is_file():
            size += stat.st_size
    return size, modified_at


def format_size(size: int) -> str:
    value = float(size)
    for unit in ("B", "KiB", "MiB", "GiB"):
        if value < 1024 or unit == "GiB":
            return f"{value:.2f} {unit}"
        value /= 1024
    raise AssertionError("unreachable")


def select_removals(entries: list[CacheEntry], max_size: int) -> list[CacheEntry]:
    remaining = sum(entry.size for entry in entries)
    removals: list[CacheEntry] = []
    for entry in sorted(entries, key=lambda item: item.modified_at):
        if remaining <= max_size:
            break
        removals.append(entry)
        remaining -= entry.size
    return removals


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Prune the local verification testcase cache by least recent use.")
    parser.add_argument("--max-size-gb", type=float, default=5.0, help="target cache size after pruning")
    parser.add_argument("--apply", action="store_true", help="remove selected cache directories")
    parser.add_argument("--all", action="store_true", help="select every cache entry")
    return parser.parse_args()


def main() -> int:
    args = parse_args()
    if args.max_size_gb < 0:
        raise ValueError("--max-size-gb must be non-negative")
    if not DEFAULT_CACHE_DIR.exists():
        print("cache directory does not exist")
        return 0

    entries = []
    for path in DEFAULT_CACHE_DIR.iterdir():
        if not path.is_dir():
            continue
        size, modified_at = directory_stats(path)
        entries.append(CacheEntry(path, size, modified_at))

    total_size = sum(entry.size for entry in entries)
    max_size = int(args.max_size_gb * 1024**3)
    removals = sorted(entries, key=lambda item: item.modified_at) if args.all else select_removals(entries, max_size)
    remove_size = sum(entry.size for entry in removals)

    mode = "apply" if args.apply else "dry-run"
    print(f"cache: {format_size(total_size)} in {len(entries)} entries")
    print(f"selected: {format_size(remove_size)} in {len(removals)} entries ({mode})")
    for entry in removals:
        print(f"  {entry.path.name}: {format_size(entry.size)}")

    if args.apply:
        for entry in removals:
            shutil.rmtree(entry.path)
        print(f"remaining: {format_size(total_size - remove_size)}")
    else:
        print("pass --apply to remove the selected entries")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
