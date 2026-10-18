---
title: bitsetの共通集計処理
documentation_of: //datastructure/bitset_count.cpp
---

## 説明
`DynamicBitset` と `StaticBitset` が共有する内部の集計処理。
利用側では各 bitset の `count()` を使う。

## 実装上の補足
128 word 以上では、対応 CPU に応じて AVX2 または AVX-512 VPOPCNTDQ で集計する。
短い配列や非対応環境では各 bitset の scalar 経路を使う。
時間は $O(\lceil N/64 \rceil)$、追加領域は $O(1)$。
