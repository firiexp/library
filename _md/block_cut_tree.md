---
title: ブロックカット木(Block-Cut Tree)
documentation_of: //graph/block_cut_tree.cpp
date: 2026-03-11
category: グラフ
tags: グラフ
---

## 説明
無向グラフの二重連結成分と関節点から block-cut tree を作る。
成分ノードと関節点ノードの二部森になる。

## できること
- `BlockCutTree g(n)`
  頂点数 `n` の graph builder を作る
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは内部で無視される
- `int build()`
  block-cut tree を構築し、ノード数を返す

## 使い方
`build()` 後は `tree`、`nodes`、`id`、`rev`、`is_articulation` を参照する。

- `tree[k]`
  block-cut tree 上の隣接ノード
- `nodes[k]`
  そのノードに対応する元グラフ頂点集合。成分ノードなら二重連結成分、関節点ノードなら 1 頂点だけ持つ
- `id[v]`
  元頂点 `v` が対応する block-cut tree ノード番号。関節点なら専用ノード、そうでなければ属する成分ノード
- `rev[k]`
  `k` が関節点ノードなら元頂点番号、成分ノードなら `-1`
- `is_articulation[v]`
  `v` が関節点なら `true`
