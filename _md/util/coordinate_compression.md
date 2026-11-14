---
title: 座標圧縮と区間変換
documentation_of: //util/coordinate_compression.cpp
date: 2026-11-15
category: util
tags: util
---

## 説明

整数の集合を小さい順に添字へ変換し、添字から元の値を取得する。
元の値で指定した区間を、セグメント木などに渡せる圧縮後の半開区間 `[l, r)` に変換する。
クエリの端点には構築時に含めなかった値も使える。

## できること

入力の要素数を $N$、異なる値の数を $M$ とする。

- `CoordinateCompression<T> cc(vector<T> values)`
  整数の集合から構築する。同じ値には同じ添字を割り当てる。 $O(N)$ 時間。$O(N)$ 領域
- `int size() const`
  異なる値の数 $M$ を返す。$O(1)$
- `int index(const T& x) const`
  登録値 `x` の添字を返す。未登録なら `-1`。$O(\log M)$
- `const T& value(int i) const`
  添字 `i` に対応する元の値を返す。`0 <= i < M` が必要。$O(1)$
- `int lower_bound(const T& x) const`
  `x` 以上の最初の登録値の添字を返す。なければ `M`。$O(\log M)$
- `int upper_bound(const T& x) const`
  `x` より大きい最初の登録値の添字を返す。なければ `M`。$O(\log M)$
- `pair<int, int> range(const T& L, const T& R) const`
  `L <= x < R` を満たす登録値の区間を返す。$O(\log M)$
- `pair<int, int> range_closed(const T& L, const T& R) const`
  `L <= x <= R` を満たす登録値の区間を返す。$O(\log M)$
- `pair<int, int> range_open(const T& L, const T& R) const`
  `L < x < R` を満たす登録値の区間を返す。$O(\log M)$
- `pair<int, int> range_open_closed(const T& L, const T& R) const`
  `L < x <= R` を満たす登録値の区間を返す。$O(\log M)$

区間変換の返り値はいずれも半開区間 `[l, r)` で、`0 <= l <= r <= M` を満たす。
該当する値がない場合や `L > R` の場合は `l == r` となる。

## 使い方

`CoordinateCompression<long long> cc(values);` のように構築する。
`T` には `int` や `long long` など64bit以下の整数型を使う。

構築後は登録値を追加できない。点更新先になり得る値は構築用の配列にすべて含める必要がある。
重複する値の個数や重みは、同じ圧縮添字へ利用側で集約する。

次は、元の値が閉区間 `[15, 40]` に入る要素の個数を求める例。

```cpp
struct Sum {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

vector<long long> values = {40, 10, 20, 20, 100};
CoordinateCompression<long long> cc(values);
vector<long long> count(cc.size());
for (long long x : values) ++count[cc.index(x)];

SegmentTree<Sum> seg(cc.size());
for (int i = 0; i < cc.size(); ++i) seg.set(i, count[i]);
seg.build();

auto [l, r] = cc.range_closed(15, 40); // [1, 3)
long long answer = seg.query(l, r); // 3
int i = cc.index(20); // 1
long long x = cc.value(i); // 20
int missing = cc.index(15); // -1
auto [l2, r2] = cc.range(15, 40); // [1, 2)
long long answer2 = seg.query(l2, r2); // 2
```

`lower_bound` と `upper_bound` が返す `M` は区間の端として使えるが、`value(M)` は呼べない。

## 実装上の補足

8192要素未満は比較ソート、それ以外は16bitずつの radix sort で値を並べ、重複を除く。
添字は二分探索で求める。
区間の左端は含むなら `lower_bound(L)`、含まないなら `upper_bound(L)` で求める。
右端は含むなら `upper_bound(R)`、含まないなら `lower_bound(R)` で求め、左端より小さければ左端にそろえる。
端点に加減算しないため、整数の最小値・最大値も指定できる。
空の配列から構築した場合、`size()` と両方の境界探索は `0`、`index(x)` は `-1`、区間変換は `{0, 0}` を返す。
