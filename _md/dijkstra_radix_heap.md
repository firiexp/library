---
title: Dijkstra法(Radix Heap)
documentation_of: //graph/dijkstra_radix_heap.cpp
---
## 説明
Radix Heap を使った Dijkstra 法である。
非負整数重みの単一始点最短路を高速に求める。

## できること
- `vector<T> dijkstra(int s, vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`

## 使い方
辺重みは非負である必要がある。
`edge<T>` の隣接リストを作って呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

## 実装上の補足
内部で `RadixHeap<ll, int>` を使うため、キーは `ll` に収まる非負整数を想定している。
通常の priority queue 版 Dijkstra より、距離が整数で増加する性質を利用して定数倍を削る。
