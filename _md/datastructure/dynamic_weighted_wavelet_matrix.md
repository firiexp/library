---
title: 動的重み付きWavelet Matrix(Dynamic Weighted Wavelet Matrix)
documentation_of: //datastructure/dynamic_weighted_wavelet_matrix.cpp
date: 2026-07-25
category: データ構造
tags: データ構造
---

## 説明
固定長配列に対して、点ごとの値・重みの変更と、位置区間・値区間に含まれる要素数と重み和を扱う。
値の更新候補を構築前に登録し、候補ごとの有効状態を動的に管理する。

## できること
$N$ は配列長、$M$ は初期値を含む候補の登録数、$\sigma$ は候補値の種類数とする。
各位置の相異なる候補値が一つだけの場合を「値固定」と呼ぶ。

- `DynamicWeightedWaveletMatrix<T, U> wm(n)`
  長さ `n` の構築前オブジェクトを作る。$O(1)$
- `add_value_candidate(k, x)`
  位置 `k` に代入する可能性がある値 `x` を登録する。構築後には呼べない。償却 $O(1)$
- `build(v, w)`
  初期値 `v` と初期重み `w` から構築する。初期値は候補へ自動で追加される。時間 $O(M \log M + M \log \sigma)$、領域 $O(M \log \sigma)$
- `bool set_value(k, x)`
  位置 `k` の値を `x` に変更する。登録候補になければ変更せず `false`。$O(\log \sigma \log M)$
- `set_weight(k, w)`
  位置 `k` の重みを `w` に変更する。$O(\log \sigma \log M)$
- `add_weight(k, delta)`
  位置 `k` の重みに `delta` を加算する。$O(\log \sigma \log M)$
- `bool set(k, x, w)`
  位置 `k` の値と重みを変更する。`x` が登録候補になければ変更せず `false`。$O(\log \sigma \log M)$
- `get_value(k)`
  位置 `k` の現在の値を返す。$O(1)$
- `get_weight(k)`
  位置 `k` の現在の重みを返す。$O(1)$
- `range_cursor(l, r)`
  区間 $[l, r)$ に対応する二分木の根を `Cursor` として返す。$O(\log N)$
- `split(cur)`
  葉でない `Cursor` を値の小さい子 `low` と大きい子 `high` に分ける。$O(\log M)$
- `Cursor::is_leaf()`
  葉なら `true`。$O(1)$
- `Cursor::empty()`
  含まれる要素がなければ `true`。$O(1)$
- `Cursor::count()`
  含まれる要素数を返す。$O(1)$
- `Cursor::sum()`
  含まれる要素の重み和を返す。$O(1)$
- `Cursor::info()`
  要素数と重み和を `CountSum` として返す。$O(1)$
- `Cursor::value()`
  空でない葉が表す値を返す。葉でない場合や空の場合は呼べない。$O(1)$
- `count_sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数と重み和を返す。$O(\log \sigma \log M)$
- `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の要素数と重み和を返す。$O(\log \sigma \log M)$
- `count_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数を返す。$O(\log \sigma \log M)$、値固定時は $O(\log \sigma)$
- `count_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の要素数を返す。$O(\log \sigma \log M)$、値固定時は $O(\log \sigma)$
- `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の重み和を返す。$O(\log \sigma \log M)$
- `sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 以下の重み和を返す。$O(\log \sigma \log M)$
- `T kth_smallest(l, r, k) const`
  区間 $[l, r)$ の小さい方から 0-indexed で `k` 番目の値を返す。`0 <= k < r - l`。時間 $O(\log \sigma \log M)$、値固定時は $O(\log \sigma)$。追加領域 $O(1)$
- `T kth_largest(l, r, k) const`
  区間 $[l, r)$ の大きい方から 0-indexed で `k` 番目の値を返す。`0 <= k < r - l`。時間 $O(\log \sigma \log M)$、値固定時は $O(\log \sigma)$。追加領域 $O(1)$
- `sum_k_smallest(l, r, k)`
  区間 $[l, r)$ の小さい方から `k` 個の重み和を返す。`0 <= k <= r - l` とし、同値なら位置が小さい順に扱う。$O(\log \sigma \log M)$
- `count_sum_equal(l, r, x)`
  区間 $[l, r)$ にある値 `x` の個数と重み和を返す。$O(\log \sigma + \log M)$
- `freq(l, r, x)`
  区間 $[l, r)$ にある値 `x` の個数を返す。$O(\log \sigma + \log M)$、値固定時は $O(\log \sigma)$
- `sum_equal(l, r, x)`
  区間 $[l, r)$ にある値 `x` の重み和を返す。$O(\log \sigma + \log M)$
- `range_count_sum(l, r, lower, upper)`
  区間 $[l, r)$ かつ $lower \leq a_i < upper$ にある要素数と重み和を返す。$O(\log \sigma \log M)$
- `range_freq(l, r, lower, upper)`
  区間 $[l, r)$ かつ $lower \leq a_i < upper$ にある要素数を返す。$O(\log \sigma \log M)$、値固定時は $O(\log \sigma)$
- `range_sum(l, r, lower, upper)`
  区間 $[l, r)$ かつ $lower \leq a_i < upper$ にある重み和を返す。$O(\log \sigma \log M)$

## 使い方
入力を先読みし、値変更で現れる `(位置, 値)` を `add_value_candidate` で登録してから `build` する。
クエリにだけ現れる境界値は登録不要。

```cpp
DynamicWeightedWaveletMatrix<int, long long> wm(n);
for (auto [k, x] : updates) wm.add_value_candidate(k, x);
wm.build(values, weights);
```

`Cursor` を使うと、必要な側だけへ値の二分木を降りられる。

```cpp
auto cur = wm.range_cursor(l, r);
assert(!cur.empty());
while (!cur.is_leaf()) {
    auto children = wm.split(cur);
    cur = children.high.empty() ? children.low : children.high;
}
auto maximum = cur.value();
```

更新を行うと、それ以前に作った `Cursor` は無効になる。

## 実装上の補足
- 各位置の候補を連続したスロットへ展開し、各位置につき一つのスロットだけを有効にする
- 値変更は旧スロットの無効化と新スロットの有効化で処理する
- `kth_smallest` と `kth_largest` は重複を出現個数で数え、重みには依存しない
- `U` は `U()` を零元として加算と減算ができる型を使う
