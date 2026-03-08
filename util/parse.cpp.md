---
category: "\u6587\u5B57\u5217"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_parse.test.cpp
    title: test/yosupo_many_aplusb_parse.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5F0F\u30D1\u30FC\u30B5(Parse)"
    links: []
  bundledCode: "#line 1 \"util/parse.cpp\"\nusing state = string::const_iterator;\n\
    \ \nint num(state &cur);\nint factor(state &cur);\nint muldiv(state &cur);\nint\
    \ addsub(state &cur);\nint expr(state &cur);\n \nint factor(state &cur) {\n  \
    \  if(isdigit(*cur)) return num(cur);\n    cur++;\n    int ans = addsub(cur);\n\
    \    cur++;\n    return ans;\n}\n \nint num(state &cur) {\n    int ans = *cur\
    \ -'0';\n    while(isdigit(*++cur)) ans = ans*10 + (*cur-'0');\n    return ans;\n\
    }\n \nint muldiv(state &cur) {\n    int ans = factor(cur);\n    while(true){\n\
    \        if(*cur == '*'){\n            cur++;\n            ans *= factor(cur);\n\
    \        }else if(*cur == '/'){\n            cur++;\n            ans /= factor(cur);\n\
    \        }else break;\n    }\n    return ans;\n}\n \nint addsub(state &cur){\n\
    \    int ans = muldiv(cur);\n    while(true){\n        if(*cur == '+'){\n    \
    \        cur++;\n            ans += muldiv(cur);\n        }else if(*cur == '-'){\n\
    \            cur++;\n            ans -= muldiv(cur);\n        }else break;\n \
    \   }\n    return ans;\n}\n \nint expr(state &cur){\n    return addsub(cur);\n\
    }\n\n/**\n * @brief \u5F0F\u30D1\u30FC\u30B5(Parse)\n */\n"
  code: "using state = string::const_iterator;\n \nint num(state &cur);\nint factor(state\
    \ &cur);\nint muldiv(state &cur);\nint addsub(state &cur);\nint expr(state &cur);\n\
    \ \nint factor(state &cur) {\n    if(isdigit(*cur)) return num(cur);\n    cur++;\n\
    \    int ans = addsub(cur);\n    cur++;\n    return ans;\n}\n \nint num(state\
    \ &cur) {\n    int ans = *cur -'0';\n    while(isdigit(*++cur)) ans = ans*10 +\
    \ (*cur-'0');\n    return ans;\n}\n \nint muldiv(state &cur) {\n    int ans =\
    \ factor(cur);\n    while(true){\n        if(*cur == '*'){\n            cur++;\n\
    \            ans *= factor(cur);\n        }else if(*cur == '/'){\n           \
    \ cur++;\n            ans /= factor(cur);\n        }else break;\n    }\n    return\
    \ ans;\n}\n \nint addsub(state &cur){\n    int ans = muldiv(cur);\n    while(true){\n\
    \        if(*cur == '+'){\n            cur++;\n            ans += muldiv(cur);\n\
    \        }else if(*cur == '-'){\n            cur++;\n            ans -= muldiv(cur);\n\
    \        }else break;\n    }\n    return ans;\n}\n \nint expr(state &cur){\n \
    \   return addsub(cur);\n}\n\n/**\n * @brief \u5F0F\u30D1\u30FC\u30B5(Parse)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/parse.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_parse.test.cpp
date: 2026-03-08
documentation_of: util/parse.cpp
layout: post
tags: "\u6587\u5B57\u5217"
title: "\u56DB\u5247\u6F14\u7B97\u30D1\u30FC\u30B5"
---

## 説明
整数と `()+-*/` からなる式を再帰下降で評価する。
空白や単項演算子は扱わない。

## できること
- `int expr(state& cur)`
  式全体を評価する。`+` と `-` を扱う
- `int addsub(state& cur)`
  加減算を評価する
- `int muldiv(state& cur)`
  乗除算を評価する
- `int factor(state& cur)`
  数値または括弧付き式を評価する
- `int num(state& cur)`
  連続する数字を読み取って整数にする。数字で始まらなければ未定義

## 使い方
`state cur = s.begin();` を作り、`expr(cur)` を呼ぶ。
式末尾には番兵として `'\0'` 相当の停止位置がある前提で、`cur == s.end()` の検査は自前で行う。

## 実装上の補足
除算は C++ の整数除算そのままで、0 除算や不正な式は想定しない。
負数を読みたいなら、呼び出し側で前処理を入れるか文法を拡張する。
