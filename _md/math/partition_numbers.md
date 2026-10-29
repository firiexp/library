---
title: 整数の分割数
documentation_of: //math/partition_numbers.cpp
date: 2026-10-30
category: 数学
tags: 数学
---

## 説明
整数 $n$ の分割数 $p(n)$ を求める。
$p(n)$ は次を満たす正整数列 $(a_1,\ldots,a_k)$ の個数である。

$$
1\leq a_1\leq\cdots\leq a_k,\qquad \sum_{i=1}^{k}a_i=n
$$

$k$ は任意の非負整数とし、空列も1通りと数えるので $p(0)=1$。

## できること
- `vector<mint> partition_numbers(int n)`
  $p(0),\ldots,p(n)$ を `998244353` で割った余りの列を返す。時間 $O(n\log n)$、領域 $O(n)$

## 使い方
$0\leq n<2^{23}$ を渡す。
法と上限は依存先の NTT に合わせて固定している。

```cpp
auto p = partition_numbers(5);
```

返り値は `{1, 1, 2, 3, 5, 7}`。

## 実装上の補足
Euler の五角数定理を使い、分母の非零係数を列挙してから既存 FPS の逆数を求める。

$$
\sum_{n\geq0}p(n)x^n
=\frac{1}{\prod_{j\geq1}(1-x^j)}
=\frac{1}{1+\sum_{k\geq1}(-1)^k\left(x^{k(3k-1)/2}+x^{k(3k+1)/2}\right)}
$$

分母の非零項は $O(\sqrt n)$ 個、零初期化を含む構築は $O(n)$。
逆数の計算では $n+1$ 以上の最小の2冪までの変換長を使う。
