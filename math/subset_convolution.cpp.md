---
category: "\u6570\u5B66"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_subset_convolution.test.cpp
    title: test/yosupo_subset_convolution.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u90E8\u5206\u96C6\u5408\u7573\u307F\u8FBC\u307F(Subset Convolution)"
    links: []
  bundledCode: "#line 1 \"math/subset_convolution.cpp\"\ntemplate<class T>\nvector<T>\
    \ subset_convolution(vector<T> a, vector<T> b){\n    int n = 1;\n    while (n\
    \ < (int)a.size() || n < (int)b.size()) n <<= 1;\n    a.resize(n);\n    b.resize(n);\n\
    \    int lg = 0;\n    while ((1 << lg) < n) ++lg;\n    int w = lg + 1;\n    vector<int>\
    \ pc(n);\n    for (int s = 1; s < n; ++s) pc[s] = pc[s >> 1] + (s & 1);\n\n  \
    \  vector<T> fa(n * w), fb(n * w), fc(n * w);\n    for (int s = 0; s < n; ++s)\
    \ {\n        int base = s * w;\n        fa[base + pc[s]] = a[s];\n        fb[base\
    \ + pc[s]] = b[s];\n    }\n\n    for (int i = 0; i < lg; ++i) {\n        for (int\
    \ s = 0; s < n; ++s) {\n            if (((s >> i) & 1) == 0) {\n             \
    \   int t = s | (1 << i);\n                int sb = s * w, tb = t * w;\n     \
    \           for (int k = 0; k <= pc[s]; ++k) {\n                    fa[tb + k]\
    \ += fa[sb + k];\n                    fb[tb + k] += fb[sb + k];\n            \
    \    }\n            }\n        }\n    }\n    for (int s = 0; s < n; ++s) {\n \
    \       int base = s * w;\n        int lim = min(lg, pc[s] * 2);\n        for\
    \ (int k = 0; k <= lim; ++k) {\n            for (int i = 0; i <= k; ++i) {\n \
    \               if (i <= pc[s] && k - i <= pc[s]) {\n                    fc[base\
    \ + k] += fa[base + i] * fb[base + k - i];\n                }\n            }\n\
    \        }\n    }\n    for (int i = 0; i < lg; ++i) {\n        for (int s = 0;\
    \ s < n; ++s) {\n            if (((s >> i) & 1) == 0) {\n                int t\
    \ = s | (1 << i);\n                int sb = s * w, tb = t * w;\n             \
    \   int lim = min(lg, pc[s] * 2);\n                for (int k = 0; k <= lim; ++k)\
    \ {\n                    fc[tb + k] -= fc[sb + k];\n                }\n      \
    \      }\n        }\n    }\n\n    vector<T> c(n);\n    for (int s = 0; s < n;\
    \ ++s) {\n        c[s] = fc[s * w + pc[s]];\n    }\n    return c;\n}\n\n/**\n\
    \ * @brief \u90E8\u5206\u96C6\u5408\u7573\u307F\u8FBC\u307F(Subset Convolution)\n\
    \ */\n"
  code: "template<class T>\nvector<T> subset_convolution(vector<T> a, vector<T> b){\n\
    \    int n = 1;\n    while (n < (int)a.size() || n < (int)b.size()) n <<= 1;\n\
    \    a.resize(n);\n    b.resize(n);\n    int lg = 0;\n    while ((1 << lg) < n)\
    \ ++lg;\n    int w = lg + 1;\n    vector<int> pc(n);\n    for (int s = 1; s <\
    \ n; ++s) pc[s] = pc[s >> 1] + (s & 1);\n\n    vector<T> fa(n * w), fb(n * w),\
    \ fc(n * w);\n    for (int s = 0; s < n; ++s) {\n        int base = s * w;\n \
    \       fa[base + pc[s]] = a[s];\n        fb[base + pc[s]] = b[s];\n    }\n\n\
    \    for (int i = 0; i < lg; ++i) {\n        for (int s = 0; s < n; ++s) {\n \
    \           if (((s >> i) & 1) == 0) {\n                int t = s | (1 << i);\n\
    \                int sb = s * w, tb = t * w;\n                for (int k = 0;\
    \ k <= pc[s]; ++k) {\n                    fa[tb + k] += fa[sb + k];\n        \
    \            fb[tb + k] += fb[sb + k];\n                }\n            }\n   \
    \     }\n    }\n    for (int s = 0; s < n; ++s) {\n        int base = s * w;\n\
    \        int lim = min(lg, pc[s] * 2);\n        for (int k = 0; k <= lim; ++k)\
    \ {\n            for (int i = 0; i <= k; ++i) {\n                if (i <= pc[s]\
    \ && k - i <= pc[s]) {\n                    fc[base + k] += fa[base + i] * fb[base\
    \ + k - i];\n                }\n            }\n        }\n    }\n    for (int\
    \ i = 0; i < lg; ++i) {\n        for (int s = 0; s < n; ++s) {\n            if\
    \ (((s >> i) & 1) == 0) {\n                int t = s | (1 << i);\n           \
    \     int sb = s * w, tb = t * w;\n                int lim = min(lg, pc[s] * 2);\n\
    \                for (int k = 0; k <= lim; ++k) {\n                    fc[tb +\
    \ k] -= fc[sb + k];\n                }\n            }\n        }\n    }\n\n  \
    \  vector<T> c(n);\n    for (int s = 0; s < n; ++s) {\n        c[s] = fc[s * w\
    \ + pc[s]];\n    }\n    return c;\n}\n\n/**\n * @brief \u90E8\u5206\u96C6\u5408\
    \u7573\u307F\u8FBC\u307F(Subset Convolution)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: math/subset_convolution.cpp
  requiredBy: []
  timestamp: '2026-03-10 23:38:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_subset_convolution.test.cpp
date: 2026-03-10
documentation_of: math/subset_convolution.cpp
layout: document
tags: "\u6570\u5B66"
title: Subset Convolution
---

## 説明
部分集合畳み込みを計算する。
`c[S] = Σ_{T ⊆ S} a[T] b[S \ T]` を返す。
計算量は `N = 2^n` として $O(n^2 N)$。

## できること
- `vector<T> subset_convolution(vector<T> a, vector<T> b)`
  部分集合畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=` が必要。
典型的には bitmask DP の畳み込みに使う。
