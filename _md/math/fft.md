---
title: 任意MOD畳み込み(3 NTT + Garner)
documentation_of: //math/fft.cpp
date: 2026-03-15
category: 数学
tags: 数学
---

## 説明
3 つの NTT 友好素数で畳み込み、Garner で任意 MOD に復元する。
複素 FFT を使わないので誤差がない。

## できること
$N$ を入力の係数数の最大値とする。

- `vector<unsigned int> ArbitraryConvolution::convolution_mod(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  `MOD` 上の畳み込みを返す。どちらかが空なら空配列。$O(N\log N)$
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す。$O(N\log N)$
- `poly inv() const`
  定数項が 0 でない多項式の逆数を返す。$O(N\log N)$

## 使い方
`MOD` を先に定義してから読み込む。
`poly` に係数を入れて `a * b` を呼べばよい。
整数値を保った畳み込みは `math/integer_convolution.cpp` を使う。

## 実装上の補足
片方が1要素ならスカラー倍、短い方が128要素以下なら直接積を計算する。
3 素数は `167772161`, `469762049`, `1224736769` を使う。
