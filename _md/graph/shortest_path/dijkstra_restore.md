---
title: 経路復元付きDijkstra法
documentation_of: //graph/shortest_path/dijkstra_restore.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
非負重みの有向グラフの単一始点最短路を求め、頂点列または入力辺ID列として復元する。
辺IDは入力辺列の添字で、平行辺も区別できる。

## できること
頂点数を $V$、辺数を $E$、復元する経路の辺数を $L$ とする。

- `dijkstra_restore(s, n, edges)`
  `edge<T>(from, to, cost)` の辺列から、`dist`・`parent`・`parent_edge` を持つ `DijkstraRestoreResult<T>` を返す。始点と未到達頂点の親頂点・親辺は `-1`、未到達距離は `INF<T>`。時間 $O((V+E)\log(V+E))$、作業領域 $O(V+E)$、返却領域 $O(V)$。
- `restore_path(s, t, result.parent)`
  `s` から `t` への頂点列を返す。未到達なら空、`s == t` なら `{s}`。$O(L+1)$。
- `restore_edge_path(s, t, result)`
  `s` から `t` への辺ID列を経路順に返す。未到達と `s == t` はともに空で、`result.dist[t]` で区別する。$O(L+1)$。

## 使い方
```cpp
vector<edge<long long>> edges;
edges.emplace_back(u, v, w);
auto result = dijkstra_restore(0, n, edges);
auto path = restore_edge_path(0, t, result);
for (int id : path) use(edges[id]);
```

## 実装上の補足
`0 <= s < n` とし、復元時も探索時と同じ始点を渡す。
距離の加算は `T` に収まり、有限距離は `INF<T>` 未満である必要がある。
同じ距離の候補では親を更新しないため、0重みの辺があっても親辺は閉路を作らない。
最短路が複数ある場合は任意の1本を返す。
距離だけが必要なら `dijkstra.cpp` を使う。
