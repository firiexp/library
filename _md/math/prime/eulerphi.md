---
title: オイラーのφ関数(Euler Phi)
documentation_of: //math/prime/eulerphi.cpp
---

## 説明
オイラーのφ関数 $\varphi(n)$ は、$1$ 以上 $n$ 以下で $n$ と互いに素な整数の個数を表す。

## できること
- `T eulerphi(T x)`
  正の整数 `x`（`int` または `long long`）を受け取り、$\varphi(x)$ を同じ型で返す。時間 $O(\sqrt{x})$、追加領域 $O(1)$。
- `T eulerphi_from_factors(const vector<T>& factors)`
  昇順・重複ありの素因数列が表す整数の `phi` を返す。空列は1を返す。
  素因数列の長さを $F$ として時間 $O(F)$、追加領域 $O(1)$。

## 使い方
`eulerphi(x)` は試し割りで素因数分解しながら $\varphi(x)=x\prod_{p\mid x}(1-1/p)$ を求める。

`eulerphi_from_factors` は素因数分解をやり直さず、`prime_factor` の結果をそのまま渡せる。

```cpp
auto phi = eulerphi(1000000000000LL);  // 400000000000
auto factors = prime_factor(1000000000000LL);
auto phi_from_factors = eulerphi_from_factors(factors);  // 400000000000
auto divisors = divisor_from_factors(factors);
```

