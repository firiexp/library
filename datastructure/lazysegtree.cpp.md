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
    path: test/yosupo_range_affine_range_sum.test.cpp
    title: test/yosupo_range_affine_range_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Lazy Segment\
      \ Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/lazysegtree.cpp\"\n#include <array>\n#include\
    \ <vector>\n\ntemplate <class M>\nstruct LazySegmentTree{\n    using T = typename\
    \ M::T;\n    using L = typename M::L;\n    int sz, n, height{};\n    vector<T>\
    \ seg; vector<L> lazy;\n    explicit LazySegmentTree(int n) : n(n) {\n       \
    \ sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n\
    \        lazy.assign(2*sz, M::l());\n    }\n\n    void set(int k, const T &x){\
    \ seg[k + sz] = x; }\n\n    void build(){\n        for (int i = sz-1; i > 0; --i)\
    \ seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);\n    }\n\n    T reflect(int k){ return\
    \ lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }\n\n    void eval(int k){\n\
    \        if(lazy[k] == M::l()) return;\n        if(k < sz){\n            lazy[(k<<1)|0]\
    \ = M::h(lazy[(k<<1)|0], lazy[k]);\n            lazy[(k<<1)|1] = M::h(lazy[(k<<1)|1],\
    \ lazy[k]);\n        }\n        seg[k] = reflect(k);\n        lazy[k] = M::l();\n\
    \    }\n    void thrust(int k){ for (int i = height; i; --i) eval(k>>i); }\n \
    \   void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0), reflect((k<<1)|1));}\n\
    \n    void update(int a, const T &x){\n        thrust(a += sz);\n        seg[a]\
    \ = x;\n        recalc(a);\n    }\n\n    void update(int a, int b, const L &x){\n\
    \        thrust(a += sz); thrust(b += sz-1);\n        for (int l = a, r = b+1;l\
    \ < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l] = M::h(lazy[l], x), l++;\n\
    \            if(r&1) --r, lazy[r] = M::h(lazy[r], x);\n        }\n        recalc(a);\n\
    \        recalc(b);\n    }\n\n    T query(int a, int b){ // [l, r)\n        thrust(a\
    \ += sz);\n        thrust(b += sz-1);\n        T ll = M::e(), rr = M::e();\n \
    \       for(int l = a, r = b+1; l < r; l >>=1, r>>=1) {\n            if (l & 1)\
    \ ll = M::f(ll, reflect(l++));\n            if (r & 1) rr = M::f(reflect(--r),\
    \ rr);\n        }\n        return M::f(ll, rr);\n    }\n\n    template<class F>\n\
    \    int search_right(int l, F cond){\n        if(l == n) return n;\n        thrust(l\
    \ += sz);\n        T val = M::e();\n        do {\n            while(!(l&1)) l\
    \ >>= 1;\n            if(!cond(M::f(val, seg[l]))){\n                while(l <\
    \ sz) {\n                    eval(l); l <<= 1;\n                    if (cond(M::f(val,\
    \ reflect(l)))){\n                        val = M::f(val, reflect(l++));\n   \
    \                 }\n                }\n                return l - sz;\n     \
    \       }\n            val = M::f(val, reflect(l++));\n        } while((l & -l)\
    \ != l);\n        return n;\n    }\n\n    template<class F>\n    int search_left(int\
    \ r, F cond){\n        if(r <= 0) return 0;\n        thrust((r += sz)-1);\n  \
    \      T val = M::e();\n        do {\n            r--;\n            while(r >\
    \ 1 && r&1) r >>= 1;\n            if(!cond(M::f(reflect(r), val))){\n        \
    \        while(r < sz) {\n                    eval(r);\n                    r\
    \ = ((r << 1)|1);\n                    if (cond(M::f(reflect(r), val))){\n   \
    \                     val = M::f(reflect(r--), val);\n                    }\n\
    \                }\n                return r + 1 - sz;\n            }\n      \
    \      val = M::f(reflect(r), val);\n        } while((r & -r) != r);\n       \
    \ return 0;\n    }\n};\n\n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n\
    \    using L = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]+b[0],\
    \ a[1]+b[1]}; }\n    static T g(T a, L b) {\n        return {a[0] * b[0] + a[1]\
    \ * b[1], a[1]};\n    }\n    static L h(L a, L b) {\n        return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]};\n    }\n    static T e() { return {0, 0}; }\n    static L l()\
    \ { return {1, 0}; }\n};\n*/\n\n/**\n * @brief \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Lazy Segment Tree)\n */\n"
  code: "#include <array>\n#include <vector>\n\ntemplate <class M>\nstruct LazySegmentTree{\n\
    \    using T = typename M::T;\n    using L = typename M::L;\n    int sz, n, height{};\n\
    \    vector<T> seg; vector<L> lazy;\n    explicit LazySegmentTree(int n) : n(n)\
    \ {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
    \ M::e());\n        lazy.assign(2*sz, M::l());\n    }\n\n    void set(int k, const\
    \ T &x){ seg[k + sz] = x; }\n\n    void build(){\n        for (int i = sz-1; i\
    \ > 0; --i) seg[i] = M::f(seg[i<<1], seg[(i<<1)|1]);\n    }\n\n    T reflect(int\
    \ k){ return lazy[k] == M::l() ? seg[k] : M::g(seg[k], lazy[k]); }\n\n    void\
    \ eval(int k){\n        if(lazy[k] == M::l()) return;\n        if(k < sz){\n \
    \           lazy[(k<<1)|0] = M::h(lazy[(k<<1)|0], lazy[k]);\n            lazy[(k<<1)|1]\
    \ = M::h(lazy[(k<<1)|1], lazy[k]);\n        }\n        seg[k] = reflect(k);\n\
    \        lazy[k] = M::l();\n    }\n    void thrust(int k){ for (int i = height;\
    \ i; --i) eval(k>>i); }\n    void recalc(int k) { while(k >>= 1) seg[k] = M::f(reflect((k<<1)|0),\
    \ reflect((k<<1)|1));}\n\n    void update(int a, const T &x){\n        thrust(a\
    \ += sz);\n        seg[a] = x;\n        recalc(a);\n    }\n\n    void update(int\
    \ a, int b, const L &x){\n        thrust(a += sz); thrust(b += sz-1);\n      \
    \  for (int l = a, r = b+1;l < r; l >>=1, r >>= 1) {\n            if(l&1) lazy[l]\
    \ = M::h(lazy[l], x), l++;\n            if(r&1) --r, lazy[r] = M::h(lazy[r], x);\n\
    \        }\n        recalc(a);\n        recalc(b);\n    }\n\n    T query(int a,\
    \ int b){ // [l, r)\n        thrust(a += sz);\n        thrust(b += sz-1);\n  \
    \      T ll = M::e(), rr = M::e();\n        for(int l = a, r = b+1; l < r; l >>=1,\
    \ r>>=1) {\n            if (l & 1) ll = M::f(ll, reflect(l++));\n            if\
    \ (r & 1) rr = M::f(reflect(--r), rr);\n        }\n        return M::f(ll, rr);\n\
    \    }\n\n    template<class F>\n    int search_right(int l, F cond){\n      \
    \  if(l == n) return n;\n        thrust(l += sz);\n        T val = M::e();\n \
    \       do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    eval(l); l\
    \ <<= 1;\n                    if (cond(M::f(val, reflect(l)))){\n            \
    \            val = M::f(val, reflect(l++));\n                    }\n         \
    \       }\n                return l - sz;\n            }\n            val = M::f(val,\
    \ reflect(l++));\n        } while((l & -l) != l);\n        return n;\n    }\n\n\
    \    template<class F>\n    int search_left(int r, F cond){\n        if(r <= 0)\
    \ return 0;\n        thrust((r += sz)-1);\n        T val = M::e();\n        do\
    \ {\n            r--;\n            while(r > 1 && r&1) r >>= 1;\n            if(!cond(M::f(reflect(r),\
    \ val))){\n                while(r < sz) {\n                    eval(r);\n   \
    \                 r = ((r << 1)|1);\n                    if (cond(M::f(reflect(r),\
    \ val))){\n                        val = M::f(reflect(r--), val);\n          \
    \          }\n                }\n                return r + 1 - sz;\n        \
    \    }\n            val = M::f(reflect(r), val);\n        } while((r & -r) !=\
    \ r);\n        return 0;\n    }\n};\n\n/*\nstruct Monoid{\n    using T = array<mint,\
    \ 2>;\n    using L = array<mint, 2>;\n    static T f(T a, T b) { return {a[0]+b[0],\
    \ a[1]+b[1]}; }\n    static T g(T a, L b) {\n        return {a[0] * b[0] + a[1]\
    \ * b[1], a[1]};\n    }\n    static L h(L a, L b) {\n        return {a[0]*b[0],\
    \ a[1]*b[0]+b[1]};\n    }\n    static T e() { return {0, 0}; }\n    static L l()\
    \ { return {1, 0}; }\n};\n*/\n\n/**\n * @brief \u9045\u5EF6\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Lazy Segment Tree)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/lazysegtree.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_range_affine_range_sum.test.cpp
  - test/aoj0355.test.cpp
date: 2018-05-01
documentation_of: datastructure/lazysegtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: "\u9045\u5EF6\u4F1D\u64ADSegmentTree"
---

## 説明
2つ配列を持つことで、セグメント木を区間に対する操作に対応させたもの。<br>
区間に操作をする際には、普通のセグメント木と同様に区間を下ろしていって、区間全体を覆うならそこにとどめておく。クエリのときに必要に応じて分割する。すると、更新と取得が$O(\log N)$回の演算で可能になる。<br>
実装では、モノイド構造体を渡すようにしている。構造体には、次のようなものを定義する。
- 要素の型 $T$
- $T$の単位元 $e$
- 作用素の型 $L$
- $L$の単位元 $l$
- $f : T \times T \to T$ 要素同士のマージ
- $g : T \times L \to T$ 要素と作用素のマージ
- $h : L \times L \to L$ 作用素同士のマージ

以下にモノイドの例をあげておく。
#### 区間加算-区間min
- $e = \infty$
- $l = 0$
- $f(x, y) = \min(x, y), g(x, y) = x + y, h(x, y) = x + y$

#### 区間更新-区間max
- $e = 0$
- $l = 0$
- $f(x, y) = \max(x, y)$
- $g(x, y) = h(x, y)$

$$
g(x, y) = h(x, y) =
\begin{cases}
x & (y = e) \\
y & (y \ne e)
\end{cases}
$$

#### 区間更新-区間sum
要素を(部分木の和, サイズ)としてもつ。範囲内は事前にサイズ1としておく。
- $e = (0, 0)$
- $l = 0$
- $f((x_1, y_1), (x_2, y_2)) = (x_1 + x_2, y_1 + y_2)$
- $g((x, y), z) = (zy, y)$
- $h(x, y)$

$$
h(x, y) =
\begin{cases}
x & (y = e) \\
y & (y \ne e)
\end{cases}
$$
