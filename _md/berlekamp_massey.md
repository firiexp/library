---
layout: post
title: Berlekamp-Massey
date: 2026-03-07
category: 数学
tags: 数学
---

## 概要
列 `s` を満たす最小次数の線形漸化式

`s_n = c_0 s_{n-1} + c_1 s_{n-2} + ... + c_{L-1} s_{n-L}`

の係数列 `c` を求める。

## 計算量
`O(N^2)` (`N = s.size()`)

## 使い方
`vector<T> c = berlekamp_massey(s);`

- `T` は加減乗除と `T(0)`, `T(1)` が使える体上の型を想定。
- 返り値の長さが最小次数 `L`。
- 返り値 `c[i]` は上式の係数 `c_i`。

