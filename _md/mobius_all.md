---
title: メビウス関数 (1からMまで)
date: 2020-01-12
category: 数学
tags: 数学
---

## 説明

次のように定義されるメビウス関数 $\mu(n)$ を、$1 \le n \le M$ のすべての $n$ に対して $\Theta(M \log \log M)$ で求める。

$$
\mu(n)=
\begin{cases}
1 & (n = 1) \\
0 & (p^2 \mid n \text{ となる素数 } p \text{ が存在}) \\
(-1)^k & (n \text{ が } k \text{ 個の相異なる素数の積})
\end{cases}
$$
