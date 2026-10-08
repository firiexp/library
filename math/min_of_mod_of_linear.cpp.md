---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_min_of_mod_of_linear.test.cpp
    title: test/yosupo_aplusb_min_of_mod_of_linear.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_min_of_mod_of_linear.test.cpp
    title: test/yosupo_min_of_mod_of_linear.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E00\u6B21\u5F0F\u306E\u5270\u4F59\u306E\u6700\u5C0F\u5024"
    links: []
  bundledCode: "#line 1 \"math/min_of_mod_of_linear.cpp\"\nll min_of_mod_of_linear(ll\
    \ n, ll m, ll a, ll b) {\n    ll ans = b;\n    while (true) {\n        if (a >\
    \ m / 2) {\n            b = ((__int128)a * (n - 1) + b) % m;\n            a =\
    \ m - a;\n        }\n        ans = min(ans, b);\n        if (a == 0) return ans;\n\
    \        ll k = ((__int128)a * (n - 1) + b) / m;\n        if (k == 0) return ans;\n\
    \        ll next_a = (a - m % a) % a;\n        ll next_b = (b - m) % a;\n    \
    \    if (next_b < 0) next_b += a;\n        n = k;\n        m = a;\n        a =\
    \ next_a;\n        b = next_b;\n    }\n}\n\n/**\n * @brief \u4E00\u6B21\u5F0F\u306E\
    \u5270\u4F59\u306E\u6700\u5C0F\u5024\n */\n"
  code: "ll min_of_mod_of_linear(ll n, ll m, ll a, ll b) {\n    ll ans = b;\n    while\
    \ (true) {\n        if (a > m / 2) {\n            b = ((__int128)a * (n - 1) +\
    \ b) % m;\n            a = m - a;\n        }\n        ans = min(ans, b);\n   \
    \     if (a == 0) return ans;\n        ll k = ((__int128)a * (n - 1) + b) / m;\n\
    \        if (k == 0) return ans;\n        ll next_a = (a - m % a) % a;\n     \
    \   ll next_b = (b - m) % a;\n        if (next_b < 0) next_b += a;\n        n\
    \ = k;\n        m = a;\n        a = next_a;\n        b = next_b;\n    }\n}\n\n\
    /**\n * @brief \u4E00\u6B21\u5F0F\u306E\u5270\u4F59\u306E\u6700\u5C0F\u5024\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/min_of_mod_of_linear.cpp
  requiredBy: []
  timestamp: '2026-10-08 14:17:40+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_min_of_mod_of_linear.test.cpp
  - test/yosupo_aplusb_min_of_mod_of_linear.test.cpp
date: 2026-10-08
documentation_of: math/min_of_mod_of_linear.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u4E00\u6B21\u5F0F\u306E\u5270\u4F59\u306E\u6700\u5C0F\u5024"
---

## 説明
$0 \le x < n$ における $(ax+b) \bmod m$ の最小値を求める。
Euclid 型の縮約を使い、時間は $O(\log m)$、追加領域は $O(1)$。

## できること
- `ll min_of_mod_of_linear(ll n, ll m, ll a, ll b)`
  $0 \le x < n$ における $(ax+b) \bmod m$ の最小値を返す。`a = 0` または `n = 1` なら `b`

## 使い方
$1 \le n,m \le \mathrm{LLONG\_MAX}$、$0 \le a,b < m$ を満たす値を渡す。
空区間と負の係数は対象外とする。中間の積と加算には `__int128` を使う。

## 実装上の補足
傾きが法の半分を超えるときは列を逆順にし、候補集合を保ったまま傾きを小さくする。
商が変わる最初の項だけを候補として法を傾きまで縮めるため、各反復で法は半分以下になる。
