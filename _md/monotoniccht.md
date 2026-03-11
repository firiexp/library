---
title: Convex-Hull Trick (クエリ単調)
documentation_of: //datastructure/monotoniccht.cpp
date: 2018-04-28
category: データ構造
tags: データ構造
---

## 説明
傾き単調な直線追加と、`x` の単調クエリを高速に処理する Convex Hull Trick。
最小値版と最大値版を template 引数で切り替える。

## できること
- `CHT<T, false> cht`
  最小値を取る CHT を作る
- `CHT<T, true> cht`
  最大値を取る CHT を作る
- `void add_line(T a, T b)`
  直線 `y = ax + b` を追加する
- `T query(T x)`
  任意順クエリで最良値を返す
- `T query_increase(T x)`
  `x` が単調増加するときの最良値を返す
- `T query_decrease(T x)`
  `x` が単調減少するときの最良値を返す

## 使い方
追加する直線の傾きは単調である必要がある。
クエリだけ単調なら `query_increase` または `query_decrease` を使うと償却 $O(1)$、任意順なら `query` で $O(\log N)$。

## 実装上の補足
交点判定は `long double` を使っている。
整数型でも定数倍や境界判定が気になる場面では注意が必要。
