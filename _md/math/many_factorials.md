---
title: Many Factorials
documentation_of: //math/many_factorials.cpp
date: 2026-03-15
category: 数学
tags: 数学
---

## 説明
複数の `n` に対して `n! mod 998244353` をまとめて計算する。
`n >= 998244353` なら `0` を返す。


## できること
- `vector<mint> many_factorials(const vector<long long>& ns)`
  各 `ns[i]` について `ns[i]! mod 998244353` を返す。`ns[i] >= 998244353` なら `0`

## 使い方
`#include "../math/many_factorials.cpp"` を読み込む。

```cpp
vector<long long> ns = {3, 5, 998244352};
auto ans = many_factorials(ns);
```

## 実装上の補足
同じ値をまとめ、`sample_point_shift` で幅512のブロックごとの積とその累積積を前計算する。
ブロック内の位置が前半なら左端から掛け足し、後半なら次のブロックの境界から割り戻す。
各クエリは高々256個の積で求める。
