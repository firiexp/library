---
title: 任意MOD畳み込み(3 NTT + Garner)
documentation_of: //math/fft.cpp
date: 2026-03-15
category: 数学
tags: 数学
---

## 説明
3 つの NTT 友好素数で畳み込み、Garner で任意 MOD に復元する。
複素 FFT を使わないので誤差がなく、計算量は $O(N \log N)$。

## できること
- `vector<unsigned int> ArbitraryConvolution::convolution_mod(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  `MOD` 上の畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> ArbitraryConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  整数値を保ったまま畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> ArbitraryConvolution::square_u64(const vector<unsigned int>& a)`
  整数値を保ったまま自己畳み込みを返す。空なら空配列
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す
- `poly inv() const`
  定数項が 0 でない多項式の逆数を返す

## 使い方
`MOD` を先に定義してから読み込む。
`poly` に係数を入れて `a * b` を呼べばよい。
exact な整数値が必要なら `ArbitraryConvolution::convolution_u64` か `ArbitraryConvolution::square_u64` を使う。

## 実装上の補足
3 素数は `167772161`, `469762049`, `1224736769` を使う。
`square_u64` は self-convolution 専用に、各 mod で変換 1 回で済む経路を持つ。
Library Checker の `convolution_mod_1000000007` は verify 済み。
