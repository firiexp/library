---
title: 逆行列(Inverse Matrix)
documentation_of: //math/inverse_matrix.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`modint` 行列の逆行列を計算する。
Gauss-Jordan 消去を使い、計算量は $O(N^3)$。

## できること
- `vector<vector<mint>> inverse_matrix(const vector<vector<mint>>& A)`
  正方行列 `A` の逆行列を返す。存在しなければ空行列を返す

## 使い方
`A` を `vector<vector<mint>>` で渡す。
返り値が空でなければ `A^{-1}` が入っている。
