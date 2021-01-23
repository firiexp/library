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
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/modinv.cpp
layout: document
redirect_from:
- /library/math/modinv.cpp
- /library/math/modinv.cpp.html
title: math/modinv.cpp
---
