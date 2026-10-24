---
title: 二項係数(mod p^q)
documentation_of: //math/binom_mod_prime_power.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
素数冪 $mod=p^q$ を法とする二項係数 `C(n, k)` を扱う。

## できること
- `BinomModPrimePower(ll p, int q)`
  法 `p^q` 用のテーブルを作る。時間・領域 $O(p^q)$
- `ll C(ll n, ll k)`
  `C(n, k) mod p^q` を返す。`k < 0` または `k > n` なら `0`。$t=\min(k,n-k)$ として、$q=1$ なら $O(\log t)$、$q>1$ なら $O(\log n+\log(p^q))$
- `ll modulus()`
  法 `p^q` を返す。$O(1)$

## 使い方
`BinomModPrimePower binom(p, q);` を作り、`binom.C(n, k)` を呼ぶ。
一般の法をまとめて扱う場合は `math/binom_mod.cpp` の `BinomMod(m)` を使う。

## 実装上の補足
`q=1` では階乗逆元表も構築し、Lucas の定理で `p` 進の各桁の二項係数を掛ける。残りの `k` が0になれば終了する。
構築時に `p` 個の `int` と $O(p)$ 時間が追加で必要だが、各クエリの逆元計算を省ける。
`q>1` では逆元表を持たず、`n!` の `p` を除いた部分と `p` の指数を再帰的に分けて計算する。
メモリは $O(p^q)$ 使うので、法が大きすぎる場合には向かない。
