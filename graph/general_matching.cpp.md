---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_general_matching.test.cpp
    title: test/yosupo_general_matching.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\
      \u30B0(General Matching)"
    links: []
  bundledCode: "#line 1 \"graph/general_matching.cpp\"\nclass GeneralMatching {\n\
    \    int n;\n    vector<vector<int>> g;\n    vector<int> match, parent, base,\
    \ q;\n    vector<bool> used, blossom;\n\n    int lca(int a, int b) {\n       \
    \ vector<bool> seen(n, false);\n        while (true) {\n            a = base[a];\n\
    \            seen[a] = true;\n            if (match[a] == -1) break;\n       \
    \     a = parent[match[a]];\n        }\n        while (true) {\n            b\
    \ = base[b];\n            if (seen[b]) return b;\n            if (match[b] ==\
    \ -1) break;\n            b = parent[match[b]];\n        }\n        return -1;\n\
    \    }\n\n    void mark_path(int v, int b, int child) {\n        while (base[v]\
    \ != b) {\n            blossom[base[v]] = blossom[base[match[v]]] = true;\n  \
    \          parent[v] = child;\n            child = match[v];\n            v =\
    \ parent[match[v]];\n        }\n    }\n\n    int find_path(int root) {\n     \
    \   fill(used.begin(), used.end(), false);\n        fill(parent.begin(), parent.end(),\
    \ -1);\n        for (int i = 0; i < n; ++i) base[i] = i;\n        int head = 0,\
    \ tail = 0;\n        q[tail++] = root;\n        used[root] = true;\n        while\
    \ (head < tail) {\n            int v = q[head++];\n            for (int to : g[v])\
    \ {\n                if (base[v] == base[to] || match[v] == to) continue;\n  \
    \              if (to == root || (match[to] != -1 && parent[match[to]] != -1))\
    \ {\n                    int cur = lca(v, to);\n                    fill(blossom.begin(),\
    \ blossom.end(), false);\n                    mark_path(v, cur, to);\n       \
    \             mark_path(to, cur, v);\n                    for (int i = 0; i <\
    \ n; ++i) {\n                        if (!blossom[base[i]]) continue;\n      \
    \                  base[i] = cur;\n                        if (used[i]) continue;\n\
    \                        used[i] = true;\n                        q[tail++] =\
    \ i;\n                    }\n                } else if (parent[to] == -1) {\n\
    \                    parent[to] = v;\n                    if (match[to] == -1)\
    \ return to;\n                    int u = match[to];\n                    used[u]\
    \ = true;\n                    q[tail++] = u;\n                }\n           \
    \ }\n        }\n        return -1;\n    }\n\npublic:\n    explicit GeneralMatching(int\
    \ n)\n        : n(n), g(n), match(n, -1), parent(n), base(n), q(n), used(n), blossom(n)\
    \ {}\n\n    void add_edge(int u, int v) {\n        g[u].push_back(v);\n      \
    \  g[v].push_back(u);\n    }\n\n    int max_matching() {\n        int res = 0;\n\
    \        for (int i = 0; i < n; ++i) {\n            if (match[i] != -1) continue;\n\
    \            int v = find_path(i);\n            if (v == -1) continue;\n     \
    \       ++res;\n            while (v != -1) {\n                int pv = parent[v];\n\
    \                int nv = pv == -1 ? -1 : match[pv];\n                match[v]\
    \ = pv;\n                if (pv != -1) match[pv] = v;\n                v = nv;\n\
    \            }\n        }\n        return res;\n    }\n\n    const vector<int>&\
    \ get_match() const {\n        return match;\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> res;\n        for (int i\
    \ = 0; i < n; ++i) {\n            if (match[i] == -1 || i > match[i]) continue;\n\
    \            res.emplace_back(i, match[i]);\n        }\n        return res;\n\
    \    }\n};\n\n/**\n * @brief \u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\
    \u30C1\u30F3\u30B0(General Matching)\n */\n"
  code: "class GeneralMatching {\n    int n;\n    vector<vector<int>> g;\n    vector<int>\
    \ match, parent, base, q;\n    vector<bool> used, blossom;\n\n    int lca(int\
    \ a, int b) {\n        vector<bool> seen(n, false);\n        while (true) {\n\
    \            a = base[a];\n            seen[a] = true;\n            if (match[a]\
    \ == -1) break;\n            a = parent[match[a]];\n        }\n        while (true)\
    \ {\n            b = base[b];\n            if (seen[b]) return b;\n          \
    \  if (match[b] == -1) break;\n            b = parent[match[b]];\n        }\n\
    \        return -1;\n    }\n\n    void mark_path(int v, int b, int child) {\n\
    \        while (base[v] != b) {\n            blossom[base[v]] = blossom[base[match[v]]]\
    \ = true;\n            parent[v] = child;\n            child = match[v];\n   \
    \         v = parent[match[v]];\n        }\n    }\n\n    int find_path(int root)\
    \ {\n        fill(used.begin(), used.end(), false);\n        fill(parent.begin(),\
    \ parent.end(), -1);\n        for (int i = 0; i < n; ++i) base[i] = i;\n     \
    \   int head = 0, tail = 0;\n        q[tail++] = root;\n        used[root] = true;\n\
    \        while (head < tail) {\n            int v = q[head++];\n            for\
    \ (int to : g[v]) {\n                if (base[v] == base[to] || match[v] == to)\
    \ continue;\n                if (to == root || (match[to] != -1 && parent[match[to]]\
    \ != -1)) {\n                    int cur = lca(v, to);\n                    fill(blossom.begin(),\
    \ blossom.end(), false);\n                    mark_path(v, cur, to);\n       \
    \             mark_path(to, cur, v);\n                    for (int i = 0; i <\
    \ n; ++i) {\n                        if (!blossom[base[i]]) continue;\n      \
    \                  base[i] = cur;\n                        if (used[i]) continue;\n\
    \                        used[i] = true;\n                        q[tail++] =\
    \ i;\n                    }\n                } else if (parent[to] == -1) {\n\
    \                    parent[to] = v;\n                    if (match[to] == -1)\
    \ return to;\n                    int u = match[to];\n                    used[u]\
    \ = true;\n                    q[tail++] = u;\n                }\n           \
    \ }\n        }\n        return -1;\n    }\n\npublic:\n    explicit GeneralMatching(int\
    \ n)\n        : n(n), g(n), match(n, -1), parent(n), base(n), q(n), used(n), blossom(n)\
    \ {}\n\n    void add_edge(int u, int v) {\n        g[u].push_back(v);\n      \
    \  g[v].push_back(u);\n    }\n\n    int max_matching() {\n        int res = 0;\n\
    \        for (int i = 0; i < n; ++i) {\n            if (match[i] != -1) continue;\n\
    \            int v = find_path(i);\n            if (v == -1) continue;\n     \
    \       ++res;\n            while (v != -1) {\n                int pv = parent[v];\n\
    \                int nv = pv == -1 ? -1 : match[pv];\n                match[v]\
    \ = pv;\n                if (pv != -1) match[pv] = v;\n                v = nv;\n\
    \            }\n        }\n        return res;\n    }\n\n    const vector<int>&\
    \ get_match() const {\n        return match;\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> res;\n        for (int i\
    \ = 0; i < n; ++i) {\n            if (match[i] == -1 || i > match[i]) continue;\n\
    \            res.emplace_back(i, match[i]);\n        }\n        return res;\n\
    \    }\n};\n\n/**\n * @brief \u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\
    \u30C1\u30F3\u30B0(General Matching)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/general_matching.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_general_matching.test.cpp
date: 2026-03-08
documentation_of: graph/general_matching.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u4E00\u822C\u30B0\u30E9\u30D5\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0(General\
  \ Matching)"
---

## 説明
Edmonds blossom による一般グラフの最大マッチング。
多重辺なし無向グラフに対して、最大本数のマッチングを $O(N^3)$ で求める。

## できること
- `GeneralMatching gm(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int u, int v)`
  無向辺 `u - v` を追加する
- `int max_matching()`
  最大マッチング数を返す
- `const vector<int>& get_match() const`
  `match[v]` を返す。未マッチなら `-1`
- `vector<pair<int, int>> get_pairs() const`
  マッチした辺集合を返す

## 使い方
辺を追加してから `max_matching()` を 1 回呼ぶ。
答えの組は `get_pairs()` で取れる。

## 実装上の補足
花の縮約を BFS 上で処理する典型実装。
`get_pairs()` は各辺を 1 回だけ返す。
