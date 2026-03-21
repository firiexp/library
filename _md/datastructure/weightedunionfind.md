---
title: 重み付きUnionFind(Weighted Union Find)
documentation_of: //datastructure/weightedunionfind.cpp
---
## 説明
各頂点にポテンシャルを持たせた Union-Find である。
併合と差分取得をほぼ償却 $O(alpha(N))$ で扱う。
ポテンシャルは群 `G` を渡して定義する。

## できること
- `WeightedUnionFind<G> uf(n)`
  頂点数 `n` の構造体を作る。
- `int root(int v)`
  頂点 `v` の代表元を返す
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す
- `bool unite(int u, int v, G::T w)`
  `weight(v) - weight(u) = w` となるように併合する。すでに同じ集合なら `false`
- `G::T weight(int v)`
  代表元から見た `v` のポテンシャルを返す
- `G::T diff(int u, int v)`
  `weight(v) - weight(u)` を返す。非連結では使わない
- `int size(int v)`
  `v` が属する集合サイズを返す

## 使い方
差分制約 `weight(y) - weight(x) = w` を追加したいときに `unite(x, y, w)` を呼ぶ。
差分を取りたいときは、先に `same(x, y)` を確認してから `diff(x, y)` を使う。

```cpp
struct Group {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
};

WeightedUnionFind<Group> uf(n);
uf.unite(x, y, w);
if (uf.same(x, y)) {
    long long d = uf.diff(x, y);
}
```
