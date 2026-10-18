---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0402.test.cpp
    title: test/aoj0402.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_fwht.test.cpp
    title: test/yosupo_aplusb_fwht.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_bitwise_xor_convolution.test.cpp
    title: test/yosupo_bitwise_xor_convolution.test.cpp
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
    \           }\n        }\n    }\n}\n\nnamespace fwht_detail {\ntemplate<class\
    \ T>\nauto inverse(vector<T> &v, int) -> decltype(T(1).inv(), void()) {\n    fwht(v);\n\
    \    T inverse_size = T(v.size()).inv();\n    for (auto &x : v) x *= inverse_size;\n\
    }\n\ntemplate<class T>\nvoid inverse(vector<T> &v, long) {\n    int sz = 1;\n\
    \    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i\
    \ < sz; i <<= 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n         \
    \   for (int k = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n\
    \                v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n            }\n    \
    \    }\n    }\n}\n}\n\ntemplate<class T>\nvoid ifwht(vector<T> &v) {\n    fwht_detail::inverse(v,\
    \ 0);\n}\n\ntemplate<class T>\nvector<T> xor_convolution(vector<T> a, vector<T>\
    \ b) {\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size()) n <<=\
    \ 1;\n    a.resize(n);\n    b.resize(n);\n    fwht(a);\n    fwht(b);\n    for\
    \ (int i = 0; i < n; ++i) a[i] *= b[i];\n    ifwht(a);\n    return a;\n}\n\n/**\n\
    \ * @brief \u9AD8\u901FWalsh-Hadamard\u5909\u63DB(FWHT)\n */\n"
  code: "template<class T>\nvoid fwht(vector<T> &v){\n    int sz = 1;\n    while(sz\
    \ < v.size()) sz <<= 1;\n    v.resize(sz);\n    for (int i = 1; i < sz; i <<=\
    \ 1) {\n        for (int j = 0; j < sz; j += (i<<1)) {\n            for (int k\
    \ = 0; k < i; ++k) {\n                T x = v[j+k], y = v[j+k+i];\n          \
    \      v[j+k] = (x+y), v[j+k+i] = (x-y);\n            }\n        }\n    }\n}\n\
    \nnamespace fwht_detail {\ntemplate<class T>\nauto inverse(vector<T> &v, int)\
    \ -> decltype(T(1).inv(), void()) {\n    fwht(v);\n    T inverse_size = T(v.size()).inv();\n\
    \    for (auto &x : v) x *= inverse_size;\n}\n\ntemplate<class T>\nvoid inverse(vector<T>\
    \ &v, long) {\n    int sz = 1;\n    while(sz < v.size()) sz <<= 1;\n    v.resize(sz);\n\
    \    for (int i = 1; i < sz; i <<= 1) {\n        for (int j = 0; j < sz; j +=\
    \ (i<<1)) {\n            for (int k = 0; k < i; ++k) {\n                T x =\
    \ v[j+k], y = v[j+k+i];\n                v[j+k] = (x+y)>>1, v[j+k+i] = (x-y)>>1;\n\
    \            }\n        }\n    }\n}\n}\n\ntemplate<class T>\nvoid ifwht(vector<T>\
    \ &v) {\n    fwht_detail::inverse(v, 0);\n}\n\ntemplate<class T>\nvector<T> xor_convolution(vector<T>\
    \ a, vector<T> b) {\n    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size())\
    \ n <<= 1;\n    a.resize(n);\n    b.resize(n);\n    fwht(a);\n    fwht(b);\n \
    \   for (int i = 0; i < n; ++i) a[i] *= b[i];\n    ifwht(a);\n    return a;\n\
    }\n\n/**\n * @brief \u9AD8\u901FWalsh-Hadamard\u5909\u63DB(FWHT)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/fwht.cpp
  requiredBy: []
  timestamp: '2026-10-18 09:29:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_bitwise_xor_convolution.test.cpp
  - test/yosupo_aplusb_fwht.test.cpp
  - test/aoj0402.test.cpp
date: 2026-03-08
documentation_of: math/fwht.cpp
layout: document
tags: "\u6570\u5B66"
title: "\u9AD8\u901FWalsh-Hadamard\u5909\u63DB(FWHT)"
---

## 説明
整数・modint の Walsh-Hadamard 変換と XOR 畳み込みを扱う。
変換後の長さを $L$ とすると、時間 $O(L\log L)$、畳み込みの追加領域は $O(L)$。

## できること
- `void fwht(vector<T>& v)`
  `v` を FWHT でその場変換する
- `void ifwht(vector<T>& v)`
  `v` を逆 FWHT でその場変換する。整数は段ごとに2で割り、modint は最後に長さの逆元を掛ける
- `vector<T> xor_convolution(vector<T> a, vector<T> b)`
  `c[k] = Σ_{i xor j = k} a[i] * b[j]` を返す。入力を保持し、両方空なら長さ1の零列を返す

## 使い方
長さが 2 冪でなくてもよく、不足分は零で埋める。
変換は入力を、畳み込みは両方の入力を収める最小の 2 冪長（最低1）を使う。
`xor_convolution(a, b)` だけで補完から逆変換まで行える。

`T` は零で初期化でき、`+`, `-` を持つこと。畳み込みには `*=` も必要。
`inv()` を持つ型は、逆変換にその逆元 API と `*=` を使う。2が可逆で、`inv()` が正しい逆元を返すことを前提とする。
既存の `mint` は奇素数の法で使う。法2には対応しない。

整数の逆変換には `>> 1` を使う。各段の和・差が2で割り切れ、変換や各点積の途中計算が型の範囲内に収まることを前提とする。
順変換してから逆変換すると、零で補完した元の列に戻る。
