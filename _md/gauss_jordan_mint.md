---
layout: post
title: Gauss Jordan Mint
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`mint` 上で Gauss-Jordan 消去を行う。
行列を簡約行基本形に変形し、階数を返す。
計算量は `O(HWmin(H, W))`。

## できること
- `int gauss_jordan(vector<vector<mint>>& A, bool is_extended = false)`
  行列 `A` を破壊的に簡約行基本形へ変形し、rank を返す。`is_extended = true` なら最後の列を拡大係数列として pivot 候補から除く

## 使い方
`A` を `vector<vector<mint>>` で渡す。
連立一次方程式 `Ax = b` を扱うときは、拡大行列 `[A | b]` を作って `is_extended = true` を指定する。

返り値の rank と、変形後の末尾行を見れば解の有無を判定できる。
自由変数の基底や特解は、変形後の pivot 列を拾って復元する。
