---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/slidingwindow.cpp\"\ntemplate<class T, class\
    \ F>\nclass sliding_window {\n    vector<T> v;\n    deque<T> Q;\n    F f;\npublic:\n\
    \    int l, r;\n    explicit sliding_window(vector<T> &v, F f) : v(v), f(f), l(0),\
    \ r(0) {};\n    void set(vector<T> &u){\n        v = u;\n        Q.clear();\n\
    \        l = 0; r = 0;\n    }\n    void reset(){\n        Q.clear();\n       \
    \ l = 0, r = 0;\n    }\n    void slideL(){\n        if(Q.front() == l++) Q.pop_front();\n\
    \    }\n    void slideR(){\n        while(!Q.empty() && !f(v[Q.back()], v[r]))\
    \ Q.pop_back();\n        Q.push_back(r++);\n    }\n    T get_index()  {\n    \
    \    if(l == r) return 0;\n        return Q.front();\n    }\n    T value()  {\n\
    \        if(l == r) return 0;\n        return v[Q.front()];\n    }\n};\n"
  code: "template<class T, class F>\nclass sliding_window {\n    vector<T> v;\n  \
    \  deque<T> Q;\n    F f;\npublic:\n    int l, r;\n    explicit sliding_window(vector<T>\
    \ &v, F f) : v(v), f(f), l(0), r(0) {};\n    void set(vector<T> &u){\n       \
    \ v = u;\n        Q.clear();\n        l = 0; r = 0;\n    }\n    void reset(){\n\
    \        Q.clear();\n        l = 0, r = 0;\n    }\n    void slideL(){\n      \
    \  if(Q.front() == l++) Q.pop_front();\n    }\n    void slideR(){\n        while(!Q.empty()\
    \ && !f(v[Q.back()], v[r])) Q.pop_back();\n        Q.push_back(r++);\n    }\n\
    \    T get_index()  {\n        if(l == r) return 0;\n        return Q.front();\n\
    \    }\n    T value()  {\n        if(l == r) return 0;\n        return v[Q.front()];\n\
    \    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/slidingwindow.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
date: 2018-04-28
documentation_of: datastructure/slidingwindow.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u30B9\u30E9\u30A4\u30C9\u6700\u5C0F\u5024(\u6700\u5927\u5024)"
---

## 説明
デックで区間 `[l, r)` の最良要素を保つ補助。
`slideR()` で右端を 1 つ伸ばし、`slideL()` で左端を 1 つ縮める。

## できること
- `sliding_window<T, F> sw(v, f)`
  配列 `v` と比較関数 `f` で初期化する
- `void slideR()`
  右端 `r` を 1 つ進めて `v[r]` を入れる
- `void slideL()`
  左端 `l` を 1 つ進める
- `T get_index()`
  現在の最良要素の添字を返す。空区間なら `0`
- `T value()`
  現在の最良値を返す。空区間なら `0`
- `void reset()`
  区間を空に戻す
- `void set(vector<T>& u)`
  参照先を差し替えて状態を初期化する

## 使い方
`f(a, b)` は `a` を残すべきなら `true` を返す比較にする。
最小値なら `[](T a, T b){ return a < b; }`、最大値なら `[](T a, T b){ return a > b; }` の形で使う。

## 実装上の補足
添字をデックで持つので、各操作は償却 $O(1)$。
空区間で `get_index()` や `value()` を呼ぶと `0` を返す。
