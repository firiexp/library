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
  bundledCode: "#line 1 \"util/kado.cpp\"\nbool IsKadomatsu(int a, int b, int c){\n\
    \    if(a == b || b == c || c == a) return false;\n    return max({a, b, c}) ==\
    \ b || min({a, b, c}) == b;\n}\n"
  code: "bool IsKadomatsu(int a, int b, int c){\n    if(a == b || b == c || c == a)\
    \ return false;\n    return max({a, b, c}) == b || min({a, b, c}) == b;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: util/kado.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: util/kado.cpp
layout: document
redirect_from:
- /library/util/kado.cpp
- /library/util/kado.cpp.html
title: util/kado.cpp
---
