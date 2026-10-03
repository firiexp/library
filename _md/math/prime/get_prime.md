---
title: 素数列挙
documentation_of: //math/prime/get_prime.cpp
date: 2026-03-12
category: 数学
tags: 数学
---

## 説明
`n` 以下の素数を wheel sieve で列挙する。
計算量は $O(n \log \log n)$。

## できること
- `vector<int> get_prime(int n)`
  `n` 以下の素数を昇順で返す。`n <= 1` なら空

## 使い方
```cpp
auto primes = get_prime(n);
```
