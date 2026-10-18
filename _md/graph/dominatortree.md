---
title: Dominator Tree
documentation_of: //graph/dominatortree.cpp
---

## 説明
有向グラフの始点 `root` から到達可能な頂点について Dominator Tree を構築する。
`u` が `v` を支配するとは、始点から `v` へのすべての経路が `u` を通ることを表す。

## できること
- `void add_edge(int a, int b)`
  有向辺 `a -> b` を追加する。自己ループ・多重辺も扱う
- `void build(int root)`
  `root` を始点に Dominator Tree を構築する
- `idom[v]`
  `v` 自身を除く `v` の支配頂点のうち、他のすべてに支配される頂点（immediate dominator）。Dominator Tree では `v` の親にあたる。根と未到達頂点は `-1`
- `bool reachable(int v) const`
  始点から `v` へ到達可能かを返す
- `bool dominates(int u, int v) const`
  `u` が `v` を支配するかを返す。どちらかが未到達なら `false`。到達可能な頂点は自分自身を支配する
- `bool reachable_without_vertex(int target, int removed) const`
  `removed` を削除しても始点から `target` へ到達可能かを返す。始点や `target` 自身を削除した場合、または元から未到達なら `false`

## 使い方
`DominatorTree dt(n)` に辺を追加し、`dt.build(root)` の後でクエリを処理する。
頂点番号は `[0, n)` とする。辺の追加や始点の変更後は再度 `build` を呼ぶ。
未到達の頂点を削除しても、元から到達可能な頂点への到達性は変わらない。

## 実装上の補足
Dominator Tree の構築後、祖先判定の前処理を $O(N)$ 時間・追加領域で行う。各クエリは $O(1)$。
削除後の到達性は、元から到達可能で、削除頂点に支配されないことと同値である。
