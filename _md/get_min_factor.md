---
category: "\u6570\u5B66"
date: 2026-03-08
layout: post
tags: "\u6570\u5B66"
title: Get Min Factor
---

## 説明
`0..n` の最小素因数を篩で求める。
素因数分解や積性関数の前計算の土台に使う。

## できること
- `vector<int> get_min_factor(int n)`
  `min_factor[x]` に `x` の最小素因数を入れた長さ `n + 1` の配列を返す。`min_factor[0] = 0`, `min_factor[1] = 1`

## 使い方
`x >= 2` の素因数分解は `x = x / min_factor[x]` を繰り返せばよい。
素数 `p` では `min_factor[p] = p` になる。
