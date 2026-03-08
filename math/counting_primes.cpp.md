---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_counting_primes.test.cpp
    title: test/yosupo_counting_primes.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D20\u6570\u6570\u3048\u4E0A\u3052(Prime Counting)"
    links: []
  bundledCode: "#line 1 \"math/counting_primes.cpp\"\n#include <cmath>\n#include <cstdint>\n\
    #include <vector>\nusing namespace std;\n\nnamespace counting_primes_internal\
    \ {\n\nusing ll = long long;\n\nconstexpr int MAX = 5000000;\nconstexpr int PHI_N\
    \ = 100000;\nconstexpr int PHI_S = 100;\n\nbool initialized = false;\nvector<int>\
    \ primes;\nvector<int> prime_pi;\nint phi_dp[PHI_S + 1][PHI_N + 1];\n\nll isqrt(ll\
    \ x) {\n    ll r = sqrtl((long double)x);\n    while ((r + 1) * (r + 1) <= x)\
    \ ++r;\n    while (r * r > x) --r;\n    return r;\n}\n\nll icbrt(ll x) {\n   \
    \ ll r = powl((long double)x, 1.0L / 3.0L);\n    while ((__int128)(r + 1) * (r\
    \ + 1) * (r + 1) <= x) ++r;\n    while ((__int128)r * r * r > x) --r;\n    return\
    \ r;\n}\n\nll iroot4(ll x) {\n    return isqrt(isqrt(x));\n}\n\nvoid init() {\n\
    \    if (initialized) return;\n    initialized = true;\n\n    vector<int> min_factor(MAX\
    \ + 1);\n    prime_pi.assign(MAX + 1, 0);\n    for (int i = 2; i <= MAX; ++i)\
    \ {\n        if (min_factor[i] == 0) {\n            min_factor[i] = i;\n     \
    \       primes.push_back(i);\n        }\n        for (int p : primes) {\n    \
    \        ll v = 1LL * i * p;\n            if (v > MAX || p > min_factor[i]) break;\n\
    \            min_factor[v] = p;\n        }\n        prime_pi[i] = prime_pi[i -\
    \ 1] + (min_factor[i] == i);\n    }\n\n    for (int n = 0; n <= PHI_N; ++n) phi_dp[0][n]\
    \ = n;\n    for (int s = 1; s <= PHI_S; ++s) {\n        int p = primes[s - 1];\n\
    \        for (int n = 0; n <= PHI_N; ++n) {\n            phi_dp[s][n] = phi_dp[s\
    \ - 1][n] - phi_dp[s - 1][n / p];\n        }\n    }\n}\n\nll phi(ll x, int s)\
    \ {\n    if (s == 0) return x;\n    if (s <= PHI_S && x <= PHI_N) return phi_dp[s][x];\n\
    \    if (s == 1) return x - x / 2;\n    return phi(x, s - 1) - phi(x / primes[s\
    \ - 1], s - 1);\n}\n\nll lehmer_pi(ll x) {\n    if (x <= MAX) return prime_pi[x];\n\
    \n    ll a = lehmer_pi(iroot4(x));\n    ll b = lehmer_pi(isqrt(x));\n    ll c\
    \ = lehmer_pi(icbrt(x));\n\n    ll sum = phi(x, (int)a) + (b + a - 2) * (b - a\
    \ + 1) / 2;\n    for (ll i = a + 1; i <= b; ++i) {\n        ll w = x / primes[i\
    \ - 1];\n        sum -= lehmer_pi(w);\n        if (i <= c) {\n            ll lim\
    \ = lehmer_pi(isqrt(w));\n            for (ll j = i; j <= lim; ++j) {\n      \
    \          sum -= lehmer_pi(w / primes[j - 1]) - (j - 1);\n            }\n   \
    \     }\n    }\n    return sum;\n}\n\n}  // namespace counting_primes_internal\n\
    \nlong long counting_primes(long long n) {\n    counting_primes_internal::init();\n\
    \    return counting_primes_internal::lehmer_pi(n);\n}\n\n/**\n * @brief \u7D20\
    \u6570\u6570\u3048\u4E0A\u3052(Prime Counting)\n */\n"
  code: "#include <cmath>\n#include <cstdint>\n#include <vector>\nusing namespace\
    \ std;\n\nnamespace counting_primes_internal {\n\nusing ll = long long;\n\nconstexpr\
    \ int MAX = 5000000;\nconstexpr int PHI_N = 100000;\nconstexpr int PHI_S = 100;\n\
    \nbool initialized = false;\nvector<int> primes;\nvector<int> prime_pi;\nint phi_dp[PHI_S\
    \ + 1][PHI_N + 1];\n\nll isqrt(ll x) {\n    ll r = sqrtl((long double)x);\n  \
    \  while ((r + 1) * (r + 1) <= x) ++r;\n    while (r * r > x) --r;\n    return\
    \ r;\n}\n\nll icbrt(ll x) {\n    ll r = powl((long double)x, 1.0L / 3.0L);\n \
    \   while ((__int128)(r + 1) * (r + 1) * (r + 1) <= x) ++r;\n    while ((__int128)r\
    \ * r * r > x) --r;\n    return r;\n}\n\nll iroot4(ll x) {\n    return isqrt(isqrt(x));\n\
    }\n\nvoid init() {\n    if (initialized) return;\n    initialized = true;\n\n\
    \    vector<int> min_factor(MAX + 1);\n    prime_pi.assign(MAX + 1, 0);\n    for\
    \ (int i = 2; i <= MAX; ++i) {\n        if (min_factor[i] == 0) {\n          \
    \  min_factor[i] = i;\n            primes.push_back(i);\n        }\n        for\
    \ (int p : primes) {\n            ll v = 1LL * i * p;\n            if (v > MAX\
    \ || p > min_factor[i]) break;\n            min_factor[v] = p;\n        }\n  \
    \      prime_pi[i] = prime_pi[i - 1] + (min_factor[i] == i);\n    }\n\n    for\
    \ (int n = 0; n <= PHI_N; ++n) phi_dp[0][n] = n;\n    for (int s = 1; s <= PHI_S;\
    \ ++s) {\n        int p = primes[s - 1];\n        for (int n = 0; n <= PHI_N;\
    \ ++n) {\n            phi_dp[s][n] = phi_dp[s - 1][n] - phi_dp[s - 1][n / p];\n\
    \        }\n    }\n}\n\nll phi(ll x, int s) {\n    if (s == 0) return x;\n   \
    \ if (s <= PHI_S && x <= PHI_N) return phi_dp[s][x];\n    if (s == 1) return x\
    \ - x / 2;\n    return phi(x, s - 1) - phi(x / primes[s - 1], s - 1);\n}\n\nll\
    \ lehmer_pi(ll x) {\n    if (x <= MAX) return prime_pi[x];\n\n    ll a = lehmer_pi(iroot4(x));\n\
    \    ll b = lehmer_pi(isqrt(x));\n    ll c = lehmer_pi(icbrt(x));\n\n    ll sum\
    \ = phi(x, (int)a) + (b + a - 2) * (b - a + 1) / 2;\n    for (ll i = a + 1; i\
    \ <= b; ++i) {\n        ll w = x / primes[i - 1];\n        sum -= lehmer_pi(w);\n\
    \        if (i <= c) {\n            ll lim = lehmer_pi(isqrt(w));\n          \
    \  for (ll j = i; j <= lim; ++j) {\n                sum -= lehmer_pi(w / primes[j\
    \ - 1]) - (j - 1);\n            }\n        }\n    }\n    return sum;\n}\n\n} \
    \ // namespace counting_primes_internal\n\nlong long counting_primes(long long\
    \ n) {\n    counting_primes_internal::init();\n    return counting_primes_internal::lehmer_pi(n);\n\
    }\n\n/**\n * @brief \u7D20\u6570\u6570\u3048\u4E0A\u3052(Prime Counting)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/counting_primes.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_counting_primes.test.cpp
date: 2026-03-08
documentation_of: math/counting_primes.cpp
layout: post
tags: "\u6570\u5B66"
title: Counting Primes
---

## 説明
`pi(N)`、つまり `N` 以下の素数の個数を求める。
Lehmer の prime counting を使う。

## できること
- `long long counting_primes(long long n)`
  `n` 以下の素数の個数を返す

## 使い方
`1 <= n <= 10^11` を想定する。
内部では `5 * 10^6` まで篩い、`phi(x, s)` と Lehmer の分割統治で `pi(n)` を計算する。
