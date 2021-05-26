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
  bundledCode: "#line 1 \"datastructure/binaryheap.cpp\"\ntemplate<typename T>\nstruct\
    \ binary_heap {\n    ll S;\n    vector<T> Q;\n    heap() : S(0), Q() {};\n\n \
    \   T top() const { return Q.top(); }\n    size_t size() const { return Q.size();\
    \ }\n    void pop() {\n        pop_heap(Q.begin(),Q.end());\n        S -= Q.back();\n\
    \        Q.pop_back();\n    }\n    void emplace(T x) {\n        S += x;\n    \
    \    Q.emplace_back(x);\n        push_heap(Q.begin(),Q.end());\n    }\n    bool\
    \ empty() { return Q.empty(); }\n    ll sum() const { return S; }\n};\n"
  code: "template<typename T>\nstruct binary_heap {\n    ll S;\n    vector<T> Q;\n\
    \    heap() : S(0), Q() {};\n\n    T top() const { return Q.top(); }\n    size_t\
    \ size() const { return Q.size(); }\n    void pop() {\n        pop_heap(Q.begin(),Q.end());\n\
    \        S -= Q.back();\n        Q.pop_back();\n    }\n    void emplace(T x) {\n\
    \        S += x;\n        Q.emplace_back(x);\n        push_heap(Q.begin(),Q.end());\n\
    \    }\n    bool empty() { return Q.empty(); }\n    ll sum() const { return S;\
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binaryheap.cpp
  requiredBy: []
  timestamp: '2021-05-26 21:57:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/binaryheap.cpp
layout: document
redirect_from:
- /library/datastructure/binaryheap.cpp
- /library/datastructure/binaryheap.cpp.html
title: datastructure/binaryheap.cpp
---
