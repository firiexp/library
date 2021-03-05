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
  bundledCode: "#line 1 \"math/get_prime_wheel.cpp\"\nstruct Prime { // Wheel factorization\n\
    \    static constexpr int wheel[] = {4, 2, 4, 2, 4, 6, 2, 6},\n            wheel2[]\
    \ = {7, 11, 13, 17, 19, 23, 29, 31},\n            wheel_sum[] = {0, 0, 0, 0, 0,\
    \ 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7};\n\
    \    static inline int f(int n){ return (n-1)/30*8 + wheel_sum[(n-1)%30]; }\n\
    \    static inline int g(int n){ return ((n-1) >> 3)*30 + wheel2[(n-1)&7]; }\n\
    \    vector<ll> primes;\n\n    Prime(int M) {\n        primes = {2, 3, 5};\n \
    \       if(M < 7){\n            while(!primes.empty() && M < primes.back()) primes.pop_back();\n\
    \            return;\n        }\n        int n = f(M), m = g(n), k = f(int(floor(sqrt(M))));\n\
    \        primes.reserve(3+max(0, (int)(n/(log(n)-1.12))));\n        vector<bool>\
    \ sieve(n+1, true);\n        for (int i = 1; i <= k; ++i) {\n            if(sieve[i]){\n\
    \                ll p = g(i), q = p*p;\n                int j = (i-1)&7;\n   \
    \             while(q <= m){\n                    sieve[f(q)] = false;\n     \
    \               q += wheel[j] * p;\n                    j = (j+1)&7;\n       \
    \         }\n            }\n        }\n        for (int i = 1; i <= n; ++i) {\n\
    \            if(sieve[i]) primes.emplace_back(g(i));\n        }\n    }\n};\nconstexpr\
    \ int Prime::wheel[], Prime::wheel2[], Prime::wheel_sum[];\n\n"
  code: "struct Prime { // Wheel factorization\n    static constexpr int wheel[] =\
    \ {4, 2, 4, 2, 4, 6, 2, 6},\n            wheel2[] = {7, 11, 13, 17, 19, 23, 29,\
    \ 31},\n            wheel_sum[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3,\
    \ 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7};\n    static inline int f(int n){\
    \ return (n-1)/30*8 + wheel_sum[(n-1)%30]; }\n    static inline int g(int n){\
    \ return ((n-1) >> 3)*30 + wheel2[(n-1)&7]; }\n    vector<ll> primes;\n\n    Prime(int\
    \ M) {\n        primes = {2, 3, 5};\n        if(M < 7){\n            while(!primes.empty()\
    \ && M < primes.back()) primes.pop_back();\n            return;\n        }\n \
    \       int n = f(M), m = g(n), k = f(int(floor(sqrt(M))));\n        primes.reserve(3+max(0,\
    \ (int)(n/(log(n)-1.12))));\n        vector<bool> sieve(n+1, true);\n        for\
    \ (int i = 1; i <= k; ++i) {\n            if(sieve[i]){\n                ll p\
    \ = g(i), q = p*p;\n                int j = (i-1)&7;\n                while(q\
    \ <= m){\n                    sieve[f(q)] = false;\n                    q += wheel[j]\
    \ * p;\n                    j = (j+1)&7;\n                }\n            }\n \
    \       }\n        for (int i = 1; i <= n; ++i) {\n            if(sieve[i]) primes.emplace_back(g(i));\n\
    \        }\n    }\n};\nconstexpr int Prime::wheel[], Prime::wheel2[], Prime::wheel_sum[];\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_prime_wheel.cpp
  requiredBy: []
  timestamp: '2021-03-05 23:15:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/get_prime_wheel.cpp
layout: document
redirect_from:
- /library/math/get_prime_wheel.cpp
- /library/math/get_prime_wheel.cpp.html
title: math/get_prime_wheel.cpp
---
