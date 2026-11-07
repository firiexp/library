---
title: オイラーのφ関数(Euler Phi)
documentation_of: //math/prime/eulerphi.cpp
date: 2026-11-07
category: 数学
tags: 数学
---

## 説明
Euler の totient function `phi(n)` を求める。
整数 `n` と互いに素な1以上 `n`  以下の整数の個数を返す。

## できること
- `int eulerphi(int x)`
  正の整数 `x` に対して `phi(x)` を返す。$O(\sqrt{x})$
- `T eulerphi_from_factors(const vector<T>& factors)`
  昇順・重複ありの素因数列が表す整数の `phi` を返す。空列は1を返す。
  素因数列の長さを $F$ として時間 $O(F)$、追加領域 $O(1)$。

## 使い方
`eulerphi(x)` は試し割りで素因数分解しながら $\varphi(x)=x\prod_{p\mid x}(1-1/p)$ を求める。

`eulerphi_from_factors` は素因数分解をやり直さず、`prime_factor` の結果をそのまま渡せる。

```cpp
auto factors = prime_factor(1000000000000LL);
long long phi = eulerphi_from_factors(factors);
auto divisors = divisor_from_factors(factors);
```

