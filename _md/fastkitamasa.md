---
title: 高速多項式剰余(高速kitamasa法)
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
$x^K \bmod f(x)$ を求める。計算量は $O(N \log N \log K)$。
$N$ は $f(x)$ の最大次数。

## 使い方
線形漸化式の $K$ 項目計算や、多項式剰余を保ったままの冪計算に使う。
