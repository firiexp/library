---
category: util
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yuki1358.test.cpp
    title: test/yuki1358.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5E8A\u9664\u7B97\u30FB\u5929\u4E95\u9664\u7B97(Floor/Ceil Division)"
    links: []
  bundledCode: "#line 1 \"util/ifloor.cpp\"\ntemplate<class T>T ifloor(T x, T y){\n\
    \    return x/y-(x%y ? (x < 0)^(y < 0) : 0);\n}\n\ntemplate<class T>inline T iceil(T\
    \ x, T y){\n    return x/y+(x%y ? (x >= 0)^(y < 0) : 0);\n}\n\n/**\n * @brief\
    \ \u5E8A\u9664\u7B97\u30FB\u5929\u4E95\u9664\u7B97(Floor/Ceil Division)\n */\n"
  code: "template<class T>T ifloor(T x, T y){\n    return x/y-(x%y ? (x < 0)^(y <\
    \ 0) : 0);\n}\n\ntemplate<class T>inline T iceil(T x, T y){\n    return x/y+(x%y\
    \ ? (x >= 0)^(y < 0) : 0);\n}\n\n/**\n * @brief \u5E8A\u9664\u7B97\u30FB\u5929\
    \u4E95\u9664\u7B97(Floor/Ceil Division)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/ifloor.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yuki1358.test.cpp
date: 2026-03-08
documentation_of: util/ifloor.cpp
layout: post
tags: util
title: IFloor
---

## 説明
符号付き整数に対する床除算と天井除算。
C++ の `/` は 0 方向丸めなので、その差を吸収する。

## できること
- `T ifloor(T x, T y)`
  `floor(x / y)` を返す
- `T iceil(T x, T y)`
  `ceil(x / y)` を返す

## 使い方
`y != 0` を仮定する。
負数を含む除算境界の計算で使う。
