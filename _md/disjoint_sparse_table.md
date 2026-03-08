## 説明
結合則だけを満たす演算に対する静的区間クエリを処理する。
前計算 `O(N log N)`、クエリ `O(1)`。

## できること
- `DisjointSparseTable<F> dst(v)`
  配列 `v` から構築する
- `void build(v)`
  配列 `v` で再構築する
- `T query(int l, int r)`
  半開区間 `[l, r)` の積を返す。空区間なら `F::e()`

## 使い方
`F` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。
冪等性は不要で、結合則だけあればよい。

```cpp
struct F {
    using T = int;
    static T f(T a, T b) { return min(a, b); }
    static T e() { return 1 << 30; }
};

DisjointSparseTable<F> dst(a);
int x = dst.query(l, r);
```

## 実装上の補足
`query(l, r)` は `l == r` のとき単位元を返す。
通常の sparse table より適用範囲は広いが、冪等演算だけなら `SparseTable` の方が軽い。
