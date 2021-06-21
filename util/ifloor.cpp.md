---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yuki1358.test.cpp
    title: test/yuki1358.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/ifloor.cpp\"\ntemplate<class T>T ifloor(T x, T y){\n\
    \    return x/y-(x%y ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class T>inline T iceil(T\
    \ x, T y){\n    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n}\n"
  code: "template<class T>T ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y <\
    \ 0) : 0);\n}\n\ntemplate<class T>inline T iceil(T x, T y){\n    return x/y+(x%y\
    \ ? (x >= 0)^(y < 0) : 0);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: util/ifloor.cpp
  requiredBy: []
  timestamp: '2021-01-23 19:30:17+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yuki1358.test.cpp
documentation_of: util/ifloor.cpp
layout: document
redirect_from:
- /library/util/ifloor.cpp
- /library/util/ifloor.cpp.html
title: util/ifloor.cpp
---
