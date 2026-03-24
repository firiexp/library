---
title: 平方根 (mod p)
documentation_of: //math/mod_sqrt.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
素数 mod で平方根を 1 つ求める。
存在しなければ `-1` を返す。
Tonelli-Shanks で計算する。

## できること
- `long long mod_sqrt(long long a, long long p)`
  `x^2 ≡ a (mod p)` を満たす `x` を 1 つ返す。存在しなければ `-1`

## 使い方
`p` は素数を仮定する。
`0 <= x < p` の解を返す。
