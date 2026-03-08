---
layout: post
title: Polynomial Interpolation
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
相異なる点列 `(x_i, y_i)` を通る次数 `n - 1` 以下の多項式を復元する。
`998244353` 上の `poly` を前提にし、計算量は `O(n log^2 n)`。

## できること
- `poly polynomial_interpolation(const vector<mint>& xs, const vector<mint>& ys)`
  `f(xs[i]) = ys[i]` を満たす多項式を返す

## 使い方
`#include "../fps/polynomial_interpolation.cpp"` を読み込む。
`xs`, `ys` を渡して `polynomial_interpolation(xs, ys)` を呼ぶ。

## 実装上の補足
`multipoint_evaluation.cpp` を内部で使う。
点 `xs[i]` は相異なることを前提にする。
