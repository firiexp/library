---
title: 素因数分解(試し割り)
documentation_of: //math/prime/primefactor.cpp
---

## 説明
前計算した素数を使い、試し割りで整数を素因数分解する。

## できること
- `vector<T> prime_factor_trial(T n)`
  $1 \le n \le 2^{31}-1$ の整数 $n$ を分解し、重複を含む素因数列を昇順に返す。$n=1$ なら空列を返す。範囲外の入力では異常終了する。$O(\sqrt{n})$

## 使い方
```cpp
auto factors = prime_factor_trial(84);  // {2, 2, 3, 7}
```

$2^{31} \le n < 2^{63}$ の整数には `primefactor_ll.cpp` の `prime_factor(n)` を使う。
