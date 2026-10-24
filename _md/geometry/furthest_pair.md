---
title: 最遠点対
documentation_of: //geometry/furthest_pair.cpp
---

## 説明
整数点集合から、距離が最大の2点の元の添字を返す。

## できること
点数を $N$ とする。

- `pair<int, int> furthest_pair(const vector<IntPoint>& points)`
  最遠点対の異なる2つの添字を返す。`points.size() >= 2` を前提とする。同距離の組が複数ある場合は任意の1組を返す。時間 $O(N\log N)$、追加領域 $O(N)$

## 使い方
点列は未整列のまま渡せる。各座標は $|x|, |y| \le 10^{18}$ とする。
重複点や全点が共線の場合も扱う。全点が一致する場合は `{0, 1}` を返す。

```cpp
vector<IntPoint> points = { {1, 2}, {3, 6}, {2, 1}};
auto [i, j] = furthest_pair(points);
```

## 実装上の補足
差分を取る前に `__int128` へ変換し、外積・距離二乗を整数で比較する。
この範囲では外積の絶対値・距離二乗は $8\times10^{36}$ 以下となり、符号付き `__int128` に収まる。
