---
category: util
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_rle.test.cpp
    title: test/yosupo_many_aplusb_rle.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E(RLE)"
    links: []
  bundledCode: "#line 1 \"util/rle.cpp\"\ntemplate<class T>\nvector<pair<T, int>>\
    \ RLE(const vector<T> &a){\n    vector<pair<T, int>> p;\n    if(a.empty()) return\
    \ p;\n    p.emplace_back(a[0], 1);\n    for (int j = 1; j < (int)a.size(); ++j)\
    \ {\n        if(p.back().first == a[j]) p.back().second++;\n        else p.emplace_back(a[j],\
    \ 1);\n    }\n    return p;\n}\n\n/**\n * @brief \u30E9\u30F3\u30EC\u30F3\u30B0\
    \u30B9\u5727\u7E2E(RLE)\n */\n"
  code: "template<class T>\nvector<pair<T, int>> RLE(const vector<T> &a){\n    vector<pair<T,\
    \ int>> p;\n    if(a.empty()) return p;\n    p.emplace_back(a[0], 1);\n    for\
    \ (int j = 1; j < (int)a.size(); ++j) {\n        if(p.back().first == a[j]) p.back().second++;\n\
    \        else p.emplace_back(a[j], 1);\n    }\n    return p;\n}\n\n/**\n * @brief\
    \ \u30E9\u30F3\u30EC\u30F3\u30B0\u30B9\u5727\u7E2E(RLE)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/rle.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_rle.test.cpp
date: 2026-03-08
documentation_of: util/rle.cpp
layout: document
tags: util
title: RLE
---

## 説明
列を run-length encoding する。
連続する同じ値を `(値, 個数)` にまとめる。
計算量は `O(N)`。

## できること
- `vector<pair<T, int>> RLE(const vector<T>& a)`
  `a` を run-length encoding した列を返す。空配列なら空配列を返す

## 使い方
`T` には `==` が必要。
返り値の各要素は出現順に並ぶ。
