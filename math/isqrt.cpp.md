---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/pell_equation.cpp
    title: math/pell_equation.cpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_many_aplusb_isqrt.test.cpp
    title: test/yosupo_many_aplusb_isqrt.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u6574\u6570\u5E73\u65B9\u6839(Integer Square Root)"
    links: []
  bundledCode: "#line 1 \"math/isqrt.cpp\"\null Isqrt(ull const &x){\n    ull ret\
    \ = (ull)sqrtl(x);\n    while(ret > 0 && ret*ret > x) --ret;\n    while(x - ret*ret\
    \ > 2*ret) ++ret;\n    return ret;\n}\n\n/**\n * @brief \u6574\u6570\u5E73\u65B9\
    \u6839(Integer Square Root)\n */\n"
  code: "ull Isqrt(ull const &x){\n    ull ret = (ull)sqrtl(x);\n    while(ret > 0\
    \ && ret*ret > x) --ret;\n    while(x - ret*ret > 2*ret) ++ret;\n    return ret;\n\
    }\n\n/**\n * @brief \u6574\u6570\u5E73\u65B9\u6839(Integer Square Root)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/isqrt.cpp
  requiredBy:
  - math/pell_equation.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_many_aplusb_isqrt.test.cpp
date: 2026-03-08
documentation_of: math/isqrt.cpp
layout: post
tags: "\u6570\u5B66"
title: ISqrt
---

## 説明
`floor(sqrt(x))` を返す。
`sqrtl` の結果を起点に前後へ補正して誤差を潰す。

## できること
- `ull Isqrt(const ull& x)`
  `floor(sqrt(x))` を返す

## 使い方
`unsigned long long` 範囲で使う。
平方判定や Pell 方程式の前処理で使う。
