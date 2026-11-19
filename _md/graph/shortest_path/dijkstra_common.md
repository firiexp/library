---
title: Dijkstra法の共通実装
documentation_of: //graph/shortest_path/dijkstra_common.cpp
---

## 説明
`dijkstra.cpp`、`dijkstra_from_distances.cpp`、`dijkstra_radix_heap.cpp`、`dijkstra_restore.cpp` が共有する内部実装。
利用側では用途に応じた各 Dijkstra ライブラリを使う。

## 実装上の補足
優先度付きキューの抽象化 `DijkstraPriorityQueue<T>` と、緩和ループ `dijkstra_relax`・単一始点入口 `dijkstra_internal` を提供する。
経路復元やキュー実装の差し替えをコールバック `on_relax` とテンプレート引数 `Queue` で共通化している。
