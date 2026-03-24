---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_sqrt_mod.test.cpp
    title: test/yosupo_sqrt_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5E73\u65B9\u6839 (mod p)"
    links: []
  bundledCode: "#line 1 \"math/mod_sqrt.cpp\"\nlong long mod_pow(long long a, long\
    \ long n, long long mod) {\n    long long r = 1;\n    while (n) {\n        if\
    \ (n & 1) r = (unsigned long long)r * a % mod;\n        a = (unsigned long long)a\
    \ * a % mod;\n        n >>= 1;\n    }\n    return r;\n}\n\nlong long mod_sqrt(long\
    \ long a, long long p) {\n    a %= p;\n    if (a < 0) a += p;\n    if (a == 0\
    \ || p == 2) return a;\n    if (mod_pow(a, (p - 1) >> 1, p) != 1) return -1;\n\
    \    if (p % 4 == 3) return mod_pow(a, (p + 1) >> 2, p);\n\n    long long q =\
    \ p - 1;\n    int s = 0;\n    while ((q & 1) == 0) {\n        ++s;\n        q\
    \ >>= 1;\n    }\n    long long z = 2;\n    while (mod_pow(z, (p - 1) >> 1, p)\
    \ == 1) ++z;\n    long long c = mod_pow(z, q, p);\n    long long t = mod_pow(a,\
    \ q, p);\n    long long r = mod_pow(a, (q + 1) >> 1, p);\n    int m = s;\n   \
    \ while (t != 1) {\n        int i = 1;\n        long long tt = (unsigned long\
    \ long)t * t % p;\n        while (i < m && tt != 1) {\n            tt = (unsigned\
    \ long long)tt * tt % p;\n            ++i;\n        }\n        long long b = mod_pow(c,\
    \ 1LL << (m - i - 1), p);\n        r = (unsigned long long)r * b % p;\n      \
    \  c = (unsigned long long)b * b % p;\n        t = (unsigned long long)t * c %\
    \ p;\n        m = i;\n    }\n    return r;\n}\n\n/**\n * @brief \u5E73\u65B9\u6839\
    \ (mod p)\n */\n"
  code: "long long mod_pow(long long a, long long n, long long mod) {\n    long long\
    \ r = 1;\n    while (n) {\n        if (n & 1) r = (unsigned long long)r * a %\
    \ mod;\n        a = (unsigned long long)a * a % mod;\n        n >>= 1;\n    }\n\
    \    return r;\n}\n\nlong long mod_sqrt(long long a, long long p) {\n    a %=\
    \ p;\n    if (a < 0) a += p;\n    if (a == 0 || p == 2) return a;\n    if (mod_pow(a,\
    \ (p - 1) >> 1, p) != 1) return -1;\n    if (p % 4 == 3) return mod_pow(a, (p\
    \ + 1) >> 2, p);\n\n    long long q = p - 1;\n    int s = 0;\n    while ((q &\
    \ 1) == 0) {\n        ++s;\n        q >>= 1;\n    }\n    long long z = 2;\n  \
    \  while (mod_pow(z, (p - 1) >> 1, p) == 1) ++z;\n    long long c = mod_pow(z,\
    \ q, p);\n    long long t = mod_pow(a, q, p);\n    long long r = mod_pow(a, (q\
    \ + 1) >> 1, p);\n    int m = s;\n    while (t != 1) {\n        int i = 1;\n \
    \       long long tt = (unsigned long long)t * t % p;\n        while (i < m &&\
    \ tt != 1) {\n            tt = (unsigned long long)tt * tt % p;\n            ++i;\n\
    \        }\n        long long b = mod_pow(c, 1LL << (m - i - 1), p);\n       \
    \ r = (unsigned long long)r * b % p;\n        c = (unsigned long long)b * b %\
    \ p;\n        t = (unsigned long long)t * c % p;\n        m = i;\n    }\n    return\
    \ r;\n}\n\n/**\n * @brief \u5E73\u65B9\u6839 (mod p)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/mod_sqrt.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_sqrt_mod.test.cpp
date: 2026-03-08
documentation_of: math/mod_sqrt.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u5E73\u65B9\u6839 (mod p)"
---

## 説明
素数 mod で平方根を 1 つ求める。
存在しなければ `-1` を返す。
Tonelli-Shanks で計算する。

## できること
- `long long mod_sqrt(long long a, long long p)`
  `x^2 ≡ a (mod p)` を満たす `x` を 1 つ返す。存在しなければ `-1`

## 使い方
`p` は素数を仮定する。
`0 <= x < p` の解を返す。
