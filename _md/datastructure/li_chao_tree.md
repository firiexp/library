---
title: Li Chao Tree
documentation_of: //datastructure/li_chao_tree.cpp
date: 2026-03-07
category: データ構造
tags: データ構造
---

## 説明
直線集合に対して、1点での最小値(または最大値)クエリを処理する。

## できること
- `LiChaoTree<T, false>(xs)` : オフライン版（`xs` に含まれる座標でのみクエリ可能）
- `OnlineLiChaoTree<T, false>(low, high)` : オンライン版（区間 `[low, high)`）
- `add_line(a, b)` : 直線 `y = ax + b` を追加
- `add_segment(a, b, l, r)` : 区間 `[l, r)` のみ有効な直線 `y = ax + b` を追加
- `query(x)` : 座標 `x` での最小値を返す。有効な直線がない場合は `numeric_limits<T>::max() / 4`、最大値版ではその符号を反転した値を返す

`LiChaoTree<T, true>` / `OnlineLiChaoTree<T, true>` を使うと最大値クエリになる。

## 実装上の補足
直線の評価に必要な乗算・加算と、最大値版の係数・評価値の符号反転は `T` に収まる必要がある。
オンライン版は整数区間を扱い、`low < high`、`high - low` が `T` に収まることを前提とする。クエリは `[low, high)` 内で行う。
有効な直線の評価値には、空集合を表す番兵による上限・下限はない。
