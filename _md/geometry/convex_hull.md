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

## 実装上の補足
返り値は辞書順最小の点から始まる反時計回り順になる。
点数が `0`, `1`, `2` のときは重複を除いた結果をそのまま返す。
外積は差分を取る前に `__int128` へ変換して計算する。
包含判定は先頭点からの扇形を二分探索し、整数演算だけで分類する。EPS や浮動小数への変換は使わない。
