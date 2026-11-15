---
title: 凸多角形の最大内積
documentation_of: //geometry/convex_hull_support.cpp
---

## 説明
固定した整数凸多角形に対し、指定方向との内積が最大になる頂点を求める。
方向を変えながら線形目的関数を最大化したり、射影区間の端点を求めたりする場合に使う。

## できること
凸包の頂点数を $H$ とする。
入力は反時計回りの凸包とし、重複点と辺上の中間点を除く。開始頂点は任意で、末尾に先頭頂点を重ねない。
各座標と方向の各成分は絶対値 $10^{18}$ 以下とする。

- `ConvexHullSupport support(vector<IntPoint> hull)`：凸包を保持し、辺方向の二分探索に必要な前処理を行う。時間・領域ともに $O(H)$
- `optional<pair<__int128, int>> max_dot(IntPoint direction) const`：`{最大内積, 頂点の添字}` を返す。添字は構築時に渡した凸包内の位置で、空の凸包では `nullopt`。$O(\log H)$

最大値を取る頂点が複数ある場合は任意の1点を返す。零方向では内積0と任意の頂点を返す。
1〜2頂点は直接比較する。

## 使い方
点集合から使う場合は `convex_hull<false>(points)` で凸包を作る。

```cpp
vector<IntPoint> points = { {0, 0}, {3, 0}, {3, 2}, {0, 2}};
auto hull = convex_hull(points);
ConvexHullSupport support(hull);
auto [value, index] = *support.max_dot({2, 1}); // 最大内積8、頂点(3, 2)
IntPoint vertex = hull[index];
```

元の点集合の添字が必要な場合は `convex_hull_indices<false>(points)` を使う。
返された添字列 `ids` の順に凸包を組み立てると、結果の `index` に対する元の添字は `ids[index]` になる。

方向 `d` への最小内積は方向 `-d` の最大内積の符号を反転して求められる。

## 実装上の補足
反時計回りの辺方向は偏角順に循環している。構築時に偏角が最小の辺を見つけ、クエリでは方向を90度反時計回りに回した角度を二分探索する。
内積が増加から減少へ切り替わる辺の始点が最大値を取る。
座標差を取る前に `__int128` へ広げ、外積・内積も同じ型で計算する。
