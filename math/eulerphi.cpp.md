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
  bundledCode: "#line 1 \"math/eulerphi.cpp\"\nint eulerphi(int x){\n    int phi =\
    \ x, xx = x;\n    for (int i = 2; i * i <= x; ++i) {\n        if (xx % i == 0)\
    \ {\n            phi -= phi / i;\n            while(xx % i == 0) xx /= i;\n  \
    \      }\n    }\n    if(xx > 1) phi -= phi/xx;\n    return phi;\n}\n"
  code: "int eulerphi(int x){\n    int phi = x, xx = x;\n    for (int i = 2; i * i\
    \ <= x; ++i) {\n        if (xx % i == 0) {\n            phi -= phi / i;\n    \
    \        while(xx % i == 0) xx /= i;\n        }\n    }\n    if(xx > 1) phi -=\
    \ phi/xx;\n    return phi;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/eulerphi.cpp
  requiredBy: []
  timestamp: '2021-02-19 21:44:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/eulerphi.cpp
layout: document
redirect_from:
- /library/math/eulerphi.cpp
- /library/math/eulerphi.cpp.html
title: math/eulerphi.cpp
---
