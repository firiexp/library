---
layout: post
title: Counting Primes
documentation_of: //math/counting_primes.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`pi(N)`、つまり `N` 以下の素数の個数を求める。
Lehmer の prime counting を使う。

## できること
- `long long counting_primes(long long n)`
  `n` 以下の素数の個数を返す

## 使い方
`1 <= n <= 10^11` を想定する。
内部では `5 * 10^6` まで篩い、`phi(x, s)` と Lehmer の分割統治で `pi(n)` を計算する。
