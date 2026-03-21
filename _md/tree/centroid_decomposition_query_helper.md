---
title: 重心分解クエリ補助(Centroid Query Helper)
documentation_of: //tree/centroid_decomposition_query_helper.cpp
date: 2026-03-11
category: 木
tags: 木
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
