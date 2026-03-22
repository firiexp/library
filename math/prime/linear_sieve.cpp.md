---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  - icon: ':warning:'
    path: math/prime/eulerphi_all.cpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u03C6\u95A2\u6570\u30C6\u30FC\u30D6\u30EB\
      (Euler Phi Table)"
  - icon: ':warning:'
    path: math/prime/get_min_factor.cpp
    title: Get Min Factor
  - icon: ':heavy_check_mark:'
    path: math/prime/get_prime.cpp
    title: "\u7D20\u6570\u5217\u6319"
  - icon: ':heavy_check_mark:'
    path: math/prime/get_prime2.cpp
    title: "\u9AD8\u901F\u7D20\u6570\u5217\u6319(ExactDiv)"
  - icon: ':warning:'
    path: math/prime/mobius_all.cpp
    title: "\u30E1\u30D3\u30A6\u30B9\u95A2\u6570\u30C6\u30FC\u30D6\u30EB(Mobius Table)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_1_c_get_prime.test.cpp
    title: test/aoj_alds1_1_c_get_prime.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_1_c_get_prime2.test.cpp
    title: test/aoj_alds1_1_c_get_prime2.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
    links: []
  bundledCode: "#line 1 \"math/prime/linear_sieve.cpp\"\n\n\n\nstruct LinearSieve\
    \ {\n    int n;\n    vector<int> primes;\n    vector<int> min_factor;\n    vector<int>\
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
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_LINEAR_SIEVE_CPP\n#define FIRIEXP_LIBRARY_MATH_LINEAR_SIEVE_CPP\n\
    \nstruct LinearSieve {\n    int n;\n    vector<int> primes;\n    vector<int> min_factor;\n\
    \    vector<int> phi;\n    vector<int> mobius;\n    vector<bool> prime_table;\n\
    \n    explicit LinearSieve(int n, bool need_min_factor = false, bool need_phi\
    \ = false, bool need_mobius = false)\n        : n(n < 0 ? 0 : n),\n          min_factor(need_min_factor\
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
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: math/prime/linear_sieve.cpp
  requiredBy:
  - math/prime/get_min_factor.cpp
  - math/prime/mobius_all.cpp
  - math/prime/eulerphi_all.cpp
  - math/prime/get_prime2.cpp
  - math/prime/get_prime.cpp
  - math/powk_all.cpp
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_1_c_get_prime.test.cpp
  - test/aoj_alds1_1_c_get_prime2.test.cpp
date: 2026-03-12
documentation_of: math/prime/linear_sieve.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
---

## 説明
`0..n` の素数列挙を線形篩で前計算する。
必要なら最小素因数、`phi`、`mu` も同時に持てる。
計算量は $O(n)$。

## できること
- `LinearSieve sieve(int n, bool need_min_factor = false, bool need_phi = false, bool need_mobius = false)`
  `0..n` を前計算する
- `vector<int> primes`
  `n` 以下の素数を昇順で持つ
- `vector<int> min_factor`
  `need_min_factor = true` のときだけ埋まる。`min_factor[x]` に `x` の最小素因数を持つ。`min_factor[1] = 1`
- `vector<int> phi`
  `need_phi = true` のときだけ埋まる。`phi[x] = φ(x)` を持つ。`phi[0] = 0`, `phi[1] = 1`
- `vector<int> mobius`
  `need_mobius = true` のときだけ埋まる。`mobius[x] = μ(x)` を持つ。`mobius[0] = 0`, `mobius[1] = 1`
- `bool is_prime(int x)`
  `x` が素数なら `true`、範囲外または合成数なら `false`

## 使い方
用途ごとに配列を直接読む。

```cpp
LinearSieve sieve(n);
auto primes = sieve.primes;

LinearSieve table(n, true, true, true);
int p = table.min_factor[x];
int phi_x = table.phi[x];
int mu_x = table.mobius[x];
```

## 実装上の補足
`get_prime.cpp`, `get_min_factor.cpp`, `eulerphi_all.cpp`, `mobius_all.cpp`, `get_prime2.cpp` はこの前計算の薄い wrapper になっている。
