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
  bundledCode: "#line 1 \"math/eulerphi_all.cpp\"\nvector<int> eulerphi_all(int M){\n\
    \    vector<int> phi(M);\n    vector<bool> isprime(M);\n    for (int i = 0; i\
    \ < M; ++i) {\n        mobius[i] = isprime[i] = 1;\n    }\n    for (int i = 2;\
    \ i < M; ++i) {\n        if(isprime[i]){\n            for (int j = i; j < M; j\
    \ += i) {\n                phi[j] -= phi[j]/i;\n                isprime[j] = 0;\n\
    \            }\n            isprime[i] = 1;\n        }\n    }\n    return phi;\n\
    }\n"
  code: "vector<int> eulerphi_all(int M){\n    vector<int> phi(M);\n    vector<bool>\
    \ isprime(M);\n    for (int i = 0; i < M; ++i) {\n        mobius[i] = isprime[i]\
    \ = 1;\n    }\n    for (int i = 2; i < M; ++i) {\n        if(isprime[i]){\n  \
    \          for (int j = i; j < M; j += i) {\n                phi[j] -= phi[j]/i;\n\
    \                isprime[j] = 0;\n            }\n            isprime[i] = 1;\n\
    \        }\n    }\n    return phi;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/eulerphi_all.cpp
  requiredBy: []
  timestamp: '2021-06-22 23:34:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/eulerphi_all.cpp
layout: document
redirect_from:
- /library/math/eulerphi_all.cpp
- /library/math/eulerphi_all.cpp.html
title: math/eulerphi_all.cpp
---
