---
title: 永続セグメント木(Persistent Segment Tree)
documentation_of: //datastructure/segmenttree/persistent_segtree.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
点更新ごとに新しい版を作り、任意の過去版の区間積を求める。
モノイドの演算を $O(1)$ として、サイズ指定の構築は $O(1)$、配列からの構築は $O(N)$。
点更新は配列の拡張を含めて償却 $O(\log N)$、区間積は最悪 $O(\log N)$。点更新の追加ノード数は $O(\log N)$。

## できること
- `PersistentSegmentTree<M> seg(n)` / `seg(values)`
  全要素が単位元の列、または配列から初期版 `0` を作る
- `int update(int t, int k, const T &x)`
  版 `t` の位置 `k` に代入し、新しい版番号を返す
- `int add(int t, int k, const T &x)`
  版 `t` の位置 `k` を `M::f(old, x)` に更新し、新しい版番号を返す
- `T query(int t, int l, int r)`
  版 `t` の半開区間 `[l, r)` の積を返す。空区間なら単位元
- `T get(int t, int k)`
  版 `t` の位置 `k` の値を返す
- `int latest_version()` / `int versions()`
  最新の版番号 / 保持している版数を返す

## 使い方
`M` に `T`、二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
`update`、`add`、`query` は版番号を省略すると最新版を使う。`seg[k]` は最新版の値を返す。
要素数が0の場合、更新は空の新しい版を作り、区間積は単位元を返す。

## 実装上の補足
サイズ指定の構築では、単位元を持つ1ノードを未更新の全区間で共有する。
更新時だけ経路をコピーし、過去版と共有ノードは変更しない。
共有ノードの子は自分自身を指す。`node` と `root` は区間境界と組み合わせる内部表現であり、子リンクだけで辿る通常の木ではない。
