---
title: 幾何ライブラリ(Geometry)
documentation_of: //geometry/geometry.cpp
---

## 説明
幾何に関するライブラリの詰め合わせ。

## できること
- `Point` 構造体 : Point 同士の加減、Point のスカラー倍、比較(デフォルトは $x$ 座標)、入力
- `Polygon` : `vector<Point>` の別名
- `convex_hull(v)` : `v` の凸包を返す
- `diameter(v)` : 反時計回りの凸多角形の直径を $O(N)$ で返す。空・1点では `0`、全点が共線の場合は両端の距離を返す
