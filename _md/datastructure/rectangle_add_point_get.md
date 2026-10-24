---
title: 長方形加算点取得(Rectangle Add Point Get)
documentation_of: //datastructure/rectangle_add_point_get.cpp
date: 2026-03-11
category: データ構造
tags: データ構造
---

## 説明
長方形加算と点取得をまとめて処理する。
長方形の端点を座標圧縮した 2 次元 BIT で、操作を登録順に処理する。

## できること
長方形数を $R$、クエリ数を $Q$ とする。

- `RectangleAddPointGet<T> solver`
  空の solver を作る。$O(1)$
- `void add_rectangle(int l, int d, int r, int u, T w)`
  半開長方形 `[l, r) x [d, u)` に重み `w` を加える操作を積む。償却 $O(1)$
- `void add_query(int x, int y)`
  点 `(x, y)` の値を取るクエリを積む。償却 $O(1)$
- `vector<T> solve() const`
  追加順に各クエリの答えを返す。時間 $O((R+Q)\log^2 R)$、追加領域 $O((R+Q)\log R)$

## 使い方
初期長方形も更新も `add_rectangle` で積む。

## 実装上の補足
$x$ 座標の圧縮には長方形の左右端だけを使う。長方形数を $R$ とすると、圧縮は $O(R\log R)$、$x$ 方向の BIT の行数は $O(R)$。
