---
category: "\u6728"
date: 2026-03-08
layout: post
tags: "\u6728"
title: HLD Edge
---

## 説明
辺を子頂点側の位置に載せる重軽分解である。
根の位置には辺がないので、`edge_index(root)` は `-1` を返す。
パスクエリ・パス更新は `O(log^2 N)`。

## できること
- `HeavyLightDecompositionEdge hld(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(vector<int> roots = {0})`
  前処理をする。森にも対応する
- `int edge_index(int v)`
  `parent(v) - v` の辺が載る位置を返す。根なら `-1`
- `pair<int, int> subtree(int v)`
  部分木の辺集合に対応する半開区間 `[l, r)` を返す
- `void path(int u, int v, F f)`
  `u - v` パス上の辺を被覆する各区間へ `f(l, r)` を呼ぶ
- `T path_query(int u, int v, T e, Q q, F f)`
  可換向け辺パスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f)`
  非可換向け順序付き辺パスクエリ
- `void apply_subtree(int v, F f)`
  部分木の辺区間へ `f(l, r)` を呼ぶ
- `T subtree_query(int v, Q q)`
  部分木の辺区間クエリ

## 使い方
各辺の値は子頂点側に置く。
`parent(v) - v` の辺を更新したいときは `edge_index(v)` を使う。
パス順序が必要なときは `path_query_ordered` を使う。

```cpp
HeavyLightDecompositionEdge hld(n);
hld.add_edge(u, v);
hld.build();

int p = hld.edge_index(v);
seg.update(p, x);

auto ans = hld.path_query_ordered(a, b, Monoid::e(), ql, qr, Monoid::f);
```

## 実装上の補足
内部では頂点版 HLD の `edge = true` を使っている。
`subtree(v)` は `v` 自身へ入る辺を含まないので、根の部分木では木全体の辺区間になる。
