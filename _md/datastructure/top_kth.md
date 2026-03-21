---
title: 上位K個を管理するデータ構造 (Treap)
documentation_of: //datastructure/top_kth.cpp
date: 2026-03-21
category: データ構造
tags: データ構造
---

## 説明
重複あり multiset を Treap で管理し、`k` 番目に大きい値と大きい方から `k` 個の総和を扱う。
各操作は期待 $O(\log N)$。

## できること
- `TopKLargestTreap<T, SumT> st(K = 0, seed = 2463534242u)`
  上位 `K` 個を基準にする空 multiset を作る
- `int k() const`
  現在の基準 `K` を返す
- `void set_k(int new_k)`
  基準 `K` を `new_k` に変える
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
- `int count(const T& x) const`
  `x` の個数を返す
- `bool contains(const T& x) const`
  `x` を含むなら `true`
- `T kth_largest(int kth) const`
  `kth` 番目に大きい値を返す。`1 <= kth <= size()` で使う
- `bool has_kth() const`
  事前に設定した `K` 番目の要素が存在するなら `true`
- `T kth_largest() const`
  `K` 番目に大きい値を返す。`has_kth()` が `true` のときに使う
- `SumT sum_largest_k(int k) const`
  大きい方から `k` 個の総和を返す。`k <= 0` なら `0`、`k >= size()` なら全要素和
- `SumT sum_topk() const`
  大きい方から `K` 個の総和を返す

## 使い方
`insert` / `erase_one` で multiset を更新し、`sum_topk()` や `kth_largest()` を読む。
`K` を途中で変えたいときは `set_k(new_k)` を使う。

たとえば「数列に値を追加・削除しながら上位 $K$ 個の和を保つ」用途にそのまま使える。
