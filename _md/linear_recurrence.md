---
category: "\u6570\u5B66"
date: 2026-03-07
layout: post
tags: "\u6570\u5B66"
title: "\u7DDA\u5F62\u6F38\u5316\u5F0F"
---

## 概要
線形漸化式

`a_n = c_0 a_{n-1} + c_1 a_{n-2} + ... + c_{k-1} a_{n-k}`

の第 `n` 項を `O(k log k log n)` で計算する。

`linear_recurrence(a, c, n)` は初項 `a` と係数 `c` が与えられたときの第 `n` 項を返す。

`linear_recurrence(a, n)` は Berlekamp-Massey で `a` の最小線形漸化式を復元して第 `n` 項を返す。

{% include a.html code="linear_recurrence.cpp" %}
