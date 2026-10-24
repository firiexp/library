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
- `MultipointEvaluator evaluator(xs)`
  点列から、積の木を構築する。点数を $M$ として $O(M\log^2 M)$ 時間、保持領域 $O(M\log M)$
- `vector<mint> evaluator.eval(const poly& f) const`
  構築時の xs で評価する。時間は単発の評価と同じ
- `poly evaluator.interpolate(const vector<mint>& ys)`
  構築時の点列と `ys` から補間する。点は相異なり、`ys.size()` は点数と等しいことが必要。

## 使い方
`#include "../fps/multipoint_evaluation.cpp"` を読み込む。
`poly f` を作り、`f.multipoint_eval(xs)` を呼ぶ。
同じ点を何度も使う場合は `MultipointEvaluator evaluator(xs)` を1回作り、`evaluator.eval(f)` を繰り返す。
元の `xs` や多項式を後から変更しても、評価点と以前の返却値は変わらない。

## 実装上の補足
内部で subproduct tree と多項式剰余を使う。
係数数または点数が16以下、または両者の積が4096以下なら、積の木を作らず Horner 法で評価する。
係数数を $K$、点数を $M$ として、この経路は $O(KM)$ 時間、出力を含めて $O(M)$ の追加領域を使う。
剰余木の途中でも、剰余の係数数または部分木の点数が16以下なら、その部分木を Horner 法でまとめて評価する。補間の導関数評価にも同じ処理を使う。
剰余は深さ優先で子へ渡し、処理済みの部分木の中間多項式は解放する。
評価点数を $m$ とすると、積の木は $O(m\log(m))$、各段の剰余係数の同時保持量は $O(m)$、再帰の深さは $O(\log(m))$。
最初に入力多項式を割る際の作業領域は入力の係数数にも依存する。
`poly` 本体は `math/ntt.cpp` にある。
