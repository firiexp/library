---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_tetration_mod.test.cpp
    title: test/yosupo_tetration_mod.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Tetration Mod
    links: []
  bundledCode: "#line 1 \"math/tetration.cpp\"\nll totient(ll n){\n    ll res = n;\n\
    \    for (ll i = 2; i*i <= n; ++i) {\n        if(n%i == 0){\n            res =\
    \ res/i*(i-1);\n            while(n%i == 0) n /= i;\n        }\n    }\n    if(n\
    \ > 1) res = res/n*(n-1);\n    return res;\n}\n\ntemplate <class T>\nT pow_tetration(T\
    \ x, T n, T M, bool &yojo){\n    ull u = 1, xx = x;\n    if(x >= M) yojo = true;\n\
    \    while (n > 0){\n        if (n&1) {\n            u = u * xx;  \n         \
    \   if(u >= M) yojo = true, u %= M;\n        }\n        if(!(n >>= 1)) break;\n\
    \        xx = xx * xx;\n        if(xx >= M) yojo = true, xx %= M;\n    }\n   \
    \ return static_cast<T>(u);\n};\n\nll tetration(ll a, ll n, const ll M, bool &yojo)\
    \ {\n    if(a == 0) return !(n&1);\n    if(M == 1) return yojo = true, 1;\n  \
    \  if(a == 1 || n == 0) return 1;\n    ll expo = tetration(a, n-1, totient(M),\
    \ yojo);\n    ll res = pow_tetration(a, expo, M, yojo);\n    return res + (yojo\
    \ ? M : 0);\n}\n\nll tetration(ll a, ll n, const ll M){\n    bool yojo = false;\n\
    \    return tetration(a, n, M, yojo)%M;\n}\n\n/**\n * @brief Tetration Mod\n */\n"
  code: "ll totient(ll n){\n    ll res = n;\n    for (ll i = 2; i*i <= n; ++i) {\n\
    \        if(n%i == 0){\n            res = res/i*(i-1);\n            while(n%i\
    \ == 0) n /= i;\n        }\n    }\n    if(n > 1) res = res/n*(n-1);\n    return\
    \ res;\n}\n\ntemplate <class T>\nT pow_tetration(T x, T n, T M, bool &yojo){\n\
    \    ull u = 1, xx = x;\n    if(x >= M) yojo = true;\n    while (n > 0){\n   \
    \     if (n&1) {\n            u = u * xx;  \n            if(u >= M) yojo = true,\
    \ u %= M;\n        }\n        if(!(n >>= 1)) break;\n        xx = xx * xx;\n \
    \       if(xx >= M) yojo = true, xx %= M;\n    }\n    return static_cast<T>(u);\n\
    };\n\nll tetration(ll a, ll n, const ll M, bool &yojo) {\n    if(a == 0) return\
    \ !(n&1);\n    if(M == 1) return yojo = true, 1;\n    if(a == 1 || n == 0) return\
    \ 1;\n    ll expo = tetration(a, n-1, totient(M), yojo);\n    ll res = pow_tetration(a,\
    \ expo, M, yojo);\n    return res + (yojo ? M : 0);\n}\n\nll tetration(ll a, ll\
    \ n, const ll M){\n    bool yojo = false;\n    return tetration(a, n, M, yojo)%M;\n\
    }\n\n/**\n * @brief Tetration Mod\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/tetration.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_tetration_mod.test.cpp
date: 2026-03-08
documentation_of: math/tetration.cpp
layout: document
tags: "\u6570\u5B66"
title: Tetration
---

## 説明
`a ↑↑ n mod M` をオイラーのトーシェント関数を使って計算する。
`a, n, M` が `long long` に収まる範囲を想定する。

## できること
- `ll totient(ll n)`
  `n` のオイラー関数 `phi(n)` を返す
- `ll tetration(ll a, ll n, ll M)`
  `a ↑↑ n mod M` を返す。`M = 1` なら `0`
- `ll tetration(ll a, ll n, ll M, bool& yojo)`
  内部用。指数の縮約で法をまたいだかを `yojo` に反映しつつ、必要なら `M` を足した値を返す

## 使い方
`tetration(a, n, M)` を呼ぶだけでよい。
`a ↑↑ 0 = 1` として扱う。

`a = 0` では `0 ↑↑ n` を `n >= 1` に対して `0, 1, 0, 1, ...` と解釈する。
再帰で `phi(M)` を辿る実装なので、`M` が小さくなっていく前提に乗る問題で使う。
