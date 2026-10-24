---
title: 長方形和集合面積(Area of Union of Rectangles)
documentation_of: //geometry/area_of_union_of_rectangles.cpp
date: 2026-03-14
category: 幾何
tags: 幾何, データ構造
---

## 説明
長方形集合の和集合の面積を求める。

## できること
長方形の個数を $N$ とする。

- `AreaOfUnionOfRectangles<Coord, Area> solver`
  長方形が未登録の状態で作る。$O(1)$
- `void add_rectangle(Coord l, Coord d, Coord r, Coord u)`
  半開長方形 `[l, r) x [d, u)` を追加する。空長方形は無視する。償却 $O(1)$
- `Area solve()`
  追加した長方形の和集合面積を返す。$O(N\log N)$

## 使い方
長方形を全部 `add_rectangle` してから `solve()` を呼ぶ。
`Coord` は座標型、`Area` は面積を保持する型で、既定は `long long` になる。
