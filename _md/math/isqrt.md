---
title: 整数平方根(Integer Square Root)
documentation_of: //math/isqrt.cpp
---

## 説明
`floor(sqrt(x))` を返す。
`sqrtl` の結果を起点に前後へ補正して誤差を潰す。

## できること
- `ull Isqrt(const ull& x)`
  $\lfloor \sqrt{x} \rfloor$ を返す。$O(1)$

## 使い方
`unsigned long long` 範囲で使う。