#!/usr/bin/env python3

from __future__ import annotations

import argparse
import pathlib
import sys

ROOT = pathlib.Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / '.scripts'))
from verification_impl import STATE, resolve, select, test_paths, verify, write_json


def main():
    parser = argparse.ArgumentParser(description='Resolve and run competitive-verifier, including untracked C++ tests.')
    parser.add_argument('paths', nargs='*', help='test paths; omit to verify all tests')
    parser.add_argument('-j', '--jobs', type=int, default=8, help='parallel test processes')
    parser.add_argument('--tle', type=float, default=60)
    parser.add_argument('--no-download', action='store_true', help='require existing testcase caches')
    parser.add_argument('--force', action='store_true', help='rerun successful unchanged tests')
    parser.add_argument('--resolve-only', action='store_true')
    parser.add_argument('--list', action='store_true')
    parser.add_argument('--split', type=int, default=1)
    parser.add_argument('--split-index', type=int, default=0)
    parser.add_argument('--result', type=pathlib.Path, default=STATE / 'result.json')
    args = parser.parse_args()
    if args.jobs < 1 or args.tle <= 0 or args.split < 1 or not 0 <= args.split_index < args.split:
        parser.error('jobs, tle and split must be positive; split-index must be in [0, split)')
    resolved = resolve(args.jobs, tle=args.tle)
    write_json(STATE / 'verify-files.json', resolved)
    paths = test_paths(resolved)
    if args.paths:
        requested = {str(pathlib.Path(path).resolve().relative_to(ROOT)) for path in args.paths}
        unknown = requested - set(paths)
        if unknown:
            parser.error(f'unknown test paths: {sorted(unknown)}')
        paths = sorted(requested)
    paths = paths[args.split_index::args.split]
    print(f'selected {len(paths)} verification tests', flush=True)
    if args.list:
        print('\n'.join(paths))
    if args.list or args.resolve_only:
        return 0
    return verify(select(resolved, paths), output=args.result, jobs=args.jobs,
                  previous=args.result, no_download=args.no_download, force=args.force)


if __name__ == '__main__':
    raise SystemExit(main())
