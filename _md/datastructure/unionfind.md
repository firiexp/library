---
title: UnionFind(素集合データ構造)
documentation_of: //datastructure/unionfind.cpp
---

## 説明
頂点を互いに素な集合に分け、集合の併合と代表元の取得を扱う。

## できること
頂点数を $N$ とする。

- `UnionFind uf(n)` : `n` 頂点をそれぞれ独立した集合として作る。$O(N)$
- `root(a)` : 頂点 `a` の代表元を取得する。償却 $O(\alpha(N))$
- `unite(a, b)` : 頂点 `a` と `b` の属する集合を併合する。既に同じなら `false`。償却 $O(\alpha(N))$
- `size()` : 集合の数を取得する。$O(1)$
- `size(i)` : `i` の属する集合の大きさを取得する。償却 $O(\alpha(N))$
- `same(a, b)` : `a` と `b` が同じ集合に属するかどうかを判定する。償却 $O(\alpha(N))$

## 使い方
`UnionFind uf(n);` を作り、`unite(a, b)` で併合し、`same(a, b)` で連結性を判定する。頂点番号は `0 <= v < n` とする。
