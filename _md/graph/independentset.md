---
title: 最大独立集合(Maximum Independent Set)
documentation_of: //graph/independentset.cpp
date: 2018-04-28
category: グラフ
tags: グラフ
---

## 説明
グラフの最大独立集合（補グラフの最大クリーク）を求める。
頂点数は $0\le V\le64$。補グラフの候補を貪欲彩色し、現在の最良解を改善できない枝を省く。

## できること
- `IndependentSet(n)`：辺のない $n$ 頂点グラフを作る
- `add_edge(u, v)`：異なる2頂点の間に無向辺を追加する
- `maximum_independent_set()`：最大サイズと頂点の bitmask を返す。同じサイズなら最大の mask を返す。空グラフは `(0, 0)`

## 使い方
辺を追加して `maximum_independent_set()` を呼ぶ。再実行や辺追加後の呼び直しもできる。

## 実装上の補足
Bron–Kerbosch 法の pivot を使う。補グラフの色数は、残りのクリークサイズの上界になる。
同サイズの解が残るときは、候補全体の mask も比較して tie-break を保つ。
三角形を並べたグラフなどで不要な極大解の列挙を減らすが、最悪時の指数時間は残る。
各部分集合は高々1回探索され、彩色と pivot 選択を含む保守的な時間上界は $O(V^2 2^V)$、領域は $O(V)$。
探索がもともと短い入力では、彩色の追加費用により遅くなる場合がある。
