---
title: 凸包(Convex Hull)
documentation_of: //geometry/convex_hull.cpp
date: 2026-03-08
category: 幾何
tags: 幾何
---

## 説明
整数座標点集合の凸包を Andrew's monotone chain で求める。

## できること
入力点数を $N$、凸包の頂点数を $H$ とする。

- `vector<IntPoint> convex_hull<keep_collinear = false>(vector<IntPoint> ps)`
  凸包を辞書順最小点から反時計回りに返す。`keep_collinear = true` なら辺上の入力点も残す。重複座標は一度だけ返す。$O(N\log N)$ 時間・$O(N)$ 追加領域
- `vector<int> convex_hull_indices<keep_collinear = false>(const vector<IntPoint>& points)`
  同じ凸包を元の入力添字で返す。重複座標は最小の添字を選ぶ。$O(N\log N)$ 時間・$O(N)$ 追加領域
- `int contains_convex(const vector<IntPoint>& hull, IntPoint p)`
  凸包の外側なら `0`（OUT）、境界上なら `1`（ON）、内部なら `2`（IN）を返す。$H\ge 3$ で $O(\log H)$ 時間・$O(1)$ 追加領域

## 使い方
点列を `vector<IntPoint>` で渡して使う。
各座標は $|x|, |y| \le 10^{18}$ とする。
`contains_convex` には `convex_hull(points)` が返す、反時計回りで重複・辺上の中間点を含まない凸包を渡す。`keep_collinear = true` の結果はそのまま渡さない。他の幾何 API へ渡す場合も、辺上の中間点を許すか確認する。判定する点も同じ座標範囲とする。
空の凸包は常に OUT、1点なら同一点だけ ON、2点なら閉線分上だけ ON を返す。この場合は定数時間で判定する。

```cpp
auto hull = convex_hull(points);
int location = contains_convex(hull, IntPoint(3, 4));
auto boundary = convex_hull<true>(points);
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
全点共線なら、既定では両端だけ、`keep_collinear = true` なら相異なる全点を辞書順に一度ずつ返す。
`convex_hull_indices` も同じ規則で代表添字を返し、全点同座標なら `{0}` になる。
外積は差分を取る前に `__int128` へ変換して計算する。
包含判定は先頭点からの扇形を二分探索し、整数演算だけで分類する。
