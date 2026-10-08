---
title: 一次式の剰余の最小値
documentation_of: //math/min_of_mod_of_linear.cpp
date: 2026-10-08
category: 数学
tags: 数学
---

## 説明
$0 \le x < n$ における $(ax+b) \bmod m$ の最小値を求める。
Euclid 型の縮約を使い、時間は $O(\log m)$、追加領域は $O(1)$。

## できること
- `ll min_of_mod_of_linear(ll n, ll m, ll a, ll b)`
  $0 \le x < n$ における $(ax+b) \bmod m$ の最小値を返す。`a = 0` または `n = 1` なら `b`

## 使い方
$1 \le n,m \le \mathrm{LLONG\_MAX}$、$0 \le a,b < m$ を満たす値を渡す。
空区間と負の係数は対象外とする。中間の積と加算には `__int128` を使う。

## 実装上の補足
傾きが法の半分を超えるときは列を逆順にし、候補集合を保ったまま傾きを小さくする。
商が変わる最初の項だけを候補として法を傾きまで縮めるため、各反復で法は半分以下になる。
