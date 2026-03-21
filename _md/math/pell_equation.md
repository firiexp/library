---
title: pell_equation
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Pell 方程式 `x^2 - d y^2 = 1` の最小正整数解を連分数から求める。
`d` が平方数なら非自明解がないので `(0, 0)` を返す。

## できること
- `vector<ll> sqrt_fraction(ll n)`
  `sqrt(n)` の連分数展開の 1 周期を返す。平方数なら `{sqrt(n)}`
- `pair<ll, ll> pell_equation(ll d)`
  最小解 `(x, y)` を返す。解がなければ `(0, 0)`

## 使い方
`auto [x, y] = pell_equation(d);` として使う。
返り値は `x^2 - d y^2 = 1` を満たす最小の正整数解になる。
