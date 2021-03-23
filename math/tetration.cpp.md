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
  bundledCode: "#line 1 \"math/tetration.cpp\"\nll totient(ll n){\n    ll res = n;\n\
    \    for (ll i = 2; i*i <= n; ++i) {\n        if(n%i == 0){\n            res =\
    \ res/i*(i-1);\n            while(n%i == 0) n /= i;\n        }\n    }\n    if(n\
    \ > 1) res = res/n*(n-1);\n    return res;\n}\n\ntemplate <class T>\nT pow_tetration(T\
    \ x, T n, T M, bool &yojo){\n    uint64_t u = 1, xx = x;\n    if(x >= M) yojo\
    \ = true;\n    while (n > 0){\n        if (n&1) {\n            u = u * xx;  \n\
    \            if(u >= M) yojo = true, u %= M;\n        }\n        if(!(n >>= 1))\
    \ break;\n        xx = xx * xx;\n        if(xx >= M) yojo = true, xx %= M;\n \
    \   }\n    return static_cast<T>(u);\n};\n\nll tetration(ll a, ll n, const ll\
    \ M, bool &yojo) {\n    if(a == 0) return !(n&1);\n    if(M == 1) return yojo\
    \ = true, 1;\n    if(a == 1 || n == 0) return 1;\n    ll expo = tetration(a, n-1,\
    \ totient(M), yojo);\n    ll res = pow_tetration(a, expo, M, yojo);\n    return\
    \ res + (yojo ? M : 0);\n}\n\nll tetration(ll a, ll n, const ll M){\n    bool\
    \ yojo = false;\n    return tetration(a, n, M, yojo)%M;\n}\n"
  code: "ll totient(ll n){\n    ll res = n;\n    for (ll i = 2; i*i <= n; ++i) {\n\
    \        if(n%i == 0){\n            res = res/i*(i-1);\n            while(n%i\
    \ == 0) n /= i;\n        }\n    }\n    if(n > 1) res = res/n*(n-1);\n    return\
    \ res;\n}\n\ntemplate <class T>\nT pow_tetration(T x, T n, T M, bool &yojo){\n\
    \    uint64_t u = 1, xx = x;\n    if(x >= M) yojo = true;\n    while (n > 0){\n\
    \        if (n&1) {\n            u = u * xx;  \n            if(u >= M) yojo =\
    \ true, u %= M;\n        }\n        if(!(n >>= 1)) break;\n        xx = xx * xx;\n\
    \        if(xx >= M) yojo = true, xx %= M;\n    }\n    return static_cast<T>(u);\n\
    };\n\nll tetration(ll a, ll n, const ll M, bool &yojo) {\n    if(a == 0) return\
    \ !(n&1);\n    if(M == 1) return yojo = true, 1;\n    if(a == 1 || n == 0) return\
    \ 1;\n    ll expo = tetration(a, n-1, totient(M), yojo);\n    ll res = pow_tetration(a,\
    \ expo, M, yojo);\n    return res + (yojo ? M : 0);\n}\n\nll tetration(ll a, ll\
    \ n, const ll M){\n    bool yojo = false;\n    return tetration(a, n, M, yojo)%M;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: math/tetration.cpp
  requiredBy: []
  timestamp: '2021-03-23 22:28:05+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/tetration.cpp
layout: document
redirect_from:
- /library/math/tetration.cpp
- /library/math/tetration.cpp.html
title: math/tetration.cpp
---
