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
- `DynamicWeightedWaveletMatrix<T, U> wm(n)`
  長さ `n` の構築前オブジェクトを作る
- `add_value_candidate(k, x)`
  位置 `k` に代入する可能性がある値 `x` を登録する。構築後には呼べない
- `build(v, w)`
  初期値 `v` と初期重み `w` から構築する。初期値は候補へ自動で追加される
- `bool set_value(k, x)`
  位置 `k` の値を `x` に変更する。`x` が位置 `k` の登録候補になければ変更せず `false`
- `set_weight(k, w)` / `add_weight(k, delta)`
  位置 `k` の重みを変更、または加算する
- `bool set(k, x, w)`
  位置 `k` の値と重みを同時に変更する。`x` が登録候補になければ変更せず `false`
- `get_value(k)` / `get_weight(k)`
  位置 `k` の現在の値または重みを返す
- `count_sum_less(l, r, x)` / `count_sum_less_equal(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満または以下の要素数と重み和を返す
- `count_less(l, r, x)` / `sum_less(l, r, x)`
  区間 $[l, r)$ のうち `x` 未満の要素数または重み和を返す
- `freq(l, r, x)` / `sum_equal(l, r, x)`
  区間 $[l, r)$ にある値 `x` の個数または重み和を返す
- `range_count_sum(l, r, lower, upper)`
  区間 $[l, r)$ かつ $lower \leq a_i < upper$ にある要素数と重み和を返す
- `range_freq(l, r, lower, upper)` / `range_sum(l, r, lower, upper)`
  同じ範囲にある要素数または重み和を返す

## 使い方
入力を先読みし、値変更で現れる `(位置, 値)` を `add_value_candidate` で登録してから `build` する。
クエリにだけ現れる境界値は登録不要。

```cpp
DynamicWeightedWaveletMatrix<int, long long> wm(n);
for (auto [k, x] : updates) wm.add_value_candidate(k, x);
wm.build(values, weights);
```

## 実装上の補足
- 各位置の候補を連続したスロットへ展開し、各位置につき一つのスロットだけを有効にする
- 値変更は旧スロットの無効化と新スロットの有効化で処理する
- $M$ を登録後の候補スロット数、$\sigma$ を候補値の種類数とする
- 構築は $O(M \log M + M \log \sigma)$
- 更新と `less`・値区間クエリは $O(\log \sigma \log M)$
- `freq` と `sum_equal` は $O(\log \sigma + \log M)$
- メモリ使用量は $O(M \log \sigma)$
- `U` は `U()` を零元として加算と減算ができる型を使う
