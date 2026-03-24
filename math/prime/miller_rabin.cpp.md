---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/prime/primefactor_ll.cpp
    title: "\u7D20\u56E0\u6570\u5206\u89E3(Pollard Rho)"
  - icon: ':heavy_check_mark:'
    path: math/prime/primitive_root.cpp
    title: "\u539F\u59CB\u6839(Primitive Root)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_factorize.test.cpp
    title: test/yosupo_factorize.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_primality_test.test.cpp
    title: test/yosupo_primality_test.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_primitive_root.test.cpp
    title: test/yosupo_primitive_root.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Miller-Rabin\u7D20\u6570\u5224\u5B9A"
    links: []
  bundledCode: "#line 1 \"math/prime/miller_rabin.cpp\"\nusing u128 = __uint128_t;\n\
    \nstruct mod64 {\n    unsigned long long n;\n    static unsigned long long mod,\
    \ inv, r2;\n    mod64() : n(0) {}\n    mod64(unsigned long long x) : n(init(x))\
    \ {}\n    static unsigned long long init(unsigned long long w) {\n        return\
    \ reduce(u128(w) * r2);\n    }\n    static void set_mod(unsigned long long m)\
    \ {\n        mod = inv = m;\n        for (int i = 0; i < 5; ++i) inv *= 2 - inv\
    \ * m;\n        r2 = -u128(m) % m;\n    }\n    static unsigned long long reduce(u128\
    \ x) {\n        unsigned long long y =\n            static_cast<unsigned long\
    \ long>(x >> 64)\n            - static_cast<unsigned long long>((u128(static_cast<unsigned\
    \ long long>(x) * inv) * mod) >> 64);\n        return (long long)y < 0 ? y + mod\
    \ : y;\n    }\n    mod64& operator*=(mod64 x) {\n        n = reduce(u128(n) *\
    \ x.n);\n        return *this;\n    }\n    mod64 operator*(mod64 x) const {\n\
    \        return mod64(*this) *= x;\n    }\n    mod64& operator+=(mod64 x) {\n\
    \        n += x.n - mod;\n        if((long long)n < 0) n += mod;\n        return\
    \ *this;\n    }\n    mod64 operator+(mod64 x) const {\n        return mod64(*this)\
    \ += x;\n    }\n    unsigned long long val() const {\n        return reduce(n);\n\
    \    }\n};\n\nunsigned long long mod64::mod, mod64::inv, mod64::r2;\n\nbool suspect(unsigned\
    \ long long a, unsigned long long s, unsigned long long d, unsigned long long\
    \ n){\n    if(mod64::mod != n) mod64::set_mod(n);\n    mod64 x(1), xx(a), one(1),\
    \ minusone(n - 1);\n    while(d > 0){\n        if(d & 1) x *= xx;\n        xx\
    \ *= xx;\n        d >>= 1;\n    }\n    if (x.n == one.n) return true;\n    for\
    \ (unsigned long long r = 0; r < s; ++r) {\n        if(x.n == minusone.n) return\
    \ true;\n        x *= x;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool\
    \ miller_rabin(T m){\n    unsigned long long n = m;\n    if (n <= 1 || (n > 2\
    \ && n % 2 == 0)) return false;\n    if (n == 2 || n == 3 || n == 5 || n == 7)\
    \ return true;\n    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;\n\
    \    unsigned long long d = n - 1, s = 0;\n    while (!(d & 1)) { ++s; d >>= 1;\
    \ }\n    static constexpr unsigned long long small[] = {2, 7, 61};\n    static\
    \ constexpr unsigned long long large[] = {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022};\n    if(n < 4759123141ULL) {\n        for (auto p : small) {\n\
    \            if(p >= n) break;\n            if(!suspect(p, s, d, n)) return false;\n\
    \        }\n    } else {\n        for (auto p : large) {\n            if(p >=\
    \ n) break;\n            if(!suspect(p, s, d, n)) return false;\n        }\n \
    \   }\n    return true;\n}\n\n/**\n * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\
    \n */\n"
  code: "using u128 = __uint128_t;\n\nstruct mod64 {\n    unsigned long long n;\n\
    \    static unsigned long long mod, inv, r2;\n    mod64() : n(0) {}\n    mod64(unsigned\
    \ long long x) : n(init(x)) {}\n    static unsigned long long init(unsigned long\
    \ long w) {\n        return reduce(u128(w) * r2);\n    }\n    static void set_mod(unsigned\
    \ long long m) {\n        mod = inv = m;\n        for (int i = 0; i < 5; ++i)\
    \ inv *= 2 - inv * m;\n        r2 = -u128(m) % m;\n    }\n    static unsigned\
    \ long long reduce(u128 x) {\n        unsigned long long y =\n            static_cast<unsigned\
    \ long long>(x >> 64)\n            - static_cast<unsigned long long>((u128(static_cast<unsigned\
    \ long long>(x) * inv) * mod) >> 64);\n        return (long long)y < 0 ? y + mod\
    \ : y;\n    }\n    mod64& operator*=(mod64 x) {\n        n = reduce(u128(n) *\
    \ x.n);\n        return *this;\n    }\n    mod64 operator*(mod64 x) const {\n\
    \        return mod64(*this) *= x;\n    }\n    mod64& operator+=(mod64 x) {\n\
    \        n += x.n - mod;\n        if((long long)n < 0) n += mod;\n        return\
    \ *this;\n    }\n    mod64 operator+(mod64 x) const {\n        return mod64(*this)\
    \ += x;\n    }\n    unsigned long long val() const {\n        return reduce(n);\n\
    \    }\n};\n\nunsigned long long mod64::mod, mod64::inv, mod64::r2;\n\nbool suspect(unsigned\
    \ long long a, unsigned long long s, unsigned long long d, unsigned long long\
    \ n){\n    if(mod64::mod != n) mod64::set_mod(n);\n    mod64 x(1), xx(a), one(1),\
    \ minusone(n - 1);\n    while(d > 0){\n        if(d & 1) x *= xx;\n        xx\
    \ *= xx;\n        d >>= 1;\n    }\n    if (x.n == one.n) return true;\n    for\
    \ (unsigned long long r = 0; r < s; ++r) {\n        if(x.n == minusone.n) return\
    \ true;\n        x *= x;\n    }\n    return false;\n}\n\ntemplate<class T>\nbool\
    \ miller_rabin(T m){\n    unsigned long long n = m;\n    if (n <= 1 || (n > 2\
    \ && n % 2 == 0)) return false;\n    if (n == 2 || n == 3 || n == 5 || n == 7)\
    \ return true;\n    if (n % 3 == 0 || n % 5 == 0 || n % 7 == 0) return false;\n\
    \    unsigned long long d = n - 1, s = 0;\n    while (!(d & 1)) { ++s; d >>= 1;\
    \ }\n    static constexpr unsigned long long small[] = {2, 7, 61};\n    static\
    \ constexpr unsigned long long large[] = {2, 325, 9375, 28178, 450775, 9780504,\
    \ 1795265022};\n    if(n < 4759123141ULL) {\n        for (auto p : small) {\n\
    \            if(p >= n) break;\n            if(!suspect(p, s, d, n)) return false;\n\
    \        }\n    } else {\n        for (auto p : large) {\n            if(p >=\
    \ n) break;\n            if(!suspect(p, s, d, n)) return false;\n        }\n \
    \   }\n    return true;\n}\n\n/**\n * @brief Miller-Rabin\u7D20\u6570\u5224\u5B9A\
    \n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime/miller_rabin.cpp
  requiredBy:
  - math/prime/primefactor_ll.cpp
  - math/prime/primitive_root.cpp
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_primality_test.test.cpp
  - test/yosupo_factorize.test.cpp
  - test/yosupo_primitive_root.test.cpp
date: 2018-04-28
documentation_of: math/prime/miller_rabin.cpp
layout: document
tags: "\u6570\u5B66"
title: "Miller-Rabin\u7D20\u6570\u5224\u5B9A"
---

## 説明
Montgomery 乗算を使った `64bit` 整数向けの Miller-Rabin 素数判定。
既知の基底集合を使うので、`uint64_t` 範囲では決定的に判定できる。

## できること
- `bool miller_rabin(T n)`
  `n` が素数なら `true`、合成数なら `false`

## 使い方
整数型 `T` を渡して呼ぶだけでよい。
`n <= 1` と偶数は先に弾き、`64bit` 整数では既知の基底で判定する。

## 実装上の補足
乗算は Montgomery 形式で処理する。
単純な `%` ベース実装より定数倍が軽い。
