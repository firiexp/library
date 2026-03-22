---
title: get_prime_wheel
documentation_of: //math/prime/get_prime_wheel.cpp
date: 2026-03-22
category: 数学
tags: 数学
---

## 説明
mod 30 の wheel sieve で `M` 以下の素数を列挙する。
`2, 3, 5` を先に処理し、それ以外は 30 と互いに素な候補だけを持つ。

## できること
- `Prime(int M)`
  `M` 以下の素数をすべて列挙する
- `Prime(int M, int a, int b)`
  `M` 以下の素数のうち、0-indexed で `b, b + a, b + 2a, ...` 番目の素数だけを `picked` に入れる
- `int count`
  `M` 以下の素数個数
- `vector<int> primes`
  `Prime(int M)` で列挙した素数
- `vector<int> picked`
  `Prime(int M, int a, int b)` で拾った素数

## 使い方
全列挙したいなら `Prime p(M);` を作って `p.primes` を参照する。
個数だけでなく等差間隔で一部だけ拾いたいなら `Prime p(M, a, b);` を使い、全体個数は `p.count`、抽出結果は `p.picked` を見る。

`Prime(int M, int a, int b)` の抽出位置は 0-indexed で、`count == b` の素数から始めて素数を 1 個見るごとに `count` を進める。
たとえば `a = 2, b = 1` なら 2 番目, 4 番目, 6 番目, ... の素数を拾う。
