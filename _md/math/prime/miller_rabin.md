---
title: Miller-Rabin素数判定
documentation_of: //math/prime/miller_rabin.cpp
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
Montgomery 乗算を使った Miller-Rabin 素数判定。
$0 \le n < 2^{63}$ の範囲で決定的に判定する。

## できること
- `bool miller_rabin(T n)`
  `n` が素数なら `true`、それ以外は `false`。`n <= 1` は負数も含めて `false`

## 使い方
整数型 `T` を渡して呼ぶ。

## 実装上の補足
乗算は Montgomery 形式で処理する。
単純な `%` ベース実装より定数倍が軽い。
