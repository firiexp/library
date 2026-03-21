---
title: Dijkstra法(Radix Heap)
documentation_of: //graph/dijkstra_radix_heap.cpp
---
## 説明
Radix Heap を使った Dijkstra 法である。
非負整数重みの単一始点最短路を高速に求める。

## できること
- `vector<long long> dijkstra_radix_heap(int s, const vector<vector<edge<long long>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<long long>`

## 使い方
辺重みは非負整数である必要がある。
`edge<long long>` の隣接リストを作って呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra_radix_heap(0, g);
```

## 実装上の補足
内部で `RadixHeap<long long, int>` を使う。
通常の priority queue 版 Dijkstra より、距離が整数で増加する性質を利用して定数倍を削る。
