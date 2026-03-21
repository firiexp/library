---
title: 橋木(Bridge Tree)
documentation_of: //graph/bridge_tree.cpp
date: 2026-03-11
category: グラフ
tags: グラフ
---

## 説明
無向グラフの二辺連結成分を縮約して、橋だけを辺に持つ森を作る。
連結グラフなら木、非連結グラフなら森になる。

## できること
- `BridgeTree g(n)`
  頂点数 `n` の graph builder を作る
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは内部で無視される
- `int build()`
  bridge tree を構築し、成分数を返す

## 使い方
`build()` 後は `tree`、`nodes`、`edges`、`id` を参照する。

- `tree[k]`
  bridge tree 上で成分 `k` に隣接する成分番号列
- `nodes[k]`
  成分 `k` に含まれる元グラフ頂点集合
- `edges`
  bridge tree の辺集合。各要素は成分番号の組
- `id[v]`
  元頂点 `v` が属する成分番号

`tecc` に内部の `TwoEdgeConnectedComponents` を保持しているので、必要なら `ord` や `low` も参照できる。
