---
layout: post
title: kruskal法(最小全域木)
date: 2018-04-28
category: グラフ
tags: グラフ
---

## 説明
MSTを求める。入力は隣接リストで与える。ソートがボトルネックで$O(E \log V)$。
{% include a.html code="kruskal.cpp" %}