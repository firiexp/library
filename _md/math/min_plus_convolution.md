---
title: min-plus畳み込み(Min-Plus Convolution)
documentation_of: //math/min_plus_convolution.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`c[k] = min_i (a[i] + b[k - i])` を計算する。
配列の凸性に応じて 3 種類の関数を使い分ける。

ここで凸とは、隣接差分が単調非減少であることを指す。

## できること
- `vector<T> min_plus_convolution_arbitrary_convex(const vector<T>& a, const vector<T>& b)`
  `a` を任意列、`b` を凸列として min-plus 畳み込みを返す。計算量は $O((N + M) log(N + M))$
- `vector<T> min_plus_convolution_convex_arbitrary(const vector<T>& a, const vector<T>& b)`
  `a` を凸列、`b` を任意列として min-plus 畳み込みを返す。計算量は $O((N + M) log(N + M))$
- `vector<T> min_plus_convolution_convex_convex(const vector<T>& a, const vector<T>& b)`
  `a, b` を凸列として min-plus 畳み込みを返す。計算量は $O(N + M)$

## 使い方
凸性がある側に応じて関数を選ぶ。
返り値の長さは常に `a.size() + b.size() - 1`。

`T` は `+` と `<` が使える型を想定する。
空配列を渡したときは空配列を返す。
