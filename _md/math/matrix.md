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
  正方行列の $k$ 乗を返す。`k = 0` なら単位行列

## 使い方
`H` に `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を定義して使う。
可変サイズの行列を素直に扱いたいときに使う。
