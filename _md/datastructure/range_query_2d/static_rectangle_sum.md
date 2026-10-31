---
title: 静的長方形和(Static Rectangle Sum)
documentation_of: //datastructure/range_query_2d/static_rectangle_sum.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
静的な重み付き点集合に対して、長方形内の重み和をまとめて処理する。
`x` 方向の sweep と `y` 上の BIT を使う。

## できること
点数を $N$、クエリ数を $Q$ とする。

- `StaticRectangleSum<T> solver`
  空の solver を作る。$O(1)$
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する。償却 $O(1)$
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` のクエリを追加する。償却 $O(1)$
- `vector<T> solve() const`
  登録したすべての点を反映し、クエリの登録順に重み和を返す。時間 $O((N+Q)\log(N+Q))$、作業領域 $O(N+Q)$

## 使い方
先に点とクエリを全部追加してから `solve()` を呼ぶ。
`y` 座標は内部で座圧し、各クエリを `x < r` と `x < l` の差に分解して処理する。
座圧と BIT には点の `y` 座標だけを使い、クエリ境界は `lower_bound` で位置を求める。

## 実装上の補足
呼び出しごとに全登録内容を再計算する。
