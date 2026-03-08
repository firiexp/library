---
title: Floor Sum
documentation_of: //math/floor_sum.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`sum_{i=0}^{n-1} floor((a i + b) / m)` を返す。
計算量は償却 `O(log m + log a)`。

## できること
- `ll floor_sum(ll n, ll m, ll a, ll b)`
  `sum_{i=0}^{n-1} floor((a i + b) / m)` を返す

## 使い方
`n = 0` なら `0` を返す。
`m > 0` を仮定する。
`a`, `b` が `m` 以上でもそのまま渡してよい。
