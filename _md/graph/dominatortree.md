---
title: Dominator Tree
documentation_of: //graph/dominatortree.cpp
---

## 説明
頂点 $r$ から任意の頂点に到達可能であるとき、$r$ を始点とした Dominator Tree を構築する。

## できること
- `add_edge(a, b)` : 有向辺 `a -> b` を追加する
- `build(root)` : `root` を始点に Dominator Tree を構築する
- `idom[v]` : 構築後の `v` の immediate dominator を返す。根と未到達頂点は `-1`
