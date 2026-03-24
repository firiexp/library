---
title: 離散対数(Discrete Logarithm)
documentation_of: //math/discrete_logarithm.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`x^k ≡ y (mod m)` を満たす最小の非負整数 `k` を求める。
解がなければ `-1` を返す。
非互いに素な場合も含めて extended BSGS で処理する。

## できること
- `long long discrete_logarithm(long long x, long long y, long long mod)`
  `x^k ≡ y (mod mod)` を満たす最小の `k` を返す。存在しなければ `-1`

## 使い方
`mod >= 1` を想定する。
計算量はおおむね $O(sqrt(mod))$。
