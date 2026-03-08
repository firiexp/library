---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_eulerphi.test.cpp
    title: test/yosupo_many_aplusb_eulerphi.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570(Euler Phi)"
    links: []
  bundledCode: "#line 1 \"math/eulerphi.cpp\"\nint eulerphi(int x){\n    int phi =\
    \ x, xx = x;\n    for (int i = 2; i * i <= x; ++i) {\n        if (xx % i == 0)\
    \ {\n            phi -= phi / i;\n            while(xx % i == 0) xx /= i;\n  \
    \      }\n    }\n    if(xx > 1) phi -= phi/xx;\n    return phi;\n}\n\n/**\n *\
    \ @brief \u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570(Euler Phi)\n */\n"
  code: "int eulerphi(int x){\n    int phi = x, xx = x;\n    for (int i = 2; i * i\
    \ <= x; ++i) {\n        if (xx % i == 0) {\n            phi -= phi / i;\n    \
    \        while(xx % i == 0) xx /= i;\n        }\n    }\n    if(xx > 1) phi -=\
    \ phi/xx;\n    return phi;\n}\n\n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\u306E\
    \u03C6\u95A2\u6570(Euler Phi)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/eulerphi.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_eulerphi.test.cpp
date: 2026-03-08
documentation_of: math/eulerphi.cpp
layout: document
tags: "\u6570\u5B66"
title: Euler Phi
---

## 説明
Euler の totient function `phi(n)` を 1 点で求める。
`1` 以上の整数 `n` と互いに素な `1..n` の個数を返す。
計算量は `O(sqrt(n))`。

## できること
- `int eulerphi(int x)`
  `phi(x)` を返す

## 使い方
`x >= 1` を仮定する。
素因数分解しながら `phi(n) = n Π (1 - 1/p)` を適用する。
