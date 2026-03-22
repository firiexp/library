---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime/linear_sieve.cpp
    title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_1_c_get_prime.test.cpp
    title: test/aoj_alds1_1_c_get_prime.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/prime/get_prime.cpp\"\
    \n\nvector<int> get_prime(int n) {\n    return LinearSieve(n).primes;\n}\n"
  code: "#include \"linear_sieve.cpp\"\n\nvector<int> get_prime(int n) {\n    return\
    \ LinearSieve(n).primes;\n}\n"
  dependsOn:
  - math/prime/linear_sieve.cpp
  isVerificationFile: false
  path: math/prime/get_prime.cpp
  requiredBy: []
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_1_c_get_prime.test.cpp
date: 2026-03-12
documentation_of: math/prime/get_prime.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u7D20\u6570\u5217\u6319"
---

## 説明
`n` 以下の素数を線形篩で列挙する。
計算量は $O(n)$。

## できること
- `vector<int> get_prime(int n)`
  `n` 以下の素数を昇順で返す。`n <= 1` なら空

## 使い方
`LinearSieve` の素数列挙だけを取り出す薄い wrapper である。

```cpp
auto primes = get_prime(n);
```
