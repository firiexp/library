---
title: MOD逆元(拡張ユークリッド互除法)
date: 2018-04-28
category: 数学
tags: 整数論
---

## 説明

$$
x \cdot x^{-1} \equiv 1 \pmod{M}
$$

を満たす $x^{-1}$ を $O(\log M)$ で求める。

## できること
- `mod_inv(x, M)` : $x^{-1} \bmod M$ を返す

## 使い方
$\gcd(x, M) = 1$ を前提とする。
