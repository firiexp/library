---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_binomial_coefficient.test.cpp
    title: test/yosupo_binomial_coefficient.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u524D\u8A08\u7B97\u4ED8\u304D\u7D20\u56E0\u6570\u5206\u89E3\
      (Prime Factorization)"
    links: []
  bundledCode: "#line 1 \"math/primefactor2.cpp\"\nusing uint = uint32_t;\n\ntemplate<typename\
    \ T>\nstruct ExactDiv {\n    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n)\
    \ : t(T(-1) / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T n) {\n        T\
    \ x = n;\n        for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n        return\
    \ x;\n    }\n    bool divide(T n) const {\n        if(val == 2) return !(n & 1);\n\
    \        return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime(int\
    \ n){\n    if(n <= 1) return vector<ExactDiv<uint>>();\n    vector<bool> is_prime(n+1,\
    \ true);\n    vector<ExactDiv<uint>> prime;\n    is_prime[0] = is_prime[1] = false;\n\
    \    for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(32000);\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n){\n    vector<T> res;\n    for (auto &&i : primes)\
    \ {\n        while (i.divide(n)){\n            res.emplace_back(i.val);\n    \
    \        n /= i.val;\n        }\n    }\n    if(n != 1) res.emplace_back(n);\n\
    \    return res;\n}\n\n/**\n * @brief \u524D\u8A08\u7B97\u4ED8\u304D\u7D20\u56E0\
    \u6570\u5206\u89E3(Prime Factorization)\n */\n"
  code: "using uint = uint32_t;\n\ntemplate<typename T>\nstruct ExactDiv {\n    T\
    \ t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n))\
    \ , val(n) {};\n    T mul_inv(T n) {\n        T x = n;\n        for (int i = 0;\
    \ i < 5; ++i) x *= 2 - n * x;\n        return x;\n    }\n    bool divide(T n)\
    \ const {\n        if(val == 2) return !(n & 1);\n        return n * this->i <=\
    \ this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime(int n){\n    if(n <=\
    \ 1) return vector<ExactDiv<uint>>();\n    vector<bool> is_prime(n+1, true);\n\
    \    vector<ExactDiv<uint>> prime;\n    is_prime[0] = is_prime[1] = false;\n \
    \   for (int i = 2; i <= n; ++i) {\n        if(is_prime[i]) prime.emplace_back(i);\n\
    \        for (auto &&j : prime){\n            if(i*j.val > n) break;\n       \
    \     is_prime[i*j.val] = false;\n            if(j.divide(i)) break;\n       \
    \ }\n    }\n    return prime;\n}\nconst auto primes = get_prime(32000);\n\ntemplate<class\
    \ T>\nvector<T> prime_factor(T n){\n    vector<T> res;\n    for (auto &&i : primes)\
    \ {\n        while (i.divide(n)){\n            res.emplace_back(i.val);\n    \
    \        n /= i.val;\n        }\n    }\n    if(n != 1) res.emplace_back(n);\n\
    \    return res;\n}\n\n/**\n * @brief \u524D\u8A08\u7B97\u4ED8\u304D\u7D20\u56E0\
    \u6570\u5206\u89E3(Prime Factorization)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/primefactor2.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_binomial_coefficient.test.cpp
date: 2026-03-08
documentation_of: math/primefactor2.cpp
layout: document
tags: "\u6570\u5B66"
title: primefactor2
---

## 説明
前計算した小さい素数列を使って整数を素因数分解する。
除算判定に `ExactDiv` を使うので、通常の `%` より軽い。

## できること
- `vector<T> prime_factor(T n)`
  `n` の素因数を昇順で列挙して返す。重複も含む

## 使い方
`const auto primes = get_prime(32000);` を前提に、`32bit` 付近の整数を分解する用途を想定している。
`n` に大きい素因数が最後に 1 個だけ残った場合もそのまま返す。
