---
title: 01-BFS
documentation_of: //graph/bfs01.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
辺重みが `0` または `1` のグラフで単一始点最短路を求める。
計算量は $O(V + E)$。

## できること
- `vector<T> bfs01(int s, vector<vector<edge<T>>>& G)`
  始点 `s` から各頂点への最短距離を返す
- 到達不能な頂点
  `INF<T>` のまま返す

## 使い方
`#include "../graph/bfs01.cpp"` を読み込む。
隣接リスト `G` を作り、各辺のコストに `0` か `1` を入れて `bfs01(s, G)` を呼ぶ。

```cpp
vector<vector<edge<int>>> G(n);
G[u].emplace_back(v, 0);
G[v].emplace_back(u, 1);
auto dist = bfs01(0, G);
```

## 実装上の補足
`edge<T>` は `dijkstra.cpp` と同じ形を使う。
重み `0` の遷移は deque の前、重み `1` の遷移は後ろへ積む。
