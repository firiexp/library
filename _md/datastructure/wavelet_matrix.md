---
title: Wavelet Matrix
documentation_of: //datastructure/wavelet_matrix.cpp
date: 2026-04-18
category: データ構造
tags: データ構造
---

## 説明
静的配列に対して、区間内の順序統計量・値の出現回数・前駆/後継検索を扱うデータ構造。

## 計算量
- 構築: $O(N \log \sigma)$
- `count_less` / `range_freq` / `freq`: $O(\log \sigma)$
- `kth_smallest` / `kth_largest`: $O(\log \sigma)$

$N$ は配列長、$\sigma$ は異なる値の個数。

## 使い方
1. `WaveletMatrix<T> wm(v);` で配列 `v` から構築する。
2. 事前に座標圧縮したなら `wm.build_from_index(idx, sorted_vals);` でも構築できる。
3. 区間 `[l, r)` に対して以下を呼ぶ。

## できること
- `build_from_index(idx, sorted_vals)` : 圧縮済み index 列 `idx` と昇順の値列 `sorted_vals` から構築する
- `count_less(l, r, x)` : 区間 $[l, r)$ のうち `x` 未満の個数を返す
- `count_less_index(l, r, xi)` : 区間 $[l, r)$ のうち圧縮 index `xi` 未満の個数を返す
- `range_freq(l, r, lower, upper)` : 区間 $[l, r)$ のうち $lower \le a_i < upper$ の個数を返す
- `freq(l, r, x)` : 区間 $[l, r)$ における `x` の出現回数を返す
- `count_equal_index(l, r, xi)` : 区間 $[l, r)$ における圧縮 index `xi` の出現回数を返す
- `top_k_freq(l, r, k)` : 区間 $[l, r)$ で頻度上位 `k` 個の `(頻度, 値)` を返す。同頻度なら値昇順
- `kth_smallest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に小さい値を返す
- `kth_largest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に大きい値を返す
- `prev_value(l, r, upper, res)` : 区間 $[l, r)$ にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`
- `next_value(l, r, lower, res)` : 区間 $[l, r)$ にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは query 側も index API を使うと二分探索を省ける。
- クエリはすべて静的配列前提。
