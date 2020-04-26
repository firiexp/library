---
layout: post
title: 高速多項式剰余(高速kitamasa法)
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
$x^K  \mod \ f(x)$を$O(N \log N \log K)$で求める。(Nはf(x)の最大次数)
{% include a.html code="fastkitamasa.cpp" %}