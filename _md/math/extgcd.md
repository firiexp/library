---
title: 拡張ユークリッド互除法(Extended GCD)
documentation_of: //math/extgcd.cpp
date: 2018-04-28
category: 数学
tags: 整数論
---

## 説明
$a, b$ が与えられるとき、

$$
ax + by = \gcd(a, b)
$$

を満たす $x, y$ を計算する。返り値は $\gcd(a, b)$。

## できること
- `T extgcd(T a, T b, T& x, T& y)`
  $ax+by=\gcd(a,b)$ を満たす係数を `x`, `y` に格納し、最大公約数を返す。$O(\log\min(a,b))$

## 使い方
`long long x, y;` を用意し、`extgcd(a, b, x, y)` を呼ぶ。
