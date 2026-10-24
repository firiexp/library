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

## 実装上の補足
$p\equiv 1\pmod 4$ では、$p-1=q2^s$ の分解と平方非剰余から作る初期値を、スレッドごとに直近の1つの法について保持する。追加領域は $O(1)$。
同じ法の反復ではこの前処理を再利用し、法が変われば作り直す。各照会の反復変数は別に持つ。
`a == 0`、`p == 2`、$p\equiv 3\pmod 4$ の短絡処理と、平方非剰余に対する `-1` は変わらない。
