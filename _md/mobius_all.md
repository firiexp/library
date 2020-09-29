---
category: "\u6570\u5B66"
date: 2020-01-12
layout: post
tags: "\u6570\u5B66"
title: "\u30E1\u30D3\u30A6\u30B9\u95A2\u6570 (1\u304B\u3089M\u307E\u3067)"
---

## 説明

次のように定義されるメビウス関数 $ \mu (n) $を $1 \leq n \leq M $ となるすべての$n$に対して $ \Theta (M \log \log M) $ で求める。
- $\mu (1) = 1 $
- $\mu (p^{2} k) = 0 $ ($p$ は素数, $k$は正整数)
- 上のどちらでもなく、$n$が$k$ 個の素数の積ならば$ \mu (n) = (-1)^k $

{% include a.html code="mobius_all.cpp" %}