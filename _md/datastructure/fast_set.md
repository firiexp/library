---
title: 整数集合の前後検索(FastSet)
documentation_of: //datastructure/fast_set.cpp
---

## 説明
$[0,N)$ の整数集合を64bit単位の階層bitsetで管理する。

## できること
- `FastSet s(n)`：空集合を作る。$O(N)$
- `FastSet s(present)`：`vector<bool>` の真の位置を集合に入れる。構築 $O(N)$
- `insert(x)` / `erase(x)`：挿入 / 削除する。重複挿入・存在しない要素の削除は何もしない。$O(\log N)$
- `contains(x)`：存在するかを返す。$O(1)$
- `next(x)`：`x` 以上の最小要素を返す。存在しなければ `-1`。$O(\log N)$
- `prev(x)`：`x` 以下の最大要素を返す。存在しなければ `-1`。$O(\log N)$

## 使い方
更新と存在判定は `0 <= x < n`、`next` は `0 <= x <= n`、`prev` は `-1 <= x < n` を前提とする。
`next(n)` と `prev(-1)` は常に `-1`。範囲外の入力を自動で切り詰めることはしない。

## 実装上の補足
各階層は下位wordが非空かを保持する。疎な集合でも空wordを線形走査しない。
階層の配列は構築時に確保し、各操作では確保しない。
