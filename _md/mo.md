---
category: "\u30AF\u30A8\u30EA"
date: 2020-02-17
layout: post
tags: "\u30AF\u30A8\u30EA"
title: Mo's algorithm
---

## 説明
区間のマージは高速に出来ないが、区間を1つ広げる/縮めることが$O(p(N))$でできれば、$Q$個のクエリを$O(N \sqrt{Q p(N)})$ で処理できる。(ブロックサイズ$B$を適切に設定すれば)
{% include a.html code="mo.cpp" %}