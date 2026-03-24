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

同じ値を先に圧縮してから計算する。
`sample_point_shift` で `B = 512` の block product を前計算し、
各 query は block 境界から近い側へ高々 `256` 個だけ掛けて求める。

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
block prefix product を土台にする。
余りが前半ならそのまま掛け足し、後半なら次 block から割り戻す。
共通計算を抑え、distinct な query を短い積で直接処理する。
