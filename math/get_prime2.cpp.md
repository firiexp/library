---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/linear_sieve.cpp
    title: "\u7DDA\u5F62\u7BE9(Linear Sieve)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_enumerate_primes_get_prime2.test.cpp
    title: test/yosupo_enumerate_primes_get_prime2.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/get_prime2.cpp\"\
    \n\ntemplate<typename T>\nstruct ExactDiv {\n    T t, i, val;\n    ExactDiv()\
    \ {}\n    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n)) , val(n) {};\n    T mul_inv(T\
    \ n) {\n        T x = n;\n        for (int i = 0; i < 5; ++i) x *= 2 - n * x;\n\
    \        return x;\n    }\n    bool divide(T n) const {\n        if(val == 2)\
    \ return !(n & 1);\n        return n * this->i <= this->t;\n    }\n};\n\nvector<ExactDiv<uint>>\
    \ get_prime_exact_div(int n) {\n    vector<ExactDiv<uint>> res;\n    auto primes\
    \ = LinearSieve(n).primes;\n    res.reserve(primes.size());\n    for (auto &&p\
    \ : primes) res.emplace_back((uint)p);\n    return res;\n}\nconst auto primes\
    \ = get_prime_exact_div(32000);\n"
  code: "#include \"linear_sieve.cpp\"\n\ntemplate<typename T>\nstruct ExactDiv {\n\
    \    T t, i, val;\n    ExactDiv() {}\n    ExactDiv(T n) : t(T(-1) / n), i(mul_inv(n))\
    \ , val(n) {};\n    T mul_inv(T n) {\n        T x = n;\n        for (int i = 0;\
    \ i < 5; ++i) x *= 2 - n * x;\n        return x;\n    }\n    bool divide(T n)\
    \ const {\n        if(val == 2) return !(n & 1);\n        return n * this->i <=\
    \ this->t;\n    }\n};\n\nvector<ExactDiv<uint>> get_prime_exact_div(int n) {\n\
    \    vector<ExactDiv<uint>> res;\n    auto primes = LinearSieve(n).primes;\n \
    \   res.reserve(primes.size());\n    for (auto &&p : primes) res.emplace_back((uint)p);\n\
    \    return res;\n}\nconst auto primes = get_prime_exact_div(32000);\n"
  dependsOn:
  - math/linear_sieve.cpp
  isVerificationFile: false
  path: math/get_prime2.cpp
  requiredBy: []
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_enumerate_primes_get_prime2.test.cpp
date: 2026-03-08
documentation_of: math/get_prime2.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u9AD8\u901F\u7D20\u6570\u5217\u6319(ExactDiv)"
---

## 説明
線形篩で `n` 以下の素数を列挙する。
素数は `ExactDiv<uint>` として保持し、除算判定を高速化できる形で返す。
計算量は $O(n)$。

## できること
- `vector<ExactDiv<uint>> get_prime_exact_div(int n)`
  `n` 以下の素数を返す。`n <= 1` なら空
- `bool ExactDiv<T>::divide(T x) const`
  `x` がこの素数で割り切れるかを返す

## 使い方
`LinearSieve` の素数列挙を `ExactDiv<uint>` に詰め直した wrapper である。
返り値の各要素は素数値を `val` に持つ。
試し割りを大量に行うコードでは `x % p == 0` の代わりに `p.divide(x)` を使える。
