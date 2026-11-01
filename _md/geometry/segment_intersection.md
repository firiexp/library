---
title: 整数座標の線分交差判定
documentation_of: //geometry/segment_intersection.cpp
date: 2026-11-01
category: 幾何
tags: 幾何
---

## 説明
整数座標の2本の閉線分が共有点を持つかを、整数演算で判定する。

## できること
- `bool segments_intersect(IntPoint a, IntPoint b, IntPoint c, IntPoint d)`
  閉線分 `ab` と `cd` が交わるなら `true`、離れていれば `false` を返す。時間・追加領域 $O(1)$

## 使い方
各座標は $|x|, |y|\le 10^{18}$ とする。
端点での接触、共線の重なり、端点が同一で点になった線分も扱う。

```cpp
IntPoint a{0, 0}, b{4, 4}, c{0, 4}, d{4, 0};
bool intersects = segments_intersect(a, b, c, d);
```

## 実装上の補足
座標区間の重なりと外積の符号で判定する。
外積は差分を取る前に `__int128` へ広げ、外積どうしの積を作らずに符号を比較する。
