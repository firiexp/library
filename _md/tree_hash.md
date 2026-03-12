---
title: 木ハッシュ(Tree Hash)
documentation_of: //tree/tree_hash.cpp
date: 2026-03-12
category: 木
tags: 木
---

## 説明
根付き木の各部分木を同型性で分類する。
各頂点 `v` について、その部分木の同型類 id を返す。

## できること
- `TreeHash th(n)`
  `n` 頂点の木を作る
- `void add_edge(int u, int v)`
  無向辺を追加する
- `vector<int> build(int root = 0)`
  `root` を根として部分木 id を構築して返す
- `int th[v]`
  頂点 `v` の部分木 id を返す
- `int kinds()`
  異なる部分木の個数を返す

## 使い方
辺をすべて追加してから `build(root)` を呼ぶ。
返る id は同じ `build` の中でのみ意味を持ち、`id[v] == id[u]` のときに限って
`v` と `u` の部分木は同型である。

```cpp
TreeHash th(n);
for (auto [u, v] : edges) th.add_edge(u, v);
auto id = th.build(0);
```

## 実装上の補足
- 子部分木の id をソートして辞書化することで canonical id を付ける
- 計算量はおおむね $O\left(\sum_v \deg(v)\log \deg(v)\right)$
