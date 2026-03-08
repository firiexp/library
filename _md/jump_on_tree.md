---
layout: post
title: Jump on Tree
date: 2026-03-08
category: 木
tags: 木
---

## 説明
木上の `k` 個先の頂点、LCA、祖先を doubling で求める。
前処理 `O(N log N)`、各クエリ `O(log N)`。

## できること
- `JumpOnTree jt(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  根 `root` で前処理する
- `int ancestor(int v, int k)`
  `v` の `k` 個上の祖先を返す。存在しなければ `-1`
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す
- `int dist(int u, int v)`
  `u` と `v` の距離を返す
- `int jump(int s, int t, int k)`
  `s` から `t` への最短路の `k` 番目の頂点を返す。存在しなければ `-1`

## 使い方
辺を張って `build(root)` を 1 回呼び、その後に `jump(s, t, k)` や `lca(u, v)` を使う。

```cpp
JumpOnTree jt(n);
for (auto [u, v] : edges) {
    jt.add_edge(u, v);
}
jt.build(0);

int x = jt.jump(s, t, k);
```

## 実装上の補足
`jump(s, t, k)` は `s -> lca(s, t)` 側と `lca(s, t) -> t` 側を分けて処理する。
