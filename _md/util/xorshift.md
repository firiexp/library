---
title: Xor-Shift
documentation_of: //util/xorshift.cpp
date: 2018-04-28
category: 乱数
tags: 乱数
---

## 説明
軽量な xorshift 乱数生成器。
`uint32_t` を返す生乱数と、区間乱数を持つ。

## できること
- `xor_shift rng`
  現在時刻を使って初期化する。$O(1)$
- `uint32_t urand()`
  `uint32_t` の乱数を返す。$O(1)$
- `int rand(int n)`
  `0..n` の一様乱数を返す。`n < 0` なら `n..0`。期待 $O(1)$
- `int rand(int a, int b)`
  `a..b` の一様乱数を返す。`a > b` でもよい。期待 $O(1)$

## 使い方
`xor_shift rng;` を作って `rng.urand()` や `rng.rand(l, r)` を呼ぶ。
乱択アルゴリズムやテストデータの生成に使う。

## 実装上の補足
`rand(int n)` は棄却法で偏りを消している。
再現性が必要な用途向けの seed 指定 API は持たない。
