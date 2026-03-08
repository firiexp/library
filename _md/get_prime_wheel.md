---
category: "\u6570\u5B66"
date: 2026-03-08
tags: "\u6570\u5B66"
title: get_prime_wheel
---

## 説明
`2, 3, 5` を除いた候補だけを持つ wheel sieve で素数を列挙する。
30 を法にした車輪を使うので、通常の篩より定数倍が軽い。

## できること
- `Prime p(int M)`
  `M` 以下の素数を列挙する
- `vector<ll> primes`
  列挙結果を昇順で持つ

## 使い方
`Prime p(M);` を作り、`p.primes` を参照する。
`M < 2` なら空、`M >= 2` なら `2, 3, 5` を含めて返す。
