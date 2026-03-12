---
title: 経路復元付きDijkstra法
documentation_of: //graph/dijkstra_restore.cpp
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
単一始点最短路と最短路木の親を求める。
辺重みが非負のときに使う。
計算量は $O((V + E) log V)$。

## できること
- `DijkstraRestoreResult<T> dijkstra_restore(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` からの最短距離と親配列を返す。未到達頂点の距離は `INF<T>`、親は `-1`
- `vector<int> restore_path(int s, int t, const vector<int>& parent)`
  親配列から `s -> t` の頂点列を復元して返す。復元できなければ空配列

## 使い方
`edge<T>` の隣接リストを作って `dijkstra_restore` を呼ぶ。
頂点列が必要なら返ってきた `parent` を `restore_path` に渡す。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto res = dijkstra_restore(0, g);
auto path = restore_path(0, t, res.parent);
```

## 実装上の補足
同じ距離の候補が複数あるとき、親は更新しない。
返る経路は最短路のひとつであり、一意性は保証しない。
