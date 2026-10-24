---
title: Dominator Tree
documentation_of: //graph/dominatortree.cpp
---

## 説明
有向グラフの始点 `root` から到達可能な頂点について Dominator Tree を構築する。
`u` が `v` を支配するとは、始点から `v` へのすべての経路が `u` を通ることを表す。

## できること
頂点数を $N$、辺数を $M$ とする。

- `DominatorTree dt(n)`
  `n` 頂点のグラフを作る。$O(N)$
- `void add_edge(int a, int b)`
  有向辺 `a -> b` を追加する。自己ループ・多重辺も扱う。償却 $O(1)$
- `void build(int root)`
  `root` を始点に Dominator Tree と祖先判定用の前処理を構築する。$O((N+M)\log N)$ 時間、$O(N+M)$ 領域
- `idom[v]`
  `v` 自身を除く `v` の支配頂点のうち、他のすべてに支配される頂点（immediate dominator）。Dominator Tree では `v` の親にあたる。根と未到達頂点は `-1`
- `bool reachable(int v) const`
  始点から `v` へ到達可能かを返す。$O(1)$
- `bool dominates(int u, int v) const`
  `u` が `v` を支配するかを返す。どちらかが未到達なら `false`。到達可能な頂点は自分自身を支配する。$O(1)$
- `bool reachable_without_vertex(int target, int removed) const`
  `removed` を削除しても始点から `target` へ到達可能かを返す。始点や `target` 自身を削除した場合、または元から未到達なら `false`。$O(1)$

## 使い方
`DominatorTree dt(n)` に辺を追加し、`dt.build(root)` の後でクエリを処理する。
頂点番号は `[0, n)` とする。辺の追加や始点の変更後は再度 `build` を呼ぶ。
未到達の頂点を削除しても、元から到達可能な頂点への到達性は変わらない。

## 実装上の補足
削除後の到達性は元から到達可能で、削除頂点に支配されないことと同値である。
