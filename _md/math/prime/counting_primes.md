---
title: 素数数え上げ(Prime Counting)
documentation_of: //math/prime/counting_primes.cpp
---

## 説明
`pi(N)`、つまり `N` 以下の素数の個数を求める。
Lehmer の prime counting を使う。

## できること
- `long long counting_primes(long long n)`
  `n` 以下の素数の個数 $\pi(n)$ を返す。初回のみ固定上限 $5\times 10^6$ までの前計算を行い、各クエリは $O(n^{2/3} / \log^2 n)$（$n \le 5\times 10^6$ なら前計算後 $O(1)$）

## 使い方
`1 <= n <= 10^11` を想定する。
内部では `5 * 10^6` まで篩い、`phi(x, s)` と Lehmer の分割統治で `pi(n)` を計算する。
