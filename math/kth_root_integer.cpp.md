---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_kth_root_integer.test.cpp
    title: test/yosupo_kth_root_integer.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u6574\u6570k\u4E57\u6839(K-th Root Integer)"
    links: []
  bundledCode: "#line 1 \"math/kth_root_integer.cpp\"\nusing ull = unsigned long long;\n\
    \nbool kth_root_integer_leq(ull x, int k, ull a) {\n    __uint128_t p = 1;\n \
    \   for (int i = 0; i < k; ++i) {\n        p *= x;\n        if (p > a) return\
    \ false;\n    }\n    return true;\n}\n\null kth_root_integer(ull a, int k) {\n\
    \    if (k == 1 || a <= 1) return a;\n    ull ng = min<ull>(a, (1ULL << 32)) +\
    \ 1, ok = 0;\n    while (ng - ok > 1) {\n        ull mid = ok + (ng - ok) / 2;\n\
    \        if (kth_root_integer_leq(mid, k, a)) ok = mid;\n        else ng = mid;\n\
    \    }\n    return ok;\n}\n\n/**\n * @brief \u6574\u6570k\u4E57\u6839(K-th Root\
    \ Integer)\n */\n"
  code: "using ull = unsigned long long;\n\nbool kth_root_integer_leq(ull x, int k,\
    \ ull a) {\n    __uint128_t p = 1;\n    for (int i = 0; i < k; ++i) {\n      \
    \  p *= x;\n        if (p > a) return false;\n    }\n    return true;\n}\n\null\
    \ kth_root_integer(ull a, int k) {\n    if (k == 1 || a <= 1) return a;\n    ull\
    \ ng = min<ull>(a, (1ULL << 32)) + 1, ok = 0;\n    while (ng - ok > 1) {\n   \
    \     ull mid = ok + (ng - ok) / 2;\n        if (kth_root_integer_leq(mid, k,\
    \ a)) ok = mid;\n        else ng = mid;\n    }\n    return ok;\n}\n\n/**\n * @brief\
    \ \u6574\u6570k\u4E57\u6839(K-th Root Integer)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/kth_root_integer.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_kth_root_integer.test.cpp
date: 2026-03-08
documentation_of: math/kth_root_integer.cpp
layout: post
tags: "\u6570\u5B66"
title: Kth Root Integer
---

## 説明
`floor(a^(1/k))` を求める。
二分探索で整数解を絞る。

## できること
- `ull kth_root_integer(ull a, int k)`
  `floor(a^(1/k))` を返す

## 使い方
`0 <= a < 2^64`, `1 <= k` を想定する。
内部では `x^k <= a` を `__int128` で判定する。
