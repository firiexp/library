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
  bundledCode: "#line 1 \"math/get_prime.cpp\"\nvector<int> get_prime(int n){\n  \
    \  if(n <= 1) return vector<int>();\n    vector<bool> is_prime(n+1, true);\n \
    \   vector<int> prime;\n    is_prime[0] = is_prime[1] = 0;\n    for (int i = 2;\
    \ i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n        for\
    \ (auto &&j : prime){\n            if(i*j > n) break;\n            is_prime[i*j]\
    \ = false;\n            if(i % j == 0) break;\n        }\n    }\n    return prime;\n\
    }\n"
  code: "vector<int> get_prime(int n){\n    if(n <= 1) return vector<int>();\n   \
    \ vector<bool> is_prime(n+1, true);\n    vector<int> prime;\n    is_prime[0] =\
    \ is_prime[1] = 0;\n    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i])\
    \ prime.emplace_back(i);\n        for (auto &&j : prime){\n            if(i*j\
    \ > n) break;\n            is_prime[i*j] = false;\n            if(i % j == 0)\
    \ break;\n        }\n    }\n    return prime;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/get_prime.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/get_prime.cpp
layout: document
redirect_from:
- /library/math/get_prime.cpp
- /library/math/get_prime.cpp.html
title: math/get_prime.cpp
---
