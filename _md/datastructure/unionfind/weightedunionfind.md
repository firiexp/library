---
title: 重み付きUnionFind(Weighted Union Find)
documentation_of: //datastructure/unionfind/weightedunionfind.cpp
---
## 説明
各頂点にポテンシャルを持たせた Union-Find である。
ポテンシャルは群 `G` を渡して定義する。群の積は `G::op`、逆元は `G::inv` に対応する。

## できること
頂点数を $N$、頂点 `v` のポテンシャルを $f(v)$ とし、群演算と `G::T` の `==` による比較を $O(1)$ とする。

- `WeightedUnionFind<G> uf(n)`
  頂点数 `n` の Union-Find を作る。$O(N)$
- `int root(int v)`
  頂点 `v` の代表元を返す。償却 $O(\alpha(N))$
- `bool same(int u, int v)`
  `u` と `v` が同じ集合かを返す。償却 $O(\alpha(N))$
- `UniteResult unite(int u, int v, G::T w)`
  $f(u)^{-1}f(v) = w$（例: $f(v) - f(u) = w$）を追加する。返り値の `ok` は制約を受け入れられたか、`merged` は新たに併合したかを表す。条件式では `ok` として判定できる。矛盾した制約は採用せず、既存の差分を保つ。償却 $O(\alpha(N))$
- `G::T weight(int v)`
  代表元から見た `v` のポテンシャルを返す。償却 $O(\alpha(N))$
- `G::T diff(int u, int v)`
  $f(u)^{-1}f(v)$（ 例: $f(v) - f(u)$ ）を返す。非連結では使わない。償却 $O(\alpha(N))$
- `int size(int v)`
  `v` が属する集合サイズを返す。償却 $O(\alpha(N))$

## 使い方
下の加法群の例では、制約 $f(y) - f(x) = w$ を追加するときに `unite(x, y, w)` を呼ぶ。
矛盾した場合は `if (!uf.unite(x, y, w))` で分岐できる。既存の差分と一致する制約も成功として扱う。
差分を取りたいときは、先に `same(x, y)` を確認してから `diff(x, y)` を使う。

```cpp
struct Group {
    using T = long long;
    static T op(T a, T b) { return a + b; }
    static T inv(T a) { return -a; }
    static T e() { return 0; }
};

WeightedUnionFind<Group> uf(n);
auto res = uf.unite(x, y, w);
if (res) {
    long long d = uf.diff(x, y);
}
```

| 判定 | 意味 |
| --- | --- |
| `!res` | 矛盾して不採用。`ok`、`merged` はともに `false` |
| `res.merged` | 新規併合。`ok`、`merged` はともに `true` |
| `res && !res.merged` | 既存の差分と一致。`ok` は `true`、`merged` は `false` |

条件式以外で成功可否を取り出すときは `res.ok` を使う。`bool` への変換は explicit である。
