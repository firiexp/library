---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/LCA.cpp
    title: "\u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)"
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: "\u88DC\u52A9\u6728(Aux Tree)"
  - icon: ':heavy_check_mark:'
    path: tree/virtual_tree_helper.cpp
    title: virtual_tree_helper
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0439.test.cpp
    title: test/aoj0439.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0439_virtual_tree_helper.test.cpp
    title: test/aoj0439_virtual_tree_helper.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_lca.test.cpp
    title: test/yosupo_lca.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_staticrmq_sparsetable.test.cpp
    title: test/yosupo_staticrmq_sparsetable.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Sparse Table
    links: []
  bundledCode: "#line 1 \"datastructure/sparsetable.cpp\"\ntemplate <class F>\nstruct\
    \ SparseTable {\n    using T = typename F::T;\n    vector<vector<T>> table;\n\
    \    vector<int> u;\n    SparseTable() = default;\n    explicit SparseTable(const\
    \ vector<T> &v){ build(v); }\n \n    void build(const vector<T> &v){\n       \
    \ int n = v.size(), m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m,\
    \ vector<T>(n));\n        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i)\
    \ {\n            u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n;\
    \ ++i) {\n            table[0][i] = v[i];\n        }\n        for (int i = 1;\
    \ i < m; ++i) {\n            int x = (1<<(i-1));\n            for (int j = 0;\
    \ j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x,\
    \ n-1)]);\n            }\n        }\n    }\n \n    T query(int a, int b){\n  \
    \      int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n"
  code: "template <class F>\nstruct SparseTable {\n    using T = typename F::T;\n\
    \    vector<vector<T>> table;\n    vector<int> u;\n    SparseTable() = default;\n\
    \    explicit SparseTable(const vector<T> &v){ build(v); }\n \n    void build(const\
    \ vector<T> &v){\n        int n = v.size(), m = 1;\n        while((1<<m) <= n)\
    \ m++;\n        table.assign(m, vector<T>(n));\n        u.assign(n+1, 0);\n  \
    \      for (int i = 2; i <= n; ++i) {\n            u[i] = u[i>>1] + 1;\n     \
    \   }\n        for (int i = 0; i < n; ++i) {\n            table[0][i] = v[i];\n\
    \        }\n        for (int i = 1; i < m; ++i) {\n            int x = (1<<(i-1));\n\
    \            for (int j = 0; j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j],\
    \ table[i-1][min(j+x, n-1)]);\n            }\n        }\n    }\n \n    T query(int\
    \ a, int b){\n        int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/sparsetable.cpp
  requiredBy:
  - tree/auxtree.cpp
  - tree/LCA.cpp
  - tree/virtual_tree_helper.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0439.test.cpp
  - test/aoj0439_virtual_tree_helper.test.cpp
  - test/yosupo_staticrmq_sparsetable.test.cpp
  - test/yosupo_lca.test.cpp
documentation_of: datastructure/sparsetable.cpp
layout: document
title: Sparse Table
---
## 説明
idempotent な演算に対する静的 RMQ/区間クエリを扱う Sparse Table である。
前処理 $O(N log N)$、クエリ $O(1)$。

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
