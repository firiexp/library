---
title: min-plus畳み込み(Min-Plus Convolution)
documentation_of: //math/convolution/min_plus_convolution.cpp
date: 2026-03-11
category: 数学
tags: 数学
---

## 説明
`c[k] = min_i (a[i] + b[k - i])` を計算する。
配列の凸性に応じて 3 種類の関数を使い分ける。

ここで凸とは、隣接差分が単調非減少であることを指す。

## できること
$N,M$ をそれぞれ `a`, `b` の長さとする。

- `vector<T> min_plus_convolution_arbitrary_convex(const vector<T>& a, const vector<T>& b)`
  `a` を任意列、`b` を凸列として min-plus 畳み込みを返す。計算量は $O((N + M) \log(N + M))$
- `vector<T> min_plus_convolution_convex_arbitrary(const vector<T>& a, const vector<T>& b)`
  `a` を凸列、`b` を任意列として min-plus 畳み込みを返す。計算量は $O((N + M) \log(N + M))$
- `vector<T> min_plus_convolution_convex_convex(const vector<T>& a, const vector<T>& b)`
  `a, b` を凸列として min-plus 畳み込みを返す。計算量は $O(N + M)$

## 使い方
凸性がある側に応じて関数を選ぶ。
どちらも空でなければ、返り値の長さは `a.size() + b.size() - 1`。

`T` は `+` と `<` が使える型を想定する。
空配列を渡したときは空配列を返す。

## 最小値を取る添字の取得

3種類の関数には、それぞれ末尾に `_with_argmin` を付けた入口がある。
返り値は `MinPlusConvolutionResult<T>` で、最小値の列 `value` と第1引数 `a` の添字列 `argmin` を持つ。

- `argmin[k]` は `a[i] + b[k-i] == value[k]` となる `i`。同値なら任意の1つを返す。
- `convex_arbitrary_with_argmin(a, b)` も、内部での引数交換によらず元の `a` の添字を返す。
- 片方が空なら `value`・`argmin` はともに空。
- 時間計算量は値だけの各入口と同じ。添字列の領域は $O(N+M)$。値だけの入口では添字列を確保しない。

```cpp
auto res = min_plus_convolution_arbitrary_convex_with_argmin(a, b);
int i = res.argmin[k];
int j = k - i;
```

有限な要素を使い、すべての加算が `T` に収まるようにする。
