---
title: 行列
documentation_of: //math/matrix.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
一般サイズの行列に対して加算、減算、積、累乗を扱う。

## できること
- `matrix<H> A(n, m)`
  `n × m` 行列を作る
- `matrix<H> A(n)`
  `n × n` 行列を作る
- `matrix<H>::I(n)`
  `n × n` 単位行列を返す
- `A += B`, `A -= B`, `A *= B`
  同じサイズの加減算、または行列積を行う
- `A.pow(k)`
  正方行列の非負整数 $k$ 乗を返す。`k = 0` なら単位行列。$k > 0$ で $O(n^3 \log(k))$
- `A.pow_sum(k)`
  正方行列と非負整数 `k` に対し、$(A^k, I+A+\cdots+A^{k-1})$ の pair を返す。`k = 0` なら単位行列と零行列。元の行列は変わらない

## 使い方
`H` に `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を定義して使う。
可変サイズの行列を素直に扱いたいときに使う。
`auto [power, sum] = A.pow_sum(k);` で冪と累積和を同時に求める。減算や逆元は使わないため、一般の半環でも使える。

## 実装上の補足
`pow_sum` は $P(2a)=P(a)^2$、$S(2a)=S(a)+P(a)S(a)$ で倍増する。時間 $O(n^2+n^3\log(k+1))$、作業領域 $O(n^2)$。
固定幅整数を使う場合は、冪・累積和とその途中演算が係数型の範囲に収まることを前提とする。
