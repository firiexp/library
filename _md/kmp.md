---
layout: post
title: KMP
documentation_of: //string/kmp.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 概要

Knuth-Morris-Pratt 法。
文字列 `pattern` の失敗関数テーブルを `kmp_table` で構築し、
`kmp_search(text, pattern)` で `pattern` の出現開始位置を列挙する。

## 計算量

- `kmp_table(s)` : `O(|s|)`
- `kmp_search(text, pattern)` : `O(|text| + |pattern|)`

## 使い方

1. `auto pos = kmp_search(text, pattern);`
2. `pos` に一致開始位置（0-indexed）が昇順で入る

## 実装上の補足

- `pattern` が空文字列のときは、`0..|text|` のすべてを返す。
