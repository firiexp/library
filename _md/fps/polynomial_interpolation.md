---
title: 多項式補間(Polynomial Interpolation)
documentation_of: //fps/polynomial_interpolation.cpp
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
相異なる点列 `(x_i, y_i)` を通る次数 `n - 1` 以下の多項式を復元する。
`998244353` 上の `poly` を使う。

## できること
- `poly polynomial_interpolation(const vector<mint>& xs, const vector<mint>& ys)`
  `f(xs[i]) = ys[i]` を満たす係数数 `xs.size()` の多項式を返す。空入力には空の多項式を返す。点数を $N$ として $O(N\log^2 N)$
- `poly MultipointEvaluator::interpolate(const vector<mint>& ys)`
  構築時の点列で補間する。返却値・点の条件は単発 API と同じ。各回 $O(N\log^2 N)$ 時間で、積の木と点ごとの逆重みを再利用する

## 使い方
`#include "../fps/polynomial_interpolation.cpp"` を読み込む。
同じ長さの `xs`, `ys` を渡して `polynomial_interpolation(xs, ys)` を呼ぶ。
同じ点で値列だけを変える場合は `MultipointEvaluator evaluator(xs)` を作り、`evaluator.interpolate(ys)` を繰り返す。同じオブジェクトで `eval(f)` も使える。

## 実装上の補足
`multipoint_evaluation.cpp` を内部で使う。
点 `xs[i]` は相異なることを前提にする。
積の木を評価と補間で共有し、補間の左右の中間多項式は親を作った後に解放する。
導関数の評価値の累積積を作り、1回の逆元計算と逆順の走査で全点の重みを求める。
重み計算は $O(n+\log MOD)$ 時間、追加領域は $O(n)$。重複する点は扱わない。
再利用するオブジェクトでは逆重みを最初の補間時に作り、以後 $O(n)$ 領域で保持する。評価だけなら逆重みを作らない。
積の木は $O(n\log(n))$、補間の中間多項式は同時に $O(n)$ の領域を使う。再帰の深さは $O(\log(n))$。
