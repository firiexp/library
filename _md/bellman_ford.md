---
layout: post
title: 単一始点最短路(Bellman-Ford法)
date: 2019-08-15
category: グラフ
tags: グラフ
---

## 説明
単一始点最短路を求める。Dijkstra法とは異なり、負辺があっても正しく動作する。$O(VE)$
{% include a.html code="bellman_ford.cpp" %}

負閉路を含む場合は、始点によって到達できる負閉路が異なる。そのため、負閉路を含みうる場合、そこから順にたどって、到達可能なら距離を$- \infty$に更新する。

{% include a.html code="bellman_ford_negative_loop.cpp" %}