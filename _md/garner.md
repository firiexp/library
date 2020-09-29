---
category: "\u6570\u5B66"
date: 2019-08-18
layout: post
tags: "\u6570\u5B66"
title: Garner's algorithm
---

## 説明

$ x = a_i \mod M_i (1 \le i \le N)$ という情報から、$x \le \mathrm{lcm} (M_1 , M_2 , \cdots , M_N)$という条件で$x \mod M$を復元する。

{% include a.html code="garner.cpp" %}