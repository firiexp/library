---
title: Slope Trick
documentation_of: //datastructure/slope_trick.cpp
date: 2026-03-08
category: データ構造
tags: データ構造
---

## 説明
下に凸な区分線形関数を保ちながら、`max(a - x, 0)` や `max(x - a, 0)` の加算、平行移動、片側累積 min を扱う。
各操作は償却 $O(log N)$。

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
`eval` は heap から実値列と prefix sum を遅延構築して使う。
更新直後の最初の `eval` は再構築が入るが、同じ状態への連続 `eval` は $O(\log N)$ で処理できる。
