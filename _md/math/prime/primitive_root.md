---
title: 原始根(Primitive Root)
documentation_of: //math/prime/primitive_root.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
素数 `p` に対する原始根を 1 つ返す。
`p - 1` の素因数を使って候補を判定する。
候補数を $G$、$p-1$ の異なる素因数数を $K$ とすると、素因数分解の時間に加えて $O(GK\log p)$ かかる。

## できること
- `ll primitive_root(ll p)`
  素数 `p` に対する原始根を 1 つ返す

## 使い方
`p` は $2 \le p < 2^{63}$ の素数を仮定する。`p = 2` では `1` を返す。
返る値は最小とは限らないが、`mod p` の乗法群を生成する。

## 実装上の補足
`p-1` の素因数分解が終わってから `mod64` の法を `p` に設定し、候補の累乗と比較を Montgomery 表現で行う。
`mod64` の法は共有されるため、呼出し前の法の値は保持しない。
