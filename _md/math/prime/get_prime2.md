---
title: 高速素数列挙(ExactDiv)
documentation_of: //math/prime/get_prime2.cpp
---

## 説明
線形篩で `n` 以下の素数を列挙する。
素数は `ExactDiv<uint>` として保持し、除算判定を高速化できる形で返す。

## できること
- `vector<ExactDiv<uint>> get_prime_exact_div(int n)`
  `n` 以下の素数を返す。`n <= 1` なら空。$O(n)$
- `ExactDiv<T> d(n)`
  `n` に 2 または奇数を指定し divide を可能にする。`T` には符号なし整数型を使う。$O(1)$
- `bool ExactDiv<T>::divide(T x) const`
  `d.divide(x)` は `x % n == 0` を返す。$O(1)$

## 使い方
`LinearSieve` の素数列挙を `ExactDiv<uint>` に詰め直した wrapper である。
返り値の各要素は素数値を `val` に持つ。
試し割りを大量に行うコードでは `x % p == 0` の代わりに `p.divide(x)` を使える。
