---
category: "\u6728"
date: 2019-10-10
layout: post
tags: "\u6728"
title: "\u91CD\u8EFD\u5206\u89E3"
---

## 説明
N頂点の根つき木について, 木を1次元区間で表し、パスを$O(\log N)$ 個の区間に分割するアルゴリズム.これを使えば,パスクエリをクエリあたり$O(\log N f(N))$で処理することができる($f(N)$は区間クエリの計算量). 

{% include a.html code="hld.cpp" %}