---
layout: post
title: Z-algorithm
date: 2019-08-15
category: 文字列
tags: 文字列
---

## 説明
文字列の各indexについて、$S$と$S[i, n$)の最大共通接頭辞の長さを記録した配列を$O(n)$で構築するアルゴリズム。
{% include a.html code="z-algorithm.cpp" %}