---
title: 点加算長方形和(Point Add Rectangle Sum)
documentation_of: //datastructure/range_query_2d/point_add_rectangle_sum.cpp
---

## 説明
点追加と長方形和クエリをまとめて処理する。
全追加点を先に集めて、座標圧縮済みの 2 次元 BIT をオフライン構築する。

## できること
- `PointAddRectangleSum<T> solver`
  空の solver を作る。$O(1)$
- `void add_point(int x, int y, T w)`
  点 `(x, y)` に重み `w` を追加する操作を積む。償却 $O(1)$
- `void add_query(int l, int d, int r, int u)`
  半開長方形 `[l, r) x [d, u)` の和クエリを積む。償却 $O(1)$
- `vector<T> solve() const`
  各クエリの答えを登録順に返す。最初のクエリより前に追加した点の重みを 2 次元 BIT の初期値に使う。加算の総数を $P$ とすると、構築は $O(P\log P)$、以降の加算とクエリは各 $O(\log^2 P)$。クエリ数を $Q$ として追加領域は $O(P\log P+Q)$
  浮動小数点数の初期重みをまとめて加算すると、登録順に加算した場合と丸めの結果が異なることがある。

## 使い方
初期点も更新点も `add_point` で順に積む。
`solve()` を呼んだ後も、操作を追加して再計算できる。

## 実装上の補足
`FenwickTree2D` で登録座標を重複排除し、全体を $y$ 順に並べて外側 BIT の各ノードに $y$ 座標列を配る。
