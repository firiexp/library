---
title: powk_all
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`1` から `n` までの各整数について `i^k` をまとめて求める。
最小素因数表を使い、積性を利用して計算する。

## できること
- `vector<mint> powk_all(int n, ll k)`
  `res[i] = i^k` を返す。`res[0]` は未使用、`res[1] = 1`。素数の個数を $\pi(n)$ として $O(n+\pi(n)\log k)$

## 使い方
`mint` は `util/modint.cpp` の modint を使う。
`n >= 1`、`k >= 0` とする。最小素因数表を作り、素数に対してだけ二分累乗を行う。
