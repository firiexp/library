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
  bundledCode: "#line 1 \"math/prime/mobius_mu.cpp\"\nint mobius_mu(ll n) {\n\tint\
    \ res = 0;\n\tfor(ll d = 2; d*d <= n; d++) {\n\t\tif(n % (d*d) == 0) return 0;\n\
    \t\telse if(n % d == 0) n /= d, res++;\n\t}\n\tif(n != 1) res++;\n\treturn res&1\
    \ ? -1 : 1;\n}\n"
  code: "int mobius_mu(ll n) {\n\tint res = 0;\n\tfor(ll d = 2; d*d <= n; d++) {\n\
    \t\tif(n % (d*d) == 0) return 0;\n\t\telse if(n % d == 0) n /= d, res++;\n\t}\n\
    \tif(n != 1) res++;\n\treturn res&1 ? -1 : 1;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/prime/mobius_mu.cpp
  requiredBy: []
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/prime/mobius_mu.cpp
layout: document
redirect_from:
- /library/math/prime/mobius_mu.cpp
- /library/math/prime/mobius_mu.cpp.html
title: math/prime/mobius_mu.cpp
---
