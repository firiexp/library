---
title: 連立一次方程式の解空間
documentation_of: //math/solve_linear_system.cpp
date: 2026-10-08
category: 数学
tags: 数学
---

## 説明
素数 mod の `mint` 上で、$Ax=b$ を満たす解を1つと、そこからすべての解を表すためのベクトル列を求める。
$N$ 行 $M$ 列の消去に $O(NM\min(N,M))$、基底の出力に $O(M(M-\mathrm{rank}))$ かかる。
入力のコピーと拡大係数列の作成に $O(NM)$、解ベクトルの確保に $O(M)$ を使う。

## できること
- `optional<LinearSystemSolution> solve_linear_system(A, b, int variables = -1)`
  入力 `A`, `b` を保持し、$Ax=b$ の解を1つと、すべての解を表すためのベクトル列を返す。解がなければ `nullopt`
- `LinearSystemSolution::rank`
  係数行列 `A` の階数
- `LinearSystemSolution::particular`
  $Ax=b$ を満たす長さ $M$ のベクトルを1つ持つ。消去で自由に選べる変数を0にした解
- `LinearSystemSolution::basis`
  $Av=0$ を満たす、互いに一次独立な長さ $M$ のベクトルを $M-\mathrm{rank}$ 本持つ。各ベクトルに任意の係数を掛けて `particular` に加えると、すべての解を表せる

## 使い方
`A` は `vector<vector<mint>>`、`b` は行数と同じ長さの `vector<mint>` で渡す。
通常は `auto sol = solve_linear_system(A, b);` とする。
成功時の全解は `sol->particular` に `sol->basis` の任意の線形結合を加えたものになる。
一意解では `basis` が空になる。

行数0では省略時の変数数を0とする。正の変数数が必要なら第3引数に指定する。
行数が正の場合は列数を自動で推論し、第3引数を渡す場合は列数と一致させる。
変数数0では `b` が全零のときだけ成功し、`particular` と `basis` はともに空になる。

## 例
mod 5 で $x+y=3$ を解くと、`particular = {3, 0}`、`basis = { {4, 1} }` になる。
すべての解は $(x,y)=(3,0)+t(4,1) \pmod 5$ と表せる。
例えば $t=1$ なら $(2,1)$、$t=3$ なら $(0,3)$ が得られる。
