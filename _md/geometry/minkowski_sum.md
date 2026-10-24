---
title: 整数凸多角形のミンコフスキー和
documentation_of: //geometry/minkowski_sum.cpp
date: 2026-10-16
category: 幾何
tags: 幾何
---

## 説明
整数凸多角形 $A, B$ のミンコフスキー和 $A+B = \{a+b \mid a \in A, b \in B\}$ を求める。

## できること
- `vector<IntPoint> minkowski_sum(const vector<IntPoint>& a, const vector<IntPoint>& b)`
  和の凸包を辞書順最小の点から反時計回りで返す。重複点と辺上の中間点は除く。どちらかが空なら空配列。最悪 $O(|A|+|B|)$ 時間、返却領域 $O(|A|+|B|)$、入力と出力を除く追加領域 $O(1)$

## 使い方
各入力は反時計回りの凸包の頂点列とし、重複点・辺上の中間点・末尾の閉点を含めない。開始位置は任意で、`convex_hull` の結果をそのまま渡せる。
1点は点、2点は線分として扱う。
各呼び出しの入力座標は $|x|, |y| \le 10^{18}$ とする。出力座標の絶対値は $2\times10^{18}$ 以下になる。

```cpp
vector<IntPoint> a = convex_hull(points_a);
vector<IntPoint> b = convex_hull(points_b);
auto sum = minkowski_sum(a, b);
```

## 実装上の補足
辺を偏角順に併合し、同方向の平行辺をまとめる。差分を取る前に `__int128` へ変換し、浮動小数点数は使わない。
