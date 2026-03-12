---
title: 半平面共通部分(Half-Plane Intersection)
documentation_of: //geometry/half_plane_intersection.cpp
date: 2026-03-12
category: 幾何
tags: 幾何
---

## 説明
有向直線の左側半平面たちの共通部分を凸多角形で返す。
大きい bounding box を内部で足して処理し、空または退化するときは空配列を返す。
計算量は $O(N \log N)$。

## できること
- `Polygon half_plane_intersection(vector<Line> ls)`
  各 `Line(a, b)` の左側半平面の共通部分を返す。空または退化なら空配列

## 使い方
各制約を `Line(a, b)` で並べて渡す。
有界な共通部分を返す用途で使う。

```cpp
vector<Line> ls;
ls.emplace_back(Point(0, 0), Point(1, 0));
ls.emplace_back(Point(1, 0), Point(1, 1));
ls.emplace_back(Point(1, 1), Point(0, 1));
ls.emplace_back(Point(0, 1), Point(0, 0));

Polygon poly = half_plane_intersection(ls);
```

## 実装上の補足
- 各 `Line(a, b)` は `a -> b` の左側を残す向きで与える
- 交差判定は `geometry.cpp` の `EPS` を使う
