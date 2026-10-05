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

## できること
- `vector<T> subset_convolution(vector<T> a, vector<T> b)`
  部分集合畳み込みを返す。結果の長さは入力の最大長以上の最小の 2 冪とし、入力配列の不足部分は 0 で補う。両方空なら長さ 1 の零配列を返す。結果の長さを $N = 2^n$ として時間 $O(n^2 N)$、領域 $O(nN)$

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=` が必要。
加法は可換群、乗法は加法に対して分配的であることを要求する。乗法の可換性は不要で、各項は `a[T] * b[S \ T]` の順で計算する。
典型的には bitmask DP の畳み込みに使う。
