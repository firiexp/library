---
title: Gauss-Jordan消去(modint)
documentation_of: //math/gauss_jordan_mint.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`mint` 上で Gauss-Jordan 消去を行う。
行列を簡約行基本形に変形し、階数を返す。
計算量は $O(HWmin(H, W))$。

## できること
- `int gauss_jordan(vector<vector<mint>>& A, bool is_extended = false)`
  行列 `A` を破壊的に簡約行基本形へ変形し、rank を返す。`is_extended = true` なら最後の列を拡大係数列として pivot 候補から除く

## 使い方
`A` を `vector<vector<mint>>` で渡す。
連立一次方程式 `Ax = b` を扱うときは、拡大行列 `[A | b]` を作って `is_extended = true` を指定する。

返り値の rank と、変形後の末尾行を見れば解の有無を判定できる。
特解と零空間の基底を直接得る場合は `math/solve_linear_system.cpp` の `solve_linear_system(A, b)` を使う。
