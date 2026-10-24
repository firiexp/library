---
title: Slope Trick
documentation_of: //datastructure/slope_trick.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。

## できること
保持する折れ点数を $K$ とする。

- `SlopeTrick<T> st`
  関数 `f(x) = 0` で初期化する。$O(1)$
- `query()`
  最小値を取る区間 `[lx, rx]` と最小値 `min_f` を持つ `Query` を返す。区間端が無限の場合は `-INF` または `INF` を返す。$O(1)$
- `add_all(a)`
  `f(x) += a`。$O(1)$
- `add_a_minus_x(a)`
  `f(x) += max(a - x, 0)`。償却 $O(\log K)$
- `add_x_minus_a(a)`
  `f(x) += max(x - a, 0)`。償却 $O(\log K)$
- `add_abs(a)`
  関数に $|x-a|$ を加える。償却 $O(\log K)$
- `clear_right()`
  関数を $f(x)=\min_{y\leq x}f(y)$ に置き換える。$O(K)$
- `clear_left()`
  関数を $f(x)=\min_{y\geq x}f(y)$ に置き換える。$O(K)$
- `shift(a, b)`
  関数を $f(x)=\min_{x-b\leq y\leq x-a}f(y)$ に置き換える。`a <= b` を前提とする。$O(1)$
- `shift(a)`
  `f(x) = f(x - a)` にする。$O(1)$
- `eval(x)`
  現在の `f(x)` を返す。キャッシュ構築時は $O(K\log K)$、構築後は $O(\log K)$
- `merge(other)`
  `f(x) += other(x)` とし、`other` の内容を破壊する。両者の折れ点数の合計を $K$ として $O(K\log K)$

## 使い方
`INF` は `numeric_limits<T>::max() / 4` を表す。
```cpp
SlopeTrick<long long> st;
st.add_abs(5);
st.add_x_minus_a(2);
auto q = st.query();
```

## 実装上の補足
左右の折れ点を priority queue で持つ典型実装である。
`add_abs` は `a` と最小区間の位置関係に応じて折れ点を追加する。最小区間内なら左右に1個ずつ追加するだけでよい。
`eval` は heap の内部配列をコピーしてソートし、整列列と累積和のキャッシュを遅延構築する。追加領域は $O(K)$。

64bit以下の整数型では移動前のキーを保持するため、`shift(a)`、`shift(a, b)`、`add_all` の後もキャッシュを再利用する。
累積和・評価座標からオフセットを引いた値・評価中の集計には `__int128` を使う。64bit整数の場合、累積和1要素は16 bytesになる。
既存の更新演算と最終的な返却値が `T` に収まることを前提とし、移動前の累積和や変換座標が `T` に収まる必要はない。

それ以外の型では実座標を保持し、`shift` 後の最初の評価で再構築する。
折れ点の追加・削除、`clear_left`、`clear_right`、`merge` によって変更されたキャッシュも次の評価で再構築する。
公開メンバーの `L`、`R` を直接変更した場合は、`eval_cache_valid = false` としてから評価する。
