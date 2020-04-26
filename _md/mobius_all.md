---
layout: post
title: メビウス関数 (1からMまで)
date: 2020-01-12
category: 数学
tags: 数学
---

## 説明

次のように定義されるメビウス関数 $ \mu (n) $を $1 \leq n \leq M $ となるすべての$n$に対して $ \Theta (M \log \log M) $ で求める。
- $\mu (1) = 1 $
- $\mu (p^{2} k) = 0 $ ($p$ は素数, $k$は正整数)
- 上のどちらでもなく、$n$が$k$ 個の素数の積ならば$ \mu (n) = (-1)^k $

{% include a.html code="mobius_all.cpp" %}