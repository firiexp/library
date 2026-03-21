---
title: 長方形加算点取得(Rectangle Add Point Get)
documentation_of: //datastructure/rectangle_add_point_get.cpp
date: 2026-03-11
category: データ構造
tags: データ構造
---

## 説明
長方形加算と点取得をまとめて処理する。
`x` 方向に sweep し、`y` 方向の差分を 1 次元 BIT で管理する。

## できること
- `RectangleAddPointGet<T> solver`
  空の solver を作る
- `void add_rectangle(int l, int d, int r, int u, T w)`
  半開長方形 `[l, r) x [d, u)` に重み `w` を加える操作を積む
- `void add_query(int x, int y)`
  点 `(x, y)` の値を取るクエリを積む
- `vector<T> solve()`
  追加順に各クエリの答えを返す

## 使い方
初期長方形も更新も `add_rectangle` で積む。
`solve()` は全 `y` 座標を座圧して、操作列を offline で処理する。
