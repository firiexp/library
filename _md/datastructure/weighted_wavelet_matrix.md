---
title: 重み付きWavelet Matrix(Weighted Wavelet Matrix)
documentation_of: //datastructure/weighted_wavelet_matrix.cpp
date: 2026-03-26
category: データ構造
tags: データ構造
---

## 説明
静的配列に対して、区間内の `x` 未満 / 以下の個数と重みの総和を扱う。

## できること
- `WeightedWaveletMatrix<T, U> wm(v, w)`
  値配列 `v` と重み配列 `w` から構築する
- `build_from_index(idx, sorted_vals, w)`
  圧縮済み index 列 `idx` と昇順の値列 `sorted_vals`、重み列 `w` から構築する
- `count_sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数と重み和を返す
- `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の要素数と重み和を返す
- `count_sum_less_index(l, r, xi)`
  区間 $[l, r)$ のうち圧縮 index `xi` 未満の要素数と重み和を返す
- `count_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の個数を返す
- `count_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の個数を返す
- `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の重み和を返す
- `sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の重み和を返す

## 使い方
`WeightedWaveletMatrix<T, U> wm(v, w);` を作る。
圧縮済みなら `build_from_index(idx, sorted_vals, w);` でも作れる。
値で区間を絞り、その中にある要素数と重み和を同時に取りたいときに使う。

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは `count_sum_less_index` を使うと query 側の二分探索を省ける。
- クエリはすべて静的配列前提。
- 各クエリは $O(\log \sigma)$、構築は $O(N \log \sigma)$。
