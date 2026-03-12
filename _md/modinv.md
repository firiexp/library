---
category: "\u6570\u5B66"
date: 2018-04-28
tags: "\u6574\u6570\u8AD6"
title: "MOD\u9006\u5143(\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u4E92\u9664\
  \u6CD5)"
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
