---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0402.test.cpp
    title: test/aoj0402.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9AD8\u901FWalsh-Hadamard\u5909\u63DB(FWHT)"
    links: []
  bundledCode: "#line 1 \"math/fwht.cpp\"\ntemplate<class T>\nvoid fwht(vector<T>\
    \ &v){\n    int sz = 1;\n    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n\
    \    for (int i = 1; i < sz; i <<= 1) {\n        for (int j = 0; j < sz; j +=\
    \ (i<<1)) {\n            for (int k = 0; k < i; ++k) {\n                T x =\
    \ v[j+k], y = v[j+k+i];\n                v[j+k] = (x+y), v[j+k+i] = (x-y);\n \
    \           }\n        }\n    }\n}\n\ntemplate<class T>\nvoid ifwht(vector<T>\
    \ &v){\n    int sz = 1;\n    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n\
    \    for (int i = 1; i < sz; i <<= 1) {\n        for (int j = 0; j < sz; j +=\
    \ (i<<1)) {\n            for (int k = 0; k < i; ++k) {\n                T x =\
    \ v[j+k], y = v[j+k+i];\n                v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n\
    \            }\n        }\n    }\n}\n\n/**\n * @brief \u9AD8\u901FWalsh-Hadamard\u5909\
    \u63DB(FWHT)\n */\n"
  code: "template<class T>\nvoid fwht(vector<T> &v){\n    int sz = 1;\n    while(sz\
    \ < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i < sz; i <<=\
    \ 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n            for (int k\
    \ = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n          \
    \      v[j+k] = (x+y), v[j+k+i] = (x-y);\n            }\n        }\n    }\n}\n\
    \ntemplate<class T>\nvoid ifwht(vector<T> &v){\n    int sz = 1;\n    while(sz\
    \ < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i < sz; i <<=\
    \ 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n            for (int k\
    \ = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n          \
    \      v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n            }\n        }\n   \
    \ }\n}\n\n/**\n * @brief \u9AD8\u901FWalsh-Hadamard\u5909\u63DB(FWHT)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fwht.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0402.test.cpp
date: 2026-03-08
documentation_of: math/fwht.cpp
layout: document
tags: "\u6570\u5B66"
title: FWHT
---

## 説明
XOR 畳み込みで使う Walsh-Hadamard 変換。
長さを 2 冪に拡張してその場変換する。
計算量は `O(N log N)`。

## できること
- `void fwht(vector<T>& v)`
  `v` を FWHT でその場変換する
- `void ifwht(vector<T>& v)`
  `v` を逆 FWHT でその場変換する。`T` に `+`, `-`, `>> 1` が必要

## 使い方
どちらも長さが 2 冪でなくてもよく、不足分は `0` で埋めてから処理する。
XOR 畳み込みは `fwht(a)`, `fwht(b)` のあと各点積を取り、`ifwht` で戻す。
