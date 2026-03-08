---
layout: post
title: miller_rabin_fast
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
Montgomery 乗算を使った高速な Miller-Rabin 素数判定。
`uint64_t` 範囲で決定的に判定する。

## できること
- `bool miller_rabin(T n)`
  `n` が素数なら `true`、合成数なら `false`

## 使い方
整数型 `T` を渡して呼ぶだけでよい。
`n <= 1` と偶数は先に弾かれ、64bit 整数では既知の基底集合で判定する。
