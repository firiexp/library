---
title: 陽に辺を持たないグラフの最短路
documentation_of: //graph/generated_shortest_path.cpp
---

## 説明
辺を隣接リストなどに保存せず、移動先を計算しながら単一始点・多始点最短路を求める。
各状態に `0..n-1` の頂点 ID を割り当てる。

## できること
`adj` には頂点 `v` から移動できる頂点を列挙する関数を渡す。
状態数を $V$、生成する辺数を $E$、始点列の長さを $S$ とする。
以下の時間計算量には `adj` 自体の処理を含めない。

- `dijkstra_generated<T>(n, src, adj)`
  辺重みが非負のグラフの最短路を求める。$O(S+(V+E)\log(V+E))$
- `bfs01_generated<T = int>(n, src, adj)`
  辺重みが0または1のグラフの最短路を求める。$O(V+E+S)$
- `bfs_generated(n, src, adj)`
  全辺の重みが1のグラフの最短路を求める。距離の型は `int`。$O(V+E+S)$
- 戻り値 `ShortestPaths<T>`
  `dist` は距離、`parent` は最短路木の親。未到達は `INF<T>`、始点と未到達の親は `-1`
- `res.path_to(t)`
  いずれかの始点から `t` までの頂点列を返す。始点自身なら1頂点、未到達・範囲外なら空配列。最悪 $O(V)$

### 終点を指定した版

戻り値は `ShortestPath<T>`

`dist` は終点までの距離、`path` はそこまでの頂点列。未到達は `INF<T>` と空配列。始点に終点が含まれれば距離0と終点1個の経路

- `dijkstra_generated_to<T>(n, src, t, adj)`
  非負重みのグラフで、終点 `t` の距離が確定した時点で探索を止める。最悪 $O(S+(V+E)\log(V+E))$
- `bfs01_generated_to<T = int>(n, src, t, adj)`
  重み0/1のグラフで、終点 `t` の距離が確定した時点で探索を止める。$O(V+E+S)$
- `bfs_generated_to(n, src, t, adj)`
  重み1のグラフで、終点 `t` の距離が確定した時点で探索を止める。$O(V+E+S)$

## 使い方
`n` は状態数、`src` は始点の頂点 ID、または複数始点の vector とする。
全始点の距離を0とし、重複始点は無視する。空の vector を渡すと全頂点が未到達となる。
終点指定でも単一始点・複数始点を渡せる。`n >= 1`、`0 <= t < n` とする。

`adj` は探索する頂点 `v` と関数 `emit` を引数に受け取る。
その中で辺 `v -> to` ごとに `emit(to, cost)` を呼び、移動先と辺重みを探索側へ渡す。
`bfs_generated` では辺重みが1なので、`emit(to)` と書く。

例えば、`v` から `v+1` へ重み1、`v-1` へ重み2で移動できる場合は次のように書く。

```cpp
auto adj = [&](int v, auto emit) {
    if (v + 1 < n) emit(v + 1, 1);
    if (v > 0) emit(v - 1, 2);
};
auto res = dijkstra_generated<long long>(n, s, adj);
auto path = res.path_to(t);
```

1つの終点だけが必要なら `auto res = dijkstra_generated_to<long long>(n, s, t, adj);` とし、`res.dist` と `res.path` を使う。
終点の `adj` は呼ばない。途中まで探索した他の頂点の距離・親は返さない。

## 実装上の補足
有限距離は `INF<T>` 未満を前提とする。Dijkstra は距離と辺重みの和が `INF<T>` 以上となる遷移を無視し、加算の overflow を避ける。
同距離では親を更新せず、返す最短路の一意性は保証しない。

辺の重複・自己ループも扱う。各到達頂点の `adj` は1回だけ呼ぶ。
距離と親は $O(V)$ 領域。BFS / 01-BFS の queue は $O(V)$、Dijkstra の queue は $O(V+E)$。
