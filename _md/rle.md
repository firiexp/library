---
category: util
date: 2026-03-08
layout: post
tags: util
title: RLE
---

## 説明
列を run-length encoding する。
連続する同じ値を `(値, 個数)` にまとめる。
計算量は `O(N)`。

## できること
- `vector<pair<T, int>> RLE(const vector<T>& a)`
  `a` を run-length encoding した列を返す。空配列なら空配列を返す

## 使い方
`T` には `==` が必要。
返り値の各要素は出現順に並ぶ。
