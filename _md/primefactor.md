---
category: "\u6570\u5B66"
date: 2018-04-28
layout: post
tags: "\u6570\u5B66"
title: "\u7D20\u56E0\u6570\u5206\u89E3(\u8A66\u3057\u5272\u308A)"
---

## 説明
$\sqrt{N}$までの素数を列挙し、順に割れるかどうか判定する。$O(\sqrt{N})$
{% include a.html code="primefactor.cpp" %}
剰余を乗算で置き換えたもの。
{% include a.html code="primefactor2.cpp" %}