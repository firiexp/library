---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0355.test.cpp
    title: test/aoj0355.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_hld_rerooted.test.cpp
    title: test/yosupo_aplusb_hld_rerooted.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
    title: test/yosupo_aplusb_segmenttree_boundaries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_range_affine_range_sum.test.cpp
    title: test/yosupo_range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment\
      \ Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/segmenttree/lazysegtree.cpp\"\ntemplate <class\
    \ M>\nstruct LazySegmentTree{\n    using T = typename M::T;\n    using L = typename\
    \ M::L;\n    int sz, n, height{};\n    vector<T> seg; vector<L> lazy;\n    explicit\
    \ LazySegmentTree(int n) : n(n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n\
    \        seg.assign(2*sz, M::e());\n        lazy.assign(2*sz, M::l());\n    }\n\
    \n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n    void build(){\n \
    \       for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);\n\
    \    }\n\n    T reflect(int k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k],\
    \ lazy[k]); }\n\n    void eval(int k){\n        if(lazy[k] == M::l()) return;\n\
    \        if(k < sz){\n            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);\n\
    \            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);\n        }\n    \
    \    seg[k] = reflect(k);\n        lazy[k] = M::l();\n    }\n    void thrust(int\
    \ k){ for (int i = height; i; --i) eval(k>>i); }\n    void recalc(int k) { while(k\
    \ >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\n    void update(int\
    \ a, const T &x){\n        thrust(a += sz);\n        seg[a] = x;\n        lazy[a]\
    \ = M::l();\n        recalc(a);\n    }\n\n    void update(int a, int b, const\
    \ L &x){\n        if(a == b) return;\n        a += sz; b += sz;\n        int ha\
    \ = __builtin_ctz(a), hb = __builtin_ctz(b);\n        for(int i = height; i >\
    \ ha; --i) eval(a >> i);\n        for(int i = height; i > hb; --i) eval((b-1)\
    \ >> i);\n        for (int l = a, r = b; l < r; l >>=1, r >>= 1) {\n         \
    \   if(l&1) lazy[l] = M::h(lazy[l], x), l++;\n            if(r&1) --r, lazy[r]\
    \ = M::h(lazy[r], x);\n        }\n        recalc(a >> ha);\n        recalc((b-1)\
    \ >> hb);\n    }\n\n    T query(int a, int b){ // [l, r)\n        if(a == b) return\
    \ M::e();\n        a += sz; b += sz;\n        int ha = __builtin_ctz(a), hb =\
    \ __builtin_ctz(b);\n        for(int i = height; i > ha; --i) eval(a >> i);\n\
    \        for(int i = height; i > hb; --i) eval((b-1) >> i);\n        T ll = M::e(),\
    \ rr = M::e();\n        for(int l = a, r = b; l < r; l >>=1, r>>=1) {\n      \
    \      if (l & 1) ll = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r),\
    \ rr);\n        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n\
    \    int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            T next = M::f(val, reflect(l));\n            if(!cond(next)){\n\
    \                while(l < sz) {\n                    eval(l); l <<= 1;\n    \
    \                next = M::f(val, reflect(l));\n                    if (cond(next)){\n\
    \                        val = move(next);\n                        l++;\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = move(next);\n            l++;\n        } while((l\
    \ & -l) != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            T next = M::f(reflect(r), val);\n          \
    \  if(!cond(next)){\n                while(r < sz) {\n                    eval(r);\n\
    \                    r = ((r << 1)|1);\n                    next = M::f(reflect(r),\
    \ val);\n                    if (cond(next)){\n                        val = move(next);\n\
    \                        r--;\n                    }\n                }\n    \
    \            return r + 1 - sz;\n            }\n            val = move(next);\n\
    \        } while((r & -r) != r);\n        return 0;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = array<mint, 2>;\n    using L = array<mint, 2>;\n    static T f(T\
    \ a, T b) { return {a[0]+b[0], a[1]+b[1]}; }\n    static T g(T a, L b) {\n   \
    \     return {a[0] * b[0] + a[1] * b[1], a[1]};\n    }\n    static L h(L a, L\
    \ b) {\n        return {a[0]*b[0], a[1]*b[0]+b[1]};\n    }\n    static T e() {\
    \ return {0, 0}; }\n    static L l() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief\
    \ \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)\n */\n"
  code: "template <class M>\nstruct LazySegmentTree{\n    using T = typename M::T;\n\
    \    using L = typename M::L;\n    int sz, n, height{};\n    vector<T> seg; vector<L>\
    \ lazy;\n    explicit LazySegmentTree(int n) : n(n) {\n        sz = 1; while(sz\
    \ < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n        lazy.assign(2*sz,\
    \ M::l());\n    }\n\n    void set(int k, const T &x){ seg[k + sz] = x; }\n\n \
    \   void build(){\n        for (int i = sz-1; i > 0; --i) seg[i] = M::f(seg[i<<1],\
    \ seg[(i<<1)|1]);\n    }\n\n    T reflect(int k){ return lazy[k] == M::l() ? seg[k]\
    \ : M::g(seg[k], lazy[k]); }\n\n    void eval(int k){\n        if(lazy[k] == M::l())\
    \ return;\n        if(k < sz){\n            lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0],\
    \ lazy[k]);\n            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1], lazy[k]);\n   \
    \     }\n        seg[k] = reflect(k);\n        lazy[k] = M::l();\n    }\n    void\
    \ thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n    void recalc(int\
    \ k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\n\
    \    void update(int a, const T &x){\n        thrust(a += sz);\n        seg[a]\
    \ = x;\n        lazy[a] = M::l();\n        recalc(a);\n    }\n\n    void update(int\
    \ a, int b, const L &x){\n        if(a == b) return;\n        a += sz; b += sz;\n\
    \        int ha = __builtin_ctz(a), hb = __builtin_ctz(b);\n        for(int i\
    \ = height; i > ha; --i) eval(a >> i);\n        for(int i = height; i > hb; --i)\
    \ eval((b-1) >> i);\n        for (int l = a, r = b; l < r; l >>=1, r >>= 1) {\n\
    \            if(l&1) lazy[l] = M::h(lazy[l], x), l++;\n            if(r&1) --r,\
    \ lazy[r] = M::h(lazy[r], x);\n        }\n        recalc(a >> ha);\n        recalc((b-1)\
    \ >> hb);\n    }\n\n    T query(int a, int b){ // [l, r)\n        if(a == b) return\
    \ M::e();\n        a += sz; b += sz;\n        int ha = __builtin_ctz(a), hb =\
    \ __builtin_ctz(b);\n        for(int i = height; i > ha; --i) eval(a >> i);\n\
    \        for(int i = height; i > hb; --i) eval((b-1) >> i);\n        T ll = M::e(),\
    \ rr = M::e();\n        for(int l = a, r = b; l < r; l >>=1, r>>=1) {\n      \
    \      if (l & 1) ll = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r),\
    \ rr);\n        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n\
    \    int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            T next = M::f(val, reflect(l));\n            if(!cond(next)){\n\
    \                while(l < sz) {\n                    eval(l); l <<= 1;\n    \
    \                next = M::f(val, reflect(l));\n                    if (cond(next)){\n\
    \                        val = move(next);\n                        l++;\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = move(next);\n            l++;\n        } while((l\
    \ & -l) != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            T next = M::f(reflect(r), val);\n          \
    \  if(!cond(next)){\n                while(r < sz) {\n                    eval(r);\n\
    \                    r = ((r << 1)|1);\n                    next = M::f(reflect(r),\
    \ val);\n                    if (cond(next)){\n                        val = move(next);\n\
    \                        r--;\n                    }\n                }\n    \
    \            return r + 1 - sz;\n            }\n            val = move(next);\n\
    \        } while((r & -r) != r);\n        return 0;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = array<mint, 2>;\n    using L = array<mint, 2>;\n    static T f(T\
    \ a, T b) { return {a[0]+b[0], a[1]+b[1]}; }\n    static T g(T a, L b) {\n   \
    \     return {a[0] * b[0] + a[1] * b[1], a[1]};\n    }\n    static L h(L a, L\
    \ b) {\n        return {a[0]*b[0], a[1]*b[0]+b[1]};\n    }\n    static T e() {\
    \ return {0, 0}; }\n    static L l() { return {1, 0}; }\n};\n*/\n\n/**\n * @brief\
    \ \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segmenttree/lazysegtree.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:36:46+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_segmenttree_boundaries.test.cpp
  - test/aoj0355.test.cpp
  - test/yosupo_range_affine_range_sum.test.cpp
  - test/yosupo_aplusb_hld_rerooted.test.cpp
date: 2018-05-01
documentation_of: datastructure/segmenttree/lazysegtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment Tree)"
---

## 説明
2 つの配列を持つことで、セグメント木を区間更新に対応させたもの。
更新も取得も $O(\log N)$ 回の演算で行える。

## できること
- `LazySegmentTree<M> seg(n)` : 要素数 `n` の遅延セグメント木を作る
- `set(k, x)` : 葉 `k` の初期値を `x` にする
- `build()` : `set` 済みの値から木を構築する
- `update(k, x)` : 位置 `k` の値を `x` に更新する
- `update(l, r, x)` : 半開区間 $[l, r)$ に作用素 `x` を適用する
- `query(l, r)` : 半開区間 $[l, r)$ の集約値を返す
- `search_right(l, cond)` : `cond(query(l, r))` を満たす最大の `r` を返す
- `search_left(r, cond)` : `cond(query(l, r))` を満たす最小の `l` を返す

## 使い方
モノイド構造体 `M` に次を定義して渡す。
- 要素の型 `T`
- `T` の単位元 `e`
- 作用素の型 `L`
- `L` の単位元 `l`
- $f : T \times T \to T$ 要素同士のマージ
- $g : T \times L \to T$ 要素と作用素のマージ
- $h : L \times L \to L$ 作用素同士のマージ

境界探索の `cond` は単位元で `true` とし、区間を伸ばすと `true` から `false` への変化が高々1回になるものを使う。

以下にモノイドの例を挙げる。

#### 区間加算-区間min
- $e = \infty$
- $l = 0$
- $f(x, y) = \min(x, y)$
- $g(x, y) = x + y$
- $h(x, y) = x + y$

#### 区間更新-区間max
- $e = 0$
- $l = \bot$ (`\bot` は作用しないことを表す番兵)
- $f(x, y) = \max(x, y)$
- $g(x, y) = h(x, y)$

$$
g(x, y) = h(x, y) =
\begin{cases}
x & (y = l) \\
y & (y \ne l)
\end{cases}
$$

#### 区間更新-区間sum
要素を `(部分木の和, サイズ)` としてもつ。範囲内は事前にサイズ 1 としておく。
- $e = (0, 0)$
- $l = \bot$ (`\bot` は作用しないことを表す番兵)
- $f((x_1, y_1), (x_2, y_2)) = (x_1 + x_2, y_1 + y_2)$
- $g((x, y), z) = (zy, y)$
- $h(x, y)$ は次で与える

$$
h(x, y) =
\begin{cases}
x & (y = l) \\
y & (y \ne l)
\end{cases}
$$

## 実装上の補足

区間操作では境界をまたぐ祖先だけを伝播・再集約し、区間内に収まる部分木の遅延作用を保つ。
