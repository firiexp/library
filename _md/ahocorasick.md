---
title: Aho-Corasick法
documentation_of: //datastructure/ahocorasick.cpp
---

## 説明
Trie 木に対応するパターンマッチングオートマトンを構築する。

## できること
- `add(s, cur)` : Trie 木の位置 `cur` に文字列 `s` を追加し、そのノードを返す
- `build()` : パターンマッチングオートマトンを構築する
- `next(x, c)` : 位置 `x` に文字 `c` を与えたときの行き先を返す

## 使い方
先に `add` でパターンを追加し、その後 `build()` を呼ぶ。
`next` は構築後の遷移を返す。
