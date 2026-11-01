---
title: 整数座標点
documentation_of: //geometry/int_point.cpp
date: 2026-10-16
category: 幾何
tags: 幾何
---

## 説明
整数幾何で共通に使う2次元の点を表す。

## できること
- `IntPoint(x, y)`：`long long` の座標 `x`, `y` を持つ点を作る。引数なしなら原点
- `p.x`, `p.y`：各座標を取得・変更する
- `p < q`：`x`, `y` の辞書順で比較する
- `p == q`, `p != q`：座標の一致・不一致を返す
- `p + q`, `p - q`, `p += q`, `p -= q`：座標ごとに加減算する。結果の各座標は `long long` に収まるものとする
- `T IntPoint::cross<T = __int128>(IntPoint a, IntPoint b, IntPoint c)`：ベクトル `a -> b` と `a -> c` の外積を、整数型 `T` で計算して返す

## 使い方
整数凸包・最近点対・最遠点対・ミンコフスキー和には `vector<IntPoint>` を渡す。
座標範囲の制約は各アルゴリズムの説明に従う。

```cpp
IntPoint p{1, 2}, q{3, 4};
IntPoint sum = p + q;
auto [x, y] = sum;
```

`cross` の計算型は省略すると `__int128` になり、各座標の絶対値 $10^{18}$ 以下で使える。
`long long` などを指定する場合は、座標・差分・積・外積がその型に収まるものとする。

```cpp
IntPoint a{0, 0}, b{3, 0}, c{0, 4};
long long area2 = IntPoint::cross<long long>(a, b, c);
```
