---
layout: post
title: Euler Phi
documentation_of: //math/eulerphi.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Euler の totient function `phi(n)` を 1 点で求める。
`1` 以上の整数 `n` と互いに素な `1..n` の個数を返す。
計算量は `O(sqrt(n))`。

## できること
- `int eulerphi(int x)`
  `phi(x)` を返す

## 使い方
`x >= 1` を仮定する。
素因数分解しながら `phi(n) = n Π (1 - 1/p)` を適用する。
