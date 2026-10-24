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
頂点数を $N$ とする。

- `TreeHash th(n)`
  `n` 頂点の木を作る。$O(N)$
- `void add_edge(int u, int v)`
  無向辺を追加する。償却 $O(1)$
- `vector<int> build(int root = 0)`
  `root` を根として部分木 id を構築して返す。$O(N\log N)$
- `int th[v]`
  頂点 `v` の部分木 id を返す。$O(1)$
- `int kinds()`
  異なる同型類の個数を返す。$O(1)$

## 使い方
辺をすべて追加してから `build(root)` を呼ぶ。
返る id は同じ `build` の中でのみ意味を持ち、`id[v] == id[u]` のときに限って
`v` と `u` の部分木は同型である。
別々の木の比較や頂点対応の復元には `tree/tree_isomorphism.cpp` の `tree_isomorphism` / `rooted_tree_isomorphism` を使う。

```cpp
TreeHash th(n);
for (auto [u, v] : edges) th.add_edge(u, v);
auto id = th.build(0);
```

## 実装上の補足
- 子部分木の id をソートして辞書化することで canonical id を付ける
