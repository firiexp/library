---
title: 遅延伝播SegmentTree
documentation_of: //datastructure/segmenttree/lazysegtree.cpp
date: 2018-05-01
category: データ構造
tags: データ構造
---

## 説明
2 つの配列を持つことで、セグメント木を区間更新に対応させたもの。
更新も取得も $O(\log N)$ 回の演算で行える。

## できること
- `LazySegmentTree<M> seg(n)` : 要素数 `n` の遅延セグメント木を作る
- `set(k, x)` : 葉 `k` の初期値を `x` にする
- `build()` : `set` 済みの値から木を構築する
- `update(k, x)` : 位置 `k` の値を `x` に更新する
- `update(l, r, x)` : 半開区間 $[l, r)$ に作用素 `x` を適用する
- `query(l, r)` : 半開区間 $[l, r)$ の集約値を返す
- `search_right(l, cond)` : 左から伸ばして `cond` が壊れる最初の位置を返す。見つからなければ `n`
- `search_left(r, cond)` : 右から伸ばして `cond` が壊れる最後の位置を返す。見つからなければ `0`

## 使い方
モノイド構造体 `M` に次を定義して渡す。
- 要素の型 `T`
- `T` の単位元 `e`
- 作用素の型 `L`
- `L` の単位元 `l`
- $f : T \times T \to T$ 要素同士のマージ
- $g : T \times L \to T$ 要素と作用素のマージ
- $h : L \times L \to L$ 作用素同士のマージ

以下にモノイドの例を挙げる。

#### 区間加算-区間min
- $e = \infty$
- $l = 0$
- $f(x, y) = \min(x, y)$
- $g(x, y) = x + y$
- $h(x, y) = x + y$

#### 区間更新-区間max
- $e = 0$
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
