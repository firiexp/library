---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: datastructure/point_add_rectangle_sum.cpp
    title: datastructure/point_add_rectangle_sum.cpp
  - icon: ':heavy_check_mark:'
    path: datastructure/static_rectangle_sum.cpp
    title: datastructure/static_rectangle_sum.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dsl_2_b.test.cpp
    title: test/aoj_dsl_2_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_binaryindexedtree.test.cpp
    title: test/yosupo_many_aplusb_binaryindexedtree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum.test.cpp
    title: test/yosupo_point_add_range_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_rectangle_sum.test.cpp
    title: test/yosupo_point_add_rectangle_sum.test.cpp
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
    links: []
  bundledCode: "#line 1 \"datastructure/binaryindexedtree.cpp\"\ntemplate<class T>\n\
    class BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n    BIT(int n): bit(n),\
    \ m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\n    T sum(int k){\n \
    \       T ret = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k - 1];\n\
    \        return ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k\
    \ <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T x) {\n\
    \        if (x <= 0) return 0;\n        int i = 0;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i + j\
    \ - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n"
  code: "template<class T>\nclass BIT {\n    vector<T> bit;\n    int m, n;\npublic:\n\
    \    BIT(int n): bit(n), m(1), n(n) {\n        while (m < n) m <<= 1;\n    }\n\
    \n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k))\
    \ ret += bit[k - 1];\n        return ret;\n    }\n\n    void add(int k, T x){\n\
    \        for (k++; k <= n; k += (k & -k)) bit[k - 1] += x;\n    }\n\n    int lower_bound(T\
    \ x) {\n        if (x <= 0) return 0;\n        int i = 0;\n        for (int j\
    \ = m; j; j >>= 1) {\n            if (i + j <= n && bit[i + j - 1] < x) x -= bit[i\
    \ + j - 1], i += j;\n        }\n        return min(i + 1, n);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binaryindexedtree.cpp
  requiredBy:
  - datastructure/point_add_rectangle_sum.cpp
  - datastructure/static_rectangle_sum.cpp
  timestamp: '2026-03-08 18:50:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
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
redirect_from:
- /library/datastructure/binaryindexedtree.cpp
- /library/datastructure/binaryindexedtree.cpp.html
title: datastructure/binaryindexedtree.cpp
---
