---
title: 二辺連結成分分解(Two-Edge-Connected Components)
documentation_of: //graph/twoedgeconnectedcomponents.cpp
date: 2020-03-25
category: グラフ
tags: グラフ
---

## 説明
無向グラフから橋を取り除いたときの連結成分を求める。
非連結グラフや多重辺も扱う。

## できること
頂点数を $V$、辺数を $E$ とする。

- `TwoEdgeConnectedComponents g(n)`
  `n` 頂点のグラフを作る。$O(V)$
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは無視する。償却 $O(1)$
- `int build()`
  二辺連結成分分解を行い、成分数を返す。時間・領域 $O(V+E)$
- `bool is_bridge_edge(int id) const`
  追加順の辺番号 `id` の辺が橋なら `true`。無視された自己ループには番号を付けない。$O(1)$
- `bridge[v]`
  頂点 `v` が属する成分の番号
- `out[c]`
  成分 `c` の頂点列

## 使い方
辺を追加して `build()` を呼び、`bridge` と `out` を参照する。

```cpp
TwoEdgeConnectedComponents g(n);
for (auto [u, v] : edges) g.add_edge(u, v);
int count = g.build();
int component = g.bridge[v];
```

## 実装上の補足
LowLink で橋を判定し、橋を通らない DFS で成分番号を付ける。
