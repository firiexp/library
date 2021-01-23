---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/weightedunionfind.cpp\"\ntemplate <class T>\n\
    class WeightedUnionFind {\n    vector<int> uni;\n    vector<T> weights;\n    int\
    \ n;\npublic:\n    explicit WeightedUnionFind(int n, T SUM_UNITY = 0) :\n    uni(static_cast<u32>(n),\
    \ -1) , n(n), weights(n,  SUM_UNITY){};\n\n    int root(int a) {\n        if (uni[a]\
    \ < 0) return a;\n        else {\n            int r = root(uni[a]);\n        \
    \    weights[a] += weights[uni[a]];\n            return (uni[a] = r);\n      \
    \  }\n    }\n\n    bool unite(int a, int b, T w) {\n        w += weight(a); w\
    \ -= weight(b);\n        a = root(a);\n        b = root(b);\n        if(a == b)\
    \ return false;\n        if(uni[a] > uni[b]) swap(a, b), w = -w;\n        uni[a]\
    \ += uni[b];\n        uni[b] = a;\n        weights[b] = w;\n        return true;\n\
    \    }\n\n    int size(int a){\n        return -uni[root(a)];\n    }\n\n    T\
    \ weight(T a){\n        root(a);\n        return weights[a];\n    }\n    int diff(int\
    \ x, int y){\n        return weight(y) - weight(x);\n    }\n};\n"
  code: "template <class T>\nclass WeightedUnionFind {\n    vector<int> uni;\n   \
    \ vector<T> weights;\n    int n;\npublic:\n    explicit WeightedUnionFind(int\
    \ n, T SUM_UNITY = 0) :\n    uni(static_cast<u32>(n), -1) , n(n), weights(n, \
    \ SUM_UNITY){};\n\n    int root(int a) {\n        if (uni[a] < 0) return a;\n\
    \        else {\n            int r = root(uni[a]);\n            weights[a] +=\
    \ weights[uni[a]];\n            return (uni[a] = r);\n        }\n    }\n\n   \
    \ bool unite(int a, int b, T w) {\n        w += weight(a); w -= weight(b);\n \
    \       a = root(a);\n        b = root(b);\n        if(a == b) return false;\n\
    \        if(uni[a] > uni[b]) swap(a, b), w = -w;\n        uni[a] += uni[b];\n\
    \        uni[b] = a;\n        weights[b] = w;\n        return true;\n    }\n\n\
    \    int size(int a){\n        return -uni[root(a)];\n    }\n\n    T weight(T\
    \ a){\n        root(a);\n        return weights[a];\n    }\n    int diff(int x,\
    \ int y){\n        return weight(y) - weight(x);\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/weightedunionfind.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/weightedunionfind.cpp
layout: document
redirect_from:
- /library/datastructure/weightedunionfind.cpp
- /library/datastructure/weightedunionfind.cpp.html
title: datastructure/weightedunionfind.cpp
---
