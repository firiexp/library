---
layout: post
title: 拡張ユークリッド互除法
date: 2018-04-28
category: 数学
tags: 整数論
---

## 説明
$a, b$が与えられる時、$ax+by= \gcd (a, b)$を満たす$x, y$を計算する。返り値は$\gcd (a, b)$である。
{% include a.html code="extgcd.cpp" %}