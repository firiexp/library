---
title: 有理型母関数のn項(N-th Term)
documentation_of: //fps/nth_term.cpp
---
## 説明
有理型母関数 `P(x) / Q(x)` の `x^n` の係数を求める。
線形漸化式の第 `n` 項計算を Bostan-Mori 法で処理する低レベル部品である。

## できること
- `mint nth_term(poly p, poly q, ll n)`
  `P(x) / Q(x)` の `x^n` 係数を返す

## 使い方
`q[0] != 0` を満たす多項式 `p`, `q` を渡す。
線形漸化式 `a_n = c_0 a_{n-1} + ... + c_{k-1} a_{n-k}` なら、`Q(x) = 1 - c_0 x - ... - c_{k-1} x^k` を作って使う。

```cpp
poly q(k + 1);
q[0] = 1;
for (int i = 0; i < k; ++i) q[i + 1] = -c[i];
poly p = (poly(a) * q).cut(k);
mint ans = nth_term(p, q, n);
```

## 実装上の補足
NTT を使うので法は `998244353` 固定である。
`p` と `q` は関数内で破壊的に変更されるため、値渡しになっている。
