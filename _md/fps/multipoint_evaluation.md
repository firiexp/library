---
title: 多点評価(Multipoint Evaluation)
documentation_of: //fps/multipoint_evaluation.cpp
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
多項式 `f` の値 `f(x_i)` を複数点でまとめて計算する。
`998244353` 上の `poly` を使う。

## できること
- `vector<mint> poly::multipoint_eval(const vector<mint>& xs) const`
  各 `xs[i]` における値を順に返す。多項式の係数数と評価点数の最大値を $N$ として $O(N\log^2 N)$

## 使い方
`#include "../fps/multipoint_evaluation.cpp"` を読み込む。
`poly f` を作り、`f.multipoint_eval(xs)` を呼ぶ。

## 実装上の補足
内部で subproduct tree と多項式剰余を使う。
係数数または点数が16以下、または両者の積が4096以下なら、積の木を作らず Horner 法で評価する。
係数数を $K$、点数を $M$ として、この経路は $O(KM)$ 時間、出力を含めて $O(M)$ の追加領域を使う。
剰余木の途中でも、剰余の係数数または部分木の点数が16以下なら、その部分木を Horner 法でまとめて評価する。補間の導関数評価にも同じ処理を使う。
剰余は深さ優先で子へ渡し、処理済みの部分木の中間多項式は解放する。
評価点数を $m$ とすると、積の木は $O(m\log(m))$、各段の剰余係数の同時保持量は $O(m)$、再帰の深さは $O(\log(m))$。
最初に入力多項式を割る際の作業領域は入力の係数数にも依存する。
`poly` 本体は `math/ntt.cpp` にある。
