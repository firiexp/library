---
category: "\u6570\u5B66"
date: 2026-03-08
layout: post
tags: "\u6570\u5B66"
title: Mod Sqrt
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
