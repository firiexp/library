---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: math/binom_mod_prime_power.cpp
    title: binom_mod_prime_power
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/modinv.cpp\"\ntemplate<typename T>  \nT mod_inv(T x,\
    \ T M){  \n   T u = 1, t = 1, v = 0, s = 0, m = M;  \n   while (x) { T q = m/x;\
    \ swap(s -= q*u, u); swap(t -= q*v, v); swap(m -= q*x, x); }  \n   if(s < 0) s\
    \ += M;  \n   return s;  \n}\n"
  code: "template<typename T>  \nT mod_inv(T x, T M){  \n   T u = 1, t = 1, v = 0,\
    \ s = 0, m = M;  \n   while (x) { T q = m/x; swap(s -= q*u, u); swap(t -= q*v,\
    \ v); swap(m -= q*x, x); }  \n   if(s < 0) s += M;  \n   return s;  \n}\n"
  dependsOn: []
  isVerificationFile: false
  path: math/modinv.cpp
  requiredBy:
  - math/binom_mod_prime_power.cpp
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
documentation_of: math/modinv.cpp
layout: document
redirect_from:
- /library/math/modinv.cpp
- /library/math/modinv.cpp.html
title: math/modinv.cpp
---
