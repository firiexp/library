---
title: UnionFind(素集合データ構造)
documentation_of: //datastructure/unionfind/unionfind.cpp
---

## 説明
頂点を互いに素な集合に分け、集合の併合と代表元の取得を扱う。

## できること
頂点数を $N$ とする。

- `UnionFind uf(n)` : `n` 頂点をそれぞれ独立した集合として作る。$O(N)$
- `int root(int a)` : 頂点 `a` の代表元を返す。償却 $O(\alpha(N))$
- `MergeResult unite(int a, int b)` : 頂点 `a` と `b` の属する集合を併合し、残った代表元 `keep` と吸収された代表元 `absorbed` を返す。既に同じ集合なら `{root(a), -1}`。償却 $O(\alpha(N))$
- `int size()` : 集合の数を返す。$O(1)$
- `int size(int i)` : `i` の属する集合の大きさを返す。償却 $O(\alpha(N))$
- `bool same(int a, int b)` : `a` と `b` が同じ集合に属するかどうかを返す。償却 $O(\alpha(N))$

## 使い方
`UnionFind uf(n);` を作り、`unite(a, b)` で併合し、`same(a, b)` で連結性を判定する。頂点番号は `0 <= v < n` とする。

`MergeResult` は条件式で使え、併合した場合だけ真になる。

成分ごとの和を外部で管理する例を示す。

```cpp
vector<long long> sum{3, 5, 7};
UnionFind uf(3);
if (auto merged = uf.unite(0, 1)) {
    sum[merged.keep] += sum[merged.absorbed];
}
long long value = sum[uf.root(1)];
```

## 実装上の補足
大きい集合の代表元を残し、同じ大きさなら第1引数側を残す。返り値の代表元はその操作時点の番号であり、後続の併合後も代表元であるとは限らない。
