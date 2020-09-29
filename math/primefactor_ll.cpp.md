---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/primefactor_ll.cpp\"\n#include <random>\ntemplate<\
    \ class T>\nT pow_ (T x, uint64_t n, uint64_t M){\n    T u = 1;\n    if(n > 0){\n\
    \        u = pow_(x, n/2, M);\n        if (n % 2 == 0) u = (u*u) % M;\n      \
    \  else u = (((u * u)% M) * x) % M;\n    }\n    return u;\n};\n\nbool suspect(__uint128_t\
    \ a, uint64_t s, uint64_t d, uint64_t n){\n    __uint128_t x = pow_(a, d, n);\n\
    \    if (x == 1) return true;\n    for (int r = 0; r < s; ++r) {\n        if(x\
    \ == n-1) return true;\n        x = x * x % n;\n    }\n    return false;\n}\n\n\
    template<class T>\nbool miller_rabin(T m){\n    uint64_t n = m;\n    if (n <=\
    \ 1 || (n > 2 && n % 2 == 0)) return false;\n    uint64_t d = n - 1, s = 0;\n\
    \    while (!(d&1)) {++s; d >>= 1;}\n    vector<uint64_t> v = {2, 325, 9375, 28178,\
    \ 450775, 9780504, 1795265022};\n    if(n <= 4759123141LL) v = {2, 7, 61};\n \
    \   for (auto &&p : v) {\n        if(p >= n) break;\n        if(!suspect(p, s,\
    \ d, n)) return false;\n    }\n    return true;\n}\n\nvector<int> get_prime(int\
    \ n){\n    if(n <= 1) return vector<int>();\n    vector<bool> is_prime(n+1, true);\n\
    \    vector<int> prime;\n    is_prime[0] = is_prime[1] = 0;\n    for (int i =\
    \ 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n        for\
    \ (auto &&j : prime){\n            if(i*j > n) break;\n            is_prime[i*j]\
    \ = false;\n            if(i % j == 0) break;\n        }\n    }\n    return prime;\n\
    }\n\nconst auto primes = get_prime(100000);\nrandom_device rng;\ntemplate<class\
    \ T>\nT pollard_rho2(T n) {\n    uniform_int_distribution<T> ra(1, n-1);\n   \
    \ while(true){\n        T c = ra(rng), g = 1, r = 1, y = ra(rng),m = 1900,\n \
    \               ys = 0, q = 1, xx = 0;\n        while(c == n-2) c = ra(rng);\n\
    \        while(g == 1){\n            xx = y;\n            for (int i = 1; i <=\
    \ r; ++i) {\n                y = static_cast<T>(((__uint128_t)y * y) % n);\n \
    \               y = static_cast<T>((__uint128_t)y + c) % n;\n            }\n \
    \           T k = 0; g = 1;\n            while(k < r && g == 1){\n           \
    \     for (int i = 1; i <= (m > (r-k) ? (r-k) : m); ++i) {\n                 \
    \   ys = y;\n                    y = static_cast<T>(((__uint128_t)y * y) % n);\n\
    \                    y = static_cast<T>((__uint128_t)y + c) % n;\n           \
    \         q = static_cast<T>(((__uint128_t)q * (xx > y ? xx - y : y - xx)) % n);\n\
    \                }\n                g = __gcd(q, n);\n                k += m;\n\
    \            }\n            r *= 2;\n        }\n        if(g == n) g = 1;\n  \
    \      while (g == 1){\n            ys = static_cast<T>(((__uint128_t)ys * ys)\
    \ % n);\n            ys = static_cast<T>((__uint128_t)ys + c) % n;\n         \
    \   g = __gcd(xx > ys ? xx - ys : ys - xx, n);\n        }\n        if (g != n\
    \ && miller_rabin(g)) return g;\n    }\n}\n\ntemplate<class T>\nvector<T> prime_factor(T\
    \ n, int d = 0){\n    vector<T> a, res;\n    if(!d) for (auto &&i : primes) {\n\
    \            while (n % i == 0){\n                res.emplace_back(i);\n     \
    \           n /= i;\n            }\n        }\n    while(n != 1){\n        if(miller_rabin(n)){\n\
    \            a.emplace_back(n);\n            break;\n        }\n        T x =\
    \ pollard_rho2(n);\n        n /= x;\n        a.emplace_back(x);\n    }\n    for\
    \ (auto &&i : a) {\n        if (miller_rabin(i)) {\n            res.emplace_back(i);\n\
    \        } else {\n            vector<T> b = prime_factor(i, d + 1);\n       \
    \     for (auto &&j : b) res.emplace_back(j);\n        }\n    }\n    return res;\n\
    }\n"
  code: "#include <random>\ntemplate< class T>\nT pow_ (T x, uint64_t n, uint64_t\
    \ M){\n    T u = 1;\n    if(n > 0){\n        u = pow_(x, n/2, M);\n        if\
    \ (n % 2 == 0) u = (u*u) % M;\n        else u = (((u * u)% M) * x) % M;\n    }\n\
    \    return u;\n};\n\nbool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t\
    \ n){\n    __uint128_t x = pow_(a, d, n);\n    if (x == 1) return true;\n    for\
    \ (int r = 0; r < s; ++r) {\n        if(x == n-1) return true;\n        x = x\
    \ * x % n;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool miller_rabin(T\
    \ m){\n    uint64_t n = m;\n    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;\n\
    \    uint64_t d = n - 1, s = 0;\n    while (!(d&1)) {++s; d >>= 1;}\n    vector<uint64_t>\
    \ v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};\n    if(n <= 4759123141LL)\
    \ v = {2, 7, 61};\n    for (auto &&p : v) {\n        if(p >= n) break;\n     \
    \   if(!suspect(p, s, d, n)) return false;\n    }\n    return true;\n}\n\nvector<int>\
    \ get_prime(int n){\n    if(n <= 1) return vector<int>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<int> prime;\n    is_prime[0] = is_prime[1] = 0;\n    for\
    \ (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j > n) break;\n           \
    \ is_prime[i*j] = false;\n            if(i % j == 0) break;\n        }\n    }\n\
    \    return prime;\n}\n\nconst auto primes = get_prime(100000);\nrandom_device\
    \ rng;\ntemplate<class T>\nT pollard_rho2(T n) {\n    uniform_int_distribution<T>\
    \ ra(1, n-1);\n    while(true){\n        T c = ra(rng), g = 1, r = 1, y = ra(rng),m\
    \ = 1900,\n                ys = 0, q = 1, xx = 0;\n        while(c == n-2) c =\
    \ ra(rng);\n        while(g == 1){\n            xx = y;\n            for (int\
    \ i = 1; i <= r; ++i) {\n                y = static_cast<T>(((__uint128_t)y *\
    \ y) % n);\n                y = static_cast<T>((__uint128_t)y + c) % n;\n    \
    \        }\n            T k = 0; g = 1;\n            while(k < r && g == 1){\n\
    \                for (int i = 1; i <= (m > (r-k) ? (r-k) : m); ++i) {\n      \
    \              ys = y;\n                    y = static_cast<T>(((__uint128_t)y\
    \ * y) % n);\n                    y = static_cast<T>((__uint128_t)y + c) % n;\n\
    \                    q = static_cast<T>(((__uint128_t)q * (xx > y ? xx - y : y\
    \ - xx)) % n);\n                }\n                g = __gcd(q, n);\n        \
    \        k += m;\n            }\n            r *= 2;\n        }\n        if(g\
    \ == n) g = 1;\n        while (g == 1){\n            ys = static_cast<T>(((__uint128_t)ys\
    \ * ys) % n);\n            ys = static_cast<T>((__uint128_t)ys + c) % n;\n   \
    \         g = __gcd(xx > ys ? xx - ys : ys - xx, n);\n        }\n        if (g\
    \ != n && miller_rabin(g)) return g;\n    }\n}\n\ntemplate<class T>\nvector<T>\
    \ prime_factor(T n, int d = 0){\n    vector<T> a, res;\n    if(!d) for (auto &&i\
    \ : primes) {\n            while (n % i == 0){\n                res.emplace_back(i);\n\
    \                n /= i;\n            }\n        }\n    while(n != 1){\n     \
    \   if(miller_rabin(n)){\n            a.emplace_back(n);\n            break;\n\
    \        }\n        T x = pollard_rho2(n);\n        n /= x;\n        a.emplace_back(x);\n\
    \    }\n    for (auto &&i : a) {\n        if (miller_rabin(i)) {\n           \
    \ res.emplace_back(i);\n        } else {\n            vector<T> b = prime_factor(i,\
    \ d + 1);\n            for (auto &&j : b) res.emplace_back(j);\n        }\n  \
    \  }\n    return res;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/primefactor_ll.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/primefactor_ll.cpp
layout: document
redirect_from:
- /library/math/primefactor_ll.cpp
- /library/math/primefactor_ll.cpp.html
title: math/primefactor_ll.cpp
---
