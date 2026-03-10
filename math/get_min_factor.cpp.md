---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_eulerphi.test.cpp
    title: test/yosupo_many_aplusb_eulerphi.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor\
      \ Table)"
    links: []
  bundledCode: "#line 1 \"math/get_min_factor.cpp\"\nvector<int> get_min_factor(int\
    \ n) {\n    if(n <= 1) return vector<int>{0, 1};\n    vector<bool> prime(n+1,\
    \ true);\n    vector<int> min_factor(n+1, 0);\n    min_factor[0] = 0, min_factor[1]\
    \ = 1;\n    prime[0] = false; prime[1] = false;\n    for(ll i = 2; i <= n; i++){\n\
    \        if(prime[i]) {\n            min_factor[i] = i;\n            for(ll j\
    \ = i << 1; j <= n; j += i) {\n                prime[j] = false;\n           \
    \     if(min_factor[j] == 0) min_factor[j] = i;\n            }\n        }\n  \
    \  }\n    return min_factor;\n}\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\
    \u30C6\u30FC\u30D6\u30EB(Min Factor Table)\n */\n"
  code: "vector<int> get_min_factor(int n) {\n    if(n <= 1) return vector<int>{0,\
    \ 1};\n    vector<bool> prime(n+1, true);\n    vector<int> min_factor(n+1, 0);\n\
    \    min_factor[0] = 0, min_factor[1] = 1;\n    prime[0] = false; prime[1] = false;\n\
    \    for(ll i = 2; i <= n; i++){\n        if(prime[i]) {\n            min_factor[i]\
    \ = i;\n            for(ll j = i << 1; j <= n; j += i) {\n                prime[j]\
    \ = false;\n                if(min_factor[j] == 0) min_factor[j] = i;\n      \
    \      }\n        }\n    }\n    return min_factor;\n}\n\n/**\n * @brief \u6700\
    \u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_min_factor.cpp
  requiredBy:
  - math/powk_all.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_eulerphi.test.cpp
date: 2026-03-08
documentation_of: math/get_min_factor.cpp
layout: document
tags: "\u6570\u5B66"
title: Get Min Factor
---

## 説明
`0..n` の最小素因数を篩で求める。

## できること
- `vector<int> get_min_factor(int n)`
  `min_factor[x]` に `x` の最小素因数を入れた長さ `n + 1` の配列を返す。`min_factor[0] = 0`, `min_factor[1] = 1`

## 使い方
`x >= 2` の素因数分解は `x = x / min_factor[x]` を繰り返せばよい。
素数 `p` では `min_factor[p] = p` になる。

## 実装上の補足
前計算は `O(n log log n)`、各クエリは素因数の個数ぶんだけ進む。
単発クエリには重いが、同じ上限以下を何度も分解する用途に向く。
