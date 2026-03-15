---
title: 多数階乗(Many Factorials)
documentation_of: //math/many_factorials.cpp
date: 2026-03-15
category: 数学
tags: 数学
---

## 説明
複数の `n` に対して `n! mod 998244353` をまとめて計算する。
`n >= 998244353` なら `0` を返す。

`sample_point_shift` で
`f_d(x) = \prod_{t=1}^{d} (x + t)`
の標本点を倍化構築し、必要な点だけ多点評価する。
`n` が `998244353 / 2` を超える側は Wilson の定理で小さい側へ移す。

## できること
- `vector<mint> many_factorials(const vector<long long>& ns)`
  各 `ns[i]` について `ns[i]! mod 998244353` を返す。`ns[i] >= 998244353` なら `0`

## 使い方
`#include "../math/many_factorials.cpp"` を読み込む。

```cpp
vector<long long> ns = {3, 5, 998244352};
auto ans = many_factorials(ns);
```

## 実装上の補足
ブロック長を 2 冪に取り、`(k d)!` の列を前計算して大きい部分を処理する。
各 query の端数部分は 2 進分解し、必要なブロック積だけを多点評価で取る。
