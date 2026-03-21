---
title: 素因数分解(試し割り)
documentation_of: //math/primefactor.cpp
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

