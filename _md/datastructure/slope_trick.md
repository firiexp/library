---
title: Slope Trick
documentation_of: //datastructure/slope_trick.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。
折れ点の追加は $O(\log K)$、平行移動と定数加算は $O(1)$。$K$ は保持する折れ点数とする。

## できること
- `SlopeTrick<T> st`
  関数 `f(x) = 0` で初期化する
- `query()`
  最小値を取る区間 `[lx, rx]` と `min_f` を返す
- `add_all(a)`
  `f(x) += a`
- `add_a_minus_x(a)`
  `f(x) += max(a - x, 0)`
- `add_x_minus_a(a)`
  `f(x) += max(x - a, 0)`
- `add_abs(a)`
  `f(x) += |x - a|`
- `clear_right()`
  `f(x) = min_{y <= x} f(y)` にする
- `clear_left()`
  `f(x) = min_{y >= x} f(y)` にする
- `shift(a, b)`
  `f(x) = min_{x-b <= y <= x-a} f(y)` にする
- `shift(a)`
  `f(x) = f(x - a)` にする
- `eval(x)`
  現在の `f(x)` を返す
- `merge(other)`
  `f(x) += other(x)` を destructive にマージする

## 使い方
```cpp
SlopeTrick<long long> st;
st.add_abs(5);
st.add_x_minus_a(2);
auto q = st.query();
```

## 実装上の補足
左右の折れ点を priority queue で持つ典型実装である。
`merge` は `other` を破壊する。
`eval` は heap から整列列と累積和を遅延構築する。構築に $O(K\log K)$、領域に $O(K)$ を使い、構築後の評価は $O(\log K)$。

64bit以下の整数型では移動前のキーを保持するため、`shift(a)`、`shift(a, b)`、`add_all` の後もキャッシュを再利用する。
累積和・評価座標からオフセットを引いた値・評価中の集計には `__int128` を使う。64bit整数の場合、累積和1要素は16 bytesになる。
既存の更新演算と最終的な返却値が `T` に収まることを前提とし、移動前の累積和や変換座標が `T` に収まる必要はない。

それ以外の型では実座標を保持し、`shift` 後の最初の評価で再構築する。
折れ点の追加・削除、`clear_left`、`clear_right`、`merge` によって変更されたキャッシュも次の評価で再構築する。
