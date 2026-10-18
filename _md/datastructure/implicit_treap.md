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
単調な条件を満たす区間の左右境界も期待 $O(\log N)$ で探索できる。

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
  半開区間 $[l, r)$ に作用素 `x` を適用する。空区間は変更せず、列全体への作用は $O(1)$
- `void reverse(int l, int r)`
  半開区間 $[l, r)$ を反転する
- `T fold(int l, int r)`
  半開区間 $[l, r)$ の順序付き集約を返す
- `int search_right(int l, F cond)`
  `cond(fold(l, r))` を満たす最大の `r` を返す。末尾まで成立すれば `size()`、1要素も含められなければ `l`
- `int search_left(int r, F cond)`
  `cond(fold(l, r))` を満たす最小の `l` を返す。先頭まで成立すれば `0`、1要素も含められなければ `r`

## 使い方
位置は 0-indexed、区間は `0 <= l <= r <= size()` を満たす半開区間とする。
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

境界探索の `cond` は `M::e()` で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。
同じ集約値への判定結果は一定とする。左右とも集約の順序は列の左から右であり、非可換モノイドでも使える。
`0 <= l, r <= size()` とし、`search_right(size(), cond)` は `size()`、`search_left(0, cond)` は `0` を返す。空列でも使える。

```cpp
int right = tr.search_right(l, [&](const auto &x) { return x.sum <= limit; });
int left = tr.search_left(r, [&](const auto &x) { return x.sum <= limit; });
```

この例では、`T` が和 `sum` を持ち、各要素と `limit` は非負とする。

## 実装上の補足
- `get` / `set` は位置へ直接降り、`fold` は完全に含まれる部分木の集約値を使って境界だけを探索する。いずれも期待 $O(\log N)$
- `apply` は木を分割せずに境界へ直接降り、完全に含まれる部分木には遅延作用を適用する。一般区間は期待 $O(\log N)$ 時間・再帰領域、偏った木では最悪 $O(N)$。列全体と空区間は $O(1)$
- 境界探索は成立する部分木を集約値で飛ばし、必要な境界へ直接降りる。期待 $O(\log N)$ 時間・再帰領域、偏った木では最悪 $O(N)$。遅延作用や反転の伝搬は行うが、列の値・順序・ノード数は変えない
- 計算量は `M` の各演算を $O(1)$ とした評価である
- 境界探索の計算量は `cond` の判定も $O(1)$ とする
- 作用素の合成順は `h(古い作用, 新しい作用)` である
- 範囲和のように長さ依存の更新をしたいときは、`T` に長さを持たせて `g` で処理する
