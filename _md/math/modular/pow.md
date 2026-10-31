---
documentation_of: //math/modular/pow.cpp
title: 繰り返し二乗法
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
$a^x \bmod M$ を求める。

## できること
- `pow_(a, x, M)` : $a^x \bmod M$ を返す。$O(\log x)$

## 使い方
`x` は非負整数、`M` は正の整数を想定する。
型は `long long` または `unsigned long long` を使い、負の底も扱える。
返り値は `0` 以上 `M` 未満に正規化される。
`M = 1` のときは、常に `0` を返す。
