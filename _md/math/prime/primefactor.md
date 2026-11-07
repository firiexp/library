---
title: 素因数分解(試し割り)
documentation_of: //math/prime/primefactor.cpp
date: 2026-11-07
category: 数学
tags: 数学
---

## 説明
前計算した小さい素数列を使って整数を素因数分解する。

## できること
- `vector<T> prime_factor_trial(T n)`
  `n` の素因数を昇順で列挙して返す。重複も含み、`n = 1` なら空列

## 使い方
`primefactor_ll.cpp` の `prime_factor(n)` や `get_prime.cpp` の素数列挙と併用できる。

## 実装上の補足
`n = 1` は $O(1)$ で返す。試し割りで残余が1になった時点で終了するため、小さい素因数だけで分解できる入力では素数表の残りを走査しない。
最悪では32000以下の全素数を調べる。素数表以外の作業領域は返す素因数列の $O(\log n)$。
