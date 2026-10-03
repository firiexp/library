---
category: "\u6570\u5B66"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime/get_prime_wheel.cpp
    title: get_prime_wheel
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_alds1_1_c_get_prime.test.cpp
    title: test/aoj_alds1_1_c_get_prime.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition.test.cpp
    title: test/yosupo_aplusb_library_composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_enumerate_primes_get_prime.test.cpp
    title: test/yosupo_enumerate_primes_get_prime.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prime/get_prime.cpp\"\n\n\n\n#line 1 \"math/prime/get_prime_wheel.cpp\"\
    \n\n\n\nstruct Prime {\n    static constexpr int wheel[8]  = {4, 2, 4, 2, 4, 6,\
    \ 2, 6};\n    static constexpr int wheel2[8] = {7, 11, 13, 17, 19, 23, 29, 31};\n\
    \    static constexpr int wheel_sum[30] = {\n        0, 0, 0, 0, 0, 0, 1, 1, 1,\
    \ 1,\n        2, 2, 3, 3, 3, 3, 4, 4, 5, 5,\n        5, 5, 6, 6, 6, 6, 6, 6, 7,\
    \ 7\n    };\n    static constexpr int off64[64] = {\n          0,  4,  6, 10,\
    \ 12, 16, 22, 24,\n         30, 34, 36, 40, 42, 46, 52, 54,\n         60, 64,\
    \ 66, 70, 72, 76, 82, 84,\n         90, 94, 96,100,102,106,112,114,\n        120,124,126,130,132,136,142,144,\n\
    \        150,154,156,160,162,166,172,174,\n        180,184,186,190,192,196,202,204,\n\
    \        210,214,216,220,222,226,232,234\n    };\n\n    // old 1-based\n    static\
    \ inline int f(long long n) { return (n - 1) / 30 * 8 + wheel_sum[(n - 1) % 30];\
    \ }\n    static inline int g(int n) { return ((n - 1) >> 3) * 30 + wheel2[(n -\
    \ 1) & 7]; }\n\n    // internal 0-based\n    static inline int f0(int n) { return\
    \ f(n) - 1; }\n    static inline int g0(int n) { return (n >> 3) * 30 + wheel2[n\
    \ & 7]; }\n\n    int count = 0;\n    vector<int> primes;\n    vector<int> picked;\n\
    \nprivate:\n    static void build_sieve(int M, vector<ull>& sieve, int& n0) {\n\
    \        if (M < 7) {\n            n0 = -1;\n            sieve.clear();\n    \
    \        return;\n        }\n\n        n0 = f0(M);\n        int sq = (int)std::sqrt((double)M);\n\
    \        int k0 = (sq >= 7 ? f0(sq) : -1);\n\n        int num = n0 + 1;\n    \
    \    sieve.assign((num + 63) >> 6, ~0ULL);\n        if (num & 63) sieve.back()\
    \ &= (1ULL << (num & 63)) - 1;\n\n        auto* sv = sieve.data();\n        array<int,\
    \ 8> delta{};\n\n        for (int i = 0; i <= k0; ++i) {\n            if (((sv[i\
    \ >> 6] >> (i & 63)) & 1ULL) == 0) continue;\n\n            int p = g0(i);\n \
    \           int phase0 = i & 7;\n\n            long long cur = 1LL * p * p;\n\
    \            int idx = f0((int)cur);\n\n            for (int t = 0; t < 8; ++t)\
    \ {\n                long long nxt = cur + 1LL * wheel[(phase0 + t) & 7] * p;\n\
    \                delta[t] = f(nxt) - f(cur);\n                cur = nxt;\n   \
    \         }\n\n            const int d0 = delta[0];\n            const int d1\
    \ = delta[1];\n            const int d2 = delta[2];\n            const int d3\
    \ = delta[3];\n            const int d4 = delta[4];\n            const int d5\
    \ = delta[5];\n            const int d6 = delta[6];\n            const int d7\
    \ = delta[7];\n\n            while (idx <= n0) {\n                sv[idx >> 6]\
    \ &= ~(1ULL << (idx & 63));\n                idx += d0;\n                if (idx\
    \ > n0) break;\n                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n     \
    \           idx += d1;\n                if (idx > n0) break;\n               \
    \ sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx += d2;\n       \
    \         if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL << (idx\
    \ & 63));\n                idx += d3;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d4;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d5;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d6;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d7;\n            }\n        }\n    }\n\
    \npublic:\n    Prime(int M) {\n        if (M >= 17) {\n            primes.reserve(max(0,\
    \ (int)(M / (log((double)M) - 1.12))));\n        }\n\n        if (M >= 2) primes.push_back(2),\
    \ ++count;\n        if (M >= 3) primes.push_back(3), ++count;\n        if (M >=\
    \ 5) primes.push_back(5), ++count;\n        if (M < 7) return;\n\n        vector<ull>\
    \ sieve;\n        int n0;\n        build_sieve(M, sieve, n0);\n\n        int words\
    \ = (n0 + 64) >> 6;\n        for (int w = 0; w < words; ++w) {\n            ull\
    \ bits = sieve[w];\n            int base = 240 * w + 7; // 64 candidates = 8 cycles\
    \ = 240 numbers\n            while (bits) {\n                int t = __builtin_ctzll(bits);\n\
    \                primes.push_back(base + off64[t]);\n                ++count;\n\
    \                bits &= bits - 1;\n            }\n        }\n    }\n\n    Prime(int\
    \ M, int a, int b) {\n        int next_pick = b;\n\n        auto add_small = [&](int\
    \ p) {\n            if (count == next_pick) {\n                picked.push_back(p);\n\
    \                next_pick += a;\n            }\n            ++count;\n      \
    \  };\n\n        if (M >= 2) add_small(2);\n        if (M >= 3) add_small(3);\n\
    \        if (M >= 5) add_small(5);\n        if (M < 7) return;\n\n        vector<ull>\
    \ sieve;\n        int n0;\n        build_sieve(M, sieve, n0);\n\n        int words\
    \ = (n0 + 64) >> 6;\n        for (int w = 0; w < words; ++w) {\n            ull\
    \ bits = sieve[w];\n            int pc = __builtin_popcountll(bits);\n\n     \
    \       if (next_pick >= count + pc) {\n                count += pc;\n       \
    \         continue;\n            }\n\n            int base = 240 * w + 7;\n  \
    \          while (bits) {\n                int t = __builtin_ctzll(bits);\n  \
    \              if (count == next_pick) {\n                    picked.push_back(base\
    \ + off64[t]);\n                    next_pick += a;\n                }\n     \
    \           ++count;\n                bits &= bits - 1;\n            }\n     \
    \   }\n    }\n};\n\nconstexpr int Prime::wheel[8];\nconstexpr int Prime::wheel2[8];\n\
    constexpr int Prime::wheel_sum[30];\nconstexpr int Prime::off64[64];\n\n\n#line\
    \ 5 \"math/prime/get_prime.cpp\"\n\nvector<int> get_prime(int n) {\n    return\
    \ Prime(n).primes;\n}\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_MATH_GET_PRIME_CPP\n#define FIRIEXP_LIBRARY_MATH_GET_PRIME_CPP\n\
    \n#include \"get_prime_wheel.cpp\"\n\nvector<int> get_prime(int n) {\n    return\
    \ Prime(n).primes;\n}\n\n#endif\n"
  dependsOn:
  - math/prime/get_prime_wheel.cpp
  isVerificationFile: false
  path: math/prime/get_prime.cpp
  requiredBy: []
  timestamp: '2026-10-03 16:51:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_library_composition.test.cpp
  - test/yosupo_enumerate_primes_get_prime.test.cpp
  - test/aoj_alds1_1_c_get_prime.test.cpp
date: 2026-03-12
documentation_of: math/prime/get_prime.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u7D20\u6570\u5217\u6319"
---

## 説明
`n` 以下の素数を wheel sieve で列挙する。
計算量は $O(n \log \log n)$。

## できること
- `vector<int> get_prime(int n)`
  `n` 以下の素数を昇順で返す。`n <= 1` なら空

## 使い方
```cpp
auto primes = get_prime(n);
```
