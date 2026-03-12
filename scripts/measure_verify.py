#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
import pathlib
import shlex
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
DEFAULT_WORKERS = max(1, os.cpu_count() or 1)


def parse_args() -> argparse.Namespace:
    parser = argparse.ArgumentParser(
        description="Run self-check and update the live measurement dashboard.",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument("paths", nargs="*", help="verification test paths; omit to run all")
    parser.add_argument("-j", "--jobs", type=int, default=DEFAULT_WORKERS, help="number of tests to measure in parallel")
    parser.add_argument("--oj-jobs", type=int, default=1, help="oj test -j value for each measured test")
    parser.add_argument("--tle", type=float, default=60.0, help="oj test --tle value")
    parser.add_argument("--skip-self-check", action="store_true", help="skip scripts/codex_self_check.py")
    parser.add_argument("--timeout", type=float, help=argparse.SUPPRESS)
    parser.add_argument("--skip-dashboard", action="store_true", help=argparse.SUPPRESS)
    return parser.parse_args()


def run_command(command: list[str]) -> int:
    print("$", shlex.join(command), flush=True)
    completed = subprocess.run(command, cwd=ROOT, check=False)
    return completed.returncode


def main() -> int:
    args = parse_args()

    if not args.skip_self_check:
        result = run_command([sys.executable, "scripts/codex_self_check.py"])
        if result != 0:
            return result

    if args.timeout is not None:
        print("--timeout is deprecated and ignored in scripts/measure_verify.py", file=sys.stderr, flush=True)
    if args.skip_dashboard:
        print("--skip-dashboard requested; measurement step was skipped", file=sys.stderr, flush=True)
        return 0

    return run_command([
        sys.executable,
        "scripts/generate_verify_dashboard.py",
        "--keep-going",
        "--tle",
        str(args.tle),
        "-j",
        str(args.jobs),
        "--oj-jobs",
        str(args.oj_jobs),
        *args.paths,
    ])


if __name__ == "__main__":
    raise SystemExit(main())
