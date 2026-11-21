---
title: 区間篩による素数列挙と素因数分解
documentation_of: //math/prime/segmented_sieve.cpp
---

## 説明
半開区間 $[l, r)$ に含まれる素数の列挙と、区間内の各整数の素因数分解をまとめて行う。

## できること
区間幅を $W = r - l$ とする。

- `vector<long long> segmented_primes(long long l, long long r)`
  区間 $[l, r)$ の素数を昇順で返す。時間 $O((\sqrt{r} + W)\log\log r)$、作業領域 $O(\sqrt{r} + W)$
- `vector<vector<long long>> segmented_prime_factors(long long l, long long r)`
  長さ $W$ の配列を返す。`factors[x - l]` は整数 $x$ の素因数を重複込みで昇順に並べた列。時間 $O((\sqrt{r} + W)\log\log r)$、作業領域 $O(\sqrt{r} + W)$

## 使い方
$0 \le l \le r$、$\sqrt{r}$ が `int` に収まる範囲で使う。`0` と `1` の素因数列は空になる。

```cpp
auto primes = segmented_primes(14, 20);  // {17, 19}
auto factors = segmented_prime_factors(14, 20);
auto f = factors[18 - 14];  // {2, 3, 3}
```
