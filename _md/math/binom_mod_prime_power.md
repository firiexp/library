---
title: binom_mod_prime_power
documentation_of: //math/binom_mod_prime_power.cpp
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
素数冪 `p^q` を法とする二項係数 `C(n, k)` を扱う。
前計算 $O(p^q)$、各クエリ $O(log_p n)$。

## できること
- `BinomModPrimePower(ll p, int q)`
  法 `p^q` 用のテーブルを作る
- `ll C(ll n, ll k)`
  `C(n, k) mod p^q` を返す。`k < 0` または `k > n` なら `0`
- `ll modulus()`
  法 `p^q` を返す

## 使い方
`BinomModPrimePower binom(p, q);` を作り、`binom.C(n, k)` を呼ぶ。
一般の合成数 mod `m` で使いたいときは、`m` を素因数分解して各 `p^q` ごとに値を出し、CRT で併合する。

## 実装上の補足
`n!` の `p` を除いた部分と `p` の指数を再帰的に分けて計算する。
メモリは $O(p^q)$ 使うので、法が大きすぎる場合には向かない。
