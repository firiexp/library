---
title: Berlekamp-Massey法
documentation_of: //math/berlekamp_massey.cpp
date: 2026-03-07
category: 数学
tags: 数学
---

## 説明
列 `s` を満たす最小次数の線形漸化式

`s_n = c_0 s_{n-1} + c_1 s_{n-2} + ... + c_{L-1} s_{n-L}`

の係数列 `c` を求める。

## できること
- `vector<T> berlekamp_massey(const vector<T>& s)`
  列 `s` の最小線形漸化式の係数列を返す。$N=\mathrm{s.size()}$ として $O(N^2)$

## 使い方
`vector<T> c = berlekamp_massey(s);`

- `T` は加減乗除と `T(0)`, `T(1)` が使える体上の型を想定。
- 返り値の長さが最小次数 `L`。
- 返り値 `c[i]` は上式の係数 `c_i`。
