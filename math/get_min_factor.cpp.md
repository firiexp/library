---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/powk_all.cpp
    title: math/powk_all.cpp
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_many_aplusb_eulerphi.test.cpp
    title: test/yosupo_many_aplusb_eulerphi.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/get_min_factor.md
    document_title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor\
      \ Table)"
    links: []
  bundledCode: "#line 1 \"math/get_min_factor.cpp\"\nvector<int> get_min_factor(int\
    \ n) {\n    if(n <= 1) return vector<int>{0, 1};\n    vector<bool> prime(n+1,\
    \ true);\n    vector<int> min_factor(n+1, 0);\n    min_factor[0] = 0, min_factor[1]\
    \ = 1;\n    prime[0] = false; prime[1] = false;\n    for(ll i = 2; i <= n; i++){\n\
    \        if(prime[i]) {\n            min_factor[i] = i;\n            for(ll j\
    \ = i << 1; j <= n; j += i) {\n                prime[j] = false;\n           \
    \     if(min_factor[j] == 0) min_factor[j] = i;\n            }\n        }\n  \
    \  }\n    return min_factor;\n}\n\n/**\n * @brief \u6700\u5C0F\u7D20\u56E0\u6570\
    \u30C6\u30FC\u30D6\u30EB(Min Factor Table)\n * @docs _md/get_min_factor.md\n */\n"
  code: "vector<int> get_min_factor(int n) {\n    if(n <= 1) return vector<int>{0,\
    \ 1};\n    vector<bool> prime(n+1, true);\n    vector<int> min_factor(n+1, 0);\n\
    \    min_factor[0] = 0, min_factor[1] = 1;\n    prime[0] = false; prime[1] = false;\n\
    \    for(ll i = 2; i <= n; i++){\n        if(prime[i]) {\n            min_factor[i]\
    \ = i;\n            for(ll j = i << 1; j <= n; j += i) {\n                prime[j]\
    \ = false;\n                if(min_factor[j] == 0) min_factor[j] = i;\n      \
    \      }\n        }\n    }\n    return min_factor;\n}\n\n/**\n * @brief \u6700\
    \u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)\n * @docs _md/get_min_factor.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/get_min_factor.cpp
  requiredBy:
  - math/powk_all.cpp
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_many_aplusb_eulerphi.test.cpp
documentation_of: math/get_min_factor.cpp
layout: document
redirect_from:
- /library/math/get_min_factor.cpp
- /library/math/get_min_factor.cpp.html
title: "\u6700\u5C0F\u7D20\u56E0\u6570\u30C6\u30FC\u30D6\u30EB(Min Factor Table)"
---
---
layout: post
title: Get Min Factor
date: 2026-03-08
category: 数学
tags: 数学
---

## 説明
`0..n` の最小素因数を篩で求める。
素因数分解や積性関数の前計算の土台に使う。

## できること
- `vector<int> get_min_factor(int n)`
  `min_factor[x]` に `x` の最小素因数を入れた長さ `n + 1` の配列を返す。`min_factor[0] = 0`, `min_factor[1] = 1`

## 使い方
`x >= 2` の素因数分解は `x = x / min_factor[x]` を繰り返せばよい。
素数 `p` では `min_factor[p] = p` になる。
