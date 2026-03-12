---
category: "\u6570\u5B66"
date: 2026-03-08
tags: "\u6570\u5B66"
title: gcd_transform
---

## 説明
添字を約数半順序とみなした zeta 変換と mobius 反転を行う。
`v[i]` に対して、変換後は `sum_{k>=1} v[i*k]` になる。
計算量は $O(n log log n)$。

## できること
- `void gcd_transform(vector<T>& v)`
  倍数側への総和を取る。`v[0]` は触らない
- `void gcd_itransform(vector<T>& v)`
  `gcd_transform` の逆変換を行う。`v[0]` は触らない

## 使い方
長さ `n + 1` の配列を渡し、`1..n` を使う。
gcd 畳み込みや、`gcd = 1` 条件の包除に使う前処理としてそのまま呼べる。
