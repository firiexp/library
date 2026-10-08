---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_swag.test.cpp
    title: test/yosupo_aplusb_swag.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_queue_operate_all_composite.test.cpp
    title: test/yosupo_queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: SWAG
    links: []
  bundledCode: "#line 1 \"datastructure/swag.cpp\"\n#include <optional>\n\ntemplate<class\
    \ G>\nclass SWAG {\n    using T = typename G::T;\n    vector<T> in, outsum;\n\
    \    optional<T> in_total;\npublic:\n    SWAG() : outsum(1, G::e()), in_total(G::e())\
    \ {}\n\n    void push(const T& v){\n        in_total.emplace(G::f(*in_total, v));\n\
    \        in.push_back(v);\n    }\n\n    void pop(){\n        if(outsum.size()\
    \ == 1){\n            do {\n                outsum.emplace_back(G::f(in.back(),\
    \ outsum.back()));\n                in.pop_back();\n            }while(!in.empty());\n\
    \            in_total.emplace(G::e());\n        }\n        outsum.pop_back();\n\
    \    }\n\n    T fold(){\n        return G::f(outsum.back(), *in_total);\n    }\n\
    };\n/*\nstruct Monoid {\n    using T = int;\n    static T f(T a, T b) { return\
    \ a+b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n * @brief SWAG\n */\n"
  code: "#include <optional>\n\ntemplate<class G>\nclass SWAG {\n    using T = typename\
    \ G::T;\n    vector<T> in, outsum;\n    optional<T> in_total;\npublic:\n    SWAG()\
    \ : outsum(1, G::e()), in_total(G::e()) {}\n\n    void push(const T& v){\n   \
    \     in_total.emplace(G::f(*in_total, v));\n        in.push_back(v);\n    }\n\
    \n    void pop(){\n        if(outsum.size() == 1){\n            do {\n       \
    \         outsum.emplace_back(G::f(in.back(), outsum.back()));\n             \
    \   in.pop_back();\n            }while(!in.empty());\n            in_total.emplace(G::e());\n\
    \        }\n        outsum.pop_back();\n    }\n\n    T fold(){\n        return\
    \ G::f(outsum.back(), *in_total);\n    }\n};\n/*\nstruct Monoid {\n    using T\
    \ = int;\n    static T f(T a, T b) { return a+b; }\n    static T e() { return\
    \ 0; }\n};\n*/\n\n/**\n * @brief SWAG\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/swag.cpp
  requiredBy: []
  timestamp: '2026-10-09 00:34:30+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_swag.test.cpp
  - test/yosupo_queue_operate_all_composite.test.cpp
date: 2020-02-19
documentation_of: datastructure/swag.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: SWAG
---

## 説明
キュー全体のモノイド積を、要素数 $N$ に対し償却 $O(1)$ の追加・削除と $O(1)$ の取得で扱う。
非可換な演算でも先頭から末尾の順に集約する。

## できること
- `SWAG<G> q` : 空のキューを作る。`G::T`、結合演算 `G::f(a, b)`、単位元 `G::e()` を定義する
- `push(v)` : 末尾に追加する
- `pop()` : 先頭を削除する。キューが空でないことが必要
- `fold()` : 全要素の積を返す。空なら単位元を返す

## 実装上の補足
入力側には各要素と全体積1個、出力側には累積積だけを保持する。領域は $O(N)$。
入力側を反転して出力側へ移す際も演算順序を保ち、逆元は使わない。
要素型はコピー構築可能であればよく、代入演算子は不要である。
