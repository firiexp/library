---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
    title: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_set_range_composite.test.cpp
    title: test/yosupo_point_set_range_composite.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_add_subtree_sum_hld_rerooted.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_hld_rerooted.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite.test.cpp
    title: test/yosupo_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
    title: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite_hld_ordered.test.cpp
    title: test/yosupo_vertex_set_path_composite_hld_ordered.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki650_hld_edge.test.cpp
    title: test/yuki650_hld_edge.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: Segment Tree
    links: []
  bundledCode: "#line 1 \"datastructure/segmenttree/segtree.cpp\"\ntemplate <class\
    \ M>\nstruct SegmentTree{\n    using T = typename M::T;\n    int sz, n, height{};\n\
    \    vector<T> seg;\n    explicit SegmentTree(int n) : n(n) {\n        sz = 1;\
    \ while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n    }\n\
    \n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n    void build(){\n \
    \       for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);\n\
    \    }\n\n    void update(int k, const T &x){\n        k += sz;\n        seg[k]\
    \ = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n    }\n\n\
    \    T query(int a, int b){\n        T l = M::e(), r = M::e();\n        for(a\
    \ += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l, seg[a++]);\n\
    \            if(b & 1) r = M::f(seg[--b], r);\n        }\n        return M::f(l,\
    \ r);\n    }\n\n    template<class F>\n    int search_right(int l, F cond){\n\
    \        if(l == n) return n;\n        T val = M::e();\n        l += sz;\n   \
    \     do {\n            while(!(l&1)) l >>= 1;\n            T next = M::f(val,\
    \ seg[l]);\n            if(!cond(next)){\n                while(l < sz) {\n  \
    \                  l <<= 1;\n                    next = M::f(val, seg[l]);\n \
    \                   if (cond(next)){\n                        val = move(next);\n\
    \                        l++;\n                    }\n                }\n    \
    \            return l - sz;\n            }\n            val = move(next);\n  \
    \          l++;\n        } while((l & -l) != l);\n        return n;\n    }\n\n\
    \    template<class F>\n    int search_left(int r, F cond){\n        if(r == 0)\
    \ return 0;\n        T val = M::e();\n        r += sz;\n        do {\n       \
    \     r--;\n            while(r > 1 && (r & 1)) r >>= 1;\n            T next =\
    \ M::f(seg[r], val);\n            if(!cond(next)){\n                while(r <\
    \ sz) {\n                    r = ((r << 1)|1);\n                    next = M::f(seg[r],\
    \ val);\n                    if (cond(next)){\n                        val = move(next);\n\
    \                        r--;\n                    }\n                }\n    \
    \            return r + 1 - sz;\n            }\n            val = move(next);\n\
    \        } while((r & -r) != r);\n        return 0;\n    }\n    T operator[](const\
    \ int &k) const { return seg[k + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using\
    \ T = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]};\
    \ }\n    static T e() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief Segment Tree\n\
    \ */\n"
  code: "template <class M>\nstruct SegmentTree{\n    using T = typename M::T;\n \
    \   int sz, n, height{};\n    vector<T> seg;\n    explicit SegmentTree(int n)\
    \ : n(n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
    \ M::e());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i],\
    \ seg[2*i+1]);\n    }\n\n    void update(int k, const T &x){\n        k += sz;\n\
    \        seg[k] = x;\n        while (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n\
    \    }\n\n    T query(int a, int b){\n        T l = M::e(), r = M::e();\n    \
    \    for(a += sz, b += sz; a < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l,\
    \ seg[a++]);\n            if(b & 1) r = M::f(seg[--b], r);\n        }\n      \
    \  return M::f(l, r);\n    }\n\n    template<class F>\n    int search_right(int\
    \ l, F cond){\n        if(l == n) return n;\n        T val = M::e();\n       \
    \ l += sz;\n        do {\n            while(!(l&1)) l >>= 1;\n            T next\
    \ = M::f(val, seg[l]);\n            if(!cond(next)){\n                while(l\
    \ < sz) {\n                    l <<= 1;\n                    next = M::f(val,\
    \ seg[l]);\n                    if (cond(next)){\n                        val\
    \ = move(next);\n                        l++;\n                    }\n       \
    \         }\n                return l - sz;\n            }\n            val =\
    \ move(next);\n            l++;\n        } while((l & -l) != l);\n        return\
    \ n;\n    }\n\n    template<class F>\n    int search_left(int r, F cond){\n  \
    \      if(r == 0) return 0;\n        T val = M::e();\n        r += sz;\n     \
    \   do {\n            r--;\n            while(r > 1 && (r & 1)) r >>= 1;\n   \
    \         T next = M::f(seg[r], val);\n            if(!cond(next)){\n        \
    \        while(r < sz) {\n                    r = ((r << 1)|1);\n            \
    \        next = M::f(seg[r], val);\n                    if (cond(next)){\n   \
    \                     val = move(next);\n                        r--;\n      \
    \              }\n                }\n                return r + 1 - sz;\n    \
    \        }\n            val = move(next);\n        } while((r & -r) != r);\n \
    \       return 0;\n    }\n    T operator[](const int &k) const { return seg[k\
    \ + sz]; }\n};\n\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n    static\
    \ T f(T a, T b) { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static T e() { return\
    \ {1, 0}; }\n};\n*/\n\n/**\n * @brief Segment Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segmenttree/segtree.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:36:46+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yuki650_hld_edge.test.cpp
  - test/yosupo_vertex_add_subtree_sum_hld_rerooted.test.cpp
  - test/yosupo_vertex_set_path_composite_hld_ordered.test.cpp
  - test/yosupo_aplusb_segmenttree_boundaries.test.cpp
  - test/yosupo_vertex_set_path_composite.test.cpp
  - test/yosupo_point_set_range_composite.test.cpp
  - test/yosupo_vertex_add_subtree_sum_hld.test.cpp
  - test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
date: 2020-03-07
documentation_of: datastructure/segmenttree/segtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Segment Tree
---

## 説明
点更新・区間積・左右の境界探索を $O(\log N)$ 時間で行う。構築時間・保持領域は $O(N)$。

## できること
- `SegmentTree<M> seg(n)` : 要素数 `n`、初期値が単位元の木を作る
- `set(k, x)` / `build()` : 葉の初期値を設定し、木を構築する
- `update(k, x)` : 位置 `k` の値を `x` に置き換える
- `query(l, r)` : 半開区間 `[l, r)` の積を返す
- `search_right(l, cond)` : `cond(query(l, r))` を満たす最大の `r` を返す
- `search_left(r, cond)` : `cond(query(l, r))` を満たす最小の `l` を返す
- `seg[k]` : 位置 `k` の値を返す

## 使い方
`M` に要素型 `T`、結合則を満たす二項演算 `f`、単位元 `e` を定義する。非可換モノイドも使える。
境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。
計算量はモノイド演算と述語が $O(1)$ の場合である。
