---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_queue_operate_all_composite.test.cpp
    title: test/yosupo_queue_operate_all_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: SWAG
    links: []
  bundledCode: "#line 1 \"datastructure/swag.cpp\"\ntemplate<class G>\nclass SWAG\
    \ {\n    using T = typename G::T;\n    vector<T> in, out, insum, outsum;\npublic:\n\
    \    SWAG() : in(0), out(0), insum(1, G::e()), outsum(1, G::e()) {}\n\n    void\
    \ push(const T& v){\n        insum.push_back(G::f(insum.back(), v));\n       \
    \ in.push_back(v);\n    }\n\n    void pop(){\n        if(out.empty()){\n     \
    \       do {\n                out.emplace_back(in.back());\n                outsum.emplace_back(G::f(in.back(),\
    \ outsum.back()));\n                in.pop_back(); insum.pop_back();\n       \
    \     }while(!in.empty());\n        }\n        out.pop_back(); outsum.pop_back();\n\
    \    }\n\n    T fold(){\n        return G::f(outsum.back(), insum.back());\n \
    \   }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static T f(T a, T b) {\
    \ return a+b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n * @brief SWAG\n\
    \ */\n"
  code: "template<class G>\nclass SWAG {\n    using T = typename G::T;\n    vector<T>\
    \ in, out, insum, outsum;\npublic:\n    SWAG() : in(0), out(0), insum(1, G::e()),\
    \ outsum(1, G::e()) {}\n\n    void push(const T& v){\n        insum.push_back(G::f(insum.back(),\
    \ v));\n        in.push_back(v);\n    }\n\n    void pop(){\n        if(out.empty()){\n\
    \            do {\n                out.emplace_back(in.back());\n            \
    \    outsum.emplace_back(G::f(in.back(), outsum.back()));\n                in.pop_back();\
    \ insum.pop_back();\n            }while(!in.empty());\n        }\n        out.pop_back();\
    \ outsum.pop_back();\n    }\n\n    T fold(){\n        return G::f(outsum.back(),\
    \ insum.back());\n    }\n};\n/*\nstruct Monoid {\n    using T = int;\n    static\
    \ T f(T a, T b) { return a+b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n\
    \ * @brief SWAG\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/swag.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_queue_operate_all_composite.test.cpp
date: 2020-02-19
documentation_of: datastructure/swag.cpp
layout: post
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Sliding Window Aggregation
---

## 説明
Queueをstack2つで表現することで、Queue内の和を求めることを高速に行う。

popするときに半分だけ持ってくるようにすると、Dequeにも対応できる。
