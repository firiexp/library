---
title: Disjoint Sparse Table
documentation_of: //datastructure/disjoint_sparse_table.cpp
---
## 説明
結合則だけを満たす演算に対する静的区間クエリを処理する。

## できること
配列長を $N$、`F` の各演算を $O(1)$ とする。

- `DisjointSparseTable<F> dst(v)`
  配列 `v` から構築する。$O(N \log N)$
- `void build(v)`
  配列 `v` で再構築する。$O(N \log N)$
- `T query(int l, int r)`
  半開区間 `[l, r)` の積を返す。空区間なら `F::e()`。$O(1)$

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
通常の sparse table より適用範囲は広いが、冪等演算だけなら `SparseTable` の方が軽い。
