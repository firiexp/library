---
layout: post
title: 素数列挙
date: 2019-08-18
category: 数学
tags: 数学
---

## 説明
$N$以下の素数を列挙する。$O(N)$であるが速度的にはエラトステネスの篩($O(N \log \log N)$)と変わらない。
{% include a.html code="get_prime.cpp" %}
こちらは除算を乗算に置き換えたコード。
{% include a.html code="get_prime2.cpp" %}