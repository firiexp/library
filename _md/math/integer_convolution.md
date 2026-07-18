---
title: 整数畳み込み(2/3 NTT)
documentation_of: //math/integer_convolution.cpp
date: 2026-07-18
category: 数学
tags: 数学
---

## 説明

NTT と中国剰余定理で非負整数列を誤差なく畳み込む。
計算量は $O(N \log N)$。

## できること

- `vector<unsigned long long> ArbitraryConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  3 素数で畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> ArbitraryConvolution::square_u64(const vector<unsigned int>& a)`
  3 素数で自己畳み込みを返す。空なら空配列
- `vector<unsigned long long> BoundedConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  2 素数で畳み込みを返す。どちらかが空なら空配列
- `vector<unsigned long long> BoundedConvolution::square_u64(const vector<unsigned int>& a)`
  2 素数で自己畳み込みを返す。空なら空配列

## 使い方

通常は `ArbitraryConvolution` を使う。
すべての出力係数が $998244353 \times 1004535809$ 未満と保証できる場合は `BoundedConvolution` を使う。

## 実装上の補足

`ArbitraryConvolution` の出力係数は `unsigned long long` に収まる必要がある。
`BoundedConvolution` の係数上限は実行時には検査しない。
`square_u64` は各 mod の変換を 1 回に減らす。
