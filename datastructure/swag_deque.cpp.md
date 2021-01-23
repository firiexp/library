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
  bundledCode: "#line 1 \"datastructure/swag_deque.cpp\"\ntemplate<class G>\nclass\
    \ TwoStackDeque {\n    using T = typename G::T;\n    vector<T> l, r, lsum, rsum;\n\
    public:\n    TwoStackDeque() : l(0), r(0), lsum(1, G::e()), rsum(1, G::e()) {}\n\
    \n    void push_front(const T& v){\n        lsum.push_back(G::f(lsum.back(), v));\n\
    \        l.push_back(v);\n    }\n\n    void push_back(const T& v){\n        rsum.push_back(G::f(v,\
    \ rsum.back()));\n        r.push_back(v);\n    }\n\n    void pop_front(){\n  \
    \      if(l.empty()){\n            if(r.empty()) r.pop_back();\n            int\
    \ lsize = (r.size() + 1) / 2, rsize = r.size() - lsize;\n            l.resize(lsize);\
    \ lsum.resize(lsize + 1);\n            for (int i = 0; i < lsize; ++i) l[i] =\
    \ r[lsize - i - 1], lsum[i+1] = G::f(l[i], lsum[i]);\n            for (int i =\
    \ 0; i < rsize; ++i) r[i] = r[i + lsize], rsum[i+1] = G::f(rsum[i], r[i]);\n \
    \           r.resize(rsize); rsum.resize(rsize + 1);\n        }\n        l.pop_back();\
    \ lsum.pop_back();\n    }\n\n    void pop_back(){\n        if(r.empty()){\n  \
    \          if(l.empty()) l.pop_back();\n            int rsize = (l.size() + 1)\
    \ / 2, lsize = l.size() - rsize;\n            r.resize(rsize); rsum.resize(rsize\
    \ + 1);\n            for (int i = 0; i < rsize; ++i) r[i] = l[rsize - i - 1],\
    \ rsum[i+1] = G::f(rsum[i], r[i]);\n            for (int i = 0; i < lsize; ++i)\
    \ l[i] = l[i + rsize], lsum[i+1] = G::f(l[i], lsum[i]);\n            l.resize(lsize);\
    \ lsum.resize(lsize + 1);\n        }\n        r.pop_back(); rsum.pop_back();\n\
    \    }\n\n    T fold(){\n        return G::f(lsum.back(), rsum.back());\n    }\n\
    };\n/*\nstruct Monoid {\n    using T = int;\n    static T f(T a, T b) { return\
    \ a+b; }\n    static T e() { return 0; }\n};\n*/\n"
  code: "template<class G>\nclass TwoStackDeque {\n    using T = typename G::T;\n\
    \    vector<T> l, r, lsum, rsum;\npublic:\n    TwoStackDeque() : l(0), r(0), lsum(1,\
    \ G::e()), rsum(1, G::e()) {}\n\n    void push_front(const T& v){\n        lsum.push_back(G::f(lsum.back(),\
    \ v));\n        l.push_back(v);\n    }\n\n    void push_back(const T& v){\n  \
    \      rsum.push_back(G::f(v, rsum.back()));\n        r.push_back(v);\n    }\n\
    \n    void pop_front(){\n        if(l.empty()){\n            if(r.empty()) r.pop_back();\n\
    \            int lsize = (r.size() + 1) / 2, rsize = r.size() - lsize;\n     \
    \       l.resize(lsize); lsum.resize(lsize + 1);\n            for (int i = 0;\
    \ i < lsize; ++i) l[i] = r[lsize - i - 1], lsum[i+1] = G::f(l[i], lsum[i]);\n\
    \            for (int i = 0; i < rsize; ++i) r[i] = r[i + lsize], rsum[i+1] =\
    \ G::f(rsum[i], r[i]);\n            r.resize(rsize); rsum.resize(rsize + 1);\n\
    \        }\n        l.pop_back(); lsum.pop_back();\n    }\n\n    void pop_back(){\n\
    \        if(r.empty()){\n            if(l.empty()) l.pop_back();\n           \
    \ int rsize = (l.size() + 1) / 2, lsize = l.size() - rsize;\n            r.resize(rsize);\
    \ rsum.resize(rsize + 1);\n            for (int i = 0; i < rsize; ++i) r[i] =\
    \ l[rsize - i - 1], rsum[i+1] = G::f(rsum[i], r[i]);\n            for (int i =\
    \ 0; i < lsize; ++i) l[i] = l[i + rsize], lsum[i+1] = G::f(l[i], lsum[i]);\n \
    \           l.resize(lsize); lsum.resize(lsize + 1);\n        }\n        r.pop_back();\
    \ rsum.pop_back();\n    }\n\n    T fold(){\n        return G::f(lsum.back(), rsum.back());\n\
    \    }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static T f(T a, T b)\
    \ { return a+b; }\n    static T e() { return 0; }\n};\n*/"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/swag_deque.cpp
  requiredBy: []
  timestamp: '2020-10-27 21:25:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/swag_deque.cpp
layout: document
redirect_from:
- /library/datastructure/swag_deque.cpp
- /library/datastructure/swag_deque.cpp.html
title: datastructure/swag_deque.cpp
---
