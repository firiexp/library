---
category: "\u6570\u5B66"
date: 2019-08-16
layout: post
tags: "\u6570\u5B66"
title: Number Theoretic Transform
---

## 説明
素数$p$が$p = q \cdot 2^{k}+1$の形で表され、原始根$g$が存在するとき、$g^q$が1の$2^k$乗根となる。それゆえ、$i \le k$について、$2^i$乗根が簡単に求められるので、$2^i$要素の数列について$\mod p$でFFTと同様にして畳み込みができる。
原始根は、よく使われるものに関してはコードに記載したが、例にないものが必要なら、Wolfram|Alphaなどで計算すればよい。 
{% include a.html code="ntt.cpp" %}