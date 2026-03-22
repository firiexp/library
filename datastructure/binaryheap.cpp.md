---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj_alds1_9_c_binaryheap.test.cpp
    title: test/aoj_alds1_9_c_binaryheap.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u4E8C\u5206\u30D2\u30FC\u30D7(Binary Heap)"
    links: []
  bundledCode: "#line 1 \"datastructure/binaryheap.cpp\"\ntemplate<typename T>\nstruct\
    \ binary_heap {\n    ll S;\n    vector<T> Q;\n    binary_heap() : S(0), Q() {}\n\
    \n    T top() const { return Q.front(); }\n    size_t size() const { return Q.size();\
    \ }\n    void pop() {\n        pop_heap(Q.begin(),Q.end());\n        S -= Q.back();\n\
    \        Q.pop_back();\n    }\n    void emplace(T x) {\n        S += x;\n    \
    \    Q.emplace_back(x);\n        push_heap(Q.begin(),Q.end());\n    }\n    bool\
    \ empty() { return Q.empty(); }\n    ll sum() const { return S; }\n};\n\n/**\n\
    \ * @brief \u4E8C\u5206\u30D2\u30FC\u30D7(Binary Heap)\n */\n"
  code: "template<typename T>\nstruct binary_heap {\n    ll S;\n    vector<T> Q;\n\
    \    binary_heap() : S(0), Q() {}\n\n    T top() const { return Q.front(); }\n\
    \    size_t size() const { return Q.size(); }\n    void pop() {\n        pop_heap(Q.begin(),Q.end());\n\
    \        S -= Q.back();\n        Q.pop_back();\n    }\n    void emplace(T x) {\n\
    \        S += x;\n        Q.emplace_back(x);\n        push_heap(Q.begin(),Q.end());\n\
    \    }\n    bool empty() { return Q.empty(); }\n    ll sum() const { return S;\
    \ }\n};\n\n/**\n * @brief \u4E8C\u5206\u30D2\u30FC\u30D7(Binary Heap)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/binaryheap.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj_alds1_9_c_binaryheap.test.cpp
documentation_of: datastructure/binaryheap.cpp
layout: document
title: "\u4E8C\u5206\u30D2\u30FC\u30D7(Binary Heap)"
---
## 説明
最大値を取り出す二分ヒープである。
`push`、`pop`、`top` を $O(log N)$ で扱い、要素和も同時に管理する。

## できること
- `binary_heap<T> pq`
  空の最大ヒープを作る
- `void emplace(T x)`
  `x` を追加する
- `T top() const`
  最大値を返す。空のときは未定義
- `void pop()`
  最大値を 1 つ削除する。空のときは未定義
- `size_t size() const`
  要素数を返す
- `bool empty()`
  空なら `true` を返す
- `ll sum() const`
  全要素の総和を返す

## 使い方
`T` は `operator<` と `ll` への加減算ができる型を想定している。

```cpp
binary_heap<int> pq;
pq.emplace(3);
pq.emplace(8);
int mx = pq.top();
ll s = pq.sum();
pq.pop();
```

## 実装上の補足
`std::push_heap` / `std::pop_heap` を使った最大ヒープである。
`sum()` は `ll` で保持するので、`T` が大きいときはオーバーフローに注意する。
