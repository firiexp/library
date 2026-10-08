---
title: pell_equation
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Pell 方程式 $x^2-dy^2=1$ の最小正整数解を整数の連分数漸化式から求める。
`d` が平方数なら非自明解がないので `(0, 0)` を返す。
連分数の周期長を $L$ として、時間・領域は $O(L)$。

## できること
- `vector<ll> sqrt_fraction(ll n)`
  $\sqrt n$ の連分数展開の初項と、それに続く1周期を返す。平方数なら初項だけ
- `pair<ll, ll> pell_equation(ll d)`
  最小正整数解 `(x, y)` を返す。`d` が平方数なら `(0, 0)`

## 使い方
`auto [x, y] = pell_equation(d);` として使う。
`sqrt_fraction(n)` は $0 \le n \le \mathrm{LLONG\_MAX}$ を扱う。
例えば `sqrt_fraction(13)` は `{3, 1, 1, 1, 1, 6}` を返す。

`pell_equation(d)` は正の `long long` の `d` に対し、平方数または最小解の両成分が `long long` に収まる入力を扱う。
収束分数と解の判定・二乗の中間計算には `__int128` を使う。
最小解が `long long` を超える入力は対象外とする。
