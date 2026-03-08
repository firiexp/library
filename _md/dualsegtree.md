---
title: 双対セグメント木(Dual Segment Tree)
documentation_of: //datastructure/dualsegtree.cpp
---
## 説明
区間更新・一点取得を扱う双対セグメント木である。
演算は結合則を満たせばよく、各操作は `O(log N)`。

## できること
- `DualSegmentTree<M> seg(n)`
  長さ `n`、初期値がすべて `M::e()` の双対セグメント木を作る
- `void update(int l, int r, T x)`
  半開区間 `[l, r)` に作用 `x` を適用する
- `T operator[](int k)`
  位置 `k` にかかっている作用の合成結果を返す

## 使い方
`M` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。
`f(a, b)` は「先に `a`、後に `b` を適用した合成」を返すようにする。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

DualSegmentTree<Monoid> seg(n);
seg.update(l, r, x);
long long v = seg[p];
```

初期配列 `a` が別にあるときは、`seg[p]` で得た作用を `a[p]` に適用して答えを作る。

## 実装上の補足
この実装は `update(l, r, x)` が半開区間である。
`eval` で単位元判定をするため、`T` には `==` が必要である。
