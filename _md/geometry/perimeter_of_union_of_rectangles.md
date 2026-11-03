---
title: 長方形和集合の周長
documentation_of: //geometry/perimeter_of_union_of_rectangles.cpp
date: 2026-11-03
category: 幾何
tags: 幾何, データ構造
---

## 説明
軸に平行な長方形の和集合について、外周と穴の境界を合わせた長さを求める。
重複した辺や、隣り合う長方形の共有辺は数えない。

## できること
登録した長方形の個数を $N$ とする。

- `PerimeterOfUnionOfRectangles<Coord, Length> solver`
  空の長方形集合を作る。座標型と集計型の既定は `long long`。$O(1)$
- `void add_rectangle(Coord l, Coord d, Coord r, Coord u)`
  半開長方形 `[l, r) x [d, u)` を追加する。`l >= r` または `d >= u` なら無視する。償却 $O(1)$
- `Length solve() const`
  和集合の周長を返す。時間 $O(N\log N)$、作業領域 $O(N)$

## 使い方
長方形を `add_rectangle` で登録してから `solve()` を呼ぶ。
座標差と周長は `Length` で計算する。全体のx座標幅・y座標幅を $W,H$ とすると、入力座標と $2N(W+H)$ を表現できる型なら十分である。
周長は各長方形の周長の和以下であり、走査中に加える長さもこの範囲に収まる。

## 実装上の補足
x座標で走査し、圧縮したy区間の被覆長・被覆区間数・両端の被覆状態を区間木に持つ。
隣り合うx座標の間では、被覆区間数の2倍とx座標差の積が水平境界の長さになる。
同じx座標では追加を削除より先に処理し、各イベントによる被覆長の変化量を垂直境界へ加える。
この順序により共有辺を除き、同じx座標で別のy区間へ入れ替わる境界も数えられる。
