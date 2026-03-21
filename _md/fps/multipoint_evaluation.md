---
title: Multipoint Evaluation
documentation_of: //fps/multipoint_evaluation.cpp
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
多項式 `f` の値 `f(x_i)` を複数点でまとめて計算する。
`998244353` 上の `poly` を前提にし、計算量は $O(n log^2 n)$。

## できること
- `vector<mint> poly::multipoint_eval(const vector<mint>& xs) const`
  各 `xs[i]` における値を順に返す

## 使い方
`#include "../fps/multipoint_evaluation.cpp"` を読み込む。
`poly f` を作り、`f.multipoint_eval(xs)` を呼ぶ。

## 実装上の補足
内部で subproduct tree と多項式剰余を使う。
`poly` 本体は `math/ntt.cpp` にある。
