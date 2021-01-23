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
  bundledCode: "#line 1 \"math/primefactor.cpp\"\nvector<int> get_prime(int n){\n\
    \    if(n <= 1) return vector<int>();\n    vector<bool> is_prime(n+1, true);\n\
    \    vector<int> prime;\n    is_prime[0] = is_prime[1] = 0;\n    for (int i =\
    \ 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n        for\
    \ (auto &&j : prime){\n            if(i*j > n) break;\n            is_prime[i*j]\
    \ = false;\n            if(i % j == 0) break;\n        }\n    }\n    return prime;\n\
    }\nconst auto primes = get_prime(65535);\n\ntemplate<class T>\nvector<T> prime_factor(T\
    \ n){\n    vector<T> res;\n    for (auto &&i : primes) {\n        while (n % i\
    \ == 0){\n            res.emplace_back(i);\n            n /= i;\n        }\n \
    \   }\n    if(n != 1) res.emplace_back(n);\n    return res;\n}\n"
  code: "vector<int> get_prime(int n){\n    if(n <= 1) return vector<int>();\n   \
    \ vector<bool> is_prime(n+1, true);\n    vector<int> prime;\n    is_prime[0] =\
    \ is_prime[1] = 0;\n    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i])\
    \ prime.emplace_back(i);\n        for (auto &&j : prime){\n            if(i*j\
    \ > n) break;\n            is_prime[i*j] = false;\n            if(i % j == 0)\
    \ break;\n        }\n    }\n    return prime;\n}\nconst auto primes = get_prime(65535);\n\
    \ntemplate<class T>\nvector<T> prime_factor(T n){\n    vector<T> res;\n    for\
    \ (auto &&i : primes) {\n        while (n % i == 0){\n            res.emplace_back(i);\n\
    \            n /= i;\n        }\n    }\n    if(n != 1) res.emplace_back(n);\n\
    \    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/primefactor.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/primefactor.cpp
layout: document
redirect_from:
- /library/math/primefactor.cpp
- /library/math/primefactor.cpp.html
title: math/primefactor.cpp
---
