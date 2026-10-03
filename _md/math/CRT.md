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
- `CRT(a)` : 合同式の列 `a` をまとめ、解があれば `(r, M)`、解がなければ `(0, 0)` を返す。空列には `(0, 1)` を返す

## 使い方
`a[i] = (a_i, M_i)` を渡す。
各 $M_i$ は正とし、剰余 $a_i$ は負数や $M_i$ 以上の値も内部で正規化する。
戻り値 `(r, M)` は $x \equiv r \pmod{M}$、$0 \le r < M$ を満たす。
最小公倍数と途中の演算が `long long` に収まる範囲で使う。
