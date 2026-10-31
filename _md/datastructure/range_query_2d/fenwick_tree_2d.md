---
title: 2次元Fenwick Tree(2D BIT)
documentation_of: //datastructure/range_query_2d/fenwick_tree_2d.cpp
date: 2026-03-11
category: データ構造
tags: データ構造
---

## 説明
更新される点集合を先に登録してから構築する座圧 2 次元 BIT。
点加算と半開長方形和を扱う。

## できること
登録点数を $N$ とする。

- `FenwickTree2D<T> fw`
  空の 2 次元 BIT を作る。$O(1)$
- `void add_point(int x, int y)`
  今後更新する可能性がある点 `(x, y)` を登録する。償却 $O(1)$
- `void build()`
  登録済みの点から内部座圧を構築する。空集合・重複登録も扱える。呼び出しは1回に限る。$O(N\log N)$
- `void add(int x, int y, T w)`
  登録済みの点 `(x, y)` に `w` を加える。未登録点は使えない。$O(\log^2 N)$
- `T sum(int x, int y)`
  半開長方形 `(-inf, x) x (-inf, y)` の総和を返す。$O(\log^2 N)$
- `T sum(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の総和を返す。`l <= r`、`d <= u` で使い、空長方形は `0` を返す。$O(\log^2 N)$

## 使い方
`T` は `0` が加算の単位元となり、`+=` と減算を使える可換群の型にする。
更新に使う全点を `add_point` で登録してから `build()` する。
`build()` 後は `add` と `sum` を任意順に呼べる。

## 実装上の補足
登録点を重複排除して $x$ の順位と各外側 BIT ノードの必要容量を求め、$y$ 順に各外側 BIT ノードへ配る。
各外側 BIT ノードが持つ $y$ 座標列は既に整列済みなので、再ソートせず重複排除だけを行う。
登録順や重複除去を利用側で管理する必要はない。

長方形和は外側・内側の BIT で共通の累積経路を省く。保持領域は $O(N\log N)$。
