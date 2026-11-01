---
title: 静的区間の重複を除いた値の重み和
documentation_of: //datastructure/wavelet_matrix/static_range_distinct_sum.cpp
---

## 説明
更新のない列について、区間内の値を重複除去し、残った各値の重みを足し合わせる。
負の重みも扱え、問い合わせの順序に制約はない。

## できること
列の長さを $N$ とし、比較・重み取得・加減算を $O(1)$ とする。

- `StaticRangeDistinctSum<T, U> distinct(values, weight)`
  値の列 `values` と、値を受け取って重みを返す関数 `weight` から構築する。時間・保持領域は $O(N\log N)$。
- `U sum(int l, int r) const`
  半開区間 `[l, r)` に現れる異なる値の重み和を返す。空区間は `U()`。時間 $O(\log N)$、追加領域 $O(1)$。

## 使い方
値の型 `T` は `<` で比較できる必要がある。
重み関数 `weight` は同じ値に対して常に同じ重みを返す必要がある。
重みとその和の型 `U` には整数型や modint のような、加減算のできる可換群の型を使う。

```cpp
vector<int> values = {2, -3, 2, 5};
StaticRangeDistinctSum<int, long long> distinct(values, [](int x) { return 1LL * x; });
long long total = distinct.sum(0, 3);
```

この例の `total` は異なる値 `2` と `-3` の和である `-1` となる。

## 実装上の補足
値の同一性は大小比較で判定する。`x < y` でも `x > y` でもない場合、2つの値を同じ種類として扱う。
実装では `x > y` の代わりに `y < x` を使うため、`>` の定義は不要である。
`U` は `U()` による零初期化と、`+`、`-`、`+=` に対応する必要がある。
整数型を使う場合、重複を含む重みの累積値と問い合わせの途中値も、その型で表せる範囲に収まる必要がある。

前出現位置 `prev[i]` と重みから Weighted Wavelet Matrix を構築する。
`[l, r)` で `prev[i] < l` となるのは各種類の最初の1出現なので、その重みだけを集計する。
