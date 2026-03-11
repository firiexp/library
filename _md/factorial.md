---
title: 階乗・二項係数(Factorial)
documentation_of: //math/factorial.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
階乗 `n!`、逆元 `n^{-1}`、階乗逆元 `(n!)^{-1}` を必要になったところまで遅延計算する。
`C(n, k)`、`P(n, k)`、`H(n, k)` を `O(1)` で返す。


## できること
- `Factorial<Mint = mint> f(int n = 0)`
  `0` から `n` まで前計算して作る
- `void ensure(int n)`
  `n` まで前計算を広げる
- `int max_n()`
  現在前計算済みの最大添字を返す
- `mint fact(int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint inv(int k)`
  `k^{-1}` を返す。`k < 0` なら `0`
- `mint inv_fact(int k)`
  `(k!)^{-1}` を返す。`k < 0` なら `0`
- `mint operator[](int k)`
  `k >= 0` なら `k!`、`k < 0` なら `(-k)!^{-1}` を返す
- `mint C(int n, int k)`
  二項係数を返す。
- `mint P(int n, int k)`
  順列数を返す。
- `mint H(int n, int k)`
  重複組合せを返す。
