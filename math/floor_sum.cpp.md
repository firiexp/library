---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_sum_of_floor_of_linear.test.cpp
    title: test/yosupo_sum_of_floor_of_linear.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Floor Sum
    links: []
  bundledCode: "#line 1 \"math/floor_sum.cpp\"\nll floor_sum(ll n, ll m, ll a, ll\
    \ b){\n    ll ans = 0;\n    if(a >= m) {\n        ans += (n-1)*n/2*(a/m);\n  \
    \      a %= m;\n    }\n    if (b >= m){\n        ans += n*(b/m);\n        b %=\
    \ m;\n    }\n    ll y = (a*n+b)/m, x = (y*m - b);\n    if(!y) return ans;\n  \
    \  ans += (n-(x+a-1)/a)*y;\n    ans += floor_sum(y, a, m, (a - x%a)%a);\n    return\
    \ ans;\n}\n\n/**\n * @brief Floor Sum\n */\n"
  code: "ll floor_sum(ll n, ll m, ll a, ll b){\n    ll ans = 0;\n    if(a >= m) {\n\
    \        ans += (n-1)*n/2*(a/m);\n        a %= m;\n    }\n    if (b >= m){\n \
    \       ans += n*(b/m);\n        b %= m;\n    }\n    ll y = (a*n+b)/m, x = (y*m\
    \ - b);\n    if(!y) return ans;\n    ans += (n-(x+a-1)/a)*y;\n    ans += floor_sum(y,\
    \ a, m, (a - x%a)%a);\n    return ans;\n}\n\n/**\n * @brief Floor Sum\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/floor_sum.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_sum_of_floor_of_linear.test.cpp
date: 2026-03-08
documentation_of: math/floor_sum.cpp
layout: post
tags: "\u6570\u5B66"
title: Floor Sum
---

## 説明
`sum_{i=0}^{n-1} floor((a i + b) / m)` を返す。
計算量は償却 `O(log m + log a)`。

## できること
- `ll floor_sum(ll n, ll m, ll a, ll b)`
  `sum_{i=0}^{n-1} floor((a i + b) / m)` を返す

## 使い方
`n = 0` なら `0` を返す。
`m > 0` を仮定する。
`a`, `b` が `m` 以上でもそのまま渡してよい。
