#!/usr/bin/env python3

from __future__ import annotations

import argparse
import os
from pathlib import Path
import shlex
import subprocess
import tempfile


ROOT = Path(__file__).resolve().parents[1]
PRELUDE = '''#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using uint = unsigned;
using ull = unsigned long long;
template<class T> constexpr T INF = numeric_limits<T>::max() / 32 * 15 + 208;
'''
PAIRS = (
    ("graph/dijkstra.cpp", "graph/bfs01.cpp"),
    ("graph/dijkstra.cpp", "graph/bellman_ford.cpp"),
    ("graph/SCC.cpp", "graph/twosat.cpp"),
    ("tree/hld.cpp", "tree/hld_edge.cpp"),
    ("graph/biconnected_components.cpp", "graph/block_cut_tree.cpp"),
    ("tree/auxtree.cpp", "tree/virtual_tree_helper.cpp"),
)


def main() -> int:
    parser = argparse.ArgumentParser(description="Compile library include pairs in both orders as separate translation units.")
    parser.add_argument("--cxx", default=os.environ.get("CXX", "g++"), help="C++ compiler command")
    parser.add_argument("--list", action="store_true", help="list include orders without compiling")
    args = parser.parse_args()
    orders = [order for pair in PAIRS for order in (pair, pair[::-1])]
    if args.list:
        for first, second in orders:
            print(f"{first} -> {second}")
        return 0
    failed = 0
    with tempfile.TemporaryDirectory(prefix="check-library-composition-") as directory:
        source = Path(directory) / "composition.cpp"
        for first, second in orders:
            source.write_text(PRELUDE + f'#include "{first}"\n#include "{second}"\nint main() {{}}\n')
            command = shlex.split(args.cxx) + ["-std=c++17", "-fsyntax-only", "-I", str(ROOT), str(source)]
            result = subprocess.run(command, capture_output=True, text=True)
            if result.returncode:
                failed += 1
                print(f"failed: {first} -> {second}\n{result.stderr}", flush=True)
            else:
                print(f"ok: {first} -> {second}", flush=True)
    print(f"library composition: {len(orders) - failed} passed, {failed} failed")
    return int(failed != 0)


if __name__ == "__main__":
    raise SystemExit(main())
