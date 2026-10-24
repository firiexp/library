---
title: Dijkstra法
documentation_of: //graph/dijkstra.cpp
---

## 説明
単一始点最短路を求める。
これを応用して、初期費用を持つ複数始点からの最小費用も求めることができる。
辺重みが非負のときに使う。

## できること
頂点数を $V$、辺数を $E$ とする。

- `vector<T> dijkstra(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`。時間 $O((V+E)\log(V+E))$、補助領域 $O(V+E)$

## 使い方
`edge<T>` の隣接リストを作って `dijkstra` を呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

初期費用を持つ複数始点を扱う場合は、`graph/dijkstra_from_distances.cpp` の `dijkstra_from_distances` を使う。

## 実装上の補足
同じ長さの最短路が複数あっても、距離だけを返す。
