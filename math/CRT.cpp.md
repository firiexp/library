---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/extgcd.cpp
    title: "\u62E1\u5F35\u30E6\u30FC\u30AF\u30EA\u30C3\u30C9\u4E92\u9664\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E2D\u56FD\u5270\u4F59\u5B9A\u7406(CRT)"
    links: []
  bundledCode: "#line 1 \"math/extgcd.cpp\"\ntemplate<typename T>\nT extgcd(T a, T\
    \ b, T &x ,T &y){\n    for (T u = y = 1, v = x = 0; a; ) {\n        ll q = b/a;\n\
    \        swap(x -= q*u, u);\n        swap(y -= q*v, v);\n        swap(b -= q*a,\
    \ a);\n    }\n    return b;\n}\n \n\n/**\n * @brief \u62E1\u5F35\u30E6\u30FC\u30AF\
    \u30EA\u30C3\u30C9\u4E92\u9664\u6CD5(Extended GCD)\n */\n#line 2 \"math/CRT.cpp\"\
    \n\npair<ll, ll> CRT(const vector<pair<ll, ll>> &a){\n    ll R = 0, M = 1;\n \
    \   for (auto &&i : a) {\n        ll r = (i.first+i.second)%i.second, m = i.second;\n\
    \        if(m < M) swap(r, R), swap(m, M);\n        if(M%m == 0){\n          \
    \  if(R % m != r) return {};\n            continue;\n        }\n        ll p,\
    \ q;\n        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'\n        ll mm\
    \ = m/g;\n        if((r-R)%g) return {0, 0};\n        ll x = (r-R)/g % mm * p\
    \ % mm;\n        R += x*M;\n        M *= mm;\n        if(R < 0) R += M;\n    }\n\
    \    return {R, M};\n}\n\n/**\n * @brief \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\
    (CRT)\n */\n"
  code: "#include \"extgcd.cpp\"\n\npair<ll, ll> CRT(const vector<pair<ll, ll>> &a){\n\
    \    ll R = 0, M = 1;\n    for (auto &&i : a) {\n        ll r = (i.first+i.second)%i.second,\
    \ m = i.second;\n        if(m < M) swap(r, R), swap(m, M);\n        if(M%m ==\
    \ 0){\n            if(R % m != r) return {};\n            continue;\n        }\n\
    \        ll p, q;\n        ll g = extgcd(M, m, p, q); // p = inv(M') mod m'\n\
    \        ll mm = m/g;\n        if((r-R)%g) return {0, 0};\n        ll x = (r-R)/g\
    \ % mm * p % mm;\n        R += x*M;\n        M *= mm;\n        if(R < 0) R +=\
    \ M;\n    }\n    return {R, M};\n}\n\n/**\n * @brief \u4E2D\u56FD\u5270\u4F59\u5B9A\
    \u7406(CRT)\n */\n"
  dependsOn:
  - math/extgcd.cpp
  isVerificationFile: false
  path: math/CRT.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
date: 2019-08-18
documentation_of: math/CRT.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u4E2D\u56FD\u5270\u4F59\u5B9A\u7406"
---

## 説明

$ x = a_i \mod M_i (1 \le i \le N)$ という情報から、$\mod \mathrm{lcm} (M_1 , M_2 , \cdots , M_N)$での$x$を復元する。
