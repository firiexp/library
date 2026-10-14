---
title: 多点評価(Multipoint Evaluation)
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
剰余は深さ優先で子へ渡し、処理済みの部分木の中間多項式は解放する。
評価点数を $m$ とすると、積の木は $O(m\log(m+1))$、各段の剰余係数の同時保持量は $O(m)$、再帰の深さは $O(\log(m+1))$。
最初に入力多項式を割る際の作業領域は入力の係数数にも依存する。
`poly` 本体は `math/ntt.cpp` にある。
