---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_and_convolution.test.cpp
    title: test/yosupo_bitwise_and_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "AND\u7573\u307F\u8FBC\u307F(Bitwise AND Convolution)"
    links: []
  bundledCode: "#line 1 \"math/and_convolution.cpp\"\ntemplate<class T>\nvoid superset_zeta_transform(vector<T>\
    \ &v){\n    int n = 1;\n    while (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n\
    \    for (int i = 1; i < n; i <<= 1) {\n        for (int s = 0; s < n; ++s) {\n\
    \            if (s & i) v[s ^ i] += v[s];\n        }\n    }\n}\n\ntemplate<class\
    \ T>\nvoid superset_mobius_transform(vector<T> &v){\n    int n = 1;\n    while\
    \ (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n    for (int i = 1; i < n; i\
    \ <<= 1) {\n        for (int s = 0; s < n; ++s) {\n            if (s & i) v[s\
    \ ^ i] -= v[s];\n        }\n    }\n}\n\ntemplate<class T>\nvector<T> and_convolution(vector<T>\
    \ a, vector<T> b){\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size())\
    \ n <<= 1;\n    a.resize(n);\n    b.resize(n);\n    superset_zeta_transform(a);\n\
    \    superset_zeta_transform(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n\
    \    superset_mobius_transform(a);\n    return a;\n}\n\n/**\n * @brief AND\u7573\
    \u307F\u8FBC\u307F(Bitwise AND Convolution)\n */\n"
  code: "template<class T>\nvoid superset_zeta_transform(vector<T> &v){\n    int n\
    \ = 1;\n    while (n < (int)v.size()) n <<= 1;\n    v.resize(n);\n    for (int\
    \ i = 1; i < n; i <<= 1) {\n        for (int s = 0; s < n; ++s) {\n          \
    \  if (s & i) v[s ^ i] += v[s];\n        }\n    }\n}\n\ntemplate<class T>\nvoid\
    \ superset_mobius_transform(vector<T> &v){\n    int n = 1;\n    while (n < (int)v.size())\
    \ n <<= 1;\n    v.resize(n);\n    for (int i = 1; i < n; i <<= 1) {\n        for\
    \ (int s = 0; s < n; ++s) {\n            if (s & i) v[s ^ i] -= v[s];\n      \
    \  }\n    }\n}\n\ntemplate<class T>\nvector<T> and_convolution(vector<T> a, vector<T>\
    \ b){\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size()) n <<=\
    \ 1;\n    a.resize(n);\n    b.resize(n);\n    superset_zeta_transform(a);\n  \
    \  superset_zeta_transform(b);\n    for (int i = 0; i < n; ++i) a[i] *= b[i];\n\
    \    superset_mobius_transform(a);\n    return a;\n}\n\n/**\n * @brief AND\u7573\
    \u307F\u8FBC\u307F(Bitwise AND Convolution)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/and_convolution.cpp
  requiredBy: []
  timestamp: '2026-03-10 23:38:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_bitwise_and_convolution.test.cpp
date: 2026-03-10
documentation_of: math/and_convolution.cpp
layout: document
tags: "\u6570\u5B66"
title: Bitwise AND Convolution
---

## 説明
bitwise AND 畳み込みを計算する。
`c[S] = Σ_{A & B = S} a[A] b[B]` を返す。
計算量は $O(N log N)$。

## できること
- `void superset_zeta_transform(vector<T>& v)`
  superset zeta transform をその場適用する
- `void superset_mobius_transform(vector<T>& v)`
  superset zeta transform の逆変換をその場適用する
- `vector<T> and_convolution(vector<T> a, vector<T> b)`
  AND 畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=`, `*=` が必要。
AND 畳み込み以外にも superset zeta / mobius transform を単体で使える。
