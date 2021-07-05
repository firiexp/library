---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/get_min_factor.cpp\"\nvector<int> get_min_factor(int\
    \ n) {\n    if(n <= 1) return vector<int>{0, 1};\n    vector<bool> prime(n+1,\
    \ true);\n    vector<int> min_factor(n+1, 0);\n    min_factor[0] = 0, min_factor[1]\
    \ = 1;\n    prime[0] = false; prime[1] = false;\n    for(ll i = 2; i <= n; i++){\n\
    \        if(prime[i]) {\n            min_factor[i] = i;\n            for(ll j\
    \ = i << 1; j <= n; j += i) {\n                prime[j] = false;\n           \
    \     if(min_factor[j] == 0) min_factor[j] = i;\n            }\n        }\n  \
    \  }\n    return min_factor;\n}\n"
  code: "vector<int> get_min_factor(int n) {\n    if(n <= 1) return vector<int>{0,\
    \ 1};\n    vector<bool> prime(n+1, true);\n    vector<int> min_factor(n+1, 0);\n\
    \    min_factor[0] = 0, min_factor[1] = 1;\n    prime[0] = false; prime[1] = false;\n\
    \    for(ll i = 2; i <= n; i++){\n        if(prime[i]) {\n            min_factor[i]\
    \ = i;\n            for(ll j = i << 1; j <= n; j += i) {\n                prime[j]\
    \ = false;\n                if(min_factor[j] == 0) min_factor[j] = i;\n      \
    \      }\n        }\n    }\n    return min_factor;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_min_factor.cpp
  requiredBy:
  - math/powk_all.cpp
  timestamp: '2021-07-05 11:47:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/get_min_factor.cpp
layout: document
redirect_from:
- /library/math/get_min_factor.cpp
- /library/math/get_min_factor.cpp.html
title: math/get_min_factor.cpp
---
