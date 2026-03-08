---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_root_integer.test.cpp
    title: test/yosupo_kth_root_integer.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/kth_root_integer.md
    document_title: K-th root integer
    links: []
  bundledCode: "#line 1 \"math/kth_root_integer.cpp\"\nusing ull = unsigned long long;\n\
    \nbool kth_root_integer_leq(ull x, int k, ull a) {\n    __uint128_t p = 1;\n \
    \   for (int i = 0; i < k; ++i) {\n        p *= x;\n        if (p > a) return\
    \ false;\n    }\n    return true;\n}\n\null kth_root_integer(ull a, int k) {\n\
    \    if (k == 1 || a <= 1) return a;\n    ull ng = min<ull>(a, (1ULL << 32)) +\
    \ 1, ok = 0;\n    while (ng - ok > 1) {\n        ull mid = ok + (ng - ok) / 2;\n\
    \        if (kth_root_integer_leq(mid, k, a)) ok = mid;\n        else ng = mid;\n\
    \    }\n    return ok;\n}\n\n/**\n * @brief K-th root integer\n * @docs _md/kth_root_integer.md\n\
    \ */\n"
  code: "using ull = unsigned long long;\n\nbool kth_root_integer_leq(ull x, int k,\
    \ ull a) {\n    __uint128_t p = 1;\n    for (int i = 0; i < k; ++i) {\n      \
    \  p *= x;\n        if (p > a) return false;\n    }\n    return true;\n}\n\null\
    \ kth_root_integer(ull a, int k) {\n    if (k == 1 || a <= 1) return a;\n    ull\
    \ ng = min<ull>(a, (1ULL << 32)) + 1, ok = 0;\n    while (ng - ok > 1) {\n   \
    \     ull mid = ok + (ng - ok) / 2;\n        if (kth_root_integer_leq(mid, k,\
    \ a)) ok = mid;\n        else ng = mid;\n    }\n    return ok;\n}\n\n/**\n * @brief\
    \ K-th root integer\n * @docs _md/kth_root_integer.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/kth_root_integer.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_kth_root_integer.test.cpp
documentation_of: math/kth_root_integer.cpp
layout: document
redirect_from:
- /library/math/kth_root_integer.cpp
- /library/math/kth_root_integer.cpp.html
title: K-th root integer
---
---
layout: post
title: Kth Root Integer
date: 2026-03-08
category: 数学
tags: 数学
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
