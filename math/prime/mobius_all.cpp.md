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
    path: test/yosupo_aplusb_linear_sieve.test.cpp
    title: test/yosupo_aplusb_linear_sieve.test.cpp
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
    \ * @brief \u7DDA\u5F62\u7BE9(Linear Sieve)\n */\n\n\n#line 2 \"math/prime/mobius_all.cpp\"\
    \n\nvector<int> mobius_all(int M) {\n    if (M <= 0) return {};\n    return LinearSieve(M\
    \ - 1, false, false, true).mobius;\n}\n"
  code: "#include \"linear_sieve.cpp\"\n\nvector<int> mobius_all(int M) {\n    if\
    \ (M <= 0) return {};\n    return LinearSieve(M - 1, false, false, true).mobius;\n\
    }\n"
  dependsOn:
  - math/prime/linear_sieve.cpp
  isVerificationFile: false
  path: math/prime/mobius_all.cpp
  requiredBy: []
  timestamp: '2026-10-18 10:17:06+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_linear_sieve.test.cpp
date: 2026-03-12
documentation_of: math/prime/mobius_all.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u30E1\u30D3\u30A6\u30B9\u95A2\u6570\u30C6\u30FC\u30D6\u30EB(Mobius Table)"
---

## 説明
`0..M-1` のメビウス関数を線形篩でまとめて求める。
計算量は $O(M)$。

## できること
- `vector<int> mobius_all(int M)`
  `mobius[i] = μ(i)` を満たす長さ `M` の配列を返す

## 使い方
`mobius[0] = 0`, `mobius[1] = 1` になる。
包除や約数和の反転でまとめて使う前計算向けである。
