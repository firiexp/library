---
title: HL分解(辺クエリ)
documentation_of: //tree/hld_edge.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
辺を子頂点側の位置に載せる重軽分解である。
根の位置には辺がないので、`edge_index(root)` は `-1` を返す。
パスクエリ・パス更新は $O(log^2 N)$。

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
- `void path_ordered(int u, int v, F f) const`
  `u -> v` の順に、空でない半開区間 `[l, r)` とその向きを callback `f` に渡す。`u = v` では呼ばない
- `T path_query(int u, int v, T e, Q q, F f)`
  可換向け辺パスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f)`
  非可換向け順序付き辺パスクエリ
- `void apply_subtree(int v, F f)`
  部分木の辺区間へ `f(l, r)` を呼ぶ
- `subtree_query(int v, Q q)`
  `v` の部分木の辺クエリ。戻り値の型は `q` から推論する

## 使い方
各辺の値は子頂点側に置く。
`parent(v) - v` の辺を更新したいときは `edge_index(v)` を使う。
パス順序付きの集約には `path_query_ordered`、区間ごとの処理には `path_ordered` を使う。
両端点は同じ連結成分に属することを前提とする。

`path_ordered` の `f` は、`int l, int r, bool reversed` を引数に取る関数として定義する。
`reversed` は HLD が区間ごとに決めて第3引数に渡す値で、`true` なら `r-1 -> l`、`false` なら `l -> r-1` の順に進む。

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
`path_ordered` は LCA の位置を除き、辺を子頂点の位置で渡す。
callback を除く時間と作業領域は $O(\log N)$ で、heap 確保は行わない。
