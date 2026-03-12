#!/usr/bin/env python3

from __future__ import annotations

import pathlib
import subprocess
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent


def main() -> int:
    print(
        "scripts/run_verify.py is deprecated; use scripts/measure_verify.py",
        file=sys.stderr,
        flush=True,
    )
    completed = subprocess.run(
        [sys.executable, "scripts/measure_verify.py", *sys.argv[1:]],
        cwd=ROOT,
        check=False,
    )
    return completed.returncode


if __name__ == "__main__":
    raise SystemExit(main())
