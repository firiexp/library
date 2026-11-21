---
title: Closest Pair
documentation_of: //geometry/closest_pair.cpp
---
## 説明
平面上の整数点集合から、距離が最小の 2 点の元の添字を返す。

## できること
点数を $N$ とする。

- `pair<int, int> closest_pair(const vector<IntPoint>& points)`
  最短距離を持つ 2 点の添字を返す。2点以上が必要。最短対が複数あるときは、そのうちの1組を返す。時間 $O(N\log N)$、作業領域 $O(N)$。

## 使い方
座標には `long long` の全範囲を使える。同じ座標の点が複数あってもよい。

```cpp
vector<IntPoint> points = { {-3, 4}, {5, 2}, {8, -2}, {4, 2} };
auto [i, j] = closest_pair(points);  // 添字 1 と 3（順不同）
```
