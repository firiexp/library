---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yuki3030.test.cpp
    title: test/yuki3030.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Miller-Rabin\u7D20\u6570\u5224\u5B9A"
    links: []
  bundledCode: "#line 1 \"math/miller_rabin.cpp\"\ntemplate< class T>\nT pow_ (T x,\
    \ uint64_t n, uint64_t M){\n    T u = 1;\n    if(n > 0){\n        u = pow_(x,\
    \ n/2, M);\n        if (n % 2 == 0) u = (u*u) % M;\n        else u = (((u * u)%\
    \ M) * x) % M;\n    }\n    return u;\n};\n\nbool suspect(__uint128_t a, uint64_t\
    \ s, uint64_t d, uint64_t n){\n    __uint128_t x = pow_(a, d, n);\n    if (x ==\
    \ 1) return true;\n    for (int r = 0; r < s; ++r) {\n        if(x == n-1) return\
    \ true;\n        x = x * x % n;\n    }\n    return false;\n}\n\ntemplate<class\
    \ T>\nbool miller_rabin(T m){\n    uint64_t n = m;\n    if (n <= 1 || (n > 2 &&\
    \ n % 2 == 0)) return false;\n    uint64_t d = n - 1, s = 0;\n    while (!(d&1))\
    \ {++s; d >>= 1;}\n    vector<uint64_t> v = {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022};\n    if(n < 4759123141LL) v = {2, 7, 61};\n    for (auto &&p :\
    \ v) {\n        if(p >= n) break;\n        if(!suspect(p, s, d, n)) return false;\n\
    \    }\n    return true;\n}\n\n/**\n * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\
    \n */\n"
  code: "template< class T>\nT pow_ (T x, uint64_t n, uint64_t M){\n    T u = 1;\n\
    \    if(n > 0){\n        u = pow_(x, n/2, M);\n        if (n % 2 == 0) u = (u*u)\
    \ % M;\n        else u = (((u * u)% M) * x) % M;\n    }\n    return u;\n};\n\n\
    bool suspect(__uint128_t a, uint64_t s, uint64_t d, uint64_t n){\n    __uint128_t\
    \ x = pow_(a, d, n);\n    if (x == 1) return true;\n    for (int r = 0; r < s;\
    \ ++r) {\n        if(x == n-1) return true;\n        x = x * x % n;\n    }\n \
    \   return false;\n}\n\ntemplate<class T>\nbool miller_rabin(T m){\n    uint64_t\
    \ n = m;\n    if (n <= 1 || (n > 2 && n % 2 == 0)) return false;\n    uint64_t\
    \ d = n - 1, s = 0;\n    while (!(d&1)) {++s; d >>= 1;}\n    vector<uint64_t>\
    \ v = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};\n    if(n < 4759123141LL)\
    \ v = {2, 7, 61};\n    for (auto &&p : v) {\n        if(p >= n) break;\n     \
    \   if(!suspect(p, s, d, n)) return false;\n    }\n    return true;\n}\n\n/**\n\
    \ * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/miller_rabin.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yuki3030.test.cpp
date: 2018-04-28
documentation_of: math/miller_rabin.cpp
layout: post
tags: "\u6570\u5B66"
title: "Miller-Rabin\u6CD5(\u78BA\u7387\u7684\u7D20\u6570\u5224\u5B9A)"
---

## 説明
与えられた数$N$が素数かどうかを判定する。$k$個の「証人」について判定するとすると、$O(k \cdot \log  ^3 N)$。 <br>
誤判定する確率は最大で$4^{-k}$であるが、$\{2, 325, 9375, 28178, 450775, 9780504, 1795265022\}$と証人の組をとると、$N \le 2^{64}$で確実に判定できることが確認されている。
