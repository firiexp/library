---
title: Dynamic Segment Tree
documentation_of: //datastructure/segmenttree/dynamic_segtree.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
必要なノードだけ作る動的セグメント木。
大きい座標範囲に対する 1 点更新、区間積、左右の境界探索を扱う。
モノイド演算と判定を定数時間として、各操作は $O(\log N)$。

## できること
- `DynamicSegmentTree<M> seg(n)`
  長さ `n`、初期値がすべて `M::e()` の動的セグメント木を作る
- `void reserve(size_t sz)`
  ノード配列を `sz` 個ぶん予約する
- `void update(long long k, T x)`
  位置 `k` を `x` に置き換える
- `void add(long long k, T x)`
  位置 `k` を `M::f(old, x)` で更新する
- `T query(long long l, long long r)`
  半開区間 `[l, r)` の積を返す。空区間なら `M::e()`
- `T get(long long k)`
  位置 `k` の値を返す
- `T operator[](long long k)`
  `get(k)` の短縮形
- `long long search_right(long long l, F cond) const`
  `cond(query(l, r))` を満たす最大の `r` を返す。末尾まで成立すれば `n`
- `long long search_left(long long r, F cond) const`
  `cond(query(l, r))` を満たす最小の `l` を返す。先頭まで成立すれば `0`

## 使い方
`M` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

DynamicSegmentTree<Monoid> seg((long long)1e9);
seg.add(123456789, 5);
seg.update(987654321, 7);
long long ans = seg.query(100000000, 900000000);
```

## 実装上の補足
未生成ノードは単位元として扱う。
境界探索は `0 <= l, r <= n`、`cond(M::e()) == true`、区間を伸ばす方向に判定が単調であることを前提とする。
`search_right(n, cond)` は `n`、`search_left(0, cond)` は `0` を返す。空の木でも使える。
集約順序を保つので非可換モノイドにも対応し、探索中にノードを追加しない。
大量の更新を先に見積もれるときは `reserve()` で再確保を減らせる。
この実装は初期配列をまとめて与える構築は持たず、必要な位置だけ更新して使う。
