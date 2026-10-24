---
title: 多始点Dijkstra法
documentation_of: //graph/dijkstra_from_distances.cpp
---

## 説明
Dijkstra 法を応用して、初期費用を持つ複数始点から各頂点への最小費用を求める。
辺重みは非負とする。初期費用には負の値も使える。

## できること
頂点数を $V$、辺数を $E$ とする。$\mathrm{dist}(s,v)$ は `s` から `v` への最短距離を表す。

- `vector<T> dijkstra_from_distances(vector<T> initial, const vector<vector<edge<T>>>& g)`
  各頂点 $v$ への最小費用 $\min_s(\mathrm{initial}[s]+\mathrm{dist}(s,v))$ を返す。`initial[s] == INF<T>` の頂点は始点候補から除く。未到達は `INF<T>`。$O((V+E)\log(V+E))$ 時間、$O(V+E)$ 補助領域

## 使い方
`initial` の長さは頂点数に合わせ、始点候補の初期費用を設定する。
通常の多始点最短路では始点だけを `0`、それ以外を `INF<T>` にする。

```cpp
vector<long long> initial(n, INF<long long>);
initial[a] = cost_a;
initial[b] = cost_b;
auto dist = dijkstra_from_distances(initial, g);
```

有限の初期費用と緩和中の和は、型 `T` の範囲に収まる `INF<T>` 未満の値を前提とする。
初期配列を保持する場合はそのまま渡し、領域を再利用する場合は `std::move(initial)` を渡す。
