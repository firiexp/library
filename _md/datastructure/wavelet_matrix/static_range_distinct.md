---
title: 静的区間の種類数
documentation_of: //datastructure/wavelet_matrix/static_range_distinct.cpp
date: 2026-10-11
category: データ構造
tags: データ構造
---

## 説明
更新のない配列について、指定した区間に含まれる値の種類数を求める。

## できること
配列長を $N$ とする。

- `StaticRangeDistinct<T> distinct(const vector<T>& values)`
  配列から構築する。$O(N\log N)$
- `int count(int l, int r) const`
  半開区間 `[l, r)` に含まれる値の種類数を返す。$O(\log N)$

## 使い方
`T` は `<` で比較できる型とし、比較に $O(1)$ 時間かかることを前提とする。
`0 <= l <= r <= values.size()` を満たす区間を渡す。

```cpp
vector<long long> values = {1, 2, 1, 3};
StaticRangeDistinct<long long> distinct(values);
int kinds = distinct.count(1, 4);
```

この例の返り値は `3`。

## 実装上の補足
各要素について、直前に同じ値が現れた位置を求め、その配列に Wavelet Matrix を構築する。
区間 `[l, r)` 内で直前の位置が `l` 未満となる要素を数えると、種類数が得られる。
実際に現れる前出現位置だけを圧縮し、各 `l` の圧縮境界を $O(N)$ 領域に保持する。問い合わせ時の二分探索は不要である。
全要素が相異なる場合は Wavelet Matrix と境界配列を作らず、`r - l` を $O(1)$ で返す。空配列にも対応する。
