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
追加した直線数を $N$ とする。クエリは1本以上追加してから呼ぶ。

- `CHT<T, false> cht`
  最小値を取る CHT を作る。$O(1)$
- `CHT<T, true> cht`
  最大値を取る CHT を作る。$O(1)$
- `CHT<T, get_max, true> cht`
  直線IDを保持する CHT を作る。`get_max` は最小値なら `false`、最大値なら `true`。$O(1)$
- `void add_line(T a, T b, int id = -1)`
  直線 `y = ax + b` を追加する。第3 template 引数が `true` の場合は `id` を関連付ける。償却 $O(1)$
- `T query(T x)`
  任意順クエリで最良値を返す。$O(\log N)$
- `T query_increase(T x)`
  `x` が単調増加するときの最良値を返す。償却 $O(1)$
- `T query_decrease(T x)`
  `x` が単調減少するときの最良値を返す。償却 $O(1)$
- `pair<T, int> query_with_id(T x)`
  任意順クエリで `{最良値, 直線ID}` を返す。第3 template 引数が `true` の CHT で使う。$O(\log N)$
- `pair<T, int> query_increase_with_id(T x)` / `query_decrease_with_id(T x)`
  対応する単調順クエリで `{最良値, 直線ID}` を返す。第3 template 引数が `true` の CHT で使う。償却 $O(1)$

## 使い方
追加する直線の傾きは単調である必要がある。
クエリの `x` が単調なら `query_increase` または `query_decrease`、任意順なら `query` を使う。
ID付きの問い合わせも同じ順序の制約に従う。単調問い合わせは不要な直線を削除するので、後から問い合わせの向きを変えない。
同じ最良値を達成する直線が複数あれば、そのうち1本のIDを返す。最小IDは保証しない。
IDは利用側で指定する整数で、重複も許す。省略時は `-1` を使う。
DPの遷移元を復元するときは `cht.add_line(a, b, state)` のように状態番号を渡す。

整数係数には 64 bit 以下の整数型を使い、傾き・切片は $|a|, |b| \le 2^{62}$ とする。
直線評価の積 `a*x` と和 `a*x+b` は `T` に収まる必要がある。最大値版では係数と返り値の符号反転も `T` に収まる必要がある。
これらの条件は呼び出し側で満たし、ライブラリ内では検査しない。

## 実装上の補足
整数の不要直線判定は `__int128` で差の積を比較する。上記の係数制約では差の絶対値が最大 $2^{63}$、積の絶対値が最大 $2^{126}$ となり、符号付き 128 bit に収まる。
浮動小数点型では `long double` で比較する。
保持領域は $O(N)$。
