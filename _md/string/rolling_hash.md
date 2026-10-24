---
title: Rolling Hash
documentation_of: //string/rolling_hash.cpp
date: 2019-09-16
category: 文字列
tags: 文字列
---

## 説明
指定した mod の Rolling Hash で部分文字列のハッシュを求める。

## できること
- `rolling_hash<M> rh(s)`
  文字列 `s` の prefix hash を構築する。$O(|s|)$
- `ll get(int l, int r)`
  `s[l, r)` のハッシュを返す。$O(1)$
- `static ll& B()`
  使用中の base を返す。$O(1)$
- `static vector<ll>& p()`
  base の $i$ 乗を mod $M$ で計算した値を `p[i]` に持つ配列を返す。$O(1)$

## 使い方
`M` は2より大きい整数とする。

```cpp
rolling_hash<1000000007> rh("ababa");
bool equal = rh.get(0, 3) == rh.get(2, 5);
```

ハッシュの一致には衝突の可能性がある。

## 実装上の補足
base は mod ごとに初回利用時に乱択で決まり、同じ mod のインスタンスで共有する。
