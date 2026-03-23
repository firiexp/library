---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_cycle_detection_undirected.test.cpp
    title: test/yosupo_cycle_detection_undirected.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7121\u5411\u9589\u8DEF\u691C\u51FA(Undirected Cycle Detection)"
    links: []
  bundledCode: "#line 1 \"graph/cycle_detection_undirected.cpp\"\nstruct CycleDetectionUndirectedResult\
    \ {\n    vector<int> vertices;\n    vector<int> edge_ids;\n};\n\nCycleDetectionUndirectedResult\
    \ cycle_detection_undirected(const vector<pair<int, int>> &edges, int n) {\n \
    \   int m = edges.size();\n    vector<vector<pair<int, int>>> g(n);\n    for (int\
    \ i = 0; i < m; ++i) {\n        auto [u, v] = edges[i];\n        g[u].push_back({v,\
    \ i});\n        g[v].push_back({u, i});\n    }\n\n    vector<int> dep(n, -1),\
    \ par_v(n, -1), par_e(n, -1);\n    vector<char> used_e(m, 0);\n    auto dfs =\
    \ [&](auto &&self, int v, int d) -> void {\n        dep[v] = d;\n        for (auto\
    \ &&[to, id] : g[v]) {\n            if (dep[to] != -1) continue;\n           \
    \ used_e[id] = 1;\n            par_v[to] = v;\n            par_e[to] = id;\n \
    \           self(self, to, d + 1);\n        }\n    };\n    for (int i = 0; i <\
    \ n; ++i) {\n        if (dep[i] == -1) dfs(dfs, i, 0);\n    }\n\n    for (int\
    \ id = 0; id < m; ++id) {\n        if (used_e[id]) continue;\n        auto [a,\
    \ b] = edges[id];\n        if (dep[a] > dep[b]) swap(a, b);\n        vector<int>\
    \ vs = {b}, es;\n        while (vs.back() != a) {\n            es.emplace_back(par_e[vs.back()]);\n\
    \            vs.emplace_back(par_v[vs.back()]);\n        }\n        es.emplace_back(id);\n\
    \        return {vs, es};\n    }\n    return {{}, {}};\n}\n\n/**\n * @brief \u7121\
    \u5411\u9589\u8DEF\u691C\u51FA(Undirected Cycle Detection)\n */\n"
  code: "struct CycleDetectionUndirectedResult {\n    vector<int> vertices;\n    vector<int>\
    \ edge_ids;\n};\n\nCycleDetectionUndirectedResult cycle_detection_undirected(const\
    \ vector<pair<int, int>> &edges, int n) {\n    int m = edges.size();\n    vector<vector<pair<int,\
    \ int>>> g(n);\n    for (int i = 0; i < m; ++i) {\n        auto [u, v] = edges[i];\n\
    \        g[u].push_back({v, i});\n        g[v].push_back({u, i});\n    }\n\n \
    \   vector<int> dep(n, -1), par_v(n, -1), par_e(n, -1);\n    vector<char> used_e(m,\
    \ 0);\n    auto dfs = [&](auto &&self, int v, int d) -> void {\n        dep[v]\
    \ = d;\n        for (auto &&[to, id] : g[v]) {\n            if (dep[to] != -1)\
    \ continue;\n            used_e[id] = 1;\n            par_v[to] = v;\n       \
    \     par_e[to] = id;\n            self(self, to, d + 1);\n        }\n    };\n\
    \    for (int i = 0; i < n; ++i) {\n        if (dep[i] == -1) dfs(dfs, i, 0);\n\
    \    }\n\n    for (int id = 0; id < m; ++id) {\n        if (used_e[id]) continue;\n\
    \        auto [a, b] = edges[id];\n        if (dep[a] > dep[b]) swap(a, b);\n\
    \        vector<int> vs = {b}, es;\n        while (vs.back() != a) {\n       \
    \     es.emplace_back(par_e[vs.back()]);\n            vs.emplace_back(par_v[vs.back()]);\n\
    \        }\n        es.emplace_back(id);\n        return {vs, es};\n    }\n  \
    \  return {{}, {}};\n}\n\n/**\n * @brief \u7121\u5411\u9589\u8DEF\u691C\u51FA\
    (Undirected Cycle Detection)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/cycle_detection_undirected.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_cycle_detection_undirected.test.cpp
date: 2026-03-08
documentation_of: graph/cycle_detection_undirected.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: Cycle Detection Undirected
---

## 説明
無向グラフから 1 つサイクルを見つける。
多重辺を含んでもよい。
計算量は $O(N + M)$。

## できること
- `CycleDetectionUndirectedResult cycle_detection_undirected(const vector<pair<int, int>>& edges, int n)`
  サイクルの頂点列と辺番号列を返す。存在しなければ両方空配列を返す

## 使い方
`edges[i] = {u, v}` を渡す。
返る `vertices` と `edge_ids` は同じ長さで、`edge_ids[i]` が `vertices[i]` と次の頂点を結ぶ。
