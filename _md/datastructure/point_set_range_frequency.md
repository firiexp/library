---
title: 点更新・区間頻度
documentation_of: //datastructure/point_set_range_frequency.cpp
---

## 説明
配列の要素を更新し、指定した値が区間内に何個あるかを求める。更新値の事前登録は不要で、直前の答えから次の更新値が決まる場合も使える。

## できること
配列長を $N$ とする。

- `PointSetRangeFrequency<T> rf(a)` : 配列 `a` から構築する。$O(N\log N)$ 時間、$O(N)$ 領域。
- `void set(int p, const T& x)` : `a[p] = x` に更新する。期待 $O(\log N)$。
- `int freq(int l, int r, const T& x) const` : 半開区間 `[l, r)` 内の `x` の個数を返す。空区間や存在しない値なら `0`。期待 $O(\log N)$。
- `const T& get(int p) const` : 現在の `a[p]` を定数参照で返す。$O(1)$。
- `int size() const` : 配列長を返す。$O(1)$。

## 使い方
`T` には `int` や `long long` など、`<` で比較できる型を使う。位置は `0 <= p < N`、区間は `0 <= l <= r <= N` を満たすこと。

```cpp
PointSetRangeFrequency<long long> rf({4, 2, 4});
int count = rf.freq(0, 3, 4);
rf.set(1, 1000000000000LL);
int next = rf.freq(1, 3, 1000000000000LL);
```

頻度だけが必要ならこの構造を使える。区間内の順位・重み和も必要で、更新値を事前登録できる場合は `DynamicWeightedWaveletMatrix` を使う。値の種類が少ない場合は、頻度だけでも後者の方が速いことがある。

## 実装上の補足
`x < y` と `y < x` がどちらも偽になる値を同値として数える。計算量は値の比較・コピーを $O(1)$ とした場合を示す。

`(値, 位置)` を1本の `OrderStatisticTree` に保持する。削除したノードを再利用するため、更新回数によらず領域は $O(N)$。木が退化した場合、更新・クエリは最悪 $O(N)$ になる。
