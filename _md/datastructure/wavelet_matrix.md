---
title: Wavelet Matrix
documentation_of: //datastructure/wavelet_matrix.cpp
date: 2026-07-26
category: データ構造
tags: データ構造
---

## 説明
静的配列に対して、区間内の順序統計量・値の出現回数・前駆/後継検索を扱うデータ構造。

## できること
配列長を $N$、異なる値の個数を $\sigma$ とし、比較を $O(1)$ とする。

- `WaveletMatrix<T> wm(v)` : 配列から構築する。$O(N\log N)$
- `build_from_index(idx, sorted_vals)` : 圧縮済み index 列 `idx` と昇順の値列 `sorted_vals` から構築する。$O(N\log \sigma)$
- `count_less(l, r, x)` : 区間 $[l, r)$ のうち `x` 未満の個数を返す。$O(\log \sigma)$
- `count_less_index(l, r, xi)` : 区間 $[l, r)$ のうち圧縮 index `xi` 未満の個数を返す。$O(\log \sigma)$
- `range_freq(l, r, lower, upper)` : 区間 $[l, r)$ のうち $lower \le a_i < upper$ の個数を返す。$O(\log \sigma)$
- `freq(l, r, x)` : 区間 $[l, r)$ における `x` の出現回数を返す。$O(\log \sigma)$
- `count_equal_index(l, r, xi)` : 区間 $[l, r)$ における圧縮 index `xi` の出現回数を返す。$O(\log \sigma)$
- `top_k_freq(l, r, k)` : 区間 $[l, r)$ で頻度上位 `k` 個の `(頻度, 値)` を返す。同頻度なら値昇順。最悪 $O(\sigma\log \sigma)$
- `kth_smallest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に小さい値を返す。`0 <= k < r-l` を前提とする。$O(\log \sigma)$
- `kth_largest(l, r, k)` : 区間 $[l, r)$ の `k` 番目 (0-indexed) に大きい値を返す。`0 <= k < r-l` を前提とする。$O(\log \sigma)$
- `prev_value(l, r, upper, res)` : 区間 $[l, r)$ にある `upper` 未満の最大値を `res` に返す。存在しない場合 `false`。$O(\log \sigma)$
- `next_value(l, r, lower, res)` : 区間 $[l, r)$ にある `lower` 以上の最小値を `res` に返す。存在しない場合 `false`。$O(\log \sigma)$
- `range_cursor(l, r)` : 区間 $[l, r)$ の読み取り専用 cursor を返す。空区間も指定できる。$O(1)$
- `split(cur)` : 非葉 cursor を値の小さい側 `low` と大きい側 `high` に分ける。$O(1)$
- `cur.count()` / `cur.empty()` : cursor 内の個数 / 空かを返す。$O(1)$
- `cur.is_leaf()` : 値が確定した葉かを返す。$O(1)$
- `cur.value()` : 空でない葉の値を返す。$O(1)$

## 使い方
`WaveletMatrix<T> wm(v);` で配列から構築する。
圧縮済みなら、`idx` の各要素を `sorted_vals` の添字として `build_from_index(idx, sorted_vals)` に渡す。
`sorted_vals` は重複のない昇順の値列とし、区間は `0 <= l <= r <= v.size()` とする。

## 例
2 区間を多重集合として合わせたときの `k` 番目（0-indexed）は、両方の cursor を同じ側へ進めて求める。重なる位置は2回数える。2区間なら $O(\log \sigma)$、一般に $K$ 区間なら $O(K\log \sigma)$ 時間かかる。

```cpp
auto a = wm.range_cursor(l1, r1);
auto b = wm.range_cursor(l2, r2);
assert(0 <= k && k < a.count() + b.count());
while (!a.is_leaf()) {
    auto x = wm.split(a), y = wm.split(b);
    int low = x.low.count() + y.low.count();
    if (k < low) {
        a = x.low;
        b = y.low;
    } else {
        k -= low;
        a = x.high;
        b = y.high;
    }
}
auto answer = a.empty() ? b.value() : a.value();
```

## 実装上の補足
- 値は内部で座標圧縮して扱う。
- 圧縮済みで使うときは query 側も index API を使うと二分探索を省ける。
- 整数値の座標圧縮は値域に必要な桁だけ radix sort する。
- GCC の x86-64 環境では実行時に CPU 機能を判定し、構築に AVX2 / AVX-512、rank に POPCNT / BMI2 を使う。コンパイルオプションの追加は不要で、非対応 CPU では通常実装へ戻る。
- クエリはすべて静的配列前提。
- cursor は生成元の `WaveletMatrix` と組み合わせて使う。生成元の再構築・代入・move・破棄で無効になる。公開された内部配列も cursor の生存中は変更しない。
