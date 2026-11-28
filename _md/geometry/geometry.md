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
- `Point project(Line l, Point p)`
  点 `p` から直線 `l` に下ろした垂線の足を返す。$O(1)$
- `Point project(Segment s, Point p)`
  点 `p` から両端点 `s.a`、`s.b` を通る直線に下ろした垂線の足を返す。足が線分の外にある場合もその点を返す。$O(1)$
- `Point refrect(Segment s, Point p)`
  線分 `s` の両端点を通る直線を軸に、点 `p` を反射した点を返す。$O(1)$
- `bool isOrthogonal(Segment s, Segment t)` / `bool isparallel(Segment s, Segment t)`
  直交判定・平行判定を返す。$O(1)$
- `Point crossPoint(Segment s, Segment t)`
  交差する2線分の交点を返す。線分が重なる場合は、共通部分の端点を1つ返す。$O(1)$
- `Point crossPoint(Line s, Line t)`
  2直線の交点を返す（交点を持つ前提）。$O(1)$
- `Polygon crossPoint(Circle c, Line l)` / `crossPoint(Circle c, Segment s)` / `crossPoint(Circle c1, Circle c2)`
  円と直線・線分・円の交点列を返す。$O(1)$
- `Polygon tangent(Circle c, Point p)` / `vector<Line> tangent(Circle c1, Circle c2)`
  点から円への接点列、2円の共通接線列を返す。$O(1)$

### 多角形・点集合
- `double area(const Polygon& v)`
  多角形の符号付き面積を返す。$O(N)$
- `double area(Circle c, Polygon& v)`
  円 `c` と多角形 `v` の共通部分の符号付き面積を返す。頂点順が反時計回りなら正、時計回りなら負とする。$O(N)$
- `double area(Circle a, Circle b)`
  2円の共通部分の面積を返す。$O(1)$
- `bool isconvex(const Polygon& v)`
  反時計回りの多角形が凸かを返す。$O(N)$
- `int contains(const Polygon& v, Point p)`
  点 `p` が多角形 `v` の内部なら `2`、辺上なら `1`、外部なら `0` を返す。$O(N)$
- `int contains_convex(Polygon& v, Point p)`
  凸多角形の頂点列を非 `const` の変数 `v` で渡す。頂点順は時計回り・反時計回りのどちらでもよく、辺上の中間点も含められる。返り値は `contains` と同じ。通常 $O(\log N)$、全頂点が共線の場合などは $O(N)$
- `Polygon convex_hull(Polygon v)`
  重複のない点列 `v` の凸包を返す。$y$ が最小の点（同値なら $x$ が最小の点）から反時計回りに並べ、辺上の入力点も残す。全点が共線なら、その始点から反対側の端点まで各点を順に1回ずつ返す。$O(N\log N)$
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
