---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2019-10-20
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Radix-Heap
---

## 説明
最大値 $D$ で、`pop` された数より小さな数が `push` されないとき、優先度付きキューの各操作を $O(\log D)$ で行う。
## 機能
- $\operatorname{emplace}(x, \mathrm{val})$ : キー $x$、値 `val` の要素を `push` する
- $\operatorname{top}()$ : 最小の要素を返す
- $\operatorname{pop}()$ : 最小の要素を取り除く
