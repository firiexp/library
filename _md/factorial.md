---
layout: post
title: 階乗ライブラリ
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明

$i! \mod M \ \ (0 \le i \le N)$とその逆元を$O(N + \log M)$で前計算する。 
\これによって二項係数の計算を$O(1)$で行うことができる。

##  機能
- fact(int k) : $k$が非負なら$k!$を、負なら$\displaystyle \frac{1}{k!}$を返す。
- C(int p, int q) : $  \displaystyle \binom{ p }{ q } = \frac{p!}{q!(p-q)!}$ を返す。
- P(int p, int q) : $  \displaystyle \frac{p!}{q!}$ を返す。
- H(int p, int q) : 重複組み合わせ$  \displaystyle {}_p\mathrm{ H }_q  =  \binom{ p+q-1 }{ q }$ を返す。
{% include a.html code="factorial.cpp" %}