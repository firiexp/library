---
title: 逆行列(Inverse Matrix)
documentation_of: //math/inverse_matrix.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`modint` 行列の逆行列を計算する。
Gauss-Jordan 消去を使う。

## できること
- `vector<vector<mint>> inverse_matrix(const vector<vector<mint>>& A)`
  正方行列 `A` の逆行列を返す。存在しなければ空行列を返す。行列の次数を $N$ として、時間 $O(N^3)$、補助領域 $O(N^2)$

## 使い方
`A` を `vector<vector<mint>>` で渡す。
空行列に対しては空行列を返す。
返り値が空でなければ `A^{-1}` が入っている。

## 実装上の補足
入力をコピーした $N\times N$ 行列をその場で逆行列に変換する。
行交換の履歴を $O(N)$ 領域に保持し、最後に逆順の列交換で戻す。
