---
title: 行列式(Matrix Determinant)
documentation_of: //math/matrix_determinant.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`modint` 行列の行列式を計算する。
Gaussian elimination を使い、計算量は $O(N^3)$。

## できること
- `mint matrix_determinant(vector<vector<mint>> A)`
  正方行列 `A` の行列式を返す。特異行列なら `0`

## 使い方
`A` を `vector<vector<mint>>` で渡す。
入力は値渡しなので、呼び出し元の行列は壊れない。
