---
title: 門松列判定
date: 2018-04-28
category: 謎
tags: 謎
---

## 説明
3つの値がすべて異なり、中央が最大または最小になる列を門松列と呼ぶ。

## できること
- `bool IsKadomatsu(int a, int b, int c)`
  `(a, b, c)` が門松列なら `true`、そうでなければ `false` を返す。$O(1)$

## 使い方
`IsKadomatsu(1, 3, 2)` は `true`、`IsKadomatsu(1, 2, 3)` は `false` を返す。

[門松列の問題例](https://yukicoder.me/problems/220)
