---
layout: post
title: Sliding Window Aggregation
date: 2020-02-19
category: データ構造
tags: データ構造
---

## 説明
Queueをstack2つで表現することで、Queue内の和を求めることを高速に行う。
{% include a.html code="swag.cpp" %}

popするときに半分だけ持ってくるようにすると、Dequeにも対応できる。
{% include a.html code="swag_deque.cpp" %}
