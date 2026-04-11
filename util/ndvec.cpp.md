---
category: "\u30E6\u30FC\u30C6\u30A3\u30EA\u30C6\u30A3"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_ndvec.test.cpp
    title: test/yosupo_aplusb_ndvec.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u6B21\u5143\u914D\u5217(NdVec)"
    links: []
  bundledCode: "#line 1 \"util/ndvec.cpp\"\ntemplate <class T, size_t N>\nstruct NdVec\
    \ {\n    array<int, N> dim{};\n    array<long long, N> stride{};\n    vector<T>\
    \ data;\n\n    NdVec() = default;\n\n    NdVec(array<int, N> dim_, const T &init\
    \ = T()) : dim(dim_) {\n        long long sz = 1;\n        for (size_t i = 0;\
    \ i < N; ++i) assert(dim[i] >= 0);\n        for (size_t i = N; i-- > 0;) {\n \
    \           stride[i] = sz;\n            sz *= dim[i];\n        }\n        data.assign(sz,\
    \ init);\n    }\n\n    long long size() const {\n        return (long long)data.size();\n\
    \    }\n\n    template <class... Idx>\n    long long index(Idx... idx) const {\n\
    \        static_assert(sizeof...(Idx) == N);\n        array<long long, N> id{static_cast<long\
    \ long>(idx)...};\n        long long p = 0;\n        for (size_t i = 0; i < N;\
    \ ++i) p += id[i] * stride[i];\n        return p;\n    }\n\n    template <class...\
    \ Idx>\n    T &operator()(Idx... idx) {\n        return data[index(idx...)];\n\
    \    }\n\n    template <class... Idx>\n    const T &operator()(Idx... idx) const\
    \ {\n        return data[index(idx...)];\n    }\n\n    void fill(const T &value)\
    \ {\n        std::fill(data.begin(), data.end(), value);\n    }\n};\n\n/**\n *\
    \ @brief \u591A\u6B21\u5143\u914D\u5217(NdVec)\n */\n"
  code: "template <class T, size_t N>\nstruct NdVec {\n    array<int, N> dim{};\n\
    \    array<long long, N> stride{};\n    vector<T> data;\n\n    NdVec() = default;\n\
    \n    NdVec(array<int, N> dim_, const T &init = T()) : dim(dim_) {\n        long\
    \ long sz = 1;\n        for (size_t i = 0; i < N; ++i) assert(dim[i] >= 0);\n\
    \        for (size_t i = N; i-- > 0;) {\n            stride[i] = sz;\n       \
    \     sz *= dim[i];\n        }\n        data.assign(sz, init);\n    }\n\n    long\
    \ long size() const {\n        return (long long)data.size();\n    }\n\n    template\
    \ <class... Idx>\n    long long index(Idx... idx) const {\n        static_assert(sizeof...(Idx)\
    \ == N);\n        array<long long, N> id{static_cast<long long>(idx)...};\n  \
    \      long long p = 0;\n        for (size_t i = 0; i < N; ++i) p += id[i] * stride[i];\n\
    \        return p;\n    }\n\n    template <class... Idx>\n    T &operator()(Idx...\
    \ idx) {\n        return data[index(idx...)];\n    }\n\n    template <class...\
    \ Idx>\n    const T &operator()(Idx... idx) const {\n        return data[index(idx...)];\n\
    \    }\n\n    void fill(const T &value) {\n        std::fill(data.begin(), data.end(),\
    \ value);\n    }\n};\n\n/**\n * @brief \u591A\u6B21\u5143\u914D\u5217(NdVec)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: util/ndvec.cpp
  requiredBy: []
  timestamp: '2026-04-11 16:39:45+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_ndvec.test.cpp
date: 2026-04-11
documentation_of: util/ndvec.cpp
layout: document
tags: "\u30E6\u30FC\u30C6\u30A3\u30EA\u30C6\u30A3"
title: "\u591A\u6B21\u5143\u914D\u5217(NdVec)"
---

## 説明
多次元配列を 1 次元 `vector` に載せて管理する。
各要素アクセスは $O(N)$。

## できること
- `NdVec<T, N> a`
  空の `NdVec` を作る
- `NdVec<T, N> a(dim, init)`
  各次元長 `dim` の配列を作り、全要素を `init` で初期化する
- `long long a.size()`
  確保した総要素数を返す
- `long long a.index(i0, i1, ..., i{N-1})`
  多次元添字に対応する 1 次元 index を返す
- `a(i0, i1, ..., i{N-1})`
  その位置の要素を参照する
- `a.fill(x)`
  全要素を `x` にする

## 使い方
`dim[k]` を第 `k` 次元の長さとして `NdVec<T, N> a(dim, init);` を作る。
添字は `a(i, j, k)` のように関数呼び出し形式で渡す。

```cpp
NdVec<long long, 3> dp({n, m, k}, -1);
dp(0, 0, 0) = 0;
dp.fill(0);
```

内部では右端の次元を最下位として持つ。
つまり `dim = {a, b, c}` のとき、`index(i, j, k) = (i b + j) c + k` になる。
