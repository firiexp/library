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
  bundledCode: "#line 1 \"math/mobius_all.cpp\"\nvector<int> mobius_all(int M){\n\
    \    vector<int> mobius(M), isprime(M);\n    for (int i = 0; i < M; ++i) {\n \
    \       mobius[i] = isprime[i] = 1;\n    }\n    for (int i = 2; i < M; ++i) {\n\
    \        if(isprime[i]){\n            for (int j = i; j < M; j += i) {\n     \
    \           mobius[j] = -mobius[j];\n                isprime[j] = 0;\n       \
    \     }\n            isprime[i] = 1;\n            ll x = (ll)i*i;\n          \
    \  if(x <= M){\n                for (int j = x; j < M; j += x) {\n           \
    \         mobius[j] = 0;\n                }\n            }\n        }\n    }\n\
    \    return mobius;\n}\n"
  code: "vector<int> mobius_all(int M){\n    vector<int> mobius(M), isprime(M);\n\
    \    for (int i = 0; i < M; ++i) {\n        mobius[i] = isprime[i] = 1;\n    }\n\
    \    for (int i = 2; i < M; ++i) {\n        if(isprime[i]){\n            for (int\
    \ j = i; j < M; j += i) {\n                mobius[j] = -mobius[j];\n         \
    \       isprime[j] = 0;\n            }\n            isprime[i] = 1;\n        \
    \    ll x = (ll)i*i;\n            if(x <= M){\n                for (int j = x;\
    \ j < M; j += x) {\n                    mobius[j] = 0;\n                }\n  \
    \          }\n        }\n    }\n    return mobius;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/mobius_all.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/mobius_all.cpp
layout: document
redirect_from:
- /library/math/mobius_all.cpp
- /library/math/mobius_all.cpp.html
title: math/mobius_all.cpp
---
