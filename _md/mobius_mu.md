---
layout: post
title: mobius_mu
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
単一の整数 `n` に対するメビウス関数 `mu(n)` を求める。
`n` に平方因子があれば `0`、異なる素因数の個数が奇数なら `-1`、偶数なら `1` を返す。
計算量は `O(sqrt(n))`。

## できること
- `int mobius_mu(ll n)`
  `mu(n)` を返す

## 使い方
1 個だけ判定したいときに使う。
多点計算なら `mobius_all` の方が向く。
