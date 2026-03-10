---
title: Get Min Factor
documentation_of: //math/get_min_factor.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`0..n` の最小素因数を篩で求める。

## できること
- `vector<int> get_min_factor(int n)`
  `min_factor[x]` に `x` の最小素因数を入れた長さ `n + 1` の配列を返す。`min_factor[0] = 0`, `min_factor[1] = 1`

## 使い方
`x >= 2` の素因数分解は `x = x / min_factor[x]` を繰り返せばよい。
素数 `p` では `min_factor[p] = p` になる。

## 実装上の補足
前計算は `O(n log log n)`、各クエリは素因数の個数ぶんだけ進む。
単発クエリには重いが、同じ上限以下を何度も分解する用途に向く。
