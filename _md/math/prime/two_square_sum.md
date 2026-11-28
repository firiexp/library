---
title: 二平方和表現の列挙
documentation_of: //math/prime/two_square_sum.cpp
---

## 説明
整数を2つの平方数の和で表す方法を列挙する。

## できること
- `vector<pair<long long, long long>> two_square_sum(long long n)`
  $x^2+y^2=n$ を満たす非負整数の順序対 $(x,y)$ を重複なく返す。列挙順は任意で、解がなければ空配列を返す。解の個数を $K$ として期待 $O(n^{1/4} + K)$

## 使い方
```cpp
auto pairs = two_square_sum(65);  // (1, 8), (4, 7), (7, 4), (8, 1) の4組
```
