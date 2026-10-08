---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_floor_sum.test.cpp
    title: test/yosupo_aplusb_floor_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sum_of_floor_of_linear.test.cpp
    title: test/yosupo_sum_of_floor_of_linear.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Floor Sum
    links: []
  bundledCode: "#line 1 \"math/floor_sum.cpp\"\nll floor_sum(ll n, ll m, ll a, ll\
    \ b) {\n    __int128 N = n, M = m, A = a, B = b, ans = 0;\n    while (true) {\n\
    \        __int128 qa = A / M - (A % M < 0);\n        __int128 qb = B / M - (B\
    \ % M < 0);\n        ans += N * (N - 1) / 2 * qa + N * qb;\n        A -= qa *\
    \ M;\n        B -= qb * M;\n        __int128 y = A * N + B;\n        if (y < M)\
    \ return (ll)ans;\n        N = y / M;\n        B = y % M;\n        __int128 next_m\
    \ = A;\n        A = M;\n        M = next_m;\n    }\n}\n\n/**\n * @brief Floor\
    \ Sum\n */\n"
  code: "ll floor_sum(ll n, ll m, ll a, ll b) {\n    __int128 N = n, M = m, A = a,\
    \ B = b, ans = 0;\n    while (true) {\n        __int128 qa = A / M - (A % M <\
    \ 0);\n        __int128 qb = B / M - (B % M < 0);\n        ans += N * (N - 1)\
    \ / 2 * qa + N * qb;\n        A -= qa * M;\n        B -= qb * M;\n        __int128\
    \ y = A * N + B;\n        if (y < M) return (ll)ans;\n        N = y / M;\n   \
    \     B = y % M;\n        __int128 next_m = A;\n        A = M;\n        M = next_m;\n\
    \    }\n}\n\n/**\n * @brief Floor Sum\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/floor_sum.cpp
  requiredBy: []
  timestamp: '2026-10-08 14:12:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_sum_of_floor_of_linear.test.cpp
  - test/yosupo_aplusb_floor_sum.test.cpp
date: 2026-03-08
documentation_of: math/floor_sum.cpp
layout: document
tags: "\u6570\u5B66"
title: Floor Sum
---

## 説明
$\sum_{i=0}^{n-1} \lfloor (ai+b)/m \rfloor$ を返す。
計算量は $O(\log m)$、追加領域は $O(1)$。

## できること
- `ll floor_sum(ll n, ll m, ll a, ll b)`
  床関数の和を返す。`n = 0` なら `0`

## 使い方
$0 \le n < 2^{32}$、$1 \le m < 2^{32}$、答えが `long long` に収まる入力を扱う。
`a`, `b` は `long long` の全範囲を受け取り、負の値や `m` 以上でもそのまま渡せる。
途中の積と負の係数の正規化には `__int128` を使う。
