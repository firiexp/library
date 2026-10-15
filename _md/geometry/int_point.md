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

## 使い方
整数凸包・最近点対・最遠点対・ミンコフスキー和には `vector<IntPoint>` を渡す。
座標範囲の制約は各アルゴリズムの説明に従う。

```cpp
IntPoint p{1, 2}, q{3, 4};
IntPoint sum = p + q;
auto [x, y] = sum;
```
