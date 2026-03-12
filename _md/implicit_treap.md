---
title: Implicit Treap
documentation_of: //datastructure/implicit_treap.cpp
date: 2026-03-12
category: データ構造
tags: データ構造
---

## 説明
列を持つ implicit treap である。
挿入、削除、区間反転、区間作用、区間集約を期待 $O(\log N)$ で扱う。

## できること
- `ImplicitTreap<M> tr`
  空列を作る
- `ImplicitTreap<M> tr(v)`
  配列 `v` から列を作る
- `int size()`
  要素数を返す
- `bool empty()`
  空列なら `true`
- `void reserve(int capacity)`
  あらかじめノード領域を確保する
- `T all_fold()`
  列全体の集約値を返す。空なら `M::e()`
- `void insert(int k, T x)`
  `x` を位置 `k` の前に挿入する
- `void push_front(T x)`, `void push_back(T x)`
  先頭または末尾に挿入する
- `T erase(int k)`
  位置 `k` の要素を削除して返す
- `T pop_front()`, `T pop_back()`
  先頭または末尾を削除して返す
- `T get(int k)`
  位置 `k` の要素を返す
- `void set(int k, T x)`
  位置 `k` の要素を `x` に置き換える
- `void apply(int l, int r, L x)`
  半開区間 $[l, r)$ に作用素 `x` を適用する
- `void reverse(int l, int r)`
  半開区間 $[l, r)$ を反転する
- `T fold(int l, int r)`
  半開区間 $[l, r)$ の順序付き集約を返す

## 使い方
`M` は次を持てばよい。

```cpp
struct Monoid {
    using T = ...;
    using L = ...;
    static T f(T a, T b);
    static T g(T a, L x);
    static L h(L a, L b);
    static T e();
    static L l();
};
```

`f` は列順を保って畳み込まれる。
`reverse` を使うので、非可換モノイドでも `fold` の順序が壊れない。
`apply` を使うときは
$$
g(f(a, b), x) = f(g(a, x), g(b, x))
$$
を満たすように `T` を設計する。

## 実装上の補足
- 作用素の合成順は `h(古い作用, 新しい作用)` である
- 範囲和のように長さ依存の更新をしたいときは、`T` に長さを持たせて `g` で処理する
