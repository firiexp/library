---
title: 行列の階数
documentation_of: //math/linear_algebra/matrix_rank.cpp
date: 2026-10-18
category: 数学
tags: 数学
---

## 説明
素数を法とする `mint` の行列から、前進消去で階数を求める。

## できること
- `int matrix_rank(vector<vector<mint>> A)`
  行列の階数を返す。空行列・0列の行列では `0`。$H$ 行 $W$ 列に対し、時間 $O(HW\min(H,W))$、作業領域 $O(HW)$

## 使い方
各行の長さが等しい行列を渡す。
元の行列が不要なら `matrix_rank(std::move(A))` でコピーを省ける。
簡約行基本形も必要な場合は `gauss_jordan` を使う。

## 実装上の補足
pivot 行を正規化せず、下側の未確定行だけを消去する。
消去済みの列は以降参照せず、上側の行も更新しない。
