---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: tree/LCA.cpp
    title: tree/LCA.cpp
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: tree/auxtree.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0439.test.cpp
    title: test/aoj0439.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \    }\n};\n"
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
    \    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/sparsetable.cpp
  requiredBy:
  - tree/auxtree.cpp
  - tree/LCA.cpp
  timestamp: '2020-10-13 14:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0439.test.cpp
documentation_of: datastructure/sparsetable.cpp
layout: document
redirect_from:
- /library/datastructure/sparsetable.cpp
- /library/datastructure/sparsetable.cpp.html
title: datastructure/sparsetable.cpp
---
