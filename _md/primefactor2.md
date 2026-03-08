---
layout: post
title: primefactor2
documentation_of: //math/primefactor2.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
前計算した小さい素数列を使って整数を素因数分解する。
除算判定に `ExactDiv` を使うので、通常の `%` より軽い。

## できること
- `vector<T> prime_factor(T n)`
  `n` の素因数を昇順で列挙して返す。重複も含む

## 使い方
`const auto primes = get_prime(32000);` を前提に、`32bit` 付近の整数を分解する用途を想定している。
`n` に大きい素因数が最後に 1 個だけ残った場合もそのまま返す。
