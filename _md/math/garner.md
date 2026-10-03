---
title: Garner's algorithm
date: 2019-08-18
category: 数学
tags: 数学
---

## 説明

$$
x \equiv a_i \pmod{M_i} \quad (1 \le i \le N)
$$

という情報から、$0 \le x < \operatorname{lcm}(M_1, M_2, \dots, M_N)$ を満たす $x$ の $M$ での剰余を復元する。

## できること
- `Garner(a, M)` : 合同式の列 `a` から、解の `M` での剰余を返す。空列には `0` を返す

## 使い方
`a[i] = (a_i, M_i)` を渡す。
各 $M_i$ は正かつ互いに素、出力の法 $M$ は正とする。
剰余 $a_i$ は負数や $M_i$ 以上の値も内部で正規化する。
途中の演算が `long long` に収まる範囲で使う。
