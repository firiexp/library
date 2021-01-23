---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/pow.cpp
    title: math/pow.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/pow.cpp\"\ntemplate <class T>\nT pow_ (T x, T n, T\
    \ M){\n    uint64_t u = 1, xx = x;\n    while (n > 0){\n        if (n&1) u = u\
    \ * xx % M;\n        xx = xx * xx % M;\n        n >>= 1;\n    }\n    return static_cast<T>(u);\n\
    };\n#line 2 \"math/primitive_root.cpp\"\nint primitive_root(int m) {\n    if (m\
    \ == 2) return 1;\n    int divs[20] = {2};\n    int cnt = 1;\n    int x = (m-1)/2;\n\
    \    while (x%2 == 0) x /= 2;\n    for (ll i = 3; i*i <= x; i += 2) {\n      \
    \  if (x%i == 0) {\n            divs[cnt++] = i;\n            while (x%i == 0)\
    \ x /= i;\n        }\n    }\n    if (x > 1) divs[cnt++] = x;\n    for (int g =\
    \ 2;; g++) {\n        bool ok = true;\n        for (int i = 0; i < cnt && ok;\
    \ i++) {\n            ok |= pow_(g, (m-1)/divs[i], m) != 1;\n        }\n     \
    \   if (ok) return g;\n    }\n}\n"
  code: "#include \"pow.cpp\"\nint primitive_root(int m) {\n    if (m == 2) return\
    \ 1;\n    int divs[20] = {2};\n    int cnt = 1;\n    int x = (m-1)/2;\n    while\
    \ (x%2 == 0) x /= 2;\n    for (ll i = 3; i*i <= x; i += 2) {\n        if (x%i\
    \ == 0) {\n            divs[cnt++] = i;\n            while (x%i == 0) x /= i;\n\
    \        }\n    }\n    if (x > 1) divs[cnt++] = x;\n    for (int g = 2;; g++)\
    \ {\n        bool ok = true;\n        for (int i = 0; i < cnt && ok; i++) {\n\
    \            ok |= pow_(g, (m-1)/divs[i], m) != 1;\n        }\n        if (ok)\
    \ return g;\n    }\n}"
  dependsOn:
  - math/pow.cpp
  isVerificationFile: false
  path: math/primitive_root.cpp
  requiredBy: []
  timestamp: '2020-09-09 00:00:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/primitive_root.cpp
layout: document
redirect_from:
- /library/math/primitive_root.cpp
- /library/math/primitive_root.cpp.html
title: math/primitive_root.cpp
---
