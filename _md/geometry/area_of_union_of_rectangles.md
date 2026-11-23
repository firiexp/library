---
title: 長方形和集合面積(Area of Union of Rectangles)
documentation_of: //geometry/area_of_union_of_rectangles.cpp
---

## 説明
軸に平行な長方形の和集合の面積を求める。

## できること
長方形の個数を $N$ とする。

- `AreaOfUnionOfRectangles<Coord, Area> solver`
  長方形が未登録の状態で作る。$O(1)$
- `void add_rectangle(Coord l, Coord d, Coord r, Coord u)`
  半開長方形 `[l, r) x [d, u)` を追加する。空長方形は無視する。償却 $O(1)$
- `Area solve() const`
  追加した長方形の和集合面積を返す。時間 $O(N\log N)$、作業領域 $O(N)$

## 使い方
座標型 `Coord` と面積型 `Area` の既定はともに `long long`。座標差も `Area` で計算するため、`Area` には座標値、座標差、和集合の面積を表せる型を選ぶ。

```cpp
AreaOfUnionOfRectangles<int, long long> solver;
solver.add_rectangle(0, 0, 3, 2);
solver.add_rectangle(1, 1, 4, 3);
auto area = solver.solve(); // 10
```
