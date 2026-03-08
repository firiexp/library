---
category: "\u6570\u5B66"
date: 2026-03-08
layout: post
tags: "\u6570\u5B66"
title: powk_all
---

## 説明
`1` から `n` までの各整数について `i^k` をまとめて求める。
最小素因数表を使い、積性を利用して計算する。

## できること
- `vector<mint> powk_all(int n, ll k)`
  `res[i] = i^k` を返す。`res[0]` は未使用、`res[1] = 1`

## 使い方
`mint` は `util/modint.cpp` の modint を使う。
`get_min_factor` を内部で呼ぶので、全体計算量は `O(n log log n)` 程度。
