---
title: 最大独立集合(Maximum Independent Set)
documentation_of: //graph/independentset.cpp
date: 2018-04-28
category: グラフ
tags: グラフ
---

## 説明
グラフの最大独立集合（補グラフの最大クリーク）を求める。
計算量は $O(3^{V/3})$ 。

## 実装上の補足
互いに辺で結ばれていない $V/3$ 個の三角形からなるグラフでは、$3^{V/3}$ 個の極大独立集合を列挙する。
