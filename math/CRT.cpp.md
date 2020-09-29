---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/extgcd.cpp
    title: math/extgcd.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/extgcd.cpp\"\ntemplate<typename T>\nT extgcd(T a, T\
    \ b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n\
    \        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a,\
    \ a);\n    }\n    return b;\n}\n \n#line 2 \"math/CRT.cpp\"\n\npair<ll, ll> CRT(const\
    \ vector<pair<ll, ll>> &a){\n    ll R = 0, M = 1;\n    for (auto &&i : a) {\n\
    \        ll r = (i.first+i.second)%i.second, m = i.second;\n        if(m < M)\
    \ swap(r, R), swap(m, M);\n        if(M%m == 0){\n            if(R % m != r) return\
    \ {};\n            continue;\n        }\n        ll p, q;\n        ll g = extgcd(M,\
    \ m, p, q); // p = inv(M') mod m'\n        ll mm = m/g;\n        if((r-R)%g) return\
    \ {0, 0};\n        ll x = (r-R)/g % mm * p % mm;\n        R += x*M;\n        M\
    \ *= mm;\n        if(R < 0) R += M;\n    }\n    return {R, M};\n}\n"
  code: "#include \"extgcd.cpp\"\n\npair<ll, ll> CRT(const vector<pair<ll, ll>> &a){\n\
    \    ll R = 0, M = 1;\n    for (auto &&i : a) {\n        ll r = (i.first+i.second)%i.second,\
    \ m = i.second;\n        if(m < M) swap(r, R), swap(m, M);\n        if(M%m ==\
    \ 0){\n            if(R % m != r) return {};\n            continue;\n        }\n\
    \        ll p, q;\n        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'\n\
    \        ll mm = m/g;\n        if((r-R)%g) return {0, 0};\n        ll x = (r-R)/g\
    \ % mm * p % mm;\n        R += x*M;\n        M *= mm;\n        if(R < 0) R +=\
    \ M;\n    }\n    return {R, M};\n}\n"
  dependsOn:
  - math/extgcd.cpp
  isVerificationFile: false
  path: math/CRT.cpp
  requiredBy: []
  timestamp: '2020-09-09 19:14:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/CRT.cpp
layout: document
redirect_from:
- /library/math/CRT.cpp
- /library/math/CRT.cpp.html
title: math/CRT.cpp
---
