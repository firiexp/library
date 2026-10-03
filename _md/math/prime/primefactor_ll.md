---
title: 素因数分解(Pollard Rho)
documentation_of: //math/prime/primefactor_ll.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
小さい素因数を試し割りで落とした後、Miller-Rabin と Pollard's rho で $1 \le n < 2^{63}$ の整数を素因数分解する。
重複を含む素因数列を昇順で返す。

## できること
- `bool miller_rabin(T n)`
  $n < 2^{63}$ の整数 `n` が素数なら `true`、それ以外は `false` を返す
- `T pollard_rho2(T n)`
  $4 \le n < 2^{63}$ の合成数 `n` の非自明因子を 1 つ返す
- `vector<T> prime_factor(T n)`
  $1 \le n < 2^{63}$ の整数 `n` の素因数を昇順で返す。重複も含む。`n = 1` なら空

## 使い方
`long long` や `unsigned long long` の整数に使う。
`prime_factor(n)` は内部で再帰分解し、最後にソートして返す。

## 実装上の補足
Pollard's rho では Montgomery 乗算を使い、値が十分小さい場合は各演算後の正規化を省く。
大きい半素数には短い Pollard's $p-1$ を併用し、完全平方数は平方根を再帰的に分解する。
大量の小さいクエリだけなら `get_min_factor.cpp` や `primefactor.cpp` のほうが軽いことがある。
