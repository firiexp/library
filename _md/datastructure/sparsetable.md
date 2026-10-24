---
title: Sparse Table
documentation_of: //datastructure/sparsetable.cpp
---
## 説明
結合則と冪等性を満たす演算に対する静的 RMQ/区間クエリを扱う Sparse Table である。

## できること
配列長を $N$、`F::f` を $O(1)$ とする。

- `SparseTable<F> st`
  空の Sparse Table を作る。$O(1)$
- `SparseTable<F> st(v)`
  配列 `v` から前処理済み Sparse Table を作る。時間・領域ともに $O(N\log N)$
- `void build(const vector<T> &v)`
  配列 `v` から前処理する。時間・領域ともに $O(N\log N)$
- `T query(int l, int r)`
  半開区間 `[l, r)` の集約値を返す。`l < r` を前提とする。$O(1)$

## 使い方
`F` に `using T` と `static T f(T, T)` を定義して使う。
`f` は冪等であることを仮定する。

```cpp
struct F {
    using T = int;
    static T f(T a, T b) { return min(a, b); }
};

SparseTable<F> st(a);
int ans = st.query(l, r);
```

## 実装上の補足
`f` が冪等でないと正しい結果にならない。
`table[i][j]` は長さ $2^i$ の区間が配列内に収まる位置だけを構築する。未使用の末尾セルは既定値で保持し、クエリでは参照しない。
