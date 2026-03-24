---
title: NTT・形式的冪級数(NTT/FPS)
documentation_of: //math/ntt.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`998244353` 上の NTT と、形式的冪級数 `poly` の基本演算をまとめた実装。
多項式積、逆数、対数、指数、冪、平方根を扱う。

## できること
- `poly(vector<mint> a)`
  係数列から多項式を作る
- `poly operator+(const poly& g)`, `poly operator-(const poly& g)`, `poly operator*(const poly& g)`
  和・差・積を返す
- `poly diff()`, `poly integral()`
  微分・積分を返す
- `poly inv(int deg = -1)`
  逆数を `x^deg` 未満で返す。定数項が `0` なら使えない
- `poly log(int deg = -1)`
  対数を `x^deg` 未満で返す。定数項が `1` である必要がある
- `poly exp(int deg = -1)`
  指数を `x^deg` 未満で返す。定数項が `0` である必要がある
- `poly pow(long long k, int deg = -1)`
  `k` 乗を `x^deg` 未満で返す
- `poly sqrt(int deg = -1)`
  平方根を `x^deg` 未満で返す。存在しなければ空多項式を返す
- `mint eval(mint x)`
  1 点での値を返す

## 使い方
`#include "../math/ntt.cpp"` を読み込み、`poly` に係数列を入れて使う。
`poly` の `i` 番目は `x^i` の係数を表す。

畳み込みだけなら `f * g` を使う。
FPS 演算は必要な次数だけ `deg` を指定して切り詰める。

## 実装上の補足
`transform` は長さが 2 冪であることを前提にする。
内部 mod は `998244353` 固定。
