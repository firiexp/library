---
title: bitsetの共通集計処理
documentation_of: //datastructure/bitset/bitset_count.cpp
---

## 説明
`DynamicBitset` と `StaticBitset` が共有する内部の集計処理。
利用側では各 bitset の `count()`、`count_and()`、`intersects()` を使う。

## 実装上の補足
128 word 以上では、対応 CPU に応じて AVX2 または AVX-512 VPOPCNTDQ で集計する。
共通 bit の集計は読み込んだ word の AND を数え、一時配列を作らない。
交差判定は 8 word 以上で AVX2 を使い、共通 bit を見つけた時点で返る。
短い配列や非対応環境では各 bitset の scalar 経路を使う。
bitset の長さを $N$ とすると、集計時間は $O(\lceil N/64 \rceil)$、追加領域は $O(1)$。
