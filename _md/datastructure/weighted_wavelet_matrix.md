---
title: 重み付きWavelet Matrix(Weighted Wavelet Matrix)
documentation_of: //datastructure/weighted_wavelet_matrix.cpp
date: 2026-07-26
category: データ構造
tags: データ構造
---

## 説明
静的配列に対して、区間内の `x` 未満 / 以下の個数と重みの総和を扱う。

## できること
- `WeightedWaveletMatrix<T, U> wm(v, w)`
  値配列 `v` と重み配列 `w` から構築する
- `build_from_index(idx, sorted_vals, w)`
  圧縮済み index 列 `idx` と昇順の値列 `sorted_vals`、重み列 `w` から構築する
- `count_sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数と重み和を返す
- `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の要素数と重み和を返す
- `count_sum_less_index(l, r, xi)`
  区間 $[l, r)$ のうち圧縮 index `xi` 未満の要素数と重み和を返す
- `count_less_index(l, r, xi)`
  区間 $[l, r)$ のうち圧縮 index `xi` 未満の要素数を返す
- `count_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の個数を返す
- `count_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の個数を返す
- `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の重み和を返す
- `sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の重み和を返す
- `range_cursor(l, r)`
  区間 $[l, r)$ の読み取り専用 Cursor を返す。空区間も指定できる
- `split(cur)`
  非葉 Cursor を値の小さい側 `low` と大きい側 `high` に分ける。元の Cursor は変わらない
- `cur.count()`, `cur.sum()`, `cur.info()`
  要素数、重み和、両者を持つ `CountSum` を返す
- `cur.empty()`, `cur.is_leaf()`
  空か、値が確定した葉かを返す
- `cur.value()`
  空でない葉の値を返す

## 使い方
`WeightedWaveletMatrix<T, U> wm(v, w);` を作る。
圧縮済みなら `build_from_index(idx, sorted_vals, w);` でも作れる。
値で区間を絞り、その中にある要素数と重み和を同時に取りたいときに使う。

## 例
2 区間を合わせた `k` 番目（0-indexed）の値と、その値未満の重み和を求める。重なる位置は2回数える。

```cpp
auto a = wm.range_cursor(l1, r1);
auto b = wm.range_cursor(l2, r2);
assert(0 <= k && k < a.count() + b.count());
long long less_sum = 0;
while (!a.is_leaf()) {
    auto x = wm.split(a), y = wm.split(b);
    int low = x.low.count() + y.low.count();
    if (k < low) {
        a = x.low;
        b = y.low;
    } else {
        k -= low;
        less_sum += x.low.sum() + y.low.sum();
        a = x.high;
        b = y.high;
    }
}
auto kth = a.empty() ? b.value() : a.value();
```

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは `count_sum_less_index` を使うと query 側の二分探索を省ける。
- 個数だけが必要なときは `count_less` / `count_less_equal` / `count_less_index` を使うと重み和の読み出しを省ける。
- x86-64 では実行時に対応を確認し、POPCNT / BMI2 を使う。非対応 CPU では通常実装へ切り替わる。
- クエリはすべて静的配列前提。
- 閾値クエリは $O(\log \sigma)$、構築は $O(N \log \sigma)$。
- Cursor の生成・分岐・各アクセサは $O(1)$、1個あたりの領域は $O(1)$。$K$ 区間の同時降下は $O(K\log \sigma)$。$\sigma$ は異なる値の個数で、空配列と1種類だけの場合も扱う。
- Cursor は生成元と組み合わせて使う。生成元の再構築・代入・move・破棄で無効になる。公開された内部配列も Cursor の生存中は変更しない。
- 重みは負でもよい。ただし、重み和に基づく単調な探索は一般にはできない。
