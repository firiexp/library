---
title: 商が一定の区間列挙
documentation_of: //math/quotient_ranges.cpp
date: 2026-11-01
category: 数学
tags: 数学
---

## 説明
$\lfloor N/i\rfloor$ が一定になる区間ごとに処理する。
約数和など、$\sum_i a_i\lfloor N/i\rfloor$ の形の和を求めるときに使う。

## できること
`f` は区間ごとの処理を行う関数で、左端 `l`、右端 `r`、商 `q` を引数に取る。

- `void for_each_quotient(long long n, F f, long long first = 1)`
  `first <= i <= n` を覆う最大の**閉区間** `[l, r]` と商 `q = n / l` を、`l` の昇順に `f(l, r, q)` へ渡す。`f` の呼び出しは高々 $2\lfloor\sqrt N\rfloor$ 回、作業領域は $O(1)$

## 使い方
`0 <= n <= LLONG_MAX`、`first >= 1` とする。
`first` を省略すると `1 <= i <= n` 全体を処理する。
指定した場合はその位置から始めるため、最初の区間だけ左端が切り詰められることがある。

次は `prefix(k)` が $\sum_{i=1}^{k} a_i$ を返すとき、$\sum_{i=1}^{N}a_i\lfloor N/i\rfloor$ を求める例。
`prefix` と積の計算には、結果が収まる型を使う。

```cpp
__int128 answer = 0;
for_each_quotient(n, [&](long long l, long long r, long long q) {
    answer += (__int128(prefix(r)) - prefix(l - 1)) * q;
});
```

## 実装上の補足
`q = n / l > l` の間は区間が1要素なので、右端の除算を省く。
`q <= l` になった後は商が1ずつ減るため、`r = n / q` だけを計算して進める。
切り替え位置は商との比較で判断し、平方根や二乗は計算しない。
最後の商1の区間は右端を `n` とし、除算と `n + 1` の計算を省く。
