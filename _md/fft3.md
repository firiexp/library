---
layout: post
title: 高速フーリエ変換 (任意MOD, 11bit分割)
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
任意 MOD の畳み込みを、係数を 11bit ずつ 3 分割して行う FFT。
`fft.cpp` より分割数を増やして精度を安定させた版で、畳み込み回数は増える代わりに大きめの係数でも誤差が出にくい。

## できること
- `FFT::multi_mod(int n1, int n2)`
  長さ `n1`, `n2` の列 `A`, `B` を畳み込み、`FFT::C` に結果を入れる
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す
- `poly inv() const`
  定数項が 0 でない多項式の逆数を返す

## 使い方
係数列を `poly` に入れて `a * b` を呼べばよい。
法は `modint<M>` のテンプレート引数で決まり、`2^30` 程度までの任意 MOD を想定している。

## 実装上の補足
各係数を 11bit, 11bit, 残りに分解し、複素 FFT を 3 回使って復元する。
`fft.cpp` より遅いが、精度面ではこちらの方が安全。
