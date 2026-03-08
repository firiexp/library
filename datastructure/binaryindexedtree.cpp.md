---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: datastructure/point_add_rectangle_sum.cpp
    title: Point Add Rectangle Sum
  - icon: ':x:'
    path: datastructure/static_rectangle_sum.cpp
    title: Static Rectangle Sum
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dsl_2_b.test.cpp
    title: test/aoj_dsl_2_b.test.cpp
  - icon: ':x:'
    path: test/yosupo_many_aplusb_binaryindexedtree.test.cpp
    title: test/yosupo_many_aplusb_binaryindexedtree.test.cpp
  - icon: ':x:'
    path: test/yosupo_point_add_range_sum.test.cpp
    title: test/yosupo_point_add_range_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo_point_add_rectangle_sum.test.cpp
    title: test/yosupo_point_add_rectangle_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo_static_range_inversions_query.test.cpp
    title: test/yosupo_static_range_inversions_query.test.cpp
  - icon: ':x:'
    path: test/yosupo_static_rectangle_sum.test.cpp
    title: test/yosupo_static_rectangle_sum.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
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
  - datastructure/static_rectangle_sum.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_point_add_range_sum.test.cpp
  - test/aoj_dsl_2_b.test.cpp
  - test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  - test/yosupo_point_add_rectangle_sum.test.cpp
  - test/yosupo_many_aplusb_binaryindexedtree.test.cpp
  - test/yosupo_static_rectangle_sum.test.cpp
  - test/yosupo_static_range_inversions_query.test.cpp
documentation_of: datastructure/binaryindexedtree.cpp
layout: document
title: Binary Indexed Tree(BIT)
---
## 説明
可換群(逆元が存在する群)について、区間和を$O(\log N)$で求め、更新を$O(\log N)$で行う。<br>
可換でなくても$[0, x)$について演算した結果だけを求めたいのであれば、使うことができる。(例: LIS)

## 操作
- $\mathrm{add}(k, x)$ : $k$番目の要素に$x$を加算する。
- $\mathrm{sum}(k)$ : 半開区間$[0, k)$の和を求める。
- $\mathrm{lower\_bound}(x)$ : $\mathrm{sum}(k)$が$x$以上になる最小の$k$を求める。存在しなければ$N$を返す。

## 使い方
`lower_bound` は累積和が単調になる状況で使う。
典型的には各要素が非負のときに使える。
