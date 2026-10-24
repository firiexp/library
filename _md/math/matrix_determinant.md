---
title: 行列式(Matrix Determinant)
documentation_of: //math/matrix_determinant.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`modint` 行列の行列式を計算する。
Gauss 消去を使う。

## できること
- `mint matrix_determinant(vector<vector<mint>> A)`
  正方行列 `A` の行列式を返す。特異行列なら `0`。行列の次数を $N$ として $O(N^3)$

## 使い方
`A` を `vector<vector<mint>>` で渡す。
