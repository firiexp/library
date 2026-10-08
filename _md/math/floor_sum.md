---
title: Floor Sum
documentation_of: //math/floor_sum.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
$\sum_{i=0}^{n-1} \lfloor (ai+b)/m \rfloor$ を返す。
計算量は $O(\log m)$、追加領域は $O(1)$。

## できること
- `ll floor_sum(ll n, ll m, ll a, ll b)`
  床関数の和を返す。`n = 0` なら `0`

## 使い方
$0 \le n < 2^{32}$、$1 \le m < 2^{32}$、答えが `long long` に収まる入力を扱う。
`a`, `b` は `long long` の全範囲を受け取り、負の値や `m` 以上でもそのまま渡せる。
途中の積と負の係数の正規化には `__int128` を使う。
