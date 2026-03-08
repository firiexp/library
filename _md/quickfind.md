---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2026-03-08
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u7D20\u96C6\u5408\u30C7\u30FC\u30BF\u69CB\u9020 (Quick-Find)"
---

## 説明
各連結成分の頂点一覧を持ちながら併合する素集合データ構造。
`same` や `root` は `O(1)`、`unite` は小さい集合を大きい集合へマージする実装で、各頂点は高々 `O(log N)` 回しか移動しない。
全体では `N` 回の併合を通して `O(N log N)` 程度で動く。

## できること
- `QuickFind(int n)`
  `0..n-1` をそれぞれ別集合として初期化する
- `int root(int a)`
  `a` が属する集合の代表元を返す
- `bool same(int a, int b)`
  `a` と `b` が同じ集合なら `true` を返す
- `bool unite(int a, int b)`
  `a` と `b` の集合を併合する。もともと同じなら `false`
- `size_t size(int a)`
  代表元 `a` が持つ集合のサイズを返す。非代表元を渡すと 0 になることがある
- `const vector<int>& components(int x)`
  `x` が属する連結成分の頂点一覧を返す

## 使い方
`QuickFind uf(n);` を作って `unite(a, b)` と `same(a, b)` を使う。
成分に含まれる頂点を直接ほしいときは `components(x)` が使える。

```cpp
QuickFind uf(n);
uf.unite(0, 1);
if (uf.same(0, 1)) {
    auto comp = uf.components(0);
}
```

## 実装上の補足
- `components(x)` は代表元ではなく任意の頂点 `x` を渡してよい
- `size(a)` は実装上 `v[a].size()` を返すので、確実に使うなら `size(root(x))` とする
