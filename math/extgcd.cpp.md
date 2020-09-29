---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/CRT.cpp
    title: math/CRT.cpp
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/extgcd.cpp\"\ntemplate<typename T>\nT extgcd(T a, T\
    \ b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n\
    \        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a,\
    \ a);\n    }\n    return b;\n}\n \n"
  code: "template<typename T>\nT extgcd(T a, T b, T &x ,T &y){\n    for (T u = y =\
    \ 1, v = x = 0; a; ) {\n        ll q = b/a;\n        swap(x -= q*u, u);\n    \
    \    swap(y -= q*v, v);\n        swap(b -= q*a, a);\n    }\n    return b;\n}\n\
    \ "
  dependsOn: []
  isVerificationFile: false
  path: math/extgcd.cpp
  requiredBy:
  - math/CRT.cpp
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/extgcd.cpp
layout: document
redirect_from:
- /library/math/extgcd.cpp
- /library/math/extgcd.cpp.html
title: math/extgcd.cpp
---
