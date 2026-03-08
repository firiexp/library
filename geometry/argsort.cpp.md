---
category: "\u5E7E\u4F55"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_argsort.test.cpp
    title: test/yosupo_many_aplusb_argsort.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)"
    links: []
  bundledCode: "#line 1 \"geometry/argsort.cpp\"\nusing Ar2 = array<int, 2>;\nvoid\
    \ argsort(vector<Ar2> &v)\n{\n    auto pos = [&](Ar2 &x) -> int\n    { if(x[1])\
    \ return x[1] < 0 ? -1 : 1; else return x[0] < 0; };\n    sort(v.begin(), v.end(),\
    \ [&](Ar2 a, Ar2 b)\n         {\n        if(pos(a) != pos(b)) return pos(a) <\
    \ pos(b);\n        return (ll)a[0]*b[1] > (ll)a[1]*b[0]; });\n}\n\n/**\n * @brief\
    \ \u504F\u89D2\u30BD\u30FC\u30C8(Argument Sort)\n */\n"
  code: "using Ar2 = array<int, 2>;\nvoid argsort(vector<Ar2> &v)\n{\n    auto pos\
    \ = [&](Ar2 &x) -> int\n    { if(x[1]) return x[1] < 0 ? -1 : 1; else return x[0]\
    \ < 0; };\n    sort(v.begin(), v.end(), [&](Ar2 a, Ar2 b)\n         {\n      \
    \  if(pos(a) != pos(b)) return pos(a) < pos(b);\n        return (ll)a[0]*b[1]\
    \ > (ll)a[1]*b[0]; });\n}\n\n/**\n * @brief \u504F\u89D2\u30BD\u30FC\u30C8(Argument\
    \ Sort)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: geometry/argsort.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_argsort.test.cpp
date: 2026-03-08
documentation_of: geometry/argsort.cpp
layout: document
tags: "\u5E7E\u4F55"
title: Arg Sort
---

## 説明
整数ベクトルを偏角順に並べる。
下半平面から始めて反時計回りになる順で sort する。
計算量は `O(N log N)`。

## できること
- `void argsort(vector<array<int, 2>>& v)`
  `v` を偏角順にその場で並べ替える

## 使い方
原点ベクトル `(0, 0)` を含むと順序の意味が弱いので基本は入れない。
同一直線上のベクトルの順序は長さでなく外積比較に従う。
