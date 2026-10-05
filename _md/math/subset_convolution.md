---
title: 部分集合畳み込み(Subset Convolution)
documentation_of: //math/subset_convolution.cpp
date: 2026-03-10
category: 数学
tags: 数学
---

## 説明
部分集合畳み込みを計算する。
`c[S] = Σ_{T ⊆ S} a[T] b[S \ T]` を返す。
計算量は `N = 2^n` として時間 $O(n^2 N)$、領域 $O(nN)$。rank table は $N(n+1)$ 要素を 2 本使う。

## できること
- `vector<T> subset_convolution(vector<T> a, vector<T> b)`
  部分集合畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張し、足りない要素を 0 とする。両方空なら長さ 1 の零配列を返す

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=` が必要。
加法は可換群、乗法は加法に対して分配的であることを要求する。乗法の可換性は不要で、各項は `a[T] * b[S \ T]` の順で計算する。
典型的には bitmask DP の畳み込みに使う。
