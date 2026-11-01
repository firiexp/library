---
title: divisor(約数列挙)
date: 2018-04-28
category: 数学
tags: 約数
---

## 説明
$N$ の正の約数を列挙する。

## できること
- `vector<T> divisor(T n)`
  `n` の正の約数を昇順で返す。$O(\sqrt n)$
- `vector<T> divisor_from_factors(const vector<T>& factors)`
  ソート済みの素因数列から正の約数を昇順・重複なしで返す。空の列には `{1}` を返す。
  素因数列の長さを $F$、約数の個数を $D$ として、時間 $O(F+D\log D)$、返却値を含む領域 $O(D)$。

## 使い方
正の整数 `n` を渡す。

`divisor_from_factors` には重複を含む昇順の素因数列を渡す。各要素は素数で、その積が `T` に収まることを前提とする。
素因数分解を実行し直さないため、`prime_factor` の結果をそのまま利用できる。素因数分解の時間・領域は上記の計算量に含まない。

```cpp
auto factors = prime_factor(1000000000000LL);
auto divisors = divisor_from_factors(factors);
```

この例では `primefactor_ll.cpp` も読み込む。
