---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/primitive_root.cpp
    title: math/primitive_root.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/pow.cpp\"\ntemplate <class T>\nT pow_ (T x, T n, T\
    \ M){\n    uint64_t u = 1, xx = x;\n    while (n > 0){\n        if (n&1) u = u\
    \ * xx % M;\n        xx = xx * xx % M;\n        n >>= 1;\n    }\n    return static_cast<T>(u);\n\
    };\n"
  code: "template <class T>\nT pow_ (T x, T n, T M){\n    uint64_t u = 1, xx = x;\n\
    \    while (n > 0){\n        if (n&1) u = u * xx % M;\n        xx = xx * xx %\
    \ M;\n        n >>= 1;\n    }\n    return static_cast<T>(u);\n};"
  dependsOn: []
  isVerificationFile: false
  path: math/pow.cpp
  requiredBy:
  - math/primitive_root.cpp
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/pow.cpp
layout: document
redirect_from:
- /library/math/pow.cpp
- /library/math/pow.cpp.html
title: math/pow.cpp
---
