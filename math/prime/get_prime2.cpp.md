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
    path: test/aoj_alds1_1_c_get_prime2.test.cpp
    title: test/aoj_alds1_1_c_get_prime2.test.cpp
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
    \   if (this->n >= 1) mobius[1] = 1;\n        }\n        if (need_min_factor)\
    \ {\n            if (need_phi) {\n                if (need_mobius) build<true,\
    \ true, true>();\n                else build<true, true, false>();\n         \
    \   } else {\n                if (need_mobius) build<true, false, true>();\n \
    \               else build<true, false, false>();\n            }\n        } else\
    \ {\n            if (need_phi) {\n                if (need_mobius) build<false,\
    \ true, true>();\n                else build<false, true, false>();\n        \
    \    } else {\n                if (need_mobius) build<false, false, true>();\n\
    \                else build<false, false, false>();\n            }\n        }\n\
    \    }\n\n    bool is_prime(int x) const {\n        if (x < 2 || x > n) return\
    \ false;\n        if (!min_factor.empty()) return min_factor[x] == x;\n      \
    \  return prime_table[x];\n    }\n\nprivate:\n    template<bool NeedMinFactor,\
    \ bool NeedPhi, bool NeedMobius>\n    void build() {\n        for (int i = 2;\
    \ i <= n; ++i) {\n            bool prime = NeedMinFactor ? min_factor[i] == 0\
    \ : prime_table[i];\n            if (prime) {\n                if constexpr (NeedMinFactor)\
    \ min_factor[i] = i;\n                if constexpr (NeedPhi) phi[i] = i - 1;\n\
    \                if constexpr (NeedMobius) mobius[i] = -1;\n                primes.emplace_back(i);\n\
    \            }\n            for (auto &&p : primes) {\n                long long\
    \ x = 1LL * i * p;\n                if (x > n) break;\n                if constexpr\
    \ (NeedMinFactor) min_factor[x] = p;\n                else prime_table[x] = false;\n\
    \                bool same = NeedMinFactor ? p == min_factor[i] : i % p == 0;\n\
    \                if constexpr (NeedPhi) phi[x] = same ? phi[i] * p : phi[i] *\
    \ (p - 1);\n                if constexpr (NeedMobius) mobius[x] = same ? 0 : -mobius[i];\n\
    \                if (same) break;\n            }\n        }\n    }\n};\n\n/**\n\
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/prime/get_prime2.cpp\"\
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
  - math/prime/linear_sieve.cpp
  isVerificationFile: false
  path: math/prime/get_prime2.cpp
  requiredBy: []
  timestamp: '2026-10-18 10:17:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_alds1_1_c_get_prime2.test.cpp
date: 2026-03-08
documentation_of: math/prime/get_prime2.cpp
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
