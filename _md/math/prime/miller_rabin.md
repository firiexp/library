---
title: Miller-Rabin法(確率的素数判定)
documentation_of: //math/prime/miller_rabin.cpp
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
Montgomery 乗算を使った `64bit` 整数向けの Miller-Rabin 素数判定。
既知の基底集合を使うので、`uint64_t` 範囲では決定的に判定できる。

## できること
- `bool miller_rabin(T n)`
  `n` が素数なら `true`、合成数なら `false`

## 使い方
整数型 `T` を渡して呼ぶだけでよい。
`n <= 1` と偶数は先に弾き、`64bit` 整数では既知の基底で判定する。

## 実装上の補足
乗算は Montgomery 形式で処理する。
単純な `%` ベース実装より定数倍が軽い。
