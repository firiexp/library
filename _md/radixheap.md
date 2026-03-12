---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2019-10-20
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Radix-Heap
---

## 説明
最大値 $D$ で、`pop` された数より小さな数が `push` されないとき、優先度付きキューの各操作を $O(\log D)$ で行う。

## できること
- `emplace(x, val)` : キー `x`、値 `val` の要素を `push` する
- `top()` : 最小の要素を返す。空なら未定義
- `pop()` : 最小の要素を取り除く。空なら未定義
- `size()` : 要素数を返す
- `empty()` : 空なら `true` を返す
