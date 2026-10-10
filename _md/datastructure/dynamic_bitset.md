---
title: 動的bitset(Dynamic Bitset)
documentation_of: //datastructure/dynamic_bitset.cpp
date: 2026-03-22
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
- `int find_last() const`
  最後に立っている bit の位置を返す。なければ `-1`
- `int find_next(int k) const`
  `k` より右で最初に立っている bit の位置を返す。なければ `-1`
- `int find_prev(int k) const`
  `k` より左で最初に立っている bit の位置を返す。なければ `-1`
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する
- `DynamicBitset &or_shift_left(int s)`, `DynamicBitset &or_shift_right(int s)`
  `bs |= bs << s`、`bs |= bs >> s` と同じ更新を一時配列なしで行い、自身への参照を返す。`s <= 0`、`s >= size()`、空 bitset では変更しない。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$、動的確保なし

## 使い方
長さが同じ bitset 同士で演算する。
`find_first`, `find_next` を使うと立っている bit だけを前から走査できる。
`find_last`, `find_prev` を使うと後ろからも走査できる。
部分和 DP は `reachable.set(0)` で初期化し、各重み `w` に対して `reachable.or_shift_left(w)` で更新できる。
