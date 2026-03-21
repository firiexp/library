---
title: Bitwise OR Convolution
documentation_of: //math/or_convolution.cpp
date: 2026-03-10
category: 数学
tags: 数学
---

## 説明
bitwise OR 畳み込みを計算する。
`c[S] = Σ_{A | B = S} a[A] b[B]` を返す。
計算量は $O(N log N)$。

## できること
- `void subset_zeta_transform(vector<T>& v)`
  subset zeta transform をその場適用する
- `void subset_mobius_transform(vector<T>& v)`
  subset zeta transform の逆変換をその場適用する
- `vector<T> or_convolution(vector<T> a, vector<T> b)`
  OR 畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=`, `*=` が必要。
OR 畳み込み以外にも subset zeta / mobius transform を単体で使える。
