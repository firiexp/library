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
  bundledCode: "#line 1 \"math/pell_equation.cpp\"\nvector<ll> sqrt_fraction(ll n){\n\
    \    set<tuple<ll, ll, ll>> s;\n    vector<ll> ret;\n    ll sq = Isqrt(n);\n \
    \   if(sq*sq == n) return {sq};\n    tuple<ll, ll, ll> a = {sq, -sq, 1};\n\n \
    \   while(!s.count(a)){\n        s.insert(a);\n        ret.emplace_back(get<0>(a));\n\
    \        auto [p, q, r] = a;\n        ll c = floor(r/(q+sqrt(n)));\n        ll\
    \ x = (n-q*q)/r;\n        a = {c, -q-c*x, x};\n    }\n    return ret;\n}\n\npair<ll,\
    \ ll> pell_equation(ll d){ // solve x^2 - dy^2 = 1\n    auto li = sqrt_fraction(d);\n\
    \    if(li.size() <= 1) return {0, 0};\n    li.pop_back();\n    ll p = li.back(),\
    \ q = 1;\n    for (int i = (int)li.size()-2; i >= 0; --i) {\n        swap(p, q);\n\
    \        p += q*li[i];\n    }\n    if(p*p - d*q*q == -1) return {p*p+d*q*q, 2*p*q};\
    \ // p' + q'\u221Ad  = (p + q\u221Ad)^2\n    return {p, q};\n}\n"
  code: "vector<ll> sqrt_fraction(ll n){\n    set<tuple<ll, ll, ll>> s;\n    vector<ll>\
    \ ret;\n    ll sq = Isqrt(n);\n    if(sq*sq == n) return {sq};\n    tuple<ll,\
    \ ll, ll> a = {sq, -sq, 1};\n\n    while(!s.count(a)){\n        s.insert(a);\n\
    \        ret.emplace_back(get<0>(a));\n        auto [p, q, r] = a;\n        ll\
    \ c = floor(r/(q+sqrt(n)));\n        ll x = (n-q*q)/r;\n        a = {c, -q-c*x,\
    \ x};\n    }\n    return ret;\n}\n\npair<ll, ll> pell_equation(ll d){ // solve\
    \ x^2 - dy^2 = 1\n    auto li = sqrt_fraction(d);\n    if(li.size() <= 1) return\
    \ {0, 0};\n    li.pop_back();\n    ll p = li.back(), q = 1;\n    for (int i =\
    \ (int)li.size()-2; i >= 0; --i) {\n        swap(p, q);\n        p += q*li[i];\n\
    \    }\n    if(p*p - d*q*q == -1) return {p*p+d*q*q, 2*p*q}; // p' + q'\u221A\
    d  = (p + q\u221Ad)^2\n    return {p, q};\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/pell_equation.cpp
  requiredBy: []
  timestamp: '2021-03-10 13:22:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/pell_equation.cpp
layout: document
redirect_from:
- /library/math/pell_equation.cpp
- /library/math/pell_equation.cpp.html
title: math/pell_equation.cpp
---
