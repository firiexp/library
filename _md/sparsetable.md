## 説明
idempotent な演算に対する静的 RMQ/区間クエリを扱う Sparse Table である。
前処理 `O(N log N)`、クエリ `O(1)`。

## できること
- `SparseTable<F> st`
  空の Sparse Table を作る
- `SparseTable<F> st(v)`
  配列 `v` から前処理済み Sparse Table を作る
- `void build(const vector<T> &v)`
  配列 `v` から前処理する
- `T query(int l, int r)`
  半開区間 `[l, r)` の値を返す

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
`query(l, r)` は `l < r` を仮定する。
`f` が冪等でないと正しい結果にならない。
