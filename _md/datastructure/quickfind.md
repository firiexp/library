---
title: Quick Find
documentation_of: //datastructure/quickfind.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
各連結成分の頂点一覧を持ちながら併合する素集合データ構造。
小さい集合を大きい集合へ移すため、各頂点の移動回数は高々 $O(\log N)$ となる。

## できること
頂点数を $N$ とする。

- `QuickFind(int n)`
  `0..n-1` をそれぞれ別集合として初期化する。$O(N)$
- `int root(int a)`
  `a` が属する集合の代表元を返す。$O(1)$
- `bool same(int a, int b)`
  `a` と `b` が同じ集合なら `true` を返す。$O(1)$
- `bool unite(int a, int b)`
  `a` と `b` の集合を併合する。もともと同じなら `false`。最悪 $O(N)$、成功した併合全体で $O(N\log N)$
- `size_t size(int a)`
  代表元 `a` が持つ集合のサイズを返す。非代表元を渡すと `0` になる。$O(1)$
- `const vector<int>& components(int x)`
  `x` が属する連結成分の頂点一覧を返す。$O(1)$

## 使い方
`QuickFind uf(n);` を作って `unite(a, b)` と `same(a, b)` を使う。
成分の頂点一覧は `components(x)`、頂点数は `size(root(x))` で取得する。

```cpp
QuickFind uf(n);
uf.unite(0, 1);
if (uf.same(0, 1)) {
    auto comp = uf.components(0);
}
```
