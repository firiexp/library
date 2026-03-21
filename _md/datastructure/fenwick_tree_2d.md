---
title: 2次元Fenwick Tree(2D BIT)
documentation_of: //datastructure/fenwick_tree_2d.cpp
date: 2026-03-11
category: データ構造
tags: データ構造
---

## 説明
更新される点集合を先に登録してから構築する座圧 2 次元 BIT。
点加算と半開長方形和を各 $O(log^2 N)$ で扱う。

## できること
- `FenwickTree2D<T> fw`
  空の 2 次元 BIT を作る
- `void add_point(int x, int y)`
  今後更新する可能性がある点 `(x, y)` を登録する
- `void build()`
  登録済みの点から内部座圧を構築する
- `void add(int x, int y, T w)`
  登録済みの点 `(x, y)` に `w` を加える。未登録点は使えない
- `T sum(int x, int y)`
  半開長方形 `(-inf, x) x (-inf, y)` の総和を返す
- `T sum(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の総和を返す

## 使い方
更新に使う全点を `add_point` で登録してから `build()` する。
`build()` 後は `add` と `sum` を任意順に呼べる。
