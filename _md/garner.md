---
category: "\u6570\u5B66"
date: 2019-08-18
tags: "\u6570\u5B66"
title: Garner's algorithm
---

## 説明

$$
x \equiv a_i \pmod{M_i} \quad (1 \le i \le N)
$$

という情報から、$0 \le x < \operatorname{lcm}(M_1, M_2, \dots, M_N)$ を満たす $x$ の $M$ での剰余を復元する。

## できること
- `Garner(a, M)` : 合同式の列 `a` から、解の `M` での剰余を返す

## 使い方
`a[i] = (a_i, M_i)` を渡す。
各 $M_i$ は互いに素であることを前提とする。
