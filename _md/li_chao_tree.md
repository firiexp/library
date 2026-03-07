---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
date: 2026-03-07
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Li Chao Tree
---

## 説明
直線集合に対して、1点での最小値(または最大値)クエリを処理する。

## 機能
- `LiChaoTree<T, false>(xs)` : オフライン版（`xs` に含まれる座標でのみクエリ可能）
- `OnlineLiChaoTree<T, false>(low, high)` : オンライン版（区間 `[low, high)`）
- `add_line(a, b)` : 直線 `y = ax + b` を追加
- `add_segment(a, b, l, r)` : 区間 `[l, r)` のみ有効な直線 `y = ax + b` を追加
- `query(x)` : 座標 `x` での最小値を返す

`LiChaoTree<T, true>` / `OnlineLiChaoTree<T, true>` を使うと最大値クエリになる。
