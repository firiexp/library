---
category: "\u4E71\u6570"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: string/rolling_hash.cpp
    title: Rolling-Hash
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0355.test.cpp
    title: test/aoj0355.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"util/xorshift.cpp\"\nclass xor_shift {\n    uint32_t x,\
    \ y, z, w;\npublic:\n    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        if(n < 0) return -rand(-n);\n       \
    \ uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);\n        uint32_t\
    \ e = urand();\n        while(e >= t) e = urand();\n        return static_cast<int>(e%(n+1));\n\
    \    }\n\n    int rand(int a, int b){\n        if(a > b) swap(a, b);\n       \
    \ return a+rand(b-a);\n    }\n};\n"
  code: "class xor_shift {\n    uint32_t x, y, z, w;\npublic:\n    xor_shift() : x(static_cast<uint32_t>((chrono::system_clock::now().time_since_epoch().count())&((1LL\
    \ << 32)-1))),\n    y(1068246329), z(321908594), w(1234567890) {};\n\n    uint32_t\
    \ urand(){\n        uint32_t t;\n        t = x ^ (x << 11);\n        x = y; y\
    \ = z; z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    };\n\n    int rand(int n){\n        if(n < 0) return -rand(-n);\n       \
    \ uint32_t t = numeric_limits<uint32_t>::max()/(n+1)*(n+1);\n        uint32_t\
    \ e = urand();\n        while(e >= t) e = urand();\n        return static_cast<int>(e%(n+1));\n\
    \    }\n\n    int rand(int a, int b){\n        if(a > b) swap(a, b);\n       \
    \ return a+rand(b-a);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: util/xorshift.cpp
  requiredBy:
  - string/rolling_hash.cpp
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0355.test.cpp
date: 2018-04-28
documentation_of: util/xorshift.cpp
layout: document
tags: "\u4E71\u6570"
title: Xor-Shift
---

## 説明
軽量な xorshift 乱数生成器。
`uint32_t` を返す生乱数と、区間乱数を持つ。

## できること
- `xor_shift rng`
  現在時刻ベースで初期化する
- `uint32_t urand()`
  `uint32_t` の乱数を返す
- `int rand(int n)`
  `0..n` の一様乱数を返す。`n < 0` なら `-n..0`
- `int rand(int a, int b)`
  `a..b` の一様乱数を返す。`a > b` でもよい

## 使い方
`xor_shift rng;` を作って `rng.urand()` や `rng.rand(l, r)` を呼ぶ。
ちょっとした randomized algorithm やテスト生成向け。

## 実装上の補足
`rand(int n)` は棄却法で偏りを消している。
再現性が必要な用途向けの seed 指定 API は持たない。
