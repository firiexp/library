---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_dsl_2_b.test.cpp
    title: test/aoj_dsl_2_b.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum.test.cpp
    title: test/yosupo_point_add_range_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/binaryindexedtree.cpp\"\ntemplate<class T>\n\
    class BIT {\n    vector<T> bit;\n    int n, m;\npublic:\n    BIT(int n): n(n),\
    \ bit(n){\n        m = 1;\n        while(m < n) m <<= 1;\n    }\n\n    T sum(int\
    \ k){\n        T ret = 0;\n        for (; k > 0; k -= (k & -k)) ret += bit[k-1];\n\
    \        return ret;\n    }\n\n    void add(int k, T x){\n        for (k++; k\
    \ <= bit.size(); k  += (k & -k)) bit[k-1] += x;\n    }\n\n    T lower_bound(T\
    \ x){\n        int i = -1;\n        for (int j = m; j; j >>= 1) {\n          \
    \  if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];\n        }\n       \
    \ return i;\n    }\n};\n"
  code: "template<class T>\nclass BIT {\n    vector<T> bit;\n    int n, m;\npublic:\n\
    \    BIT(int n): n(n), bit(n){\n        m = 1;\n        while(m < n) m <<= 1;\n\
    \    }\n\n    T sum(int k){\n        T ret = 0;\n        for (; k > 0; k -= (k\
    \ & -k)) ret += bit[k-1];\n        return ret;\n    }\n\n    void add(int k, T\
    \ x){\n        for (k++; k <= bit.size(); k  += (k & -k)) bit[k-1] += x;\n   \
    \ }\n\n    T lower_bound(T x){\n        int i = -1;\n        for (int j = m; j;\
    \ j >>= 1) {\n            if(i+j < bit.size() && bit[i+j] < x) x -= bit[i += j];\n\
    \        }\n        return i;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binaryindexedtree.cpp
  requiredBy: []
  timestamp: '2020-09-09 23:52:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_add_range_sum.test.cpp
  - test/aoj_dsl_2_b.test.cpp
documentation_of: datastructure/binaryindexedtree.cpp
layout: document
redirect_from:
- /library/datastructure/binaryindexedtree.cpp
- /library/datastructure/binaryindexedtree.cpp.html
title: datastructure/binaryindexedtree.cpp
---
