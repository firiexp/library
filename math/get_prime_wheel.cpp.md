---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
    title: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/get_prime_wheel.cpp\"\nstruct Prime { // Wheel factorization\n\
    \    static constexpr int wheel[] = {4, 2, 4, 2, 4, 6, 2, 6},\n            wheel2[]\
    \ = {7, 11, 13, 17, 19, 23, 29, 31},\n            wheel_sum[] = {0, 0, 0, 0, 0,\
    \ 0, 1, 1, 1, 1, 2, 2, 3, 3, 3, 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7};\n\
    \    static inline int f(int n){ return (n-1)/30*8 + wheel_sum[(n-1)%30]; }\n\
    \    static inline int g(int n){ return ((n-1) >> 3)*30 + wheel2[(n-1)&7]; }\n\
    \    vector<int> primes;\n\n    Prime(int M) {\n        if (M >= 2) primes.emplace_back(2);\n\
    \        if (M >= 3) primes.emplace_back(3);\n        if (M >= 5) primes.emplace_back(5);\n\
    \        if(M < 7){\n            return;\n        }\n        int n = f(M), m =\
    \ g(n), k = f((int)floor(sqrt((long double)M)));\n        primes.reserve(3 + max(0,\
    \ (int)(M / (log((double)M) - 1.12))));\n        vector<unsigned long long> sieve((n\
    \ + 64) >> 6, ~0ULL);\n        auto *sv = sieve.data();\n        for (int i =\
    \ 1; i <= k; ++i) {\n            if ((sv[i >> 6] >> (i & 63)) & 1ULL) {\n    \
    \            int p = g(i);\n                int q = p * p;\n                int\
    \ j = (i - 1) & 7;\n                while (q <= m) {\n                    int\
    \ idx = f(q);\n                    sv[idx >> 6] &= ~(1ULL << (idx & 63));\n  \
    \                  q += wheel[j] * p;\n                    j = (j + 1) & 7;\n\
    \                }\n            }\n        }\n        for (int i = 1; i <= n;\
    \ ++i) {\n            if ((sv[i >> 6] >> (i & 63)) & 1ULL) primes.emplace_back(g(i));\n\
    \        }\n    }\n};\nconstexpr int Prime::wheel[], Prime::wheel2[], Prime::wheel_sum[];\n"
  code: "struct Prime { // Wheel factorization\n    static constexpr int wheel[] =\
    \ {4, 2, 4, 2, 4, 6, 2, 6},\n            wheel2[] = {7, 11, 13, 17, 19, 23, 29,\
    \ 31},\n            wheel_sum[] = {0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 3, 3, 3,\
    \ 3, 4, 4, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7};\n    static inline int f(int n){\
    \ return (n-1)/30*8 + wheel_sum[(n-1)%30]; }\n    static inline int g(int n){\
    \ return ((n-1) >> 3)*30 + wheel2[(n-1)&7]; }\n    vector<int> primes;\n\n   \
    \ Prime(int M) {\n        if (M >= 2) primes.emplace_back(2);\n        if (M >=\
    \ 3) primes.emplace_back(3);\n        if (M >= 5) primes.emplace_back(5);\n  \
    \      if(M < 7){\n            return;\n        }\n        int n = f(M), m = g(n),\
    \ k = f((int)floor(sqrt((long double)M)));\n        primes.reserve(3 + max(0,\
    \ (int)(M / (log((double)M) - 1.12))));\n        vector<unsigned long long> sieve((n\
    \ + 64) >> 6, ~0ULL);\n        auto *sv = sieve.data();\n        for (int i =\
    \ 1; i <= k; ++i) {\n            if ((sv[i >> 6] >> (i & 63)) & 1ULL) {\n    \
    \            int p = g(i);\n                int q = p * p;\n                int\
    \ j = (i - 1) & 7;\n                while (q <= m) {\n                    int\
    \ idx = f(q);\n                    sv[idx >> 6] &= ~(1ULL << (idx & 63));\n  \
    \                  q += wheel[j] * p;\n                    j = (j + 1) & 7;\n\
    \                }\n            }\n        }\n        for (int i = 1; i <= n;\
    \ ++i) {\n            if ((sv[i >> 6] >> (i & 63)) & 1ULL) primes.emplace_back(g(i));\n\
    \        }\n    }\n};\nconstexpr int Prime::wheel[], Prime::wheel2[], Prime::wheel_sum[];\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_prime_wheel.cpp
  requiredBy: []
  timestamp: '2026-03-13 22:14:25+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
documentation_of: math/get_prime_wheel.cpp
layout: document
redirect_from:
- /library/math/get_prime_wheel.cpp
- /library/math/get_prime_wheel.cpp.html
title: math/get_prime_wheel.cpp
---
