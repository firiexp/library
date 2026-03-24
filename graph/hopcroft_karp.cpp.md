---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bipartitematching_hopcroft_karp.test.cpp
    title: test/yosupo_bipartitematching_hopcroft_karp.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Hopcroft-Karp\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/hopcroft_karp.cpp\"\nclass HopcroftKarp {\n    int\
    \ l, r;\n    vector<vector<int>> g;\n    vector<int> dist;\n\npublic:\n    vector<int>\
    \ match_left, match_right;\n\n    explicit HopcroftKarp(int l, int r) : l(l),\
    \ r(r), g(l), dist(l), match_left(l, -1), match_right(r, -1) {}\n\n    void add_edge(int\
    \ a, int b) {\n        g[a].push_back(b);\n    }\n\n    bool bfs() {\n       \
    \ queue<int> q;\n        fill(dist.begin(), dist.end(), -1);\n        for (int\
    \ i = 0; i < l; ++i) {\n            if (match_left[i] != -1) continue;\n     \
    \       dist[i] = 0;\n            q.push(i);\n        }\n        bool found =\
    \ false;\n        while (!q.empty()) {\n            int v = q.front();\n     \
    \       q.pop();\n            for (int to : g[v]) {\n                int u = match_right[to];\n\
    \                if (u == -1) {\n                    found = true;\n         \
    \           continue;\n                }\n                if (dist[u] != -1) continue;\n\
    \                dist[u] = dist[v] + 1;\n                q.push(u);\n        \
    \    }\n        }\n        return found;\n    }\n\n    bool dfs(int v) {\n   \
    \     for (int to : g[v]) {\n            int u = match_right[to];\n          \
    \  if (u != -1 && (dist[u] != dist[v] + 1 || !dfs(u))) continue;\n           \
    \ match_left[v] = to;\n            match_right[to] = v;\n            return true;\n\
    \        }\n        dist[v] = -1;\n        return false;\n    }\n\n    int max_matching()\
    \ {\n        int ret = 0;\n        while (bfs()) {\n            for (int i = 0;\
    \ i < l; ++i) {\n                if (match_left[i] == -1 && dfs(i)) ++ret;\n \
    \           }\n        }\n        return ret;\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> ret;\n        for (int i\
    \ = 0; i < l; ++i) {\n            if (match_left[i] != -1) ret.emplace_back(i,\
    \ match_left[i]);\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Hopcroft-Karp\u6CD5\n */\n"
  code: "class HopcroftKarp {\n    int l, r;\n    vector<vector<int>> g;\n    vector<int>\
    \ dist;\n\npublic:\n    vector<int> match_left, match_right;\n\n    explicit HopcroftKarp(int\
    \ l, int r) : l(l), r(r), g(l), dist(l), match_left(l, -1), match_right(r, -1)\
    \ {}\n\n    void add_edge(int a, int b) {\n        g[a].push_back(b);\n    }\n\
    \n    bool bfs() {\n        queue<int> q;\n        fill(dist.begin(), dist.end(),\
    \ -1);\n        for (int i = 0; i < l; ++i) {\n            if (match_left[i] !=\
    \ -1) continue;\n            dist[i] = 0;\n            q.push(i);\n        }\n\
    \        bool found = false;\n        while (!q.empty()) {\n            int v\
    \ = q.front();\n            q.pop();\n            for (int to : g[v]) {\n    \
    \            int u = match_right[to];\n                if (u == -1) {\n      \
    \              found = true;\n                    continue;\n                }\n\
    \                if (dist[u] != -1) continue;\n                dist[u] = dist[v]\
    \ + 1;\n                q.push(u);\n            }\n        }\n        return found;\n\
    \    }\n\n    bool dfs(int v) {\n        for (int to : g[v]) {\n            int\
    \ u = match_right[to];\n            if (u != -1 && (dist[u] != dist[v] + 1 ||\
    \ !dfs(u))) continue;\n            match_left[v] = to;\n            match_right[to]\
    \ = v;\n            return true;\n        }\n        dist[v] = -1;\n        return\
    \ false;\n    }\n\n    int max_matching() {\n        int ret = 0;\n        while\
    \ (bfs()) {\n            for (int i = 0; i < l; ++i) {\n                if (match_left[i]\
    \ == -1 && dfs(i)) ++ret;\n            }\n        }\n        return ret;\n   \
    \ }\n\n    vector<pair<int, int>> get_pairs() const {\n        vector<pair<int,\
    \ int>> ret;\n        for (int i = 0; i < l; ++i) {\n            if (match_left[i]\
    \ != -1) ret.emplace_back(i, match_left[i]);\n        }\n        return ret;\n\
    \    }\n};\n\n/**\n * @brief Hopcroft-Karp\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/hopcroft_karp.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_bipartitematching_hopcroft_karp.test.cpp
date: 2026-03-08
documentation_of: graph/hopcroft_karp.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "Hopcroft-Karp\u6CD5"
---

## 説明
二部グラフの最大マッチングを Hopcroft-Karp 法で求める。
左頂点数を `L`、右頂点数を `R`、辺数を `M` とすると計算量は $O(M sqrt(L + R))$。

## できること
- `HopcroftKarp hk(l, r)`
  左 `l` 頂点、右 `r` 頂点の二部グラフを作る
- `void add_edge(int a, int b)`
  左 `a` と右 `b` の間に辺を追加する
- `int max_matching()`
  最大マッチング数を返す
- `vector<pair<int, int>> get_pairs()`
  現在のマッチングを `(左, 右)` の列で返す

## 使い方
辺をすべて追加してから `max_matching()` を呼ぶ。
マッチ先は `match_left` と `match_right` に入り、必要なら `get_pairs()` で列挙できる。

## 実装上の補足
左側だけに BFS/DFS の層グラフを持つ標準的な Hopcroft-Karp 法。
