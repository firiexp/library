---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_staticrmq_disjoint_sparse_table.test.cpp
    title: test/yosupo_staticrmq_disjoint_sparse_table.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Disjoint Sparse Table
    links: []
  bundledCode: "#line 1 \"datastructure/disjoint_sparse_table.cpp\"\ntemplate<class\
    \ F>\nstruct DisjointSparseTable {\n    using T = typename F::T;\n    int n, lg;\n\
    \    vector<vector<T>> table;\n\n    DisjointSparseTable(): n(0), lg(0), table()\
    \ {}\n    explicit DisjointSparseTable(const vector<T> &v) { build(v); }\n\n \
    \   void build(const vector<T> &v) {\n        n = v.size();\n        lg = 0;\n\
    \        while ((1 << lg) < max(1, n)) ++lg;\n        table.assign(lg + 1, vector<T>(n));\n\
    \        if (n == 0) return;\n        table[0] = v;\n        for (int k = 1; k\
    \ <= lg; ++k) table[k] = v;\n        for (int k = 0; k < lg; ++k) {\n        \
    \    int len = 1 << k;\n            for (int mid = len; mid < n; mid += len <<\
    \ 1) {\n                int l = mid - len;\n                int r = min(n, mid\
    \ + len);\n                table[k + 1][mid - 1] = v[mid - 1];\n             \
    \   for (int i = mid - 2; i >= l; --i) {\n                    table[k + 1][i]\
    \ = F::f(v[i], table[k + 1][i + 1]);\n                }\n                table[k\
    \ + 1][mid] = v[mid];\n                for (int i = mid + 1; i < r; ++i) {\n \
    \                   table[k + 1][i] = F::f(table[k + 1][i - 1], v[i]);\n     \
    \           }\n            }\n        }\n    }\n\n    T query(int l, int r) const\
    \ {\n        if (l >= r) return F::e();\n        --r;\n        if (l == r) return\
    \ table[0][l];\n        int k = 31 - __builtin_clz(l ^ r);\n        return F::f(table[k\
    \ + 1][l], table[k + 1][r]);\n    }\n};\n\n/**\n * @brief Disjoint Sparse Table\n\
    \ */\n"
  code: "template<class F>\nstruct DisjointSparseTable {\n    using T = typename F::T;\n\
    \    int n, lg;\n    vector<vector<T>> table;\n\n    DisjointSparseTable(): n(0),\
    \ lg(0), table() {}\n    explicit DisjointSparseTable(const vector<T> &v) { build(v);\
    \ }\n\n    void build(const vector<T> &v) {\n        n = v.size();\n        lg\
    \ = 0;\n        while ((1 << lg) < max(1, n)) ++lg;\n        table.assign(lg +\
    \ 1, vector<T>(n));\n        if (n == 0) return;\n        table[0] = v;\n    \
    \    for (int k = 1; k <= lg; ++k) table[k] = v;\n        for (int k = 0; k <\
    \ lg; ++k) {\n            int len = 1 << k;\n            for (int mid = len; mid\
    \ < n; mid += len << 1) {\n                int l = mid - len;\n              \
    \  int r = min(n, mid + len);\n                table[k + 1][mid - 1] = v[mid -\
    \ 1];\n                for (int i = mid - 2; i >= l; --i) {\n                \
    \    table[k + 1][i] = F::f(v[i], table[k + 1][i + 1]);\n                }\n \
    \               table[k + 1][mid] = v[mid];\n                for (int i = mid\
    \ + 1; i < r; ++i) {\n                    table[k + 1][i] = F::f(table[k + 1][i\
    \ - 1], v[i]);\n                }\n            }\n        }\n    }\n\n    T query(int\
    \ l, int r) const {\n        if (l >= r) return F::e();\n        --r;\n      \
    \  if (l == r) return table[0][l];\n        int k = 31 - __builtin_clz(l ^ r);\n\
    \        return F::f(table[k + 1][l], table[k + 1][r]);\n    }\n};\n\n/**\n *\
    \ @brief Disjoint Sparse Table\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/disjoint_sparse_table.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_staticrmq_disjoint_sparse_table.test.cpp
documentation_of: datastructure/disjoint_sparse_table.cpp
layout: document
title: Disjoint Sparse Table
---
## 説明
結合則だけを満たす演算に対する静的区間クエリを処理する。
前計算 $O(N log N)$、クエリ $O(1)$。

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
