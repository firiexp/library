---
title: Dijkstra法
documentation_of: //graph/dijkstra.cpp
---

## 説明
単一始点最短路と、初期費用を持つ複数始点からの最小費用を求める。
辺重みが非負のときに使う。

## できること
- `vector<T> dijkstra(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`。時間 $O((V+E)\log(V+E+1))$、補助領域 $O(V+E)$
- `vector<T> dijkstra_from_distances(vector<T> initial, const vector<vector<edge<T>>>& g)`
  各頂点 $v$ への最小費用 $\min_s(\mathrm{initial}[s]+\mathrm{dist}(s,v))$ を返す。`initial[s] == INF<T>` の頂点は始点候補から除く。有限の初期値の個数を $S$ として $O(V+(E+S)\log(V+E+1))$ 時間、$O(V+E)$ 補助領域

## 使い方
`edge<T>` の隣接リストを作って `dijkstra` を呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

`dijkstra_from_distances` に渡す `initial` の長さは頂点数に合わせる。
通常の多始点最短路では始点だけを `0`、それ以外を `INF<T>` にする。
初期費用には負の値も使える。有限の初期費用と緩和中の和は、型 `T` の範囲に収まる `INF<T>` 未満の値を前提とする。
初期配列を保持する場合はそのまま渡し、領域を再利用する場合は `std::move(initial)` を渡す。

## 実装上の補足
到達不能頂点の距離は `INF<T>` のまま残る。
同じ長さの最短路が複数あっても、距離だけを返す。
