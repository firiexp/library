---
title: 連立一次方程式の解空間
documentation_of: //math/solve_linear_system.cpp
date: 2026-10-08
category: 数学
tags: 数学
---

## 説明
素数法の `mint` 上で $Ax=b$ の特解と零空間の基底を求める。
$N$ 行 $M$ 列の消去に $O(NM\min(N,M))$、基底の出力に $O(M(M-\mathrm{rank}))$ かかる。
入力のコピーと拡大係数列の作成に $O(N(M+1))$、特解の確保に $O(M)$ を使う。

## できること
- `optional<LinearSystemSolution> solve_linear_system(A, b, int variables = -1)`
  入力 `A`, `b` を保持して解空間を返す。解がなければ `nullopt`
- `LinearSystemSolution::rank`
  係数行列 `A` の階数
- `LinearSystemSolution::particular`
  長さ $M$ の特解
- `LinearSystemSolution::basis`
  零空間の基底。長さ $M$ のベクトルを $M-\mathrm{rank}$ 本持つ

## 使い方
`A` は `vector<vector<mint>>`、`b` は行数と同じ長さの `vector<mint>` で渡す。
通常は `auto sol = solve_linear_system(A, b);` とする。
成功時の全解は `sol->particular` に `sol->basis` の任意の線形結合を加えたものになる。
一意解では `basis` が空になる。

行数0では省略時の変数数を0とする。正の変数数が必要なら第3引数に指定する。
行数が正の場合は列数を自動で推論し、第3引数を渡す場合は列数と一致させる。
変数数0では `b` が全零のときだけ成功し、特解と基底はともに空になる。
