---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/pell_equation.cpp
    title: math/pell_equation.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/isqrt.cpp\"\nu64 Isqrt(u64 const &x){\n    u64 ret\
    \ = (u64)sqrtl(x);\n    while(ret > 0 && ret*ret > x) --ret;\n    while(x - ret*ret\
    \ > 2*ret) ++ret;\n    return ret;\n}\n"
  code: "u64 Isqrt(u64 const &x){\n    u64 ret = (u64)sqrtl(x);\n    while(ret > 0\
    \ && ret*ret > x) --ret;\n    while(x - ret*ret > 2*ret) ++ret;\n    return ret;\n\
    }"
  dependsOn: []
  isVerificationFile: false
  path: math/isqrt.cpp
  requiredBy:
  - math/pell_equation.cpp
  timestamp: '2021-03-10 13:23:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/isqrt.cpp
layout: document
redirect_from:
- /library/math/isqrt.cpp
- /library/math/isqrt.cpp.html
title: math/isqrt.cpp
---
