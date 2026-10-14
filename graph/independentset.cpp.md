---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_independent_set_boundaries.test.cpp
    title: test/yosupo_aplusb_independent_set_boundaries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_maximum_independent_set.test.cpp
    title: test/yosupo_maximum_independent_set.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)"
    links: []
  bundledCode: "#line 1 \"graph/independentset.cpp\"\nclass IndependentSet {\n   \
    \ int n;\n    vector<ull> G;\n    ull full_mask() const { return n == 64 ? ~0ull\
    \ : (1ull << n) - 1; }\n    int color_bound(ull vertices) const {\n        int\
    \ colors = 0;\n        while (vertices) {\n            ++colors;\n           \
    \ ull available = vertices;\n            while (available) {\n               \
    \ int v = 63 - __builtin_clzll(available);\n                ull bit = 1ull <<\
    \ v;\n                vertices &= ~bit;\n                available &= ~bit & ~G[v];\n\
    \            }\n        }\n        return colors;\n    }\n    void dfs(ull R,\
    \ ull P, ull X, pair<int, ull> &best) {\n        if (!P && !X) {\n           \
    \ best = max(best, pair<int, ull>{__builtin_popcountll(R), R});\n            return;\n\
    \        }\n        if (!P) return;\n        int bound = __builtin_popcountll(R)\
    \ + color_bound(P);\n        if (bound < best.first || (bound == best.first &&\
    \ (R | P) <= best.second)) return;\n        int pivot = -1, max_neighbors = -1;\n\
    \        for (ull vertices = P | X; vertices; vertices &= vertices - 1) {\n  \
    \          int u = __builtin_ctzll(vertices);\n            int neighbors = __builtin_popcountll(P\
    \ & G[u]);\n            if (neighbors >= max_neighbors) {\n                pivot\
    \ = u;\n                max_neighbors = neighbors;\n            }\n        }\n\
    \        ull z = P & ~G[pivot];\n        while (z) {\n            int i = 63 -\
    \ __builtin_clzll(z);\n            z &= ~(1ull << i);\n            dfs(R | (1ull\
    \ << i), P & G[i], X & G[i], best);\n            P ^= 1ull << i;\n           \
    \ X |= 1ull << i;\n        }\n    }\n\n\npublic:\n    explicit IndependentSet(int\
    \ n): n(n), G(n) {\n        for (int i = 0; i < n; ++i) {\n            G[i] =\
    \ full_mask() ^ (1ull << i);\n        }\n    }\n    void add_edge(int u, int v){\n\
    \        G[u] &= ~(1ull << v);\n        G[v] &= ~(1ull << u);\n    }\n    pair<int,\
    \ ull> maximum_independent_set() {\n        pair<int, ull> best = {-1, 0};\n \
    \       dfs(0, full_mask(), 0, best);\n        return best;\n    }\n};\n\n/**\n\
    \ * @brief \u6700\u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)\n */\n"
  code: "class IndependentSet {\n    int n;\n    vector<ull> G;\n    ull full_mask()\
    \ const { return n == 64 ? ~0ull : (1ull << n) - 1; }\n    int color_bound(ull\
    \ vertices) const {\n        int colors = 0;\n        while (vertices) {\n   \
    \         ++colors;\n            ull available = vertices;\n            while\
    \ (available) {\n                int v = 63 - __builtin_clzll(available);\n  \
    \              ull bit = 1ull << v;\n                vertices &= ~bit;\n     \
    \           available &= ~bit & ~G[v];\n            }\n        }\n        return\
    \ colors;\n    }\n    void dfs(ull R, ull P, ull X, pair<int, ull> &best) {\n\
    \        if (!P && !X) {\n            best = max(best, pair<int, ull>{__builtin_popcountll(R),\
    \ R});\n            return;\n        }\n        if (!P) return;\n        int bound\
    \ = __builtin_popcountll(R) + color_bound(P);\n        if (bound < best.first\
    \ || (bound == best.first && (R | P) <= best.second)) return;\n        int pivot\
    \ = -1, max_neighbors = -1;\n        for (ull vertices = P | X; vertices; vertices\
    \ &= vertices - 1) {\n            int u = __builtin_ctzll(vertices);\n       \
    \     int neighbors = __builtin_popcountll(P & G[u]);\n            if (neighbors\
    \ >= max_neighbors) {\n                pivot = u;\n                max_neighbors\
    \ = neighbors;\n            }\n        }\n        ull z = P & ~G[pivot];\n   \
    \     while (z) {\n            int i = 63 - __builtin_clzll(z);\n            z\
    \ &= ~(1ull << i);\n            dfs(R | (1ull << i), P & G[i], X & G[i], best);\n\
    \            P ^= 1ull << i;\n            X |= 1ull << i;\n        }\n    }\n\n\
    \npublic:\n    explicit IndependentSet(int n): n(n), G(n) {\n        for (int\
    \ i = 0; i < n; ++i) {\n            G[i] = full_mask() ^ (1ull << i);\n      \
    \  }\n    }\n    void add_edge(int u, int v){\n        G[u] &= ~(1ull << v);\n\
    \        G[v] &= ~(1ull << u);\n    }\n    pair<int, ull> maximum_independent_set()\
    \ {\n        pair<int, ull> best = {-1, 0};\n        dfs(0, full_mask(), 0, best);\n\
    \        return best;\n    }\n};\n\n/**\n * @brief \u6700\u5927\u72EC\u7ACB\u96C6\
    \u5408(Maximum Independent Set)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/independentset.cpp
  requiredBy: []
  timestamp: '2026-10-14 20:34:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_maximum_independent_set.test.cpp
  - test/yosupo_aplusb_independent_set_boundaries.test.cpp
date: 2018-04-28
documentation_of: graph/independentset.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u6700\u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)"
---

## 説明
グラフの最大独立集合（補グラフの最大クリーク）を求める。
頂点数は $0\le V\le64$。補グラフの候補を貪欲彩色し、現在の最良解を改善できない枝を省く。

## できること
- `IndependentSet(n)`：辺のない $n$ 頂点グラフを作る
- `add_edge(u, v)`：異なる2頂点の間に無向辺を追加する
- `maximum_independent_set()`：最大サイズと頂点の bitmask を返す。同じサイズなら最大の mask を返す。空グラフは `(0, 0)`

## 使い方
辺を追加して `maximum_independent_set()` を呼ぶ。再実行や辺追加後の呼び直しもできる。

## 実装上の補足
Bron–Kerbosch 法の pivot を使う。補グラフの色数は、残りのクリークサイズの上界になる。
同サイズの解が残るときは、候補全体の mask も比較して tie-break を保つ。
三角形を並べたグラフなどで不要な極大解の列挙を減らすが、最悪時の指数時間は残る。
各部分集合は高々1回探索され、彩色と pivot 選択を含む保守的な時間上界は $O(V^2 2^V)$、領域は $O(V)$。
探索がもともと短い入力では、彩色の追加費用により遅くなる場合がある。
