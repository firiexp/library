---
title: 半平面共通部分(Half-Plane Intersection)
documentation_of: //geometry/half_plane_intersection.cpp
date: 2026-03-12
category: 幾何
tags: 幾何
---

## 説明
有向直線の左側半平面たちの共通部分を凸多角形で返す。

## できること
半平面の個数を $N$ とする。

- `Polygon half_plane_intersection(vector<Line> ls)`
  各 `Line(a, b)` の左側半平面の共通部分を返す。空または退化なら空配列。$O(N\log N)$

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
大きな bounding box を内部で追加して処理する。

- 各 `Line(a, b)` は `a -> b` の左側を残す向きで与える
- 交差判定は `geometry.cpp` の `EPS` を使う
- 角度のソートには `EPS` を使わず、平行判定と同方向の制約の整理はソート後に行う
