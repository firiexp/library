---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_minimum_vertex_cover.test.cpp
    title: test/yosupo_aplusb_minimum_vertex_cover.test.cpp
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
    \ l, r;\n    vector<pair<int, int>> edges;\n    vector<int> start, elist;\n  \
    \  vector<int> dist;\n    bool dirty = true;\n\n    void build_graph() {\n   \
    \     start.assign(l + 1, 0);\n        elist.assign(edges.size(), 0);\n      \
    \  for (auto &&[a, b] : edges) ++start[a + 1];\n        for (int i = 0; i < l;\
    \ ++i) start[i + 1] += start[i];\n        auto counter = start;\n        for (auto\
    \ &&[a, b] : edges) {\n            elist[counter[a]++] = b;\n        }\n    }\n\
    \npublic:\n    vector<int> match_left, match_right;\n\n    explicit HopcroftKarp(int\
    \ l, int r) : l(l), r(r), start(l + 1), dist(l), match_left(l, -1), match_right(r,\
    \ -1) {}\n\n    void add_edge(int a, int b) {\n        edges.emplace_back(a, b);\n\
    \        dirty = true;\n    }\n\n    bool bfs() {\n        queue<int> q;\n   \
    \     fill(dist.begin(), dist.end(), -1);\n        for (int i = 0; i < l; ++i)\
    \ {\n            if (match_left[i] != -1) continue;\n            dist[i] = 0;\n\
    \            q.push(i);\n        }\n        bool found = false;\n        while\
    \ (!q.empty()) {\n            int v = q.front();\n            q.pop();\n     \
    \       for (int ei = start[v]; ei < start[v + 1]; ++ei) {\n                int\
    \ to = elist[ei];\n                int u = match_right[to];\n                if\
    \ (u == -1) {\n                    found = true;\n                    continue;\n\
    \                }\n                if (dist[u] != -1) continue;\n           \
    \     dist[u] = dist[v] + 1;\n                q.push(u);\n            }\n    \
    \    }\n        return found;\n    }\n\n    bool dfs(int v) {\n        for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n            int to = elist[ei];\n\
    \            int u = match_right[to];\n            if (u != -1 && (dist[u] !=\
    \ dist[v] + 1 || !dfs(u))) continue;\n            match_left[v] = to;\n      \
    \      match_right[to] = v;\n            return true;\n        }\n        dist[v]\
    \ = -1;\n        return false;\n    }\n\n    int max_matching() {\n        int\
    \ ret = 0;\n        for (int v : match_left) if (v != -1) ++ret;\n        if (!dirty)\
    \ return ret;\n        build_graph();\n        while (bfs()) {\n            for\
    \ (int i = 0; i < l; ++i) {\n                if (match_left[i] == -1 && dfs(i))\
    \ ++ret;\n            }\n        }\n        dirty = false;\n        return ret;\n\
    \    }\n\n    pair<vector<int>, vector<int>> minimum_vertex_cover() {\n      \
    \  max_matching();\n        vector<char> seen_left(l), seen_right(r);\n      \
    \  queue<int> q;\n        for (int i = 0; i < l; ++i) {\n            if (match_left[i]\
    \ != -1) continue;\n            seen_left[i] = true;\n            q.push(i);\n\
    \        }\n        while (!q.empty()) {\n            int v = q.front();\n   \
    \         q.pop();\n            for (int ei = start[v]; ei < start[v + 1]; ++ei)\
    \ {\n                int to = elist[ei];\n                if (to == match_left[v]\
    \ || seen_right[to]) continue;\n                seen_right[to] = true;\n     \
    \           int u = match_right[to];\n                if (u != -1 && !seen_left[u])\
    \ {\n                    seen_left[u] = true;\n                    q.push(u);\n\
    \                }\n            }\n        }\n        vector<int> left, right;\n\
    \        for (int i = 0; i < l; ++i) if (!seen_left[i]) left.push_back(i);\n \
    \       for (int i = 0; i < r; ++i) if (seen_right[i]) right.push_back(i);\n \
    \       return {move(left), move(right)};\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> ret;\n        for (int i\
    \ = 0; i < l; ++i) {\n            if (match_left[i] != -1) ret.emplace_back(i,\
    \ match_left[i]);\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Hopcroft-Karp\u6CD5\n */\n"
  code: "class HopcroftKarp {\n    int l, r;\n    vector<pair<int, int>> edges;\n\
    \    vector<int> start, elist;\n    vector<int> dist;\n    bool dirty = true;\n\
    \n    void build_graph() {\n        start.assign(l + 1, 0);\n        elist.assign(edges.size(),\
    \ 0);\n        for (auto &&[a, b] : edges) ++start[a + 1];\n        for (int i\
    \ = 0; i < l; ++i) start[i + 1] += start[i];\n        auto counter = start;\n\
    \        for (auto &&[a, b] : edges) {\n            elist[counter[a]++] = b;\n\
    \        }\n    }\n\npublic:\n    vector<int> match_left, match_right;\n\n   \
    \ explicit HopcroftKarp(int l, int r) : l(l), r(r), start(l + 1), dist(l), match_left(l,\
    \ -1), match_right(r, -1) {}\n\n    void add_edge(int a, int b) {\n        edges.emplace_back(a,\
    \ b);\n        dirty = true;\n    }\n\n    bool bfs() {\n        queue<int> q;\n\
    \        fill(dist.begin(), dist.end(), -1);\n        for (int i = 0; i < l; ++i)\
    \ {\n            if (match_left[i] != -1) continue;\n            dist[i] = 0;\n\
    \            q.push(i);\n        }\n        bool found = false;\n        while\
    \ (!q.empty()) {\n            int v = q.front();\n            q.pop();\n     \
    \       for (int ei = start[v]; ei < start[v + 1]; ++ei) {\n                int\
    \ to = elist[ei];\n                int u = match_right[to];\n                if\
    \ (u == -1) {\n                    found = true;\n                    continue;\n\
    \                }\n                if (dist[u] != -1) continue;\n           \
    \     dist[u] = dist[v] + 1;\n                q.push(u);\n            }\n    \
    \    }\n        return found;\n    }\n\n    bool dfs(int v) {\n        for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n            int to = elist[ei];\n\
    \            int u = match_right[to];\n            if (u != -1 && (dist[u] !=\
    \ dist[v] + 1 || !dfs(u))) continue;\n            match_left[v] = to;\n      \
    \      match_right[to] = v;\n            return true;\n        }\n        dist[v]\
    \ = -1;\n        return false;\n    }\n\n    int max_matching() {\n        int\
    \ ret = 0;\n        for (int v : match_left) if (v != -1) ++ret;\n        if (!dirty)\
    \ return ret;\n        build_graph();\n        while (bfs()) {\n            for\
    \ (int i = 0; i < l; ++i) {\n                if (match_left[i] == -1 && dfs(i))\
    \ ++ret;\n            }\n        }\n        dirty = false;\n        return ret;\n\
    \    }\n\n    pair<vector<int>, vector<int>> minimum_vertex_cover() {\n      \
    \  max_matching();\n        vector<char> seen_left(l), seen_right(r);\n      \
    \  queue<int> q;\n        for (int i = 0; i < l; ++i) {\n            if (match_left[i]\
    \ != -1) continue;\n            seen_left[i] = true;\n            q.push(i);\n\
    \        }\n        while (!q.empty()) {\n            int v = q.front();\n   \
    \         q.pop();\n            for (int ei = start[v]; ei < start[v + 1]; ++ei)\
    \ {\n                int to = elist[ei];\n                if (to == match_left[v]\
    \ || seen_right[to]) continue;\n                seen_right[to] = true;\n     \
    \           int u = match_right[to];\n                if (u != -1 && !seen_left[u])\
    \ {\n                    seen_left[u] = true;\n                    q.push(u);\n\
    \                }\n            }\n        }\n        vector<int> left, right;\n\
    \        for (int i = 0; i < l; ++i) if (!seen_left[i]) left.push_back(i);\n \
    \       for (int i = 0; i < r; ++i) if (seen_right[i]) right.push_back(i);\n \
    \       return {move(left), move(right)};\n    }\n\n    vector<pair<int, int>>\
    \ get_pairs() const {\n        vector<pair<int, int>> ret;\n        for (int i\
    \ = 0; i < l; ++i) {\n            if (match_left[i] != -1) ret.emplace_back(i,\
    \ match_left[i]);\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Hopcroft-Karp\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/hopcroft_karp.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:51:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_bipartitematching_hopcroft_karp.test.cpp
  - test/yosupo_aplusb_minimum_vertex_cover.test.cpp
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
- `pair<vector<int>, vector<int>> minimum_vertex_cover()`
  最小頂点被覆の左・右それぞれの頂点番号列を返す。番号は 0-indexed。必要なら内部で最大マッチングを更新する

## 使い方
辺をすべて追加してから `max_matching()` を呼ぶ。
マッチ先は `match_left` と `match_right` に入り、必要なら `get_pairs()` で列挙できる。
最小頂点被覆は辺の追加後に `minimum_vertex_cover()` を呼ぶ。繰り返し取得でき、事前の `max_matching()` は不要。

## 実装上の補足
左側だけに BFS/DFS の層グラフを持つ標準的な Hopcroft-Karp 法。
最大マッチング計算後の最小頂点被覆の抽出は $O(L + R + M)$、作業領域は $O(L + R)$。
