---
title: 整数k乗根(K-th Root Integer)
documentation_of: //math/kth_root_integer.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`floor(a^(1/k))` を求める。
二分探索で整数解を絞る。

## できること
- `ull kth_root_integer(ull a, int k)`
  `floor(a^(1/k))` を返す

## 使い方
`0 <= a < 2^64`, `1 <= k` を想定する。
内部では `x^k <= a` を `__int128` で判定する。
