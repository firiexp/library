---
layout: post
title: 素因数分解(試し割り)
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
$\sqrt{N}$までの素数を列挙し、順に割れるかどうか判定する。$O(\sqrt{N})$
{% include a.html code="primefactor.cpp" %}
剰余を乗算で置き換えたもの。
{% include a.html code="primefactor2.cpp" %}