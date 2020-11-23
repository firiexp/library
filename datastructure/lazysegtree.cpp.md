---
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
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/lazysegtree.cpp\"\ntemplate <class M>\nstruct\
    \ LazySegmentTree{\n    using T = typename M::T;\n    using L = typename M::L;\n\
    \    int sz, n, height{};\n    vector<T> seg; vector<L> lazy;\n    explicit LazySegmentTree(int\
    \ n) : n(n) {\n        sz = 1; while(sz < n) sz <<= 1, height++;\n        seg.assign(2*sz,\
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
    \ { return {1, 0}; }\n};\n*/\n"
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
    \ { return {1, 0}; }\n};\n*/"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/lazysegtree.cpp
  requiredBy: []
  timestamp: '2020-10-27 21:25:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0355.test.cpp
  - test/yosupo_range_affine_range_sum.test.cpp
documentation_of: datastructure/lazysegtree.cpp
layout: document
redirect_from:
- /library/datastructure/lazysegtree.cpp
- /library/datastructure/lazysegtree.cpp.html
title: datastructure/lazysegtree.cpp
---
