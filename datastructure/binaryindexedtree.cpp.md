---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: datastructure/fenwick_tree_2d.cpp
    title: "2\u6B21\u5143Fenwick Tree(2D BIT)"
  - icon: ':heavy_check_mark:'
    path: datastructure/point_add_rectangle_sum.cpp
    title: "\u70B9\u52A0\u7B97\u9577\u65B9\u5F62\u548C(Point Add Rectangle Sum)"
  - icon: ':heavy_check_mark:'
    path: datastructure/static_rectangle_sum.cpp
    title: "\u9759\u7684\u9577\u65B9\u5F62\u548C(Static Rectangle Sum)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dsl_2_b.test.cpp
    title: test/aoj_dsl_2_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum.test.cpp
    title: test/yosupo_point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum.test.cpp
    title: test/yosupo_point_add_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
    title: test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_range_inversions_query.test.cpp
    title: test/yosupo_static_range_inversions_query.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_rectangle_sum.test.cpp
    title: test/yosupo_static_rectangle_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Binary Indexed Tree(BIT)
    links: []
  bundledCode: "#line 1 \"datastructure/binaryindexedtree.cpp\"\ntemplate<class T>\n\
    class BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n): bit(n),\
    \ m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    T sum(int k){\n \
    \       T ret = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n\
    \        return ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k\
    \ <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n\
    \        if (x <= 0) return 0;\n        int i = 0;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j\
    \ - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n\
    \ * @brief Binary Indexed Tree(BIT)\n */\n"
  code: "template<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n\n/**\n\
    \ * @brief Binary Indexed Tree(BIT)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binaryindexedtree.cpp
  requiredBy:
  - datastructure/point_add_rectangle_sum.cpp
  - datastructure/fenwick_tree_2d.cpp
  - datastructure/static_rectangle_sum.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_rectangle_sum.test.cpp
  - test/yosupo_point_add_range_sum.test.cpp
  - test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  - test/yosupo_point_add_rectangle_sum_fenwick_tree_2d.test.cpp
  - test/aoj_dsl_2_b.test.cpp
  - test/yosupo_static_range_inversions_query.test.cpp
  - test/yosupo_point_add_rectangle_sum.test.cpp
documentation_of: datastructure/binaryindexedtree.cpp
layout: document
title: Binary Indexed Tree(BIT)
---

## 説明
可換群(逆元が存在する群)について、区間和を $O(\log N)$ で求め、更新を $O(\log N)$ で行う。
可換でなくても、前からの累積 $[0, x)$ だけを扱うなら使える。例として LIS がある。

## できること
- `add(k, x)` : `k` 番目の要素に `x` を加算する
- `sum(k)` : 半開区間 $[0, k)$ の和を求める
- `lower_bound(x)` : `sum(k)` が `x` 以上になる最小の `k` を求める。存在しなければ `N` を返す

## 使い方
`lower_bound` は累積和が単調になる状況で使う。
典型的には各要素が非負のときに使える。
