---
title: 最遠点対
documentation_of: //geometry/furthest_pair.cpp
---

## 説明
整数点集合または構築済みの凸包から、距離が最大の2点の添字を返す。

## できること
同距離の組が複数ある場合は任意の1組を返す。

- `pair<int, int> furthest_pair(const vector<IntPoint>& points)`
  最遠点対を元の入力内の異なる2つの添字で返す。点数を $N$ として時間 $O(N\log N)$、追加領域 $O(N)$
- `pair<int, int> furthest_pair_convex(const vector<IntPoint>& hull)`
  最遠点対を凸包内の異なる2つの添字で返す。0〜1頂点なら `{-1, -1}`。凸包の頂点数を $H$ として時間 $O(H)$、追加領域 $O(1)$

## 使い方
点列は未整列のまま渡せる。各座標は $|x|, |y| \le 10^{18}$ とする。
重複点や全点が共線の場合も扱う。全点が一致する場合は `{0, 1}` を返す。

```cpp
vector<IntPoint> points = { {1, 2}, {3, 6}, {2, 1}};
auto [i, j] = furthest_pair(points);
```

`furthest_pair_convex` には `convex_hull<false>(points)` で得た凸包を渡す。開始頂点は任意。

元の入力添字が必要な場合は、`convex_hull_indices<false>` の返却列に対応付ける。

```cpp
auto ids = convex_hull_indices<false>(points);
vector<IntPoint> hull;
for (int id : ids) hull.push_back(points[id]);
auto [u, v] = furthest_pair_convex(hull);
int i = ids[u], j = ids[v];
```

## 実装上の補足
点集合用の入口は凸包を構築してから、凸包用の入口と共通の回転カルパーで最遠点対を求める。
構築済みの凸包を渡す場合は、点列のコピー・ソート・凸包の再構築を行わない。
差分を取る前に `__int128` へ変換し、外積・距離二乗を整数で比較する。
この範囲では外積の絶対値・距離二乗は $8\times10^{36}$ 以下となり、符号付き `__int128` に収まる。
