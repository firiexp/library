---
title: Segment Tree
documentation_of: //datastructure/segmenttree/segtree.cpp
---

## 説明
点更新・区間積・左右の境界探索を扱う。

## できること
配列長を $N$ とし、モノイド演算と述語の判定を $O(1)$ とする。

- `SegmentTree<M> seg(n)` : 要素数 `n`、初期値が単位元の木を作る。$O(N)$
- `SegmentTree<M> seg(values)` : 初期配列 `values`（`vector<T>`）から木を構築する。$O(N)$
- `set(k, x)` : 葉の初期値を `x` に設定する。$O(1)$
- `build()` : 設定した葉の値から木を構築する。$O(N)$
- `update(k, x)` : 位置 `k` の値を `x` に置き換える。$O(\log N)$
- `T all_query() const` : 配列全体の積を返す。$O(1)$
- `T query(int l, int r) const` : 半開区間 $[l, r)$ の積を返す。$O(\log N)$
- `int search_right(int l, F cond) const` : `cond(query(l, r))` を満たす最大の `r` を返す。$O(\log N)$
- `int search_left(int r, F cond) const` : `cond(query(l, r))` を満たす最小の `l` を返す。$O(\log N)$
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

vector<long long> values = {5, 1, 2};
const SegmentTree<Monoid> seg(values);
long long total = seg.all_query(); // 8
long long sum = seg.query(1, 3);   // 3
```
