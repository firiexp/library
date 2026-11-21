---
title: オイラーのφ関数(Euler Phi)
documentation_of: //math/prime/eulerphi.cpp
---

## 説明
オイラーのφ関数 $\varphi(n)$ を求める。
$1$ 以上 $n$ 以下で $n$ と互いに素な整数の個数を返す。

## できること
- `T eulerphi(T x)`
  正の整数 `x` に対して $\varphi(x)$ を返す。`int` や `long long` に対応。$O(\sqrt{x})$
- `T eulerphi_from_factors(const vector<T>& factors)`
  昇順・重複ありの素因数列が表す整数の $\varphi$ を返す。空列なら `1`。素因数列の長さを $F$ として $O(F)$

## 使い方
`eulerphi(x)` は試し割りで素因数分解しながら $\varphi(x)=x\prod_{p\mid x}(1-1/p)$ を求める。
`eulerphi_from_factors` は素因数分解をやり直さず、`prime_factor` の結果をそのまま渡せる。

```cpp
auto phi = eulerphi(1000000000000LL);  // 400000000000
auto factors = prime_factor(1000000000000LL);
auto phi_from_factors = eulerphi_from_factors(factors);  // 400000000000
auto divisors = divisor_from_factors(factors);
```
