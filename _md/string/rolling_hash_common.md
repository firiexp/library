---
title: Rolling Hashの共通処理
documentation_of: //string/rolling_hash_common.cpp
---

## 説明
`rolling_hash<M>` と `rolling_hash_ull` の共通処理をまとめた内部実装。

## できること
- 各要素からハッシュ計算に使う整数を求める。1 要素あたり $O(1)$
- 2 区間のハッシュを比較して最長共通接頭辞長を求める。短い方の区間長を $L$ として $O(\log L)$

## 使い方
mod を指定する場合は `rolling_hash<M>`、mod $2^{61}-1$ を使う場合は `rolling_hash_ull` を使う。
