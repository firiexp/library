---
title: ISqrt
documentation_of: //math/isqrt.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`floor(sqrt(x))` を返す。
`sqrtl` の結果を起点に前後へ補正して誤差を潰す。

## できること
- `ull Isqrt(const ull& x)`
  `floor(sqrt(x))` を返す

## 使い方
`unsigned long long` 範囲で使う。
平方判定や Pell 方程式の前処理で使う。
