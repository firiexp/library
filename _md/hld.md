---
layout: post
title: 重軽分解
date: 2019-10-10
category: 木
tags: 木
---

## 説明
N頂点の根つき木について, 木を1次元区間で表し、パスを$O(\log N)$ 個の区間に分割するアルゴリズム.これを使えば,パスクエリをクエリあたり$O(\log N f(N))$で処理することができる($f(N)$は区間クエリの計算量). 

{% include a.html code="hld.cpp" %}