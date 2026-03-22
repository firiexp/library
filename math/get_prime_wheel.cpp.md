---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
    title: test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/get_prime_wheel.cpp\"\nstruct Prime {\n    static constexpr\
    \ int wheel[8]  = {4, 2, 4, 2, 4, 6, 2, 6};\n    static constexpr int wheel2[8]\
    \ = {7, 11, 13, 17, 19, 23, 29, 31};\n    static constexpr int wheel_sum[30] =\
    \ {\n        0, 0, 0, 0, 0, 0, 1, 1, 1, 1,\n        2, 2, 3, 3, 3, 3, 4, 4, 5,\
    \ 5,\n        5, 5, 6, 6, 6, 6, 6, 6, 7, 7\n    };\n    static constexpr int off64[64]\
    \ = {\n          0,  4,  6, 10, 12, 16, 22, 24,\n         30, 34, 36, 40, 42,\
    \ 46, 52, 54,\n         60, 64, 66, 70, 72, 76, 82, 84,\n         90, 94, 96,100,102,106,112,114,\n\
    \        120,124,126,130,132,136,142,144,\n        150,154,156,160,162,166,172,174,\n\
    \        180,184,186,190,192,196,202,204,\n        210,214,216,220,222,226,232,234\n\
    \    };\n\n    // old 1-based\n    static inline int f(int n) { return (n - 1)\
    \ / 30 * 8 + wheel_sum[(n - 1) % 30]; }\n    static inline int g(int n) { return\
    \ ((n - 1) >> 3) * 30 + wheel2[(n - 1) & 7]; }\n\n    // internal 0-based\n  \
    \  static inline int f0(int n) { return f(n) - 1; }\n    static inline int g0(int\
    \ n) { return (n >> 3) * 30 + wheel2[n & 7]; }\n\n    int count = 0;\n    vector<int>\
    \ primes;\n    vector<int> picked;\n\nprivate:\n    static void build_sieve(int\
    \ M, vector<ull>& sieve, int& n0) {\n        if (M < 7) {\n            n0 = -1;\n\
    \            sieve.clear();\n            return;\n        }\n\n        n0 = f0(M);\n\
    \        int sq = (int)std::sqrt((double)M);\n        int k0 = (sq >= 7 ? f0(sq)\
    \ : -1);\n\n        int num = n0 + 1;\n        sieve.assign((num + 63) >> 6, ~0ULL);\n\
    \        if (num & 63) sieve.back() &= (1ULL << (num & 63)) - 1;\n\n        auto*\
    \ sv = sieve.data();\n        array<int, 8> delta{};\n\n        for (int i = 0;\
    \ i <= k0; ++i) {\n            if (((sv[i >> 6] >> (i & 63)) & 1ULL) == 0) continue;\n\
    \n            int p = g0(i);\n            int phase0 = i & 7;\n\n            long\
    \ long cur = 1LL * p * p;\n            int idx = f0((int)cur);\n\n           \
    \ for (int t = 0; t < 8; ++t) {\n                long long nxt = cur + 1LL * wheel[(phase0\
    \ + t) & 7] * p;\n                delta[t] = f((int)nxt) - f((int)cur);\n    \
    \            cur = nxt;\n            }\n\n            const int d0 = delta[0];\n\
    \            const int d1 = delta[1];\n            const int d2 = delta[2];\n\
    \            const int d3 = delta[3];\n            const int d4 = delta[4];\n\
    \            const int d5 = delta[5];\n            const int d6 = delta[6];\n\
    \            const int d7 = delta[7];\n\n            while (idx <= n0) {\n   \
    \             sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx += d0;\n\
    \                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d1;\n                if (idx > n0) break;\n\
    \                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx +=\
    \ d2;\n                if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL\
    \ << (idx & 63));\n                idx += d3;\n                if (idx > n0) break;\n\
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
    constexpr int Prime::wheel_sum[30];\nconstexpr int Prime::off64[64];\n"
  code: "struct Prime {\n    static constexpr int wheel[8]  = {4, 2, 4, 2, 4, 6, 2,\
    \ 6};\n    static constexpr int wheel2[8] = {7, 11, 13, 17, 19, 23, 29, 31};\n\
    \    static constexpr int wheel_sum[30] = {\n        0, 0, 0, 0, 0, 0, 1, 1, 1,\
    \ 1,\n        2, 2, 3, 3, 3, 3, 4, 4, 5, 5,\n        5, 5, 6, 6, 6, 6, 6, 6, 7,\
    \ 7\n    };\n    static constexpr int off64[64] = {\n          0,  4,  6, 10,\
    \ 12, 16, 22, 24,\n         30, 34, 36, 40, 42, 46, 52, 54,\n         60, 64,\
    \ 66, 70, 72, 76, 82, 84,\n         90, 94, 96,100,102,106,112,114,\n        120,124,126,130,132,136,142,144,\n\
    \        150,154,156,160,162,166,172,174,\n        180,184,186,190,192,196,202,204,\n\
    \        210,214,216,220,222,226,232,234\n    };\n\n    // old 1-based\n    static\
    \ inline int f(int n) { return (n - 1) / 30 * 8 + wheel_sum[(n - 1) % 30]; }\n\
    \    static inline int g(int n) { return ((n - 1) >> 3) * 30 + wheel2[(n - 1)\
    \ & 7]; }\n\n    // internal 0-based\n    static inline int f0(int n) { return\
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
    \                delta[t] = f((int)nxt) - f((int)cur);\n                cur =\
    \ nxt;\n            }\n\n            const int d0 = delta[0];\n            const\
    \ int d1 = delta[1];\n            const int d2 = delta[2];\n            const\
    \ int d3 = delta[3];\n            const int d4 = delta[4];\n            const\
    \ int d5 = delta[5];\n            const int d6 = delta[6];\n            const\
    \ int d7 = delta[7];\n\n            while (idx <= n0) {\n                sv[idx\
    \ >> 6] &= ~(1ULL << (idx & 63));\n                idx += d0;\n              \
    \  if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL << (idx & 63));\n\
    \                idx += d1;\n                if (idx > n0) break;\n          \
    \      sv[idx >> 6] &= ~(1ULL << (idx & 63));\n                idx += d2;\n  \
    \              if (idx > n0) break;\n                sv[idx >> 6] &= ~(1ULL <<\
    \ (idx & 63));\n                idx += d3;\n                if (idx > n0) break;\n\
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
    constexpr int Prime::wheel_sum[30];\nconstexpr int Prime::off64[64];\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_prime_wheel.cpp
  requiredBy: []
  timestamp: '2026-03-22 18:32:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_enumerate_primes_get_prime_wheel.test.cpp
date: 2026-03-22
documentation_of: math/get_prime_wheel.cpp
layout: document
tags: "\u6570\u5B66"
title: get_prime_wheel
---

## 説明
mod 30 の wheel sieve で `M` 以下の素数を列挙する。
`2, 3, 5` を先に処理し、それ以外は 30 と互いに素な候補だけを持つ。

## できること
- `Prime(int M)`
  `M` 以下の素数をすべて列挙する
- `Prime(int M, int a, int b)`
  `M` 以下の素数のうち、0-indexed で `b, b + a, b + 2a, ...` 番目の素数だけを `picked` に入れる
- `int count`
  `M` 以下の素数個数
- `vector<int> primes`
  `Prime(int M)` で列挙した素数
- `vector<int> picked`
  `Prime(int M, int a, int b)` で拾った素数

## 使い方
全列挙したいなら `Prime p(M);` を作って `p.primes` を参照する。
個数だけでなく等差間隔で一部だけ拾いたいなら `Prime p(M, a, b);` を使い、全体個数は `p.count`、抽出結果は `p.picked` を見る。

`Prime(int M, int a, int b)` の抽出位置は 0-indexed で、`count == b` の素数から始めて素数を 1 個見るごとに `count` を進める。
たとえば `a = 2, b = 1` なら 2 番目, 4 番目, 6 番目, ... の素数を拾う。
