---
title: グリッドの4近傍最短路
documentation_of: //graph/grid_bfs.cpp
---

## 説明
通行できるマス間を上下左右へ1歩で移動する最短路を求める。
範囲外のマスへの遷移は内部で除き、明示的な隣接リストを作らない。

## できること
- `grid_bfs(h, w, source, passable)`
  `source` は `{row, column}` の pair、または複数始点の vector。行・列は0-indexed
- `passable(r, c)`
  マスを通行できるか返す。範囲内の座標だけで呼ぶ。探索中は判定結果を変えない
- `result.distance(r, c)`
  最寄りの始点からの歩数。壁・未到達は `INF<int>`。座標は範囲内とする
- `result.path_to(r, c)`
  始点から目的マスまでの座標列。未到達・範囲外なら空配列

## 使い方
`h,w >= 0`、`h*w <= INT_MAX` とする。始点は範囲内に限り、壁上の始点は無視する。
空のグリッドでは空の始点 vector を渡す。`INF<T>` は利用側で定義する。

```cpp
auto result = grid_bfs(h, w, pair<int, int>{sr, sc},
    [&](int r, int c) { return grid[r][c] != '#'; });
int distance = result.distance(tr, tc);
auto path = result.path_to(tr, tc);
```

`result.paths` は頂点 ID を `r*w+c` とした `GeneratedShortestPathResult<int>`。
層・方向を持つ状態や4近傍以外の遷移は、汎用の `bfs_generated` / `bfs01_generated` / `dijkstra_generated` で記述する。

## 実装上の補足
通行判定を $O(1)$ とすると、時間・領域は $O(hw)$。到達領域が狭い場合も全マスの距離初期化は行う。
経路復元の時間・追加領域は経路長に比例する。
