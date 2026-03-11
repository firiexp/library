---
title: 3次元幾何(Geometry 3D)
documentation_of: //geometry/geometry3d.cpp
date: 2026-03-12
category: 幾何
tags: 幾何
---

## 説明
3 次元ベクトル演算と、3 点から決まる平面、直線と平面の交点を扱う最小限の補助である。
凸包や球、距離計算などはまだ持たない。

## できること
- `Point3(x, y, z)`
  3 次元点・ベクトルを作る
- `a + b`, `a - b`, `a * k`, `a / k`
  ベクトル演算をする
- `Real3 dot(Point3 a, Point3 b)`
  内積を返す
- `Real3 norm(Point3 a)`
  二乗ノルムを返す
- `Real3 abs(Point3 a)`
  ノルムを返す
- `Point3 cross(Point3 a, Point3 b)`
  外積を返す
- `Plane(a, b, c, d)`
  平面 $ax + by + cz + d = 0$ を作る
- `Plane(p, q, r)`
  3 点を通る平面を作る。3 点が同一直線上なら法線が 0 になる
- `Real3 eval(Plane p, Point3 x)`
  点 `x` を平面式へ代入した値を返す
- `Point3 crossPoint(Point3 s, Point3 t, Plane p)`
  直線 `s` - `t` と平面 `p` の交点を返す。平行なときは使えない

## 使い方
`Point3` をベクトルとして扱い、`Plane` は係数指定か 3 点指定で作る。
直線と平面の交点は `crossPoint` を使う。

```cpp
Point3 a(0, 0, 0), b(1, 0, 0), c(0, 1, 0);
Plane p(a, b, c);
Point3 s(0, 0, 1), t(0, 0, -1);
Point3 x = crossPoint(s, t, p);
```

## 実装上の補足
`Real3` は `double` で、許容誤差として `EPS3` を置いている。
`crossPoint` は分母が 0 に近いと不安定なので、必要なら `abs(den) < EPS3` 相当の判定を呼び出し側で入れる。
