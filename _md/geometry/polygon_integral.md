---
title: 多角形の区間面積と重心
documentation_of: //geometry/polygon_integral.cpp
date: 2026-10-18
category: 幾何
tags: 幾何
---

## 説明
与えられた整数凸多角形について、周に沿った頂点列と弦で囲む領域の面積・重心を整数演算で求める。
面積は符号付き面積の2倍、重心は分数で返すため、半整数の面積や整数でない重心も誤差なく扱える。
時計回り・反時計回りのどちらも扱う。

## できること
頂点数を $N$ とする。

- `PolygonIntegral index(points)`
  `vector<IntPoint>` から面積・重心の計算に使う累積和を作る。時間・領域は $O(N)$
- `Result query(int u, int v) const`
  `u` から `v` へ入力順に進み、辺 `v -> u` で閉じた領域を返す。`u > v` は末尾を越えて周回する。`u == v` は面積 $0$ の退化領域。$O(1)$
- `Result whole() const`
  多角形全体の集計を返す。空列・1点・2点は面積 $0$。$O(1)$
- `__int128 result.area2() const`
  符号付き面積の2倍を返す。面積の大小比較や加算を整数のまま行える。反時計回りなら正、時計回りなら負。$O(1)$
- `optional<RationalPoint> result.centroid() const`
  重心を正確な分数で返す。面積が $0$ なら `nullopt`。$O(1)$
- `point.x_num`, `point.y_num`, `point.den`
  `RationalPoint` の `__int128` の分子と共通分母。座標は $(\mathrm{x\_num}/\mathrm{den},\mathrm{y\_num}/\mathrm{den})$ で、`den > 0`。約分はしない

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
assert(lower.area2() == 8);
assert(full.area2() == 16);
auto center = full.centroid();
if (center) {
    __int128 k = 2;
    bool x_equals_k = center->x_num == k * center->den;
    bool x_is_integer = center->x_num % center->den == 0;
}
```

`lower` は頂点列 `0, 1, 2` の三角形で、面積 $4$、重心 $(8/3, 2/3)$。
重心の返却値は `x_num = 64, y_num = 16, den = 24` となる。
`upper` は頂点列 `2, 3, 0` の三角形で、面積 $4$、重心 $(4/3, 4/3)$。
`full` は面積 $8$、重心 $(2,1)$ となり、例の2つの判定はいずれも `true`。`query(0, 0)` とは異なる。
隣接頂点の `query(u, u+1)` は退化するが、逆向きのクエリは残りの周回路を使う。

小数が必要な場合だけ、`(long double)result.area2() / 2` や `(long double)center->x_num / center->den` へ変換する。
整数除算では小数部分が失われる。分数の比較で交差積を使う場合は、その積も整数型に収まる必要がある。

同じ境界を逆順に走査すると `area2()` の符号が反転し、重心の分子・分母は変わらない。
同じ入力に対して `query(u,v)` を `query(v,u)` に交換すると補領域を選ぶため、重心も一般には異なる。

## 実装上の補足
辺 $a \to b$ の寄与は次のとおり。

$$
d = a_x b_y - a_y b_x, \qquad
(D,X,Y) = (d, (a_x+b_x)d, (a_y+b_y)d)
$$

内部では $D$ を面積の2倍、$X,Y$ を重心の分子として累積する。
周回区間の累積和の差に閉じる弦の寄与を加え、重心を $(X/(3D),Y/(3D))$ で求める。
`centroid()` は $D>0$ なら $(X,Y,3D)$、$D<0$ なら $(-X,-Y,-3D)$ を返し、分母を正にする。

座標の積・和は計算前に `__int128` へ変換する。
各辺・弦の寄与、累積和、区間差、周回補正と弦の加算を含め、すべての中間値が符号付き `__int128` に収まることを前提とする。
`centroid()` を呼ぶ場合は、分母 $3|D|$ と符号を整えた分子も符号付き `__int128` に収まることを追加の前提とする。
例えば $N \le 2\times10^5$, $|x|,|y| \le 10^9$ はこの範囲に収まる。
