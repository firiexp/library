---
title: 二辺連結成分分解(Two-Edge-Connected Components)
documentation_of: //graph/connectivity/twoedgeconnectedcomponents.cpp
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
明示的なスタックでLowLink・DFS順・部分木サイズを求める。再帰を使わないため、長い道でもスタックサイズの変更は不要。
DFSの発見順に頂点を処理し、親との辺が橋なら新しい成分、それ以外なら親と同じ成分へ入れる。
成分番号や成分内の頂点順は保証しない。辺追加後の再構築もできる。
