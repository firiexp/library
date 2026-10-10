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

整数係数には 64 bit 以下の整数型を使い、傾き・切片は $|a|, |b| \le 2^{62}$ とする。
直線評価の積 `a*x` と和 `a*x+b` は `T` に収まる必要がある。最大値版では係数と返り値の符号反転も `T` に収まる必要がある。
これらの条件は呼び出し側で満たし、ライブラリ内では検査しない。

## 実装上の補足
整数の不要直線判定は `__int128` で差の積を比較する。上記の係数制約では差の絶対値が最大 $2^{63}$、積の絶対値が最大 $2^{126}$ となり、符号付き 128 bit に収まる。
浮動小数点型では `long double` で比較する。
直線追加は償却 $O(1)$、保持領域は $O(N)$。
