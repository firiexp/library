---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
    title: test/yosupo_range_affine_point_get_dualsegtree.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment\
      \ Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/dualsegtree.cpp\"\ntemplate <class M>\nstruct\
    \ DualSegmentTree{\n    using T = typename M::T;\n    int sz, height{};\n    vector<T>\
    \ lazy;\n    explicit DualSegmentTree(int n) {\n        sz = 1; while(sz < n)\
    \ sz <<= 1, height++;\n        lazy.assign(2*sz, M::e());\n    }\n\n    void eval(int\
    \ k){\n        if(lazy[k] == M::e()) return;\n        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0],\
    \ lazy[k]);\n        lazy[(k<<1)|1] = M::f(lazy[(k<<1)|1], lazy[k]);\n       \
    \ lazy[k] = M::e();\n    }\n    void thrust(int k){ for (int i = height; i; --i)\
    \ eval(k>>i); }\n    void update(int a, int b, const T &x){\n        thrust(a\
    \ += sz); thrust(b += sz-1);\n        for (int l = a, r = b+1;l < r; l >>=1, r\
    \ >>= 1) {\n            if(l&1) lazy[l] = M::f(lazy[l], x), l++;\n           \
    \ if(r&1) --r, lazy[r] = M::f(lazy[r], x);\n        }\n    }\n\n    T operator[](int\
    \ k){\n        thrust(k += sz);\n        return lazy[k];\n    }\n};\n/*\nstruct\
    \ Monoid{\n    using T = ll;\n    static T f(T a, T b) { return a+b; }\n    static\
    \ T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u53CC\u5BFE\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728(Dual Segment Tree)\n */\n"
  code: "template <class M>\nstruct DualSegmentTree{\n    using T = typename M::T;\n\
    \    int sz, height{};\n    vector<T> lazy;\n    explicit DualSegmentTree(int\
    \ n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        lazy.assign(2*sz,\
    \ M::e());\n    }\n\n    void eval(int k){\n        if(lazy[k] == M::e()) return;\n\
    \        lazy[(k<<1)|0] = M::f(lazy[(k<<1)|0], lazy[k]);\n        lazy[(k<<1)|1]\
    \ = M::f(lazy[(k<<1)|1], lazy[k]);\n        lazy[k] = M::e();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void update(int\
    \ a, int b, const T &x){\n        thrust(a += sz); thrust(b += sz-1);\n      \
    \  for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l]\
    \ = M::f(lazy[l], x), l++;\n            if(r&1) --r, lazy[r] = M::f(lazy[r], x);\n\
    \        }\n    }\n\n    T operator[](int k){\n        thrust(k += sz);\n    \
    \    return lazy[k];\n    }\n};\n/*\nstruct Monoid{\n    using T = ll;\n    static\
    \ T f(T a, T b) { return a+b; }\n    static T e() { return 0; }\n};\n*/\n\n/**\n\
    \ * @brief \u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment Tree)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dualsegtree.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_range_affine_point_get_dualsegtree.test.cpp
documentation_of: datastructure/dualsegtree.cpp
layout: document
title: "\u53CC\u5BFE\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Dual Segment Tree)"
---
## 説明
区間更新・一点取得を扱う双対セグメント木である。
演算は結合則を満たせばよく、各操作は `O(log N)`。

## できること
- `DualSegmentTree<M> seg(n)`
  長さ `n`、初期値がすべて `M::e()` の双対セグメント木を作る
- `void update(int l, int r, T x)`
  半開区間 `[l, r)` に作用 `x` を適用する
- `T operator[](int k)`
  位置 `k` にかかっている作用の合成結果を返す

## 使い方
`M` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。
`f(a, b)` は「先に `a`、後に `b` を適用した合成」を返すようにする。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

DualSegmentTree<Monoid> seg(n);
seg.update(l, r, x);
long long v = seg[p];
```

初期配列 `a` が別にあるときは、`seg[p]` で得た作用を `a[p]` に適用して答えを作る。

## 実装上の補足
この実装は `update(l, r, x)` が半開区間である。
`eval` で単位元判定をするため、`T` には `==` が必要である。
