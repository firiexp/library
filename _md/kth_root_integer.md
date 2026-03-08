---
category: "\u6570\u5B66"
date: 2026-03-08
layout: post
tags: "\u6570\u5B66"
title: Kth Root Integer
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
