---
title: スライド最小値(最大値)
documentation_of: //datastructure/slidingwindow.cpp
date: 2018-04-28
category: データ構造
tags: データ構造
---

## 説明
配列の区間 `[l, r)` の最小値または最大値をデックで管理する。
`slideR()` で右端を 1 つ伸ばし、`slideL()` で左端を 1 つ縮める。

## できること
配列長を $N$、比較を $O(1)$ とする。

- `sliding_window<T, F> sw(v, f)`
  配列 `v` と比較関数 `f` で初期化する。配列をコピーする。$O(N)$
- `void slideR()`
  右端 `r` を 1 つ進めて `v[r]` を入れる。`r < N` を前提とする。償却 $O(1)$
- `void slideL()`
  左端 `l` を 1 つ進める。空でない区間で使う。$O(1)$
- `int get_index()`
  現在の最良要素の添字を返す。空区間なら `0`。$O(1)$
- `T value()`
  現在の最良値を返す。空区間なら `0`。$O(1)$
- `void reset()`
  区間を空に戻す。$O(N)$
- `void set(vector<T>& u)`
  配列 `u` をコピーし、区間を空に戻す。$O(N)$

## 使い方
`f(a, b)` は `a` を残すべきなら `true` を返す比較にする。
最小値なら `[](T a, T b){ return a < b; }`、最大値なら `[](T a, T b){ return a > b; }` の形で使う。

## 実装上の補足
添字をデックで持つ。各要素は高々1回ずつ追加・削除される。
