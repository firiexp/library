---
title: Dominator Tree
documentation_of: //graph/dominatortree.cpp
---

## 説明
有向グラフの始点 `root` から到達可能な頂点について支配木を構築する。
`u` が `v` を支配するとは、始点から `v` へのすべての経路が `u` を通ることを表す。

## できること
- `void add_edge(int a, int b)`
  有向辺 `a -> b` を追加する。自己ループ・多重辺も扱う
- `void build(int root)`
  `root` を始点に支配木と問い合わせ用の入退時刻を構築する
- `idom[v]`
  `v` の immediate dominator。根と未到達頂点は `-1`
- `bool reachable(int v) const`
  始点から `v` へ到達可能かを返す
- `bool dominates(int u, int v) const`
  `u` が `v` を支配するかを返す。どちらかが未到達なら `false`。到達可能な頂点は自分自身を支配する
- `bool reachable_without_vertex(int target, int removed) const`
  `removed` を削除しても始点から `target` へ到達可能かを返す。始点や `target` 自身を削除した場合、または元から未到達なら `false`

## 使い方
`DominatorTree dt(n)` に辺を追加し、`dt.build(root)` の後で問い合わせる。
頂点番号は `[0, n)` とする。辺の追加や始点の変更後は再度 `build` を呼ぶ。
未到達の頂点を削除しても、元から到達可能な頂点への到達性は変わらない。

## 実装上の補足
支配木の構築後、祖先判定用の入退時刻を $O(N)$ 時間・追加領域で作る。各問い合わせは $O(1)$。
構築中の bucket 配列を子の列挙に再利用し、入退時刻の計算は再帰を使わない。
削除後の到達性は、元から到達可能で、削除頂点に支配されないことと同値である。
