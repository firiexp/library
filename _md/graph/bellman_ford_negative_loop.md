---
title: Bellman-Ford法(負閉路伝播)
documentation_of: //graph/bellman_ford_negative_loop.cpp
---
## 説明
負辺を含む単一始点最短路を求め、始点から到達できる負閉路の影響下にある頂点を `-INF` にする。
計算量は $O(VE)$。

## できること
- `vector<T> bellman_ford(int s, int n, vector<edge<T>>& es)`
  始点 `s` から各頂点への距離を返す。未到達は `INF<T>`、負閉路の影響下は `-INF<T>`

## 使い方
`edge<T>` の列を用意して呼ぶ。
`T` は加算と比較ができる数値型を想定している。

```cpp
vector<edge<long long>> es;
es.emplace_back(u, v, w);
auto dist = bellman_ford(0, n, es);
if (dist[v] == INF<long long>) {
    // unreachable
} else if (dist[v] == -INF<long long>) {
    // affected by a negative cycle
}
```

## 実装上の補足
負閉路そのものに乗る頂点だけでなく、そこから到達できる頂点も `-INF` にする。
このファイル単体では `INF<T>`、`ll`、`vector` を外側で用意する前提である。
