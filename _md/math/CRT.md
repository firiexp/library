---
title: 中国剰余定理(Chinese Remainder Theorem)
documentation_of: //math/CRT.cpp
date: 2019-08-18
category: 数学
tags: 数学
---

## 説明

$$
x \equiv a_i \pmod{M_i} \quad (1 \le i \le N)
$$

という情報から、$\operatorname{lcm}(M_1, M_2, \dots, M_N)$ を法とする $x$ を復元する。

## できること
- `CRT(a)` : 合同式の列 `a` をまとめ、解があれば `(r, M)` を返す。解がなければ空または `(0, 0)`

## 使い方
`a[i] = (a_i, M_i)` を渡す。
戻り値 `(r, M)` は $x \equiv r \pmod{M}$ を表す。
