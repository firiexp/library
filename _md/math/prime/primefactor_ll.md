---
title: 素因数分解(Pollard Rho)
documentation_of: //math/prime/primefactor_ll.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
小さい素因数を試し割りで落とした後、Miller-Rabin と Pollard's rho で 64bit 整数を素因数分解する。
重複を含む素因数列を昇順で返す。
`primefactor` 系で `64bit` 整数を扱うならこれを使う。

## できること
- `bool miller_rabin(T n)`
  `n` が素数なら `true` を返す
- `T pollard_rho2(T n)`
  `n` の非自明因子を 1 つ返す
- `vector<T> prime_factor(T n)`
  `n` の素因数を昇順で返す。重複も含む

## 使い方
`unsigned long long` 相当の整数に使う。
`prime_factor(n)` は内部で再帰分解し、最後にソートして返す。

## 実装上の補足
Montgomery 乗算を使っている。
大量の小さいクエリだけなら `get_min_factor.cpp` や `primefactor.cpp` のほうが軽いことがある。
