---
title: ランレングス圧縮(RLE)
documentation_of: //util/rle.cpp
date: 2026-03-08
category: util
tags: util
---

## 説明
列を run-length encoding する。
連続する同じ値を `(値, 個数)` にまとめる。

## できること
- `vector<pair<T, int>> RLE(const vector<T>& a)`
  `a` を run-length encoding した列を返す。$O(|a|)$

## 使い方
`T` には `==` が必要。
返り値の各要素は出現順に並ぶ。
