---
title: 遅延セグメント木(Lazy Segment Tree)
documentation_of: //datastructure/segmenttree/lazysegtree.cpp
date: 2018-05-01
category: データ構造
tags: データ構造
---

## 説明
列の区間更新・区間集約と、単調な条件を満たす区間の左右境界探索を扱う。

## できること
配列長を $N$、`M` の各演算と述語の判定を $O(1)$ とする。

- `LazySegmentTree<M> seg(n)` : 要素数 `n` の遅延セグメント木を作る。$O(N)$
- `set(k, x)` : 葉 `k` の初期値を `x` にする。$O(1)$
- `build()` : `set` 済みの値から木を構築する。$O(N)$
- `update(k, x)` : 位置 `k` の値を `x` に更新する。$O(\log N)$
- `update(l, r, x)` : 半開区間 $[l, r)$ に作用素 `x` を適用する。$O(\log N)$
- `query(l, r)` : 半開区間 $[l, r)$ の集約値を返す。$O(\log N)$
- `search_right(l, cond)` : `cond(query(l, r))` を満たす最大の `r` を返す。$O(\log N)$
- `search_left(r, cond)` : `cond(query(l, r))` を満たす最小の `l` を返す。$O(\log N)$

## 使い方
モノイド構造体 `M` に次を定義して渡す。
- 要素の型 `T`
- `T` の単位元 `e`
- 作用素の型 `L`
- `L` の単位元 `l`
- $f : T \times T \to T$ 要素同士のマージ
- $g : T \times L \to T$ 要素と作用素のマージ
- $h : L \times L \to L$ 作用素同士のマージ

境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。

区間加算・区間和なら次のように定義する。各要素の初期値は `{値, 1}` とする。

```cpp
struct Monoid {
    struct T { long long sum; int len; };
    using L = long long;
    static T f(T a, T b) { return {a.sum + b.sum, a.len + b.len}; }
    static T g(T a, L x) { return {a.sum + x * a.len, a.len}; }
    static L h(L a, L b) { return a + b; }
    static T e() { return {0, 0}; }
    static L l() { return 0; }
};

LazySegmentTree<Monoid> seg(n);
for (int i = 0; i < n; ++i) seg.set(i, {values[i], 1});
seg.build();
seg.update(l, r, 2);
auto sum = seg.query(l, r).sum;
```

作用素の合成順は `h(古い作用, 新しい作用)` である。`L` は等値比較できる型にする。
他の代表的な演算は次のように定義できる。

#### 区間加算-区間min
- $e = \infty$
- $l = 0$
- $f(x, y) = \min(x, y)$
- $g(x, y) = x + y$
- $h(x, y) = x + y$

#### 区間更新-区間max
- $e = -\infty$
- $l = \bot$ (`\bot` は作用しないことを表す番兵)
- $f(x, y) = \max(x, y)$
- $g(x, y) = h(x, y)$

$$
g(x, y) = h(x, y) =
\begin{cases}
x & (y = l) \\
y & (y \ne l)
\end{cases}
$$

#### 区間更新-区間sum
要素を `(部分木の和, サイズ)` としてもつ。範囲内は事前にサイズ 1 としておく。
- $e = (0, 0)$
- $l = \bot$ (`\bot` は作用しないことを表す番兵)
- $f((x_1, y_1), (x_2, y_2)) = (x_1 + x_2, y_1 + y_2)$
- $g((x, y), z) = (zy, y)$
- $h(x, y)$ は次で与える

$$
h(x, y) =
\begin{cases}
x & (y = l) \\
y & (y \ne l)
\end{cases}
$$

## 実装上の補足

区間操作では境界をまたぐ祖先だけを伝播・再集約し、区間内に収まる部分木の遅延作用を保つ。
