---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/garner.cpp\"\ntemplate <class T>\nT pow_ (T x, T n,\
    \ T M){\n    uint64_t u = 1, xx = x;\n    while (n > 0){\n        if (n&1) u =\
    \ u * xx % M;\n        xx = xx * xx % M;\n        n >>= 1;\n    }\n    return\
    \ static_cast<T>(u);\n};\n\n\ntemplate<typename T>\nT extgcd(T a, T b, T &x ,T\
    \ &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n       \
    \ swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a, a);\n\
    \    }\n    return b;\n}\n\ntemplate<typename T>\nT mod_inv(T x, T m){\n    T\
    \ s, t;\n    extgcd(x, m, s, t);\n    return (m+s)% m;\n}\n\nll Garner(vector<pair<ll,\
    \ ll>> a, ll mod){\n    a.emplace_back(0, mod);\n    vector<ll> A(a.size(), 1),\
    \ B(a.size(), 0);\n    for (int i = 0; i < a.size(); ++i) {\n        ll t = (a[i].first+a[i].second-B[i])*\
    \ mod_inv(A[i], a[i].second) % a[i].second;\n        for (int j = i+1; j < a.size()\
    \ ; ++j) {\n            (B[j] += t * A[j]) %= a[j].second;\n            (A[j]\
    \ *= a[i].second) %= a[j].second;\n        }\n    }\n    return B.back();\n}\n"
  code: "template <class T>\nT pow_ (T x, T n, T M){\n    uint64_t u = 1, xx = x;\n\
    \    while (n > 0){\n        if (n&1) u = u * xx % M;\n        xx = xx * xx %\
    \ M;\n        n >>= 1;\n    }\n    return static_cast<T>(u);\n};\n\n\ntemplate<typename\
    \ T>\nT extgcd(T a, T b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n\
    \        ll q = b/a;\n        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n\
    \        swap(b -= q*a, a);\n    }\n    return b;\n}\n\ntemplate<typename T>\n\
    T mod_inv(T x, T m){\n    T s, t;\n    extgcd(x, m, s, t);\n    return (m+s)%\
    \ m;\n}\n\nll Garner(vector<pair<ll, ll>> a, ll mod){\n    a.emplace_back(0, mod);\n\
    \    vector<ll> A(a.size(), 1), B(a.size(), 0);\n    for (int i = 0; i < a.size();\
    \ ++i) {\n        ll t = (a[i].first+a[i].second-B[i])* mod_inv(A[i], a[i].second)\
    \ % a[i].second;\n        for (int j = i+1; j < a.size() ; ++j) {\n          \
    \  (B[j] += t * A[j]) %= a[j].second;\n            (A[j] *= a[i].second) %= a[j].second;\n\
    \        }\n    }\n    return B.back();\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/garner.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/garner.cpp
layout: document
redirect_from:
- /library/math/garner.cpp
- /library/math/garner.cpp.html
title: math/garner.cpp
---
