---
title: 辺を都度生成する最短路
documentation_of: //graph/generated_shortest_path.cpp
---

## 説明
探索中の頂点から出る辺を callback で生成し、単一始点・多始点最短路を求める。
全辺の構築・保存は不要。状態を `0..n-1` の整数に対応させて使う。

## できること
- `dijkstra_generated<T>(n, sources, for_each_edge)`
  非負重みの最短路。`for_each_edge(v, emit)` から `emit(to, cost)` を呼ぶ
- `bfs01_generated<T = int>(n, sources, for_each_edge)`
  重みが0または1の最短路。辺の通知方法は Dijkstra と同じ
- `bfs_generated(n, sources, for_each_edge)`
  全辺の重みが1の最短路。`emit(to)` で辺を通知する。距離の型は int
- 各関数の `sources` は頂点 ID の vector、または単一の頂点 ID
  全始点の距離を0とする。重複始点は無視し、空なら全頂点が未到達
- 戻り値 `GeneratedShortestPathResult<T>`
  `dist` は距離、`parent` は最短路木の親。未到達は `INF<T>`、始点と未到達の親は `-1`
- `result.path_to(t)`
  いずれかの始点から `t` までの頂点列を返す。始点自身なら1頂点、未到達・範囲外なら空配列

## 使い方
`INF<T>` は既存の最短路と同様に利用側で定義する。頂点数・始点・遷移先は有効な範囲とする。
探索中に遷移の意味を変更せず、callback 内で直ちに `emit` を呼ぶ。
同距離では親を更新せず、返す最短路の一意性は保証しない。
有限距離は `INF<T>` 未満を前提とする。Dijkstra は距離と辺重みの和が `INF<T>` 以上となる遷移を無視し、加算の overflow を避ける。

```cpp
auto result = bfs01_generated(2 * h * w, 0, [&](int id, auto emit) {
    int layer = id / (h * w), cell = id % (h * w);
    int r = cell / w, c = cell % w;
    if (c + 1 < w) emit(layer * h * w + r * w + c + 1, 1);
    if (can_switch(r, c)) emit((1 - layer) * h * w + cell, 0);
});
auto path = result.path_to(target);
```

## 実装上の補足
状態数を $V$、到達頂点から生成する辺数を $E$ とする。辺の重複・自己ループも扱う。
callback 自体の費用を除き、BFS / 01-BFS は $O(V+E)$ 時間、Dijkstra は $O((V+E)\log(V+E+1))$ 時間。
始点列の長さを $S$ とすると、その読み取りに別途 $O(S)$ 時間を使う。各到達頂点の callback は1回だけ呼ぶ。
距離と親は $O(V)$ 領域。BFS / 01-BFS の queue は $O(V)$、Dijkstra の queue は $O(V+E)$。
復元は経路長に比例する時間・追加領域を使う。
