---
title: 線形篩(Linear Sieve)
documentation_of: //math/prime/linear_sieve.cpp
date: 2026-11-07
category: 数学
tags: 数学
---

## 説明
`0..n` の素数列挙を線形篩で前計算する。

## できること
- `LinearSieve sieve(int n, bool need_min_factor = false, bool need_phi = false, bool need_mobius = false)`
  `0..n` を前計算する。$O(n)$
- `vector<int> primes`
  `n` 以下の素数を昇順で持つ
- `vector<int> min_factor`
  `min_factor[x]` に `x` の最小素因数を持つ。`need_min_factor = true` のときのみ。 `min_factor[1] = 1`
- `vector<int> phi`
  `phi[x] = φ(x)` を持つ。`need_phi = true` のときのみ。
- `vector<int> mobius`
  `mobius[x] = μ(x)` を持つ。`need_mobius = true` のときのみ。
- `bool is_prime(int x)`
  `x` が素数なら `true`、範囲外または合成数なら `false`。$O(1)$
- `vector<int> prime_factor(int x) const`
  `x` の素因数を昇順・重複ありで返す。`x = 1` なら空。 `need_min_factor = true` のときのみ。

## 使い方

```cpp
LinearSieve sieve(n);
auto primes = sieve.primes;

LinearSieve table(n, true, true, true);
int p = table.min_factor[x];
int phi_x = table.phi[x];
int mu_x = table.mobius[x];
```

同じ上限以下の整数を何度も分解する場合は、最小素因数表を一度作って使い回す。
分解結果は `divisor.cpp` の `divisor_from_factors` にそのまま渡せる。

```cpp
LinearSieve sieve(1000000, true);
for (int x : {360, 997, 1000000}) {
    auto factors = sieve.prime_factor(x);
    auto divisors = divisor_from_factors(factors);
}
```

## 実装上の補足
`get_min_factor.cpp`, `eulerphi_all.cpp`, `mobius_all.cpp`, `get_prime2.cpp` はこの前計算の薄い wrapper になっている。
`get_prime.cpp` は wheel sieve による素数列挙を使う。
