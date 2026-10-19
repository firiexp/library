---
title: 陽に辺を持たないグラフの最短路
documentation_of: //graph/generated_shortest_path.cpp
---

## 説明
辺を隣接リストなどに保存せず、移動先を計算しながら単一始点・多始点最短路を求める。
各状態に `0..n-1` の頂点 ID を割り当てる。

## できること
`for_each_edge` には頂点 `v` から移動できる頂点を列挙する関数を渡す。

- `dijkstra_generated<T>(n, sources, for_each_edge)`
  辺重みが非負のグラフの最短路を求める
- `bfs01_generated<T = int>(n, sources, for_each_edge)`
  辺重みが0または1のグラフの最短路を求める
- `bfs_generated(n, sources, for_each_edge)`
  全辺の重みが1のグラフの最短路を求める。距離の型は int
- 戻り値 `GeneratedShortestPathResult<T>`
  `dist` は距離、`parent` は最短路木の親。未到達は `INF<T>`、始点と未到達の親は `-1`
- `result.path_to(t)`
  いずれかの始点から `t` までの頂点列を返す。始点自身なら1頂点、未到達・範囲外なら空配列

### 終点を指定した版

戻り値は `GeneratedShortestPathTargetResult<T>`

`distance` は終点までの距離、`path` はそこまでの頂点列。未到達は `INF<T>` と空配列。始点に終点が含まれれば距離0と終点1個の経路

- `dijkstra_generated_to<T>(n, sources, t, for_each_edge)`
  非負重みのグラフで、終点 `t` の距離が確定した時点で探索を止める
- `bfs01_generated_to<T = int>(n, sources, t, for_each_edge)`
  重み0/1のグラフで、終点 `t` の距離が確定した時点で探索を止める
- `bfs_generated_to(n, sources, t, for_each_edge)`
  重み1のグラフで、終点 `t` の距離が確定した時点で探索を止める

## 使い方
`n` は状態数、`sources` は始点の頂点 ID、または複数始点の vector とする。
全始点の距離を0とし、重複始点は無視する。空の vector を渡すと全頂点が未到達となる。
終点指定でも単一始点・複数始点を渡せる。`n >= 1`、`0 <= t < n` とする。

`for_each_edge` は探索する頂点 `v` と関数 `emit` を引数に受け取る。
その中で辺 `v -> to` ごとに `emit(to, cost)` を呼び、移動先と辺重みを探索側へ渡す。
`bfs_generated` では辺重みが1なので、`emit(to)` と書く。

例えば、`v` から `v+1` へ重み1、`v-1` へ重み2で移動できる場合は次のように書く。

```cpp
auto for_each_edge = [&](int v, auto emit) {
    if (v + 1 < n) emit(v + 1, 1);
    if (v > 0) emit(v - 1, 2);
};
auto result = dijkstra_generated<long long>(n, s, for_each_edge);
auto path = result.path_to(target);
```

1つの終点だけが必要なら `auto result = dijkstra_generated_to<long long>(n, s, target, for_each_edge);` とし、`result.distance` と `result.path` を使う。
終点の `for_each_edge` は呼ばない。途中まで探索した他の頂点の距離・親は返さない。

## 実装上の補足
有限距離は `INF<T>` 未満を前提とする。Dijkstra は距離と辺重みの和が `INF<T>` 以上となる遷移を無視し、加算の overflow を避ける。
同距離では親を更新せず、返す最短路の一意性は保証しない。

状態数を $V$、到達頂点から生成する辺数を $E$ とする。辺の重複・自己ループも扱う。
`for_each_edge` 自体の費用を除き、BFS / 01-BFS は $O(V+E)$ 時間、Dijkstra は $O((V+E)\log(V+E+1))$ 時間。
始点列の長さを $S$ とすると、その読み取りに別途 $O(S)$ 時間を使う。各到達頂点の `for_each_edge` は1回だけ呼ぶ。
距離と親は $O(V)$ 領域。BFS / 01-BFS の queue は $O(V)$、Dijkstra の queue は $O(V+E)$。
復元は経路長に比例する時間・追加領域を使う。

