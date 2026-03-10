---
title: Subset Convolution
documentation_of: //math/subset_convolution.cpp
date: 2026-03-10
category: 数学
tags: 数学
---

## 説明
部分集合畳み込みを計算する。
`c[S] = Σ_{T ⊆ S} a[T] b[S \ T]` を返す。
計算量は `N = 2^n` として `O(n^2 N)`。

## できること
- `vector<T> subset_convolution(vector<T> a, vector<T> b)`
  部分集合畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=` が必要。
典型的には bitmask DP の畳み込みに使う。
