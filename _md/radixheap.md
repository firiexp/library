---
layout: post
title: Radix-Heap
date: 2019-10-20
category: データ構造
tags: データ構造
---

## 説明
最大値$D$で、popされた数より小さな数がpushされないとき、優先度付きキューの各操作を$O(\log D)$で行う。
## 機能
- $\mathrm{emplace}(x, val)$ : キーxで値valの要素をpushする
- $\mathrm{top}()$ : 最小の要素を返す
- $\mathrm{pop}()$ : 最小の要素を取り除く
{% include a.html code="radixheap.cpp" %}