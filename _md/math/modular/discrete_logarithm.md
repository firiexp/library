---
title: 離散対数(Discrete Logarithm)
documentation_of: //math/modular/discrete_logarithm.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`x^k ≡ y (mod m)` を満たす最小の非負整数 `k` を求める。
解がなければ `-1` を返す。

## できること
- `ll discrete_logarithm(ll x, ll y, ll mod)`
  `x^k ≡ y (mod mod)` を満たす最小の `k` を返す。存在しなければ `-1`。期待時間・領域 $O(\sqrt{\mathrm{mod}})$

## 使い方
`mod >= 1` を想定する。負の `x`・`y` を与えても、`mod` で正規化して計算する。

## 実装上の補足

非互いに素な場合も含めて extended BSGS で処理する。
giant step の幅に対応する冪は二分累乗で求め、途中の積には128 bit整数を使う。
ハッシュ表は同じ剰余に対する最初の指数だけを保持し、位数が小さい場合も重複したノードを作らない。
