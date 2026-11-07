---
title: 整数多角形の包含判定
documentation_of: //geometry/polygon_contains.cpp
---

## 説明
整数座標の単純多角形に対して、点が外側・境界上・内部のどこにあるかを整数演算で判定する。凹多角形と、時計回り・反時計回りの両方を扱う。

## できること

- `int contains_polygon(const vector<IntPoint>& polygon, IntPoint p)`
  外側なら `0`（OUT）、境界上なら `1`（ON）、内部なら `2`（IN）を返す。頂点数を $N$ として時間 $O(N)$、追加領域 $O(1)$

## 使い方
頂点は周上の順に並べ、末尾に先頭を重複させない。自己交差・穴を含まない多角形を渡す。辺上の中間頂点は残してよい。
多角形と判定点の各座標は $|x|,|y|\le 10^{18}$ とする。

空列は常に OUT、1点なら同一点だけ ON、2点なら閉線分上だけ ON を返す。
分類値は `contains_convex` と共通である。凸包への多数の問い合わせには、$O(\log N)$ で判定する `contains_convex` を使える。

```cpp
vector<IntPoint> polygon{ {0, 0}, {4, 0}, {4, 1}, {1, 1}, {1, 4}, {0, 4} };
int boundary = contains_polygon(polygon, IntPoint(2, 0));
int outside = contains_polygon(polygon, IntPoint(2, 2));
```

この例では `boundary == 1`、`outside == 0` となる。

## 実装上の補足
各辺上の点を先に判定し、右向きの半直線が辺を横切る回数の偶奇を調べる。端点の高さを半開区間として扱い、頂点を通る交差の重複を防ぐ。
差分を取る前に `__int128` へ変換し、外積と座標比較だけを使う。除算や浮動小数点の誤差は生じない。
