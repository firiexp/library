---
title: 多角形の格子点数
documentation_of: //geometry/polygon_lattice_points.cpp
---

## 説明
整数座標の単純多角形について、内部と境界上にある格子点の個数を求める。凹多角形と、時計回り・反時計回りの両方を扱う。

## できること

- `LatticePointCount polygon_lattice_points(const vector<IntPoint>& polygon)`
  内部の個数 `interior` と境界上の個数 `boundary` を返す。両方とも `long long`。頂点数を $N$、座標の絶対値の最大値を $C$ として時間 $O(N\log C)$、追加領域 $O(1)$

## 使い方
頂点は周上の順に並べ、末尾に先頭を重複させない。自己交差・穴を含まず、面積が正の多角形を渡す。辺上の中間頂点は残してよい。

```cpp
vector<IntPoint> polygon{ {0, 0}, {4, 0}, {4, 2}, {0, 2} };
auto count = polygon_lattice_points(polygon);
assert(count.interior == 3);
assert(count.boundary == 12);
```

各座標と返却値は `long long` に、全中間値は符号付き `__int128` に収まることを前提とする。

## 実装上の補足
差分と積は計算前に `__int128` へ広げる。境界点数 $B$ は各辺の $\gcd(|\Delta x|,|\Delta y|)$ の和で求める。
符号付き面積の2倍を $D$ とすると、Pick の定理から内部点数は次の式になる。

$$
I = \frac{|D|-B+2}{2}
$$

面積の符号を除いてから計算するため、頂点順の向きによらず同じ個数を返す。
