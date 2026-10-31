---
title: グリッドの4近傍最短路
documentation_of: //graph/shortest_path/grid_bfs.cpp
---

## 説明
通行できるマス間を上下左右へ1歩で移動する最短路を求める。
範囲外のマスへの遷移は内部で除き、明示的な隣接リストを作らない。

## できること
行数を $h$、列数を $w$、始点列の長さを $S$ とし、通行判定は $O(1)$ とする。

- `grid_bfs(h, w, sr, sc, passable)`
  マス `(sr, sc)` を始点に探索する。行・列は0-indexed
  `passable` にはマス `(r, c)` を通行できるとき `true` を返す関数を渡す。$O(hw)$
- `grid_bfs(h, w, src, passable)`
  複数始点から探索する。`src` は始点の `(行, 列)` を並べた `vector<pair<int, int>>`。`passable` は単一始点の場合と同じ。$O(hw+S)$
- `res.dist(r, c)`
  最寄りの始点からマス `(r, c)` までの歩数。壁・未到達は `INF<int>`。座標は範囲内とする。$O(1)$
- `res.path_to(r, c)`
  始点からマス `(r, c)` までの座標列。未到達・範囲外なら空配列。最悪 $O(hw)$
- `grid_bfs_to(h, w, sr, sc, tr, tc, passable)`
  単一始点から終点 `(tr, tc)` まで探索し、その距離が確定した時点で止める。$O(hw)$
- `grid_bfs_to(h, w, src, tr, tc, passable)`
  複数始点から終点まで探索する。壁上の始点は無視する。$O(hw+S)$
- 終点指定の戻り値 `GridPath`
  `dist` は終点までの歩数、`path` は座標列。終点が壁・未到達なら `INF<int>` と空配列。通行可能な始点に終点が含まれれば距離0と終点1個の経路

## 使い方
`h,w >= 0`、`h*w <= INT_MAX` とする。始点は範囲内に限り、壁上の始点は無視する。
空のグリッドでは空の始点 vector を渡す。
終点指定では `h,w >= 1` とし、終点も範囲内に限る。
`passable` は範囲内の座標だけで呼ばれる。探索中は判定結果を変えない。

```cpp
auto res = grid_bfs(h, w, sr, sc,
    [&](int r, int c) { return grid[r][c] != '#'; });
int dist = res.dist(tr, tc);
auto path = res.path_to(tr, tc);
```

終点だけが必要なら `auto res = grid_bfs_to(h, w, sr, sc, tr, tc, passable);` とし、`res.dist` と `res.path` を使う。
終点からの隣接マスの探索は行わない。

`res.paths` は頂点 ID を `r*w+c` とした `ShortestPaths<int>`。
層・方向を持つ状態や4近傍以外の遷移は、汎用の `bfs_generated` / `bfs01_generated` / `dijkstra_generated` で記述する。

## 実装上の補足
領域は単一始点で $O(hw)$、複数始点で $O(hw+S)$。
終点指定は確定後の探索を省くが、到達領域が狭い場合も全マスの距離初期化は行う。到達不能なら全探索になる。
