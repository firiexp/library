---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/dualsegtree.cpp\"\ntemplate <class M>\nstruct\
    \ DualSegmentTree{\n    using T = typename M::T;\n    int sz, height{};\n    vector<T>\
    \ lazy;\n    explicit DualSegmentTree(int n) {\n        sz = 1; while(sz < n)\
    \ sz <<= 1, height++;\n        lazy.assign(2*sz, M::e());\n    }\n\n    void eval(int\
    \ k){\n        if(lazy[k] == M::e()) return;\n        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0],\
    \ lazy[k]);\n        lazy[(k<<1)|1] = M::f(lazy[(k<<1)|1], lazy[k]);\n       \
    \ lazy[k] = M::e();\n    }\n    void thrust(int k){ for (int i = height; i; --i)\
    \ eval(k>>i); }\n    void update(int a, int b, const T &x){\n        thrust(a\
    \ += sz); thrust(b += sz-1);\n        for (int l = a, r = b+1;l < r; l >>=1, r\
    \ >>= 1) {\n            if(l&1) lazy[l] = M::f(lazy[l], x), l++;\n           \
    \ if(r&1) --r, lazy[r] = M::f(lazy[r], x);\n        }\n    }\n\n    T operator[](int\
    \ k){\n        thrust(k += sz);\n        return lazy[k];\n    }\n};\n\nstruct\
    \ Monoid{\n    using T = ll;\n    static T f(T a, T b) { return a+b; }\n    static\
    \ T e() { return 0; }\n};\n"
  code: "template <class M>\nstruct DualSegmentTree{\n    using T = typename M::T;\n\
    \    int sz, height{};\n    vector<T> lazy;\n    explicit DualSegmentTree(int\
    \ n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        lazy.assign(2*sz,\
    \ M::e());\n    }\n\n    void eval(int k){\n        if(lazy[k] == M::e()) return;\n\
    \        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0], lazy[k]);\n        lazy[(k<<1)|1]\
    \ = M::f(lazy[(k<<1)|1], lazy[k]);\n        lazy[k] = M::e();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void update(int\
    \ a, int b, const T &x){\n        thrust(a += sz); thrust(b += sz-1);\n      \
    \  for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l]\
    \ = M::f(lazy[l], x), l++;\n            if(r&1) --r, lazy[r] = M::f(lazy[r], x);\n\
    \        }\n    }\n\n    T operator[](int k){\n        thrust(k += sz);\n    \
    \    return lazy[k];\n    }\n};\n\nstruct Monoid{\n    using T = ll;\n    static\
    \ T f(T a, T b) { return a+b; }\n    static T e() { return 0; }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dualsegtree.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: datastructure/dualsegtree.cpp
layout: document
redirect_from:
- /library/datastructure/dualsegtree.cpp
- /library/datastructure/dualsegtree.cpp.html
title: datastructure/dualsegtree.cpp
---
