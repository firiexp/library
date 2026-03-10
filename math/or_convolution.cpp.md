---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_or_convolution.test.cpp
    title: test/yosupo_bitwise_or_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "OR\u7573\u307F\u8FBC\u307F(Bitwise OR Convolution)"
    links: []
  bundledCode: "#line 1 \"math/or_convolution.cpp\"\ntemplate<class T>\nvoid subset_zeta_transform(vector<T>\
    \ &v){\n    int n = 1;\n    while (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n\
    \    for (int i = 1; i < n; i <<= 1) {\n        for (int s = 0; s < n; ++s) {\n\
    \            if ((s & i) == 0) v[s | i] += v[s];\n        }\n    }\n}\n\ntemplate<class\
    \ T>\nvoid subset_mobius_transform(vector<T> &v){\n    int n = 1;\n    while (n\
    \ < (int)v.size()) n <<= 1;\n    v.resize(n);\n    for (int i = 1; i < n; i <<=\
    \ 1) {\n        for (int s = 0; s < n; ++s) {\n            if ((s & i) == 0) v[s\
    \ | i] -= v[s];\n        }\n    }\n}\n\ntemplate<class T>\nvector<T> or_convolution(vector<T>\
    \ a, vector<T> b){\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size())\
    \ n <<= 1;\n    a.resize(n);\n    b.resize(n);\n    subset_zeta_transform(a);\n\
    \    subset_zeta_transform(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n\
    \    subset_mobius_transform(a);\n    return a;\n}\n\n/**\n * @brief OR\u7573\u307F\
    \u8FBC\u307F(Bitwise OR Convolution)\n */\n"
  code: "template<class T>\nvoid subset_zeta_transform(vector<T> &v){\n    int n =\
    \ 1;\n    while (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n    for (int i\
    \ = 1; i < n; i <<= 1) {\n        for (int s = 0; s < n; ++s) {\n            if\
    \ ((s & i) == 0) v[s | i] += v[s];\n        }\n    }\n}\n\ntemplate<class T>\n\
    void subset_mobius_transform(vector<T> &v){\n    int n = 1;\n    while (n < (int)v.size())\
    \ n <<= 1;\n    v.resize(n);\n    for (int i = 1; i < n; i <<= 1) {\n        for\
    \ (int s = 0; s < n; ++s) {\n            if ((s & i) == 0) v[s | i] -= v[s];\n\
    \        }\n    }\n}\n\ntemplate<class T>\nvector<T> or_convolution(vector<T>\
    \ a, vector<T> b){\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size())\
    \ n <<= 1;\n    a.resize(n);\n    b.resize(n);\n    subset_zeta_transform(a);\n\
    \    subset_zeta_transform(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n\
    \    subset_mobius_transform(a);\n    return a;\n}\n\n/**\n * @brief OR\u7573\u307F\
    \u8FBC\u307F(Bitwise OR Convolution)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/or_convolution.cpp
  requiredBy: []
  timestamp: '2026-03-10 23:38:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_bitwise_or_convolution.test.cpp
date: 2026-03-10
documentation_of: math/or_convolution.cpp
layout: document
tags: "\u6570\u5B66"
title: Bitwise OR Convolution
---

## 説明
bitwise OR 畳み込みを計算する。
`c[S] = Σ_{A | B = S} a[A] b[B]` を返す。
計算量は `O(N log N)`。

## できること
- `void subset_zeta_transform(vector<T>& v)`
  subset zeta transform をその場適用する
- `void subset_mobius_transform(vector<T>& v)`
  subset zeta transform の逆変換をその場適用する
- `vector<T> or_convolution(vector<T> a, vector<T> b)`
  OR 畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=`, `*=` が必要。
OR 畳み込み以外にも subset zeta / mobius transform を単体で使える。
