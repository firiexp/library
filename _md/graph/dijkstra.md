---
title: Dijkstra法
documentation_of: //graph/dijkstra.cpp
---

## 説明
単一始点最短路を求める。
辺重みが非負のときに使う。
計算量は $O((V + E) log V)$。

## できること
- `vector<T> dijkstra(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`

## 使い方
`edge<T>` の隣接リストを作って `dijkstra` を呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

## 実装上の補足
到達不能頂点の距離は `INF<T>` のまま残る。
同じ長さの最短路が複数あっても、距離だけを返す。
