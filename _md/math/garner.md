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
余り $a_i$ が負数や $M_i$ 以上の場合には内部で正規化する。
各 $M_i$ と $M$ が $2^{31}-1$ 以下なら、内部の演算は `long long` に収まる。
