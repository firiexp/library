---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/quickfind.cpp\"\nstruct QuickFind {\n    int\
    \ n;\n    vector<int> roots;\n    vector<vector<int>> v;\n    explicit QuickFind(int\
    \ n) : n(n) {\n        v.resize(n);\n        for (int i = 0; i < n; ++i) v[i].emplace_back(i);\n\
    \        roots.resize(n);\n        iota(roots.begin(),roots.end(), 0);\n    }\n\
    \ \n    int root(int a){ return roots[a]; }\n    size_t size(int a){ return v[a].size();\
    \ }\n    bool unite(int a, int b){\n        if(same(a, b)) return false;\n   \
    \     a = roots[a], b = roots[b];\n        if(size(a) < size(b)) swap(a, b);\n\
    \        for (auto &&i : v[b]) {\n            v[a].emplace_back(i);\n        \
    \    roots[i] = a;\n        }\n        v[b].clear();\n        v[b].shrink_to_fit();\n\
    \        return true;\n    }\n    bool same(int a, int b){ return roots[a] ==\
    \ roots[b]; }\n    const vector<int>& components(int x){ return v[roots[x]];}\n\
    };\n"
  code: "struct QuickFind {\n    int n;\n    vector<int> roots;\n    vector<vector<int>>\
    \ v;\n    explicit QuickFind(int n) : n(n) {\n        v.resize(n);\n        for\
    \ (int i = 0; i < n; ++i) v[i].emplace_back(i);\n        roots.resize(n);\n  \
    \      iota(roots.begin(),roots.end(), 0);\n    }\n \n    int root(int a){ return\
    \ roots[a]; }\n    size_t size(int a){ return v[a].size(); }\n    bool unite(int\
    \ a, int b){\n        if(same(a, b)) return false;\n        a = roots[a], b =\
    \ roots[b];\n        if(size(a) < size(b)) swap(a, b);\n        for (auto &&i\
    \ : v[b]) {\n            v[a].emplace_back(i);\n            roots[i] = a;\n  \
    \      }\n        v[b].clear();\n        v[b].shrink_to_fit();\n        return\
    \ true;\n    }\n    bool same(int a, int b){ return roots[a] == roots[b]; }\n\
    \    const vector<int>& components(int x){ return v[roots[x]];}\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/quickfind.cpp
  requiredBy: []
  timestamp: '2020-10-27 21:25:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/quickfind.cpp
layout: document
redirect_from:
- /library/datastructure/quickfind.cpp
- /library/datastructure/quickfind.cpp.html
title: datastructure/quickfind.cpp
---
