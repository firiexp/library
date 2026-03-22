---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_discrete_logarithm_mod.test.cpp
    title: test/yosupo_discrete_logarithm_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u96E2\u6563\u5BFE\u6570(Discrete Logarithm)"
    links: []
  bundledCode: "#line 1 \"math/discrete_logarithm.cpp\"\nlong long discrete_logarithm_mul(long\
    \ long a, long long b, long long mod) {\n    using i128 = __int128_t;\n    return\
    \ (long long)((i128)a * b % mod);\n}\n\nlong long discrete_logarithm(long long\
    \ x, long long y, long long mod) {\n    if (mod == 1) return 0;\n    x %= mod;\n\
    \    y %= mod;\n    if (x < 0) x += mod;\n    if (y < 0) y += mod;\n    if (y\
    \ == 1) return 0;\n\n    long long add = 0;\n    long long k = 1 % mod;\n    while\
    \ (true) {\n        long long g = std::gcd(x, mod);\n        if (g == 1) break;\n\
    \        if (y == k) return add;\n        if (y % g != 0) return -1;\n       \
    \ y /= g;\n        mod /= g;\n        ++add;\n        k = discrete_logarithm_mul(k,\
    \ x / g, mod);\n    }\n\n    long long n = (long long)std::sqrt((long double)mod)\
    \ + 1;\n    std::unordered_map<long long, long long> baby;\n    baby.reserve((size_t)n\
    \ * 2 + 1);\n\n    long long giant = 1;\n    for (long long i = 0; i < n; ++i)\
    \ {\n        giant = discrete_logarithm_mul(giant, x, mod);\n    }\n\n    long\
    \ long cur = k;\n    for (long long p = 1; p <= n; ++p) {\n        cur = discrete_logarithm_mul(cur,\
    \ giant, mod);\n        if (!baby.count(cur)) baby[cur] = p;\n    }\n\n    long\
    \ long ans = std::numeric_limits<long long>::max();\n    cur = y;\n    for (long\
    \ long q = 0; q <= n; ++q) {\n        auto it = baby.find(cur);\n        if (it\
    \ != baby.end()) {\n            long long cand = it->second * n - q + add;\n \
    \           if (cand < ans) ans = cand;\n        }\n        cur = discrete_logarithm_mul(cur,\
    \ x, mod);\n    }\n    return ans == std::numeric_limits<long long>::max() ? -1\
    \ : ans;\n}\n\n/**\n * @brief \u96E2\u6563\u5BFE\u6570(Discrete Logarithm)\n */\n"
  code: "long long discrete_logarithm_mul(long long a, long long b, long long mod)\
    \ {\n    using i128 = __int128_t;\n    return (long long)((i128)a * b % mod);\n\
    }\n\nlong long discrete_logarithm(long long x, long long y, long long mod) {\n\
    \    if (mod == 1) return 0;\n    x %= mod;\n    y %= mod;\n    if (x < 0) x +=\
    \ mod;\n    if (y < 0) y += mod;\n    if (y == 1) return 0;\n\n    long long add\
    \ = 0;\n    long long k = 1 % mod;\n    while (true) {\n        long long g =\
    \ std::gcd(x, mod);\n        if (g == 1) break;\n        if (y == k) return add;\n\
    \        if (y % g != 0) return -1;\n        y /= g;\n        mod /= g;\n    \
    \    ++add;\n        k = discrete_logarithm_mul(k, x / g, mod);\n    }\n\n   \
    \ long long n = (long long)std::sqrt((long double)mod) + 1;\n    std::unordered_map<long\
    \ long, long long> baby;\n    baby.reserve((size_t)n * 2 + 1);\n\n    long long\
    \ giant = 1;\n    for (long long i = 0; i < n; ++i) {\n        giant = discrete_logarithm_mul(giant,\
    \ x, mod);\n    }\n\n    long long cur = k;\n    for (long long p = 1; p <= n;\
    \ ++p) {\n        cur = discrete_logarithm_mul(cur, giant, mod);\n        if (!baby.count(cur))\
    \ baby[cur] = p;\n    }\n\n    long long ans = std::numeric_limits<long long>::max();\n\
    \    cur = y;\n    for (long long q = 0; q <= n; ++q) {\n        auto it = baby.find(cur);\n\
    \        if (it != baby.end()) {\n            long long cand = it->second * n\
    \ - q + add;\n            if (cand < ans) ans = cand;\n        }\n        cur\
    \ = discrete_logarithm_mul(cur, x, mod);\n    }\n    return ans == std::numeric_limits<long\
    \ long>::max() ? -1 : ans;\n}\n\n/**\n * @brief \u96E2\u6563\u5BFE\u6570(Discrete\
    \ Logarithm)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/discrete_logarithm.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_discrete_logarithm_mod.test.cpp
date: 2026-03-08
documentation_of: math/discrete_logarithm.cpp
layout: document
tags: "\u6570\u5B66"
title: Discrete Logarithm
---

## 説明
`x^k ≡ y (mod m)` を満たす最小の非負整数 `k` を求める。
解がなければ `-1` を返す。
非互いに素な場合も含めて extended BSGS で処理する。

## できること
- `long long discrete_logarithm(long long x, long long y, long long mod)`
  `x^k ≡ y (mod mod)` を満たす最小の `k` を返す。存在しなければ `-1`

## 使い方
`mod >= 1` を想定する。
計算量はおおむね $O(sqrt(mod))$。
