---
title: Segment Tree
documentation_of: //datastructure/segmenttree/segtree.cpp
date: 2020-03-07
category: データ構造
tags: データ構造
---

## 説明
点更新・区間積・左右の境界探索を $O(\log N)$ 時間で行う。構築時間・保持領域は $O(N)$。

## できること
- `SegmentTree<M> seg(n)` : 要素数 `n`、初期値が単位元の木を作る
- `set(k, x)` / `build()` : 葉の初期値を設定し、木を構築する
- `update(k, x)` : 位置 `k` の値を `x` に置き換える
- `query(l, r)` : 半開区間 `[l, r)` の積を返す
- `search_right(l, cond)` : `cond(query(l, r))` を満たす最大の `r` を返す
- `search_left(r, cond)` : `cond(query(l, r))` を満たす最小の `l` を返す
- `seg[k]` : 位置 `k` の値を返す

## 使い方
`M` に要素型 `T`、結合則を満たす二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。
計算量はモノイド演算と述語が $O(1)$ の場合である。
