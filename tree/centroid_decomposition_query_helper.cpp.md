---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/range_contour_sum.cpp
    title: "\u6728\u306E\u9802\u70B9\u52A0\u7B97\u30FB\u8DDD\u96E2\u533A\u9593\u548C"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_range_contour_sum.test.cpp
    title: test/yosupo_aplusb_range_contour_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
    title: test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid\
      \ Query Helper)"
    links: []
  bundledCode: "#line 1 \"tree/centroid_decomposition_query_helper.cpp\"\nusing namespace\
    \ std;\n\nstruct CentroidDecompositionQueryHelper {\n    int n, root;\n    vector<vector<int>>\
    \ G, tree, path, dist;\n    vector<int> sz, parent, depth;\n    vector<char> used;\n\
    \n    explicit CentroidDecompositionQueryHelper(int n)\n        : n(n), root(-1),\
    \ G(n), tree(n), path(n), dist(n), sz(n), parent(n, -1), depth(n), used(n, 0)\
    \ {}\n\n    void add_edge(int u, int v) {\n        G[u].push_back(v);\n      \
    \  G[v].push_back(u);\n    }\n\n    int build(int start = 0) {\n        tree.assign(n,\
    \ {});\n        path.assign(n, {});\n        dist.assign(n, {});\n        fill(parent.begin(),\
    \ parent.end(), -1);\n        fill(depth.begin(), depth.end(), 0);\n        fill(used.begin(),\
    \ used.end(), 0);\n        dfs_parent.resize(n);\n        order.reserve(n);\n\
    \        if (n == 0) return root = -1;\n        return root = decompose(start,\
    \ -1, 0);\n    }\n\nprivate:\n    vector<int> dfs_parent, order;\n\n    int dfs_size(int\
    \ v, int p) {\n        order.clear();\n        order.push_back(v);\n        dfs_parent[v]\
    \ = p;\n        for (int i = 0; i < (int)order.size(); ++i) {\n            int\
    \ x = order[i];\n            sz[x] = 1;\n            for (int u : G[x]) {\n  \
    \              if (u == dfs_parent[x] || used[u]) continue;\n                dfs_parent[u]\
    \ = x;\n                order.push_back(u);\n            }\n        }\n      \
    \  for (int i = (int)order.size() - 1; i > 0; --i)\n            sz[dfs_parent[order[i]]]\
    \ += sz[order[i]];\n        return sz[v];\n    }\n\n    int find_centroid(int\
    \ v, int p, int half) {\n        while (true) {\n            int next = -1;\n\
    \            for (int u : G[v]) {\n                if (u != p && !used[u] && sz[u]\
    \ > half) {\n                    next = u;\n                    break;\n     \
    \           }\n            }\n            if (next == -1) return v;\n        \
    \    p = v;\n            v = next;\n        }\n    }\n\n    void collect(int v,\
    \ int p, int d, vector<pair<int, int>> &buf) {\n        buf.emplace_back(v, d);\n\
    \        dfs_parent[v] = p;\n        for (int i = 0; i < (int)buf.size(); ++i)\
    \ {\n            auto [x, distance] = buf[i];\n            for (int u : G[x])\
    \ {\n                if (u == dfs_parent[x] || used[u]) continue;\n          \
    \      dfs_parent[u] = x;\n                buf.emplace_back(u, distance + 1);\n\
    \            }\n        }\n    }\n\n    int decompose(int start, int p, int dep)\
    \ {\n        int centroid = find_centroid(start, -1, dfs_size(start, -1) / 2);\n\
    \        used[centroid] = 1;\n        parent[centroid] = p;\n        depth[centroid]\
    \ = dep;\n        path[centroid].push_back(centroid);\n        dist[centroid].push_back(0);\n\
    \        for (auto &&u : G[centroid]) {\n            if (used[u]) continue;\n\
    \            vector<pair<int, int>> buf;\n            collect(u, centroid, 1,\
    \ buf);\n            int child = decompose(u, centroid, dep + 1);\n          \
    \  tree[centroid].push_back(child);\n            for (auto &&[v, d] : buf) {\n\
    \                path[v].push_back(centroid);\n                dist[v].push_back(d);\n\
    \            }\n        }\n        return centroid;\n    }\n};\n\n/**\n * @brief\
    \ \u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid Query Helper)\n\
    \ */\n"
  code: "using namespace std;\n\nstruct CentroidDecompositionQueryHelper {\n    int\
    \ n, root;\n    vector<vector<int>> G, tree, path, dist;\n    vector<int> sz,\
    \ parent, depth;\n    vector<char> used;\n\n    explicit CentroidDecompositionQueryHelper(int\
    \ n)\n        : n(n), root(-1), G(n), tree(n), path(n), dist(n), sz(n), parent(n,\
    \ -1), depth(n), used(n, 0) {}\n\n    void add_edge(int u, int v) {\n        G[u].push_back(v);\n\
    \        G[v].push_back(u);\n    }\n\n    int build(int start = 0) {\n       \
    \ tree.assign(n, {});\n        path.assign(n, {});\n        dist.assign(n, {});\n\
    \        fill(parent.begin(), parent.end(), -1);\n        fill(depth.begin(),\
    \ depth.end(), 0);\n        fill(used.begin(), used.end(), 0);\n        dfs_parent.resize(n);\n\
    \        order.reserve(n);\n        if (n == 0) return root = -1;\n        return\
    \ root = decompose(start, -1, 0);\n    }\n\nprivate:\n    vector<int> dfs_parent,\
    \ order;\n\n    int dfs_size(int v, int p) {\n        order.clear();\n       \
    \ order.push_back(v);\n        dfs_parent[v] = p;\n        for (int i = 0; i <\
    \ (int)order.size(); ++i) {\n            int x = order[i];\n            sz[x]\
    \ = 1;\n            for (int u : G[x]) {\n                if (u == dfs_parent[x]\
    \ || used[u]) continue;\n                dfs_parent[u] = x;\n                order.push_back(u);\n\
    \            }\n        }\n        for (int i = (int)order.size() - 1; i > 0;\
    \ --i)\n            sz[dfs_parent[order[i]]] += sz[order[i]];\n        return\
    \ sz[v];\n    }\n\n    int find_centroid(int v, int p, int half) {\n        while\
    \ (true) {\n            int next = -1;\n            for (int u : G[v]) {\n   \
    \             if (u != p && !used[u] && sz[u] > half) {\n                    next\
    \ = u;\n                    break;\n                }\n            }\n       \
    \     if (next == -1) return v;\n            p = v;\n            v = next;\n \
    \       }\n    }\n\n    void collect(int v, int p, int d, vector<pair<int, int>>\
    \ &buf) {\n        buf.emplace_back(v, d);\n        dfs_parent[v] = p;\n     \
    \   for (int i = 0; i < (int)buf.size(); ++i) {\n            auto [x, distance]\
    \ = buf[i];\n            for (int u : G[x]) {\n                if (u == dfs_parent[x]\
    \ || used[u]) continue;\n                dfs_parent[u] = x;\n                buf.emplace_back(u,\
    \ distance + 1);\n            }\n        }\n    }\n\n    int decompose(int start,\
    \ int p, int dep) {\n        int centroid = find_centroid(start, -1, dfs_size(start,\
    \ -1) / 2);\n        used[centroid] = 1;\n        parent[centroid] = p;\n    \
    \    depth[centroid] = dep;\n        path[centroid].push_back(centroid);\n   \
    \     dist[centroid].push_back(0);\n        for (auto &&u : G[centroid]) {\n \
    \           if (used[u]) continue;\n            vector<pair<int, int>> buf;\n\
    \            collect(u, centroid, 1, buf);\n            int child = decompose(u,\
    \ centroid, dep + 1);\n            tree[centroid].push_back(child);\n        \
    \    for (auto &&[v, d] : buf) {\n                path[v].push_back(centroid);\n\
    \                dist[v].push_back(d);\n            }\n        }\n        return\
    \ centroid;\n    }\n};\n\n/**\n * @brief \u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\
    \u88DC\u52A9(Centroid Query Helper)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/centroid_decomposition_query_helper.cpp
  requiredBy:
  - tree/range_contour_sum.cpp
  timestamp: '2026-10-10 19:50:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_vertex_add_range_contour_sum_on_tree.test.cpp
  - test/yosupo_aplusb_range_contour_sum.test.cpp
date: 2026-03-11
documentation_of: tree/centroid_decomposition_query_helper.cpp
layout: document
tags: "\u6728"
title: "\u91CD\u5FC3\u5206\u89E3\u30AF\u30A8\u30EA\u88DC\u52A9(Centroid Query Helper)"
---

## 説明
重心分解の重心木と、各頂点から重心祖先への距離列を前計算する補助。
最近点距離、加点・集約系などの典型クエリで、そのままループを書き始めやすい形にする。

## できること
- `CentroidDecompositionQueryHelper cd(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `int build(int start = 0)`
  重心分解して重心木の根を返す

## 使い方
`build()` 後は `tree`、`parent`、`depth`、`path`、`dist` を参照する。

- `tree[c]`
  重心木での子重心
- `parent[c]`
  重心木での親重心。根なら `-1`
- `depth[c]`
  重心木での深さ
- `path[v][i]`
  頂点 `v` から見た `i` 番目の重心祖先。近い順に入る
- `dist[v][i]`
  頂点 `v` から `path[v][i]` までの距離

`path[v]` と `dist[v]` は同じ長さで、`path[v].back()` は重心木の根になる。
構築時間・領域は $O(N\log(N+1))$。元の木の走査は反復で行い、再帰の深さは重心木の $O(\log(N+1))$ に収まる。

## 例
最近点距離クエリは、重心ごとに最良値を持てば書ける。

```cpp
const int INF = 1e9;
vector<int> best(n, INF);

auto add = [&](int v) {
    for (int i = 0; i < (int)cd.path[v].size(); ++i) {
        best[cd.path[v][i]] = min(best[cd.path[v][i]], cd.dist[v][i]);
    }
};

auto query = [&](int v) {
    int ans = INF;
    for (int i = 0; i < (int)cd.path[v].size(); ++i) {
        ans = min(ans, best[cd.path[v][i]] + cd.dist[v][i]);
    }
    return ans;
};
```
