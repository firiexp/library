---
title: 線形漸化式(Linear Recurrence)
documentation_of: //fps/linear_recurrence.cpp
date: 2026-03-07
category: 数学
tags: 数学
---

## 説明
線形漸化式

$$a_n = c_0 a_{n-1} + c_1 a_{n-2} + \cdots + c_{k-1} a_{n-k}$$

の第 `n` 項を求める。

## できること
- `linear_recurrence(a, c, n)`
  初項 `a` と係数 `c` から第 `n` 項を返す
- `linear_recurrence(a, n)`
  Berlekamp-Massey で `a` の最小線形漸化式を推定し、第 `n` 項を返す

## 使い方
`n >= 0` とする。係数を指定する場合は、漸化式の次数 `k` 項分の初項を渡す。
自動推定には、想定する次数の 2 倍以上の項を渡す。

## 実装上の補足
`n < a.size()` なら、どちらの関数も推定や第 `n` 項の計算を行わず、時間・追加領域 $O(1)$ で `a[n]` を返す。
それ以外では第 `n` 項の計算に $O(k\log k\log n)$ 時間を使う。
自動推定には別途 $O(|a|^2)$ 時間を使う。
