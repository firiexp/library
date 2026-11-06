---
title: 無向グラフの全域木数
documentation_of: //graph/spanning_tree/count_spanning_trees.cpp
date: 2026-11-01
category: グラフ
tags: グラフ
---

## 説明
無向グラフの全域木について、含まれる辺の重みの積を足し合わせる。
すべての重みを1にすると全域木の個数になる。

## できること
- `SpanningTreeEdge{u, v, weight}`
  頂点 `u`, `v` を結ぶ重み `weight` の辺。重みを省略すると1
- `mint count_spanning_trees(int n, const vector<SpanningTreeEdge>& edges)`
  $\sum_T\prod_{e\in T}w_e$ を返す。非連結なら0、1頂点なら1。$N$ 頂点・$M$ 辺で、葉を繰り返し除いた後に $K$ 頂点残る場合、時間 $O(N+M+K^3)$、入力を除く作業領域 $O(N+M+K^2)$

## 使い方
`n >= 1`、頂点番号は `0` 以上 `n` 未満とする。`MOD` には素数を指定する。
平行辺はそれぞれ別の選択肢として数え、自己ループは無視する。
重みには0や負数も使える。相殺や法によって、連結でも結果が0になることがある。

```cpp
vector<SpanningTreeEdge> edges{ {0, 1}, {1, 2}, {2, 0} };
mint count = count_spanning_trees(3, edges);
edges[0].weight = 2;
mint weighted_sum = count_spanning_trees(3, edges);
```

この例では `count` は3、`weighted_sum` は5になる。

## 実装上の補足
まず自己ループを除いた次数を数える。2頂点以上で孤立点がある場合は0を返す。
葉がある場合は連結性を調べ、非連結なら行列を作らず0を返す。葉がなければ隣接表の構築と葉の除去を省き、そのまま行列式を計算する。
次数1の頂点の辺はすべての全域木で使うため、その重みを係数に掛けて頂点を除く。
次数は重みと独立に数え、平行辺をまとめない。元のグラフが木なら、この処理だけで全辺の重みの積を返す。
残った部分に行列木定理を使い、Laplacian から1頂点の行・列を除いた行列の行列式を求め、除いた辺の重みの積を掛ける。
消去には既存の `matrix_determinant` を使う。
