---
title: 順序木(Order Statistic Tree)
documentation_of: //datastructure/order_statistic_tree.cpp
date: 2026-05-25
category: データ構造
tags: データ構造
---

## 説明
Treap で順序付き multiset を管理する。
`find_by_order` と `order_of_key` を使って、順位から値、値から順位を求める。

## できること
要素数を $N$、比較を $O(1)$ とする。木を辿る操作は退化時に $O(N)$ となる。

- `OrderStatisticTree<T, Compare> st(seed = 2463534242u, comp = Compare())`
  空の順序統計木を作る。順序は `Compare` に従う。$O(1)$
- `void reserve(int capacity)`
  ノード領域を `capacity` 個ぶん事前確保する。確保済みノード数に比例する時間
- `int size() const`
  要素数を返す。重複分も数える。$O(1)$
- `bool empty() const`
  空なら `true`。$O(1)$
- `void insert(T x)`
  `x` を 1 個追加する。期待償却 $O(\log N)$
- `bool erase_one(T x)`
  `x` を 1 個削除する。存在しなければ `false`。期待償却 $O(\log N)$
- `int count(T x) const`
  `x` の個数を返す。存在しなければ `0`。期待 $O(\log N)$
- `bool contains(T x) const`
  `x` を含むなら `true`。期待 $O(\log N)$
- `T find_by_order(int k) const`
  `0`-indexed で `k` 番目の値を返す。`0 <= k < size()` で使う。期待 $O(\log N)$
- `int order_of_key(T x) const`
  `Compare` の順序で `x` より前にある要素数を返す。期待 $O(\log N)$

## 使い方
`insert` / `erase_one` で集合を更新し、`find_by_order(k)` と `order_of_key(x)` で順位クエリを処理する。
`Compare` は狭義弱順序を定めるものを使う。互いに前に来ない値を同値とし、重複数をまとめて持つ。

```cpp
OrderStatisticTree<long long> st;
st.insert(5);
st.insert(1);
st.insert(5);

long long x = st.find_by_order(1); // 5
int c = st.order_of_key(5);        // 1
```

## 実装上の補足
`__gnu_pbds::tree` と違い、`find_by_order` は iterator ではなく値を返す。
重複を区別したいときは `OrderStatisticTree<pair<T, int>>` のように ID を持たせる。
`Compare = greater<T>` にすると、大きい順で順位を数える。
