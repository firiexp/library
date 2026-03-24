---
title: HL分解(HL Decomposition)
documentation_of: //tree/hld.cpp
date: 2019-10-10
category: 木
tags: 木
---

## 説明
根つき木を Euler Tour 順の連続区間へ写し、パスや部分木を少数個の区間に分解する。
パスクエリ・パス更新は $O(log^2 N)$、部分木クエリは $O(f(N))$ で扱える。

## できること
- `HeavyLightDecomposition hld(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(vector<int> roots = {0})`
  前処理をする。森にも対応する
- `int lca(int u, int v)`
  最近共通祖先を返す
- `int parent(int v)`
  親を返す。根なら `-1`
- `int ancestor(int v, int k)`
  `k` 個上の祖先を返す。存在しなければ `-1`
- `int distance(int u, int v)`
  木上距離を返す
- `pair<int, int> subtree(int v, bool edge = false)`
  部分木に対応する半開区間 `[l, r)` を返す
- `void path(int u, int v, F f, bool edge = false)`
  パスを被覆する各区間へ `f(l, r)` を呼ぶ
- `T path_query(int u, int v, T e, Q q, F f, bool edge = false)`
  可換向けパスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f, bool edge = false)`
  非可換向け順序付きパスクエリ
- `void apply_subtree(int v, F f, bool edge = false)`
  部分木区間へ `f(l, r)` を呼ぶ
- `T subtree_query(int v, Q q, bool edge = false)`
  部分木区間クエリ

## 使い方
`id[v]` を頂点 `v` の 1 次元位置としてセグ木や BIT に載せる。
部分木は `subtree(v)` の区間 1 本で取れる。
パスは `path` / `path_query` / `path_query_ordered` を使う。

```cpp
HeavyLightDecomposition hld(n);
hld.add_edge(u, v);
hld.build();

auto [l, r] = hld.subtree(v);
auto sub = seg.query(l, r);

auto ans = hld.path_query_ordered(a, b, Monoid::e(), ql, qr, Monoid::f, false);
```

## 実装上の補足
`edge = true` にすると、LCA 側の頂点を除いた辺クエリ区間になる。
`path_query_ordered` は `u -> v` の向きを保つ。
