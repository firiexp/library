---
title: 凸包(Convex Hull)
documentation_of: //geometry/convex_hull.cpp
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数座標点集合の凸包を Andrew's monotone chain で求める。
計算量は $O(N log N)$。

## できること
- `vector<IntPoint> convex_hull(vector<IntPoint> ps)`
  点集合の凸包の頂点を反時計回り順で返す。辺上の中間点と重複点は除く
- `vector<int> convex_hull_indices(const vector<IntPoint>& points)`
  凸包の頂点を元の入力添字で返す。座標の順序は `convex_hull(points)` と同じで、重複座標は最小の添字を選ぶ。$O(N\log N)$ 時間・$O(N)$ 追加領域
- `int contains_convex(const vector<IntPoint>& hull, IntPoint p)`
  凸包の外側なら `0`（OUT）、境界上なら `1`（ON）、内部なら `2`（IN）を返す。頂点数 $H\ge 3$ で $O(\log H)$ 時間・$O(1)$ 追加領域

## 使い方
点列を `vector<IntPoint>` で渡して使う。
各座標は $|x|, |y| \le 10^{18}$ とする。
`contains_convex` には `convex_hull` が返す、反時計回りで重複・辺上の中間点を含まない凸包を渡す。照会点も同じ座標範囲とする。
空の凸包は常に OUT、1点なら同一点だけ ON、2点なら閉線分上だけ ON を返す。この場合は定数時間で判定する。

```cpp
auto hull = convex_hull(points);
int location = contains_convex(hull, IntPoint(3, 4));
```

## 例
頂点に重みなどの付随情報がある場合は、元添字を共通に使える。

```cpp
vector<IntPoint> points{ {1, 1}, {0, 0}, {1, 0}, {0, 0} };
vector<int> weights{10, 20, 30, 40};
auto ids = convex_hull_indices(points);
for (int id : ids) {
    auto point = points[id];
    int weight = weights[id];
}
```

この例では `ids` は `{1, 2, 0}`。同じ座標を持つ添字3は選ばない。

## 実装上の補足
返り値は辞書順最小の点から始まる反時計回り順になる。
点数が `0`, `1`, `2` のときは重複を除いた結果をそのまま返す。
`convex_hull_indices` も空・1点・2点・共線の入力を扱い、全点同座標なら `{0}`、共線なら両端の代表添字を返す。
外積は差分を取る前に `__int128` へ変換して計算する。
包含判定は先頭点からの扇形を二分探索し、整数演算だけで分類する。EPS や浮動小数への変換は使わない。
