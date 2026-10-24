---
title: 固定長bitset(Static Bitset)
documentation_of: //datastructure/static_bitset.cpp
date: 2026-03-22
category: データ構造
tags: データ構造
---

## 説明
長さがコンパイル時定数の bitset。
`uint64_t` 単位で持ち、集合演算、shift、立っている bit の走査を扱う。

## できること
$N$ は bitset の長さとする。

- `StaticBitset<N> bs(bool x = false)`
  長さ `N` の bitset を作る。`x = true` なら全 bit を 1 で初期化する。$O(\lceil N/64 \rceil)$
- `int size() const`
  長さを返す。$O(1)$
- `bool test(int k) const`
  `k` bit 目を返す。$O(1)$
- `void set(int k)`, `void reset(int k)`, `void flip(int k)`, `void assign(int k, bool x)`
  `k` bit 目を更新する。$O(1)$
- `void set()`, `void reset()`, `void flip()`
  全体を更新する。$O(\lceil N/64 \rceil)$
- `bool any() const`, `bool none() const`, `bool all() const`
  1 があるか、全て 0 か、全て 1 かを返す。$O(\lceil N/64 \rceil)$
- `int count() const`
  1 の個数を返す。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `int count_and(const StaticBitset &other) const`
  両方で 1 の bit 数を返す。空なら `0`。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `bool intersects(const StaticBitset &other) const`
  両方で 1 の bit があれば `true`。なければ空も含めて `false`。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$
- `int find_first() const`
  最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_last() const`
  最後に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_next(int k) const`
  `k` より右で最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `int find_prev(int k) const`
  `k` より左で最初に立っている bit の位置を返す。なければ `-1`。$O(\lceil N/64 \rceil)$
- `bs &= other`, `bs |= other`, `bs ^= other`
  bitset 同士の演算をその場で行う。$O(\lceil N/64 \rceil)$
- `bs << s`, `bs >> s`, `bs <<= s`, `bs >>= s`
  shift する。$O(\lceil N/64 \rceil)$
- `bs.or_shift_left(s)`, `bs.or_shift_right(s)`
  `bs |= bs << s` / `bs |= bs >> s` をその場で行い、自身への参照を返す。`s <= 0` または `s >= N` なら変更しない。時間 $O(\lceil N/64 \rceil)$、追加領域 $O(1)$

## 使い方
長さが同じ bitset 同士で演算する。
共通要素の個数は `a.count_and(b)`、有無は `a.intersects(b)` で求める。
`StaticBitset<2048> bs;` のように長さをテンプレート引数で指定する。
部分和 DP では `bs.set(0)` で初期化し、各重み `w` に対して `bs.or_shift_left(w)` で更新する。

## 実装上の補足
`count()` は短い配列では scalar、長い配列では対応 CPU に応じた SIMD 集計を使う。
`DynamicBitset` と集計処理を共有し、両方を同時に include できる。
`intersects` は共通 bit を見つけた時点で返る。
