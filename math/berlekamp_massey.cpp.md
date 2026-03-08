---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: fps/linear_recurrence.cpp
    title: "\u7DDA\u5F62\u6F38\u5316\u5F0F"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_find_linear_recurrence.test.cpp
    title: test/yosupo_find_linear_recurrence.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
    title: test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Berlekamp-Massey\u6CD5"
    links: []
  bundledCode: "#line 1 \"math/berlekamp_massey.cpp\"\ntemplate<class T>\nvector<T>\
    \ berlekamp_massey(const vector<T> &s) {\n    vector<T> c(1, T(1)), b(1, T(1));\n\
    \    int l = 0, m = 1;\n    T y = T(1);\n    for (int n = 0; n < (int)s.size();\
    \ ++n) {\n        T d = T(0);\n        for (int i = 0; i <= l; ++i) d += c[i]\
    \ * s[n - i];\n        if (d == T(0)) {\n            ++m;\n            continue;\n\
    \        }\n        auto t = c;\n        T coef = d / y;\n        if ((int)c.size()\
    \ < (int)b.size() + m) c.resize((int)b.size() + m, T(0));\n        for (int i\
    \ = 0; i < (int)b.size(); ++i) c[i + m] -= coef * b[i];\n        if (2 * l <=\
    \ n) {\n            l = n + 1 - l;\n            b = t;\n            y = d;\n \
    \           m = 1;\n        } else {\n            ++m;\n        }\n    }\n   \
    \ c.erase(c.begin());\n    for (auto &x : c) x = -x;\n    return c;\n}\n\n/**\n\
    \ * @brief Berlekamp-Massey\u6CD5\n */\n"
  code: "template<class T>\nvector<T> berlekamp_massey(const vector<T> &s) {\n   \
    \ vector<T> c(1, T(1)), b(1, T(1));\n    int l = 0, m = 1;\n    T y = T(1);\n\
    \    for (int n = 0; n < (int)s.size(); ++n) {\n        T d = T(0);\n        for\
    \ (int i = 0; i <= l; ++i) d += c[i] * s[n - i];\n        if (d == T(0)) {\n \
    \           ++m;\n            continue;\n        }\n        auto t = c;\n    \
    \    T coef = d / y;\n        if ((int)c.size() < (int)b.size() + m) c.resize((int)b.size()\
    \ + m, T(0));\n        for (int i = 0; i < (int)b.size(); ++i) c[i + m] -= coef\
    \ * b[i];\n        if (2 * l <= n) {\n            l = n + 1 - l;\n           \
    \ b = t;\n            y = d;\n            m = 1;\n        } else {\n         \
    \   ++m;\n        }\n    }\n    c.erase(c.begin());\n    for (auto &x : c) x =\
    \ -x;\n    return c;\n}\n\n/**\n * @brief Berlekamp-Massey\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/berlekamp_massey.cpp
  requiredBy:
  - fps/linear_recurrence.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_kth_term_of_linearly_recurrent_sequence.test.cpp
  - test/yosupo_find_linear_recurrence.test.cpp
date: 2026-03-07
documentation_of: math/berlekamp_massey.cpp
layout: document
tags: "\u6570\u5B66"
title: Berlekamp-Massey
---

## 概要
列 `s` を満たす最小次数の線形漸化式

`s_n = c_0 s_{n-1} + c_1 s_{n-2} + ... + c_{L-1} s_{n-L}`

の係数列 `c` を求める。

## 計算量
`O(N^2)` (`N = s.size()`)

## 使い方
`vector<T> c = berlekamp_massey(s);`

- `T` は加減乗除と `T(0)`, `T(1)` が使える体上の型を想定。
- 返り値の長さが最小次数 `L`。
- 返り値 `c[i]` は上式の係数 `c_i`。
