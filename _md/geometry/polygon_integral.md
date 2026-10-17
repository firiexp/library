---
title: 多角形の区間面積と重心
documentation_of: //geometry/polygon_integral.cpp
date: 2026-10-18
category: 幾何
tags: 幾何
---

## 説明
固定した整数凸多角形について、周に沿った頂点列と弦で囲む領域の符号付き面積・重心を求める。
時計回り・反時計回りのどちらも扱う。前処理・保持領域は $O(N)$、各照会は $O(1)$。

## できること
- `PolygonIntegral index(points)`
  `vector<IntPoint>` を入力順のまま保持し、辺の寄与の累積和を作る。入力は変更しない
- `Result query(int u, int v) const`
  `u` から `v` へ入力順に進み、辺 `v -> u` で閉じた領域を返す。`u > v` は末尾を越えて周回する。`u == v` は面積 $0$ の退化領域
- `Result whole() const`
  多角形全体の集計を返す。空列・1点・2点は面積 $0$
- `result.area2`, `result.moment_x`, `result.moment_y`
  正確な符号付き集計 $D, X, Y$ を `__int128` で保持する
- `long double result.area() const`
  符号付き面積 $D/2$ を返す。半整数を切り捨てない
- `optional<pair<long double, long double>> result.centroid() const`
  重心の $(x,y)$ を返す。$D=0$ なら `nullopt`

## 使い方
頂点は周上の順に並べ、末尾に先頭を重複させない。凸性の検査は行わない。
`query` の添字は `0 <= u, v < N` とする。
反時計回りでは面積が正、時計回りでは負となる。

```cpp
vector<IntPoint> points{ {0, 0}, {4, 0}, {4, 2}, {0, 2} };
PolygonIntegral index(points);
auto lower = index.query(0, 2);
auto upper = index.query(2, 0);
auto full = index.whole();
```

`lower` は頂点列 `0, 1, 2` の三角形で、面積 $4$、重心 $(8/3, 2/3)$。
`upper` は頂点列 `2, 3, 0` の三角形で、面積 $4$、重心 $(4/3, 4/3)$。
`full` は面積 $8$、重心 $(2,1)$ となる。`query(0, 0)` とは異なる。
隣接頂点の `query(u, u+1)` は退化するが、逆向きの照会は残りの周回路を使う。

同じ境界を逆順に走査すると $D,X,Y$ はすべて反転し、重心は変わらない。
固定した入力で `query(u,v)` を `query(v,u)` に交換すると補領域を選ぶため、重心も一般には異なる。

## 実装上の補足
辺 $a \to b$ の寄与は次のとおり。

$$
d = a_x b_y - a_y b_x, \qquad
(D,X,Y) = (d, (a_x+b_x)d, (a_y+b_y)d)
$$

周回区間の累積和の差に閉じる弦の寄与を加え、重心を $(X/(3D),Y/(3D))$ で求める。
除算の分母は `3 * (long double)D` とし、整数型内で `3D` を作らない。

座標の積・和は計算前に `__int128` へ変換する。
各辺・弦の寄与、累積和、区間差、周回補正と弦の加算を含め、すべての中間値が符号付き `__int128` に収まることを前提とする。
例えば $N \le 2\times10^5$, $|x|,|y| \le 10^9$ はこの範囲に収まる。
`long long` 座標全域を無条件には保証しない。`area()` と `centroid()` の最終結果には浮動小数点の丸め誤差がある。
