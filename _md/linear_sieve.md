---
title: 線形篩(Linear Sieve)
documentation_of: //math/linear_sieve.cpp
date: 2026-03-12
category: 数学
tags: 数学
---

## 説明
`0..n` の素数列挙を線形篩で前計算する。
必要なら最小素因数、`phi`、`mu` も同時に持てる。
計算量は $O(n)$。

## できること
- `LinearSieve sieve(int n, bool need_min_factor = false, bool need_phi = false, bool need_mobius = false)`
  `0..n` を前計算する
- `vector<int> primes`
  `n` 以下の素数を昇順で持つ
- `vector<int> min_factor`
  `need_min_factor = true` のときだけ埋まる。`min_factor[x]` に `x` の最小素因数を持つ。`min_factor[1] = 1`
- `vector<int> phi`
  `need_phi = true` のときだけ埋まる。`phi[x] = φ(x)` を持つ。`phi[0] = 0`, `phi[1] = 1`
- `vector<int> mobius`
  `need_mobius = true` のときだけ埋まる。`mobius[x] = μ(x)` を持つ。`mobius[0] = 0`, `mobius[1] = 1`
- `bool is_prime(int x)`
  `x` が素数なら `true`、範囲外または合成数なら `false`

## 使い方
用途ごとに配列を直接読む。

```cpp
LinearSieve sieve(n);
auto primes = sieve.primes;

LinearSieve table(n, true, true, true);
int p = table.min_factor[x];
int phi_x = table.phi[x];
int mu_x = table.mobius[x];
```

## 実装上の補足
`get_prime.cpp`, `get_min_factor.cpp`, `eulerphi_all.cpp`, `mobius_all.cpp`, `get_prime2.cpp` はこの前計算の薄い wrapper になっている。
