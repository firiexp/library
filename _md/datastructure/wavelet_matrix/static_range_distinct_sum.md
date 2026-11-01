---
title: 静的区間の異なる値の重み和
documentation_of: //datastructure/wavelet_matrix/static_range_distinct_sum.cpp
---

## 説明
更新のない列について、区間内に現れる値の重みを種類ごとに1回だけ足す。
負の重みも扱え、問い合わせの順序に制約はない。

## できること
列の長さを $N$ とし、比較・重み取得・加減算を $O(1)$ とする。

- `StaticRangeDistinctSum<T, U> distinct(values, weight)`
  値の列 `vector<T>` と `weight(value)` から構築する。時間・保持領域は $O(N\log N)$。
- `U sum(int l, int r) const`
  半開区間 `[l, r)` に現れる異なる値の重み和を返す。空区間は `U()`。時間 $O(\log N)$、追加領域 $O(1)$。

## 使い方
`0 <= l <= r <= values.size()` とする。空の列も構築できる。
`T` は `<` で比較できる型とし、どちらも小さくない2値を同じ種類とみなす。
`weight` は同じ種類に常に同じ重みを与える。構築後は呼ばれない。
`U` は零を表す `U()`、コピー、加減算と `+=` を扱える可換群の型とし、整数型や modint を使える。
整数型では、重複を含む重みの累積値と問い合わせの途中値も `U` に収める。

```cpp
vector<int> values = {2, -3, 2, 5};
StaticRangeDistinctSum<int, long long> distinct(values, [](int x) { return 1LL * x; });
long long total = distinct.sum(0, 3);
```

この例の `total` は、異なる値 `2` と `-3` の和である `-1` となる。

## 実装上の補足
前出現位置 `prev[i]` と重みから Weighted Wavelet Matrix を構築する。
`[l, r)` で `prev[i] < l` となるのは各種類の最初の1出現なので、その重みだけを集計する。
