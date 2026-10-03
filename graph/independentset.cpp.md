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
    \ : (1ull << n) - 1; }\n    pair<int, ull> dfs(ull R, ull P, ull X) {\n      \
    \  if (!P && !X) {\n            return {__builtin_popcountll(R), R};\n       \
    \ }\n        if (!P) return {-1, 0};\n        pair<int, ull> res = {-1, 0};\n\
    \        int pivot = -1, max_neighbors = -1;\n        for (ull vertices = P |\
    \ X; vertices; vertices &= vertices - 1) {\n            int u = __builtin_ctzll(vertices);\n\
    \            int neighbors = __builtin_popcountll(P & G[u]);\n            if (neighbors\
    \ > max_neighbors) {\n                pivot = u;\n                max_neighbors\
    \ = neighbors;\n            }\n        }\n        ull z = P & ~G[pivot];\n   \
    \     while (z) {\n            int i = __builtin_ctzll(z);\n            z &= z\
    \ - 1;\n            res = max(res, dfs(R | (1ull << i), P & G[i], X & G[i]));\n\
    \            P ^= 1ull << i;\n            X |= 1ull << i;\n        }\n       \
    \ return res;\n    }\n\n\npublic:\n    explicit IndependentSet(int n): n(n), G(n)\
    \ {\n        for (int i = 0; i < n; ++i) {\n            G[i] = full_mask() ^ (1ull\
    \ << i);\n        }\n    }\n    void add_edge(int u, int v){\n        G[u] &=\
    \ ~(1ull << v);\n        G[v] &= ~(1ull << u);\n    }\n    pair<int, ull> maximum_independent_set()\
    \ {\n        return dfs(0, full_mask(), 0);\n    }\n};\n\n/**\n * @brief \u6700\
    \u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)\n */\n"
  code: "class IndependentSet {\n    int n;\n    vector<ull> G;\n    ull full_mask()\
    \ const { return n == 64 ? ~0ull : (1ull << n) - 1; }\n    pair<int, ull> dfs(ull\
    \ R, ull P, ull X) {\n        if (!P && !X) {\n            return {__builtin_popcountll(R),\
    \ R};\n        }\n        if (!P) return {-1, 0};\n        pair<int, ull> res\
    \ = {-1, 0};\n        int pivot = -1, max_neighbors = -1;\n        for (ull vertices\
    \ = P | X; vertices; vertices &= vertices - 1) {\n            int u = __builtin_ctzll(vertices);\n\
    \            int neighbors = __builtin_popcountll(P & G[u]);\n            if (neighbors\
    \ > max_neighbors) {\n                pivot = u;\n                max_neighbors\
    \ = neighbors;\n            }\n        }\n        ull z = P & ~G[pivot];\n   \
    \     while (z) {\n            int i = __builtin_ctzll(z);\n            z &= z\
    \ - 1;\n            res = max(res, dfs(R | (1ull << i), P & G[i], X & G[i]));\n\
    \            P ^= 1ull << i;\n            X |= 1ull << i;\n        }\n       \
    \ return res;\n    }\n\n\npublic:\n    explicit IndependentSet(int n): n(n), G(n)\
    \ {\n        for (int i = 0; i < n; ++i) {\n            G[i] = full_mask() ^ (1ull\
    \ << i);\n        }\n    }\n    void add_edge(int u, int v){\n        G[u] &=\
    \ ~(1ull << v);\n        G[v] &= ~(1ull << u);\n    }\n    pair<int, ull> maximum_independent_set()\
    \ {\n        return dfs(0, full_mask(), 0);\n    }\n};\n\n/**\n * @brief \u6700\
    \u5927\u72EC\u7ACB\u96C6\u5408(Maximum Independent Set)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/independentset.cpp
  requiredBy: []
  timestamp: '2026-10-03 14:43:28+09:00'
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
計算量は $O(3^{V/3})$ 。

## 実装上の補足
互いに辺で結ばれていない $V/3$ 個の三角形からなるグラフでは、$3^{V/3}$ 個の極大独立集合を列挙する。
