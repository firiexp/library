---
category: "\u30AF\u30A8\u30EA"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_static_range_inversions_query.test.cpp
    title: test/yosupo_static_range_inversions_query.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Mo's Algorithm
    links: []
  bundledCode: "#line 1 \"util/mo.cpp\"\nstruct Query {\n    static inline int bucket_size\
    \ = 1;\n    static inline int &B = bucket_size;\n    int l, r, no;\n    Query(int\
    \ l, int r, int no) : l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n\
    \    bool operator<(const Query &a) const {\n        int ablock = this->l / bucket_size,\
    \ bblock = a.l / bucket_size;\n        if(ablock != bblock) return ablock < bblock;\n\
    \        if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n/*\nfor (auto &&X : query) {\n    while(X.l < l) g(--l);\n    while(r\
    \ < X.r) f(r++);\n    while(l < X.l) g(l++);\n    while(X.r < r) f(--r);\n   \
    \ ans[X.no] = ans;\n}\n*/\n\n/**\n * @brief Mo's Algorithm\n */\n"
  code: "struct Query {\n    static inline int bucket_size = 1;\n    static inline\
    \ int &B = bucket_size;\n    int l, r, no;\n    Query(int l, int r, int no) :\
    \ l(l), r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n    bool operator<(const\
    \ Query &a) const {\n        int ablock = this->l / bucket_size, bblock = a.l\
    \ / bucket_size;\n        if(ablock != bblock) return ablock < bblock;\n     \
    \   if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n/*\nfor (auto &&X : query) {\n    while(X.l < l) g(--l);\n    while(r\
    \ < X.r) f(r++);\n    while(l < X.l) g(l++);\n    while(X.r < r) f(--r);\n   \
    \ ans[X.no] = ans;\n}\n*/\n\n/**\n * @brief Mo's Algorithm\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/mo.cpp
  requiredBy: []
  timestamp: '2026-03-25 22:24:13+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_static_range_inversions_query.test.cpp
date: 2026-03-25
documentation_of: util/mo.cpp
layout: document
tags: "\u30AF\u30A8\u30EA"
title: Mo's Algorithm
---

## 説明
区間のマージは高速にできないが、区間を 1 つ広げる/縮めることが $O(p(N))$ でできれば、$Q$ 個のクエリをまとめて処理できる。

## できること
- `Query(l, r, no)`
  半開区間 `[l, r)` のクエリを作る
- `Query::B`
  左端を分けるバケット幅。`sort` 前に利用側で設定する
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる

## 使い方
クエリを読み込んだら `Query::bucket_size = B;` を設定し、`sort(qs.begin(), qs.end())` で並べ替える。
あとは区間の左右端を少しずつ動かしながら答えを更新する。

## 実装上の補足
- 典型的な計算量評価は、左端の移動が $O(QB)$、右端の移動が $O(N^2 / B)$ なので、1 回の追加・削除が $O(p(N))$ なら合計は
$$
O\left(\left(QB + \frac{N^2}{B}\right) p(N)\right)
$$
  になる
- これを最小化する目安が
$$
B \approx \frac{N}{\sqrt{Q}}
$$
  なので、まずはこの値を目安に `Query::bucket_size` を決め、必要なら定数倍を見ながら手で調整するとよい
- `Q` と `N` が同程度なら $B \approx \sqrt{N}$ と見てよい
