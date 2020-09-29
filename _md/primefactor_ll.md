---
category: "\u6570\u5B66"
date: 2018-04-28
layout: post
tags: "\u6570\u5B66"
title: "\u7D20\u56E0\u6570\u5206\u89E3(Pollard's rho\u6CD5)"
---

## 説明
小さい素因数を試し割りで取り除いてから、Pollard's rho法によって素因数分解する。int128_tを使っているため、Codeforcesでは動かない。計算量は不明。
{% include a.html code="primefactor_ll.cpp" %}
剰余算を乗算に置き換えたもの。
{% include a.html code="primefactor_ll2.cpp" %}