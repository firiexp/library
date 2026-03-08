---
layout: post
title: Dynamic Bitset
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
可変長の bitset。
`uint64_t` 単位で持ち、集合演算、shift、立っている bit の走査を扱う。

## できること
- `DynamicBitset bs(int n, bool x = false)`
  長さ `n` の bitset を作る。`x = true` なら全 bit を 1 で初期化する
- `int size() const`
  長さを返す
- `bool test(int k) const`
  `k` bit 目を返す
- `void set(int k)`, `void reset(int k)`, `void flip(int k)`, `void assign(int k, bool x)`
  `k` bit 目を更新する
- `void set()`, `void reset()`, `void flip()`
  全体を更新する
- `bool any() const`, `bool none() const`, `bool all() const`
  1 があるか、全て 0 か、全て 1 かを返す
- `int count() const`
  1 の個数を返す
- `int find_first() const`
  最初に立っている bit の位置を返す。なければ `-1`
- `int find_next(int k) const`
  `k` より右で最初に立っている bit の位置を返す。なければ `-1`
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する

## 使い方
長さが同じ bitset 同士で演算する。
`find_first`, `find_next` を使うと立っている bit だけを走査できる。
