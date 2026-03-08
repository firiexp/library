---
layout: post
title: Euler Phi All
documentation_of: //math/eulerphi_all.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`0..M-1` の Euler の totient function をまとめて求める。
篩で各素数の倍数に `phi[j] -= phi[j] / p` を入れる。
計算量は `O(M log log M)`。

## できること
- `vector<int> eulerphi_all(int M)`
  `phi[i] = phi(i)` を満たす長さ `M` の配列を返す

## 使い方
`phi[0] = 0`, `phi[1] = 1` になる。
前計算して prefix sum を取れば totient の総和にも使える。
