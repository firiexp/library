---
title: スライド最小値(最大値)
documentation_of: //datastructure/slidingwindow.cpp
date: 2018-04-28
category: データ構造
tags: データ構造
---

## 説明
デックで区間 `[l, r)` の最良要素を保つ補助。
`slideR()` で右端を 1 つ伸ばし、`slideL()` で左端を 1 つ縮める。

## できること
- `sliding_window<T, F> sw(v, f)`
  配列 `v` と比較関数 `f` で初期化する
- `void slideR()`
  右端 `r` を 1 つ進めて `v[r]` を入れる
- `void slideL()`
  左端 `l` を 1 つ進める
- `T get_index()`
  現在の最良要素の添字を返す。空区間なら `0`
- `T value()`
  現在の最良値を返す。空区間なら `0`
- `void reset()`
  区間を空に戻す
- `void set(vector<T>& u)`
  参照先を差し替えて状態を初期化する

## 使い方
`f(a, b)` は `a` を残すべきなら `true` を返す比較にする。
最小値なら `[](T a, T b){ return a < b; }`、最大値なら `[](T a, T b){ return a > b; }` の形で使う。

## 実装上の補足
添字をデックで持つので、各操作は償却 $O(1)$。
空区間で `get_index()` や `value()` を呼ぶと `0` を返す。
