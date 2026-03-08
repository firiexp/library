---
category: "\u6570\u5B66"
date: 2026-03-08
layout: post
tags: "\u6570\u5B66"
title: ISqrt
---

## 説明
`floor(sqrt(x))` を返す。
`sqrtl` の結果を起点に前後へ補正して誤差を潰す。

## できること
- `ull Isqrt(const ull& x)`
  `floor(sqrt(x))` を返す

## 使い方
`unsigned long long` 範囲で使う。
平方判定や Pell 方程式の前処理で使う。
