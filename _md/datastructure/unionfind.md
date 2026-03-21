---
title: UnionFind(素集合データ構造)
documentation_of: //datastructure/unionfind.cpp
---

## 説明
頂点の併合、代表元の取得を $O(\alpha(n))$ で行う。

## できること
- `root(a)` : 頂点 `a` の代表元を取得する
- `unite(a, b)` : 頂点 `a` と `b` の属する集合を併合する。既に同じなら `false`
- `size()` : 集合の数を取得する
- `size(i)` : `i` の属する集合の大きさを取得する
- `same(a, b)` : `a` と `b` が同じ集合に属するかどうかを判定する
