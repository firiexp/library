---
title: 区間篩による素数列挙と素因数分解
documentation_of: //math/prime/segmented_sieve.cpp
---

## 説明

半開区間 $[l,r)$ の素数を列挙する。区間内の各整数をまとめて素因数分解することもできる。

## できること

$0 \le l \le r$ とし、区間幅を $W=r-l$ とする。空区間ではどちらの関数も空配列を返す。
空でない区間では、篩に使う素数の上限 $\lfloor\sqrt{r-1}\rfloor$ が `int` に収まる必要がある。
どちらも時間は $O((\sqrt r+W)\log\log r)$、返り値を除く作業領域は $O(\sqrt r+W)$。

- `vector<long long> segmented_primes(long long l, long long r)`
  区間内の素数を昇順で返す。0 と 1 は含まない。
- `vector<vector<long long>> segmented_prime_factors(long long l, long long r)`
  長さ $W$ の配列 `factors` を返す。`factors[x - l]` は整数 $x$ の素因数を重複も含めて昇順に並べた列である。
  0 は素因数分解できないため、その位置を空配列にする。1 の素因数列も空になる。
  重複を含む素因数の総数を $F$ とすると、返り値は $O(W+F)$ の領域を使う。

## 使い方

```cpp
auto primes = segmented_primes(14, 20);  // {17, 19}
auto factors = segmented_prime_factors(14, 20);
auto f = factors[18 - 14];  // {2, 3, 3}
```
