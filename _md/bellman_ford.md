---
category: "\u30B0\u30E9\u30D5"
date: 2019-08-15
layout: post
tags: "\u30B0\u30E9\u30D5"
title: "\u5358\u4E00\u59CB\u70B9\u6700\u77ED\u8DEF(Bellman-Ford\u6CD5)"
---

## 説明
単一始点最短路を求める。Dijkstra法とは異なり、負辺があっても正しく動作する。$O(VE)$
{% include a.html code="bellman_ford.cpp" %}

負閉路を含む場合は、始点によって到達できる負閉路が異なる。そのため、負閉路を含みうる場合、そこから順にたどって、到達可能なら距離を$- \infty$に更新する。

{% include a.html code="bellman_ford_negative_loop.cpp" %}