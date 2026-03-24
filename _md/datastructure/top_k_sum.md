---
title: 上位K個の和を管理する
documentation_of: //datastructure/top_k_sum.cpp
date: 2026-03-21
category: データ構造
tags: データ構造
---

## 説明
重複あり multiset を 2 分割して管理し、順序に従う先頭 `K` 個の総和を扱う。
`Largest = true` なら大きい順、`Largest = false` なら小さい順になる。
`sum_topk()` は $O(1)$、`insert` / `erase_one` は $O(\log N)$。

## できること
- `TopKSum<T, SumT, Largest> ds(K = 0)`
  順序付き先頭 `K` 個を基準にする空 multiset を作る
- `int k() const`
  現在の基準 `K` を返す
- `void set_k(int new_k)`
  基準 `K` を `new_k` に変える。計算量は $O(|new\_k-K| \log N)$
- `int size() const`
  要素数を返す。重複分も数える
- `bool empty() const`
  空なら `true`
- `SumT total_sum() const`
  全要素の総和を返す
- `void insert(const T& x)`
  `x` を 1 個追加する
- `bool erase_one(const T& x)`
  `x` を 1 個削除する。存在しなければ `false`
- `bool has_kth() const`
  事前に設定した `K` 番目の要素が存在するなら `true`
- `T kth() const`
  順序に従う `K` 番目の値を返す。`has_kth()` が `true` のときに使う
- `SumT sum_topk() const`
  順序に従う先頭 `K` 個の総和を返す

## 使い方
`selected` に先頭 `K` 個、`other` に残りを入れる 2 分割を保って使う。
値の追加・削除をしながら `sum_topk()` を高頻度に読みたい用途に向く。

`TopKSum<long long, long long, false>` とすると小さい方から `K` 個の和、`TopKSum<long long, long long, true>` とすると大きい方から `K` 個の和を扱う。

## 実装上の補足
- `kth()` は `selected` 側の境界値を返す
- `kth(int)` や `sum_k(int)` のような汎用順位クエリは持たない
