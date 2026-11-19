---
title: 幾何ライブラリ(Geometry)
documentation_of: //geometry/geometry.cpp
---

## 説明
2次元浮動小数点数幾何（`double`、`EPS = 1e-10`）の型と基本アルゴリズムをまとめたライブラリ。

## できること
多角形・点列の頂点数を $N$ とする。

### 基本型・ベクトル演算
- `Point(x = 0, y = 0)`
  2次元点・ベクトル。加減、スカラー乗除、`<`（`x` 優先、同値なら `y`）、`>>` 入力を持つ。$O(1)$
- `Segment(a, b)` / `Line(a, b)` / `Circle(c, r)` / `Polygon`
  線分・直線・円・多角形（`vector<Point>` の別名）
- `dot(a, b)` / `cross(a, b)` / `abs(a)` / `arg(p)` / `polar(r, t)`
  内積、外積、ノルム、偏角、極座標からの点生成。各 $O(1)$
- `angle(a, b)`
  非零ベクトルのなす角をラジアンで $[0, \pi]$ に返す。内積・外積を `double` で評価できる範囲を前提とする。$O(1)$
- `int ccw(Point a, Point b, Point c)`
  `a -> b` に対する `c` の位置関係を返す（`COUNTER_CLOCKWISE = 1`、`CLOCKWISE = -1`、`ONLINE_BACK = 2`、`ONLINE_FRONT = -2`、`ON_SEGMENT = 0`）。$O(1)$

### 交差・距離・射影・接線
- `bool intersect(Segment s, Segment t)` / `bool intersect(Segment s, Line t)`
  線分同士、または線分と直線が交差するかを返す。$O(1)$
- `int intersect(Circle c1, Circle c2)`
  2円の共通接線の本数に対応する位置関係を返す（`CONTAIN = 0`、`INSCRIBE = 1`、`INTERSECT = 2`、`CIRCUMSCRIBED = 3`、`SEPARATE = 4`）。$O(1)$
- `double distance(Line l, Point c)` / `distance(Segment s, Point c)` / `distance(Segment s, Segment t)`
  直線・線分と点、または線分同士の距離を返す。$O(1)$
- `Point project(Line l, Point p)` / `project(Segment s, Point p)` / `refrect(Segment s, Point p)`
  垂線の足（射影）と線対称な点（反射）を返す。$O(1)$
- `bool isOrthogonal(Segment s, Segment t)` / `bool isparallel(Segment s, Segment t)`
  直交判定・平行判定を返す。$O(1)$
- `Point crossPoint(Segment s, Segment t)` / `crossPoint(Line s, Line t)`
  2線分・2直線の交点を返す（交点を持つ前提）。$O(1)$
- `Polygon crossPoint(Circle c, Line l)` / `crossPoint(Circle c, Segment s)` / `crossPoint(Circle c1, Circle c2)`
  円と直線・線分・円の交点列を返す。$O(1)$
- `Polygon tangent(Circle c, Point p)` / `vector<Line> tangent(Circle c1, Circle c2)`
  点から円への接点列、2円の共通接線列を返す。$O(1)$

### 多角形・点集合
- `double area(const Polygon& v)` / `area(Circle c, Polygon& v)` / `area(Circle a, Circle b)`
  多角形の符号付き面積（$O(N)$）、円と多角形の共通部分面積（$O(N)$）、2円の共通部分面積（$O(1)$）を返す
- `bool isconvex(const Polygon& v)`
  反時計回りの多角形が凸かを返す。$O(N)$
- `int contains(const Polygon& v, Point p)` / `int contains_convex(Polygon& v, Point p)`
  点 `p` の包含関係を返す（内部 `2`、辺上 `1`、外部 `0`）。一般多角形は $O(N)$、凸多角形は $O(\log N)$
- `Polygon convex_hull(Polygon v)`
  `v` の凸包を返す（重複頂点を含まない前提）。$O(N\log N)$
- `double diameter(const Polygon& v)`
  反時計回りの凸多角形の直径を返す。空・1点では `0`、全点が共線の場合は両端の距離を返す。$O(N)$
- `Polygon convexCut(const Polygon& v, Line l)`
  反時計回りの凸多角形を直線 `l` の左側で切断した多角形を返す。$O(N)$
- `double closest_pair(Polygon& v, int l = 0, int r = -1)`
  2点以上の区間 `[l, r)` の最近点間距離を返す。重複点があれば `0`。時間 $O(N\log N)$、追加領域 $O(N)$（`r` を指定する場合の $N$ は `r - l`）

## 使い方
`closest_pair(v)` は全体を $x$ 座標順に並べ替えてから最近点対を求め、終了時は $y$ 座標順になる。
`r` を指定する場合は、呼び出し側で `[l, r)` を `Point::operator<` 順に並べておく。
この場合は区間内だけを $y$ 座標順へ並べ替え、区間外は読み書きしない。
`r == -1` の場合は、全体を $x$ 座標順にしてから `[l, v.size())` を処理する。
座標差・距離の二乗とその和が有限の `double` に収まることを前提とし、比較に `EPS` は加えない。

## 実装上の補足
入口で1本の作業配列を確保し、各再帰の $y$ 座標順 merge と境界付近の候補列に共用する。
再帰内での配列確保はない。
