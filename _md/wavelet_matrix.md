---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2026-03-07
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Wavelet Matrix
---

## 概要
静的配列に対して、区間内の順序統計量・値の出現回数・前駆/後継検索を扱うデータ構造。

## 計算量
- 構築: $O(N \log \sigma)$
- `count_less` / `range_freq` / `freq`: $O(\log \sigma)$
- `kth_smallest` / `kth_largest`: $O(\log \sigma)$

$N$ は配列長、$\sigma$ は異なる値の個数。

## 使い方
1. `WaveletMatrix<T> wm(v);` で配列 `v` から構築する。
2. 区間 `[l, r)` に対して以下を呼ぶ。

## 公開メンバ
- `int count_less(int l, int r, const T &x)`
: 区間 `[l, r)` のうち `x` 未満の個数。
- `int range_freq(int l, int r, const T &lower, const T &upper)`
: 区間 `[l, r)` のうち `lower <= a[i] < upper` の個数。
- `int freq(int l, int r, const T &x)`
: 区間 `[l, r)` における `x` の出現回数。
- `T kth_smallest(int l, int r, int k)`
: 区間 `[l, r)` の `k` 番目 (0-indexed) に小さい値。
- `T kth_largest(int l, int r, int k)`
: 区間 `[l, r)` の `k` 番目 (0-indexed) に大きい値。
- `bool prev_value(int l, int r, const T &upper, T &res)`
: 区間 `[l, r)` にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`。
- `bool next_value(int l, int r, const T &lower, T &res)`
: 区間 `[l, r)` にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`。

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- クエリはすべて静的配列前提。
