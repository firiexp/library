---
layout: post
title: 単一始点最短路(Dijkstra法)
date: 2018-04-28
category: グラフ
tags: グラフ
---

## 説明
単一始点最短路を求める。負辺があると正しく動作しない。
$O(V \log E)$
{% include a.html code="dijkstra.cpp" %}