---
title: 最小包含円
documentation_of: //geometry/minimum_enclosing_circle.cpp
---

## 説明
整数座標の点集合を含む最小の円と、その円周上にある全入力点を求める。
包含・円周判定は整数演算で行い、EPS を使わない。

## できること
入力点数を $N$ とする。

- `minimum_enclosing_circle(const vector<IntPoint>& points, uint64_t seed = random_device{}())`
  最小包含円を `optional<MinimumEnclosingCircleResult>` で返す。空入力なら `nullopt`。
  座標は $|x|, |y| \le 10^9$ とする。期待 $O(N)$ 時間、最悪 $O(N^3)$ 時間、$O(N)$ 領域。
- `result.center.x`, `result.center.y`, `result.radius`
  中心座標と半径の近似値。型は `long double`。1点または同一点だけなら半径0。
- `result.boundary_indices`
  円周上にある入力点の0-indexedの添字を昇順に並べた列。同じ座標も添字ごとに含む。

## 使い方
```cpp
vector<IntPoint> points{ {0, 0}, {2, 0}, {1, 1} };
auto circle = minimum_enclosing_circle(points);
long double radius = circle->radius;
vector<int> boundary = circle->boundary_indices;
```

再現可能な実行には第2引数で seed を指定する。期待計算量は shuffle の乱数に関するもので、特定の seed に対する最悪時間の保証ではない。

## 実装上の補足
一度 shuffle した順序で randomized incremental 法を適用し、最大3点の支持点を円周上に保つ。
一直線上の支持点は両端の直径円にする。中心と半径だけを最後に浮動小数点数へ変換する。

差の計算から `__int128` を使う。3点円の判定式は、平方距離と三角形の外積の積を3項足し引きする。
座標範囲から平方距離は $8\cdot10^{18}$ 以下、外積の絶対値は $4\cdot10^{18}$ 以下なので、途中の絶対値も $96\cdot10^{36}<2^{127}$ に収まる。
