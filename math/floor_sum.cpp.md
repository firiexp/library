---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sum_of_floor_of_linear.test.cpp
    title: test/yosupo_sum_of_floor_of_linear.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/floor_sum.cpp\"\nll floor_sum(ll n, ll m, ll a, ll\
    \ b){\n    ll ans = 0;\n    if(a >= m) {\n        ans += (n-1)*n/2*(a/m);\n  \
    \      a %= m;\n    }\n    if (b >= m){\n        ans += n*(b/m);\n        b %=\
    \ m;\n    }\n    ll y = (a*n+b)/m, x = (y*m - b);\n    if(!y) return ans;\n  \
    \  ans += (n-(x+a-1)/a)*y;\n    ans += floor_sum(y, a, m, (a - x%a)%a);\n    return\
    \ ans;\n}\n"
  code: "ll floor_sum(ll n, ll m, ll a, ll b){\n    ll ans = 0;\n    if(a >= m) {\n\
    \        ans += (n-1)*n/2*(a/m);\n        a %= m;\n    }\n    if (b >= m){\n \
    \       ans += n*(b/m);\n        b %= m;\n    }\n    ll y = (a*n+b)/m, x = (y*m\
    \ - b);\n    if(!y) return ans;\n    ans += (n-(x+a-1)/a)*y;\n    ans += floor_sum(y,\
    \ a, m, (a - x%a)%a);\n    return ans;\n}"
  dependsOn: []
  isVerificationFile: false
  path: math/floor_sum.cpp
  requiredBy: []
  timestamp: '2020-09-09 21:30:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_sum_of_floor_of_linear.test.cpp
documentation_of: math/floor_sum.cpp
layout: document
redirect_from:
- /library/math/floor_sum.cpp
- /library/math/floor_sum.cpp.html
title: math/floor_sum.cpp
---
