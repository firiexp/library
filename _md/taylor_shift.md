---
layout: post
title: Taylor Shift
date: 2026-03-08
category: FPS
tags: FPS
---

## 説明
多項式 `f(x)` から `f(x + c)` の係数列を計算する。
`998244353` 上の `poly` を前提にし、計算量は `O(n log n)`。

## できること
- `poly taylor_shift(const poly& f, mint c)`
  `f(x + c)` の係数列を返す

## 使い方
`#include "../fps/taylor_shift.cpp"` を読み込む。
`taylor_shift(f, c)` を呼ぶ。

## 実装上の補足
階乗と逆階乗で重み付けして 1 回の畳み込みに帰着する。
