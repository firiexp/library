---
title: 約数列挙(Divisor)
documentation_of: //math/prime/divisor.cpp
---

## 説明
$N$ の正の約数を列挙する。

## できること
- `vector<T> divisor(T n)`
  正の整数 `n` を受け取り、正の約数を昇順で返す。$O(\sqrt n)$
- `vector<T> divisor_from_factors(const vector<T>& factors)`
  重複を含む昇順の素因数列から、その積の正の約数を昇順で重複なく返す。
  約数の個数を $D$、素因数分解に現れる最大の指数を $E$ とすると、列挙にかかる時間は $O(D\log E)$、補助領域は $O(D)$。
## 使い方
`primefactor_ll.cpp` の `prime_factor` で素因数分解した結果をそのまま渡せる。

```cpp
auto factors = prime_factor(1000000000000LL);
auto divisors = divisor_from_factors(factors);
```

## 実装上の補足
最初の素数の冪を昇順に生成する。以降は素数 $p$ の指数を $e$ として、それまでの約数列の $1,p,\ldots,p^e$ 倍を作り、隣り合う列を2本ずつマージする。
