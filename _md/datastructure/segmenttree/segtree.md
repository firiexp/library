---
title: Segment Tree
documentation_of: //datastructure/segmenttree/segtree.cpp
date: 2020-03-07
category: データ構造
tags: データ構造
---

## 説明
点更新・区間積・左右の境界探索を扱う。

## できること
配列長を $N$ とし、モノイド演算と述語の判定を $O(1)$ とする。

- `SegmentTree<M> seg(n)` : 要素数 `n`、初期値が単位元の木を作る。$O(N)$
- `set(k, x)` : 葉の初期値を `x` に設定する。$O(1)$
- `build()` : 設定した葉の値から木を構築する。$O(N)$
- `update(k, x)` : 位置 `k` の値を `x` に置き換える。$O(\log N)$
- `query(l, r)` : 半開区間 `[l, r)` の積を返す。$O(\log N)$
- `search_right(l, cond)` : `cond(query(l, r))` を満たす最大の `r` を返す。$O(\log N)$
- `search_left(r, cond)` : `cond(query(l, r))` を満たす最小の `l` を返す。$O(\log N)$
- `seg[k]` : 位置 `k` の値を返す。$O(1)$

## 使い方
`M` に要素型 `T`、結合則を満たす二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

SegmentTree<Monoid> seg(3);
seg.set(0, 5);
seg.build();
long long sum = seg.query(0, 3);
```
