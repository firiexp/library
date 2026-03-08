---
layout: post
title: Primitive Root
documentation_of: //math/primitive_root.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
素数 `p` に対する原始根を 1 つ返す。
`p - 1` の素因数を使って候補を判定する。
計算量はおおむね `O(sqrt(p) + k log p)`。

## できること
- `ll primitive_root(ll p)`
  素数 `p` に対する原始根を 1 つ返す

## 使い方
`p` は素数を仮定する。
返る値は最小とは限らないが、`mod p` の乗法群を生成する。
