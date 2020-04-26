---
layout: post
title: 素因数分解(Pollard's rho法)
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
小さい素因数を試し割りで取り除いてから、Pollard's rho法によって素因数分解する。int128_tを使っているため、Codeforcesでは動かない。計算量は不明。
{% include a.html code="primefactor_ll.cpp" %}
剰余算を乗算に置き換えたもの。
{% include a.html code="primefactor_ll2.cpp" %}