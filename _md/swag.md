---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2020-02-19
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Sliding Window Aggregation
---

## 説明
Queueをstack2つで表現することで、Queue内の和を求めることを高速に行う。
{% include a.html code="swag.cpp" %}

popするときに半分だけ持ってくるようにすると、Dequeにも対応できる。
{% include a.html code="swag_deque.cpp" %}
