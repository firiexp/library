---
layout: post
title: get_prime2
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
線形篩で `n` 以下の素数を列挙する。
素数は `ExactDiv<uint>` として保持し、除算判定を高速化できる形で返す。
計算量は `O(n)`。

## できること
- `vector<ExactDiv<uint>> get_prime(int n)`
  `n` 以下の素数を返す。`n <= 1` なら空
- `bool ExactDiv<T>::divide(T x) const`
  `x` がこの素数で割り切れるかを返す

## 使い方
返り値の各要素は素数値を `val` に持つ。
試し割りを大量に行うコードでは `x % p == 0` の代わりに `p.divide(x)` を使える。
