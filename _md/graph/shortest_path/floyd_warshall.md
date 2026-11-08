---
title: 全頂点対最短距離(Floyd–Warshall法)
documentation_of: //graph/shortest_path/floyd_warshall.cpp
---

## 説明
負辺を含む重み付き有向グラフの全頂点対最短距離を求める。
数十〜数百頂点の密グラフなどで使う。

## できること
頂点数を $N$、辺数を $M$ とする。

- `vector<vector<T>> floyd_warshall(int n, const vector<edge<T>>& edges)`
  `dist[u][v]` が頂点 `u` から `v` への最短距離となる表を返す。到達不能は `INF<T>`、対角は0。
  グラフのどこかに負閉路があれば空配列。`n >= 1` とする。時間 $O(N^3+M)$、追加領域 $O(N^2)$。
  辺重み・単純路の重みの絶対値は `INF<T>` 未満とする。

## 使い方
頂点は0-indexed。多重辺は最小の重みを使い、負の自己ループも負閉路として扱う。

```cpp
vector<edge<long long>> edges{ {0, 1, 3}, {1, 2, -5}, {0, 2, 4}};
auto dist = floyd_warshall(3, edges);
if (dist.empty()) {
    out.println("NEGATIVE CYCLE");
} else {
    out.println(dist[0][2]);
}
```
