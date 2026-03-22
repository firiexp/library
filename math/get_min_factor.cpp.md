---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/linear_sieve.cpp
    title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    document_title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor\
      \ Table)"
    links: []
  bundledCode: "#line 1 \"math/linear_sieve.cpp\"\n\n\n\nstruct LinearSieve {\n  \
    \  int n;\n    vector<int> primes;\n    vector<int> min_factor;\n    vector<int>\
    \ phi;\n    vector<int> mobius;\n    vector<bool> prime_table;\n\n    explicit\
    \ LinearSieve(int n, bool need_min_factor = false, bool need_phi = false, bool\
    \ need_mobius = false)\n        : n(n < 0 ? 0 : n),\n          min_factor(need_min_factor\
    \ ? this->n + 1 : 0),\n          phi(need_phi ? this->n + 1 : 0),\n          mobius(need_mobius\
    \ ? this->n + 1 : 0),\n          prime_table(need_min_factor ? 0 : this->n + 1,\
    \ true) {\n        if (!prime_table.empty()) {\n            prime_table[0] = false;\n\
    \            if (this->n >= 1) prime_table[1] = false;\n        }\n        if\
    \ (!min_factor.empty() && this->n >= 1) min_factor[1] = 1;\n        if (!phi.empty())\
    \ {\n            phi[0] = 0;\n            if (this->n >= 1) phi[1] = 1;\n    \
    \    }\n        if (!mobius.empty()) {\n            mobius[0] = 0;\n         \
    \   if (this->n >= 1) mobius[1] = 1;\n        }\n        for (int i = 2; i <=\
    \ this->n; ++i) {\n            bool prime = min_factor.empty() ? prime_table[i]\
    \ : min_factor[i] == 0;\n            if (prime) {\n                if (!min_factor.empty())\
    \ min_factor[i] = i;\n                if (!phi.empty()) phi[i] = i - 1;\n    \
    \            if (!mobius.empty()) mobius[i] = -1;\n                primes.emplace_back(i);\n\
    \            }\n            for (auto &&p : primes) {\n                long long\
    \ x = 1LL * i * p;\n                if (x > this->n) break;\n                if\
    \ (!prime_table.empty()) prime_table[x] = false;\n                if (!min_factor.empty())\
    \ min_factor[x] = p;\n                bool same = i % p == 0;\n              \
    \  if (!phi.empty()) phi[x] = same ? phi[i] * p : phi[i] * (p - 1);\n        \
    \        if (!mobius.empty()) mobius[x] = same ? 0 : -mobius[i];\n           \
    \     if (same) break;\n            }\n        }\n    }\n\n    bool is_prime(int\
    \ x) const {\n        if (x < 2 || x > n) return false;\n        if (!min_factor.empty())\
    \ return min_factor[x] == x;\n        return prime_table[x];\n    }\n};\n\n/**\n\
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/get_min_factor.cpp\"\
    \n\nvector<int> get_min_factor(int n) {\n    return LinearSieve(n, true).min_factor;\n\
    }\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min\
    \ Factor Table)\n */\n"
  code: "#include \"linear_sieve.cpp\"\n\nvector<int> get_min_factor(int n) {\n  \
    \  return LinearSieve(n, true).min_factor;\n}\n\n/**\n * @brief \u6700\u5C0F\u7D20\
    \u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)\n */\n"
  dependsOn:
  - math/linear_sieve.cpp
  isVerificationFile: false
  path: math/get_min_factor.cpp
  requiredBy:
  - math/powk_all.cpp
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
date: 2026-03-08
documentation_of: math/get_min_factor.cpp
layout: document
tags: "\u6570\u5B66"
title: Get Min Factor
---

## 説明
`0..n` の最小素因数を線形篩で求める。

## できること
- `vector<int> get_min_factor(int n)`
  `min_factor[x]` に `x` の最小素因数を入れた長さ `n + 1` の配列を返す。`min_factor[0] = 0`, `min_factor[1] = 1`

## 使い方
`x >= 2` の素因数分解は `x = x / min_factor[x]` を繰り返せばよい。
素数 `p` では `min_factor[p] = p` になる。

## 実装上の補足
前計算は $O(n)$、各クエリは素因数の個数ぶんだけ進む。
単発クエリには重いが、同じ上限以下を何度も分解する用途に向く。
