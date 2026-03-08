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
    document_title: "\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570\u30C6\u30FC\u30D6\
      \u30EB(Euler Phi Table)"
    links: []
  bundledCode: "#line 1 \"math/eulerphi_all.cpp\"\nvector<int> eulerphi_all(int M){\n\
    \    vector<int> phi(M);\n    vector<bool> isprime(M);\n    for (int i = 0; i\
    \ < M; ++i) {\n        phi[i] = i;\n        isprime[i] = 1;\n    }\n    for (int\
    \ i = 2; i < M; ++i) {\n        if(isprime[i]){\n            for (int j = i; j\
    \ < M; j += i) {\n                phi[j] -= phi[j]/i;\n                isprime[j]\
    \ = 0;\n            }\n            isprime[i] = 1;\n        }\n    }\n    return\
    \ phi;\n}\n\n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570\u30C6\
    \u30FC\u30D6\u30EB(Euler Phi Table)\n */\n"
  code: "vector<int> eulerphi_all(int M){\n    vector<int> phi(M);\n    vector<bool>\
    \ isprime(M);\n    for (int i = 0; i < M; ++i) {\n        phi[i] = i;\n      \
    \  isprime[i] = 1;\n    }\n    for (int i = 2; i < M; ++i) {\n        if(isprime[i]){\n\
    \            for (int j = i; j < M; j += i) {\n                phi[j] -= phi[j]/i;\n\
    \                isprime[j] = 0;\n            }\n            isprime[i] = 1;\n\
    \        }\n    }\n    return phi;\n}\n\n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\
    \u306E\u03C6\u95A2\u6570\u30C6\u30FC\u30D6\u30EB(Euler Phi Table)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/eulerphi_all.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_eulerphi.test.cpp
date: 2026-03-08
documentation_of: math/eulerphi_all.cpp
layout: document
tags: "\u6570\u5B66"
title: Euler Phi All
---

## 説明
`0..M-1` の Euler の totient function をまとめて求める。
篩で各素数の倍数に `phi[j] -= phi[j] / p` を入れる。
計算量は `O(M log log M)`。

## できること
- `vector<int> eulerphi_all(int M)`
  `phi[i] = phi(i)` を満たす長さ `M` の配列を返す

## 使い方
`phi[0] = 0`, `phi[1] = 1` になる。
前計算して prefix sum を取れば totient の総和にも使える。
