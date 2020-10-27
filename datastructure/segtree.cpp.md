---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_set_range_composite.test.cpp
    title: test/yosupo_point_set_range_composite.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/segtree.cpp\"\ntemplate <class M>\nstruct\
    \ SegmentTree{\n    using T = typename M::T;\n    int sz, n, height{};\n    vector<T>\
    \ seg;\n    explicit SegmentTree(int n) : n(n) {\n        sz = 1; while(sz < n)\
    \ sz <<= 1, height++;\n        seg.assign(2*sz, M::e());\n    }\n\n    void set(int\
    \ k, const T &x){ seg[k + sz] = x; }\n\n    void build(){\n        for (int i\
    \ = sz-1; i > 0; --i) seg[i] = M::f(seg[2*i], seg[2*i+1]);\n    }\n\n    void\
    \ update(int k, const T &x){\n        k += sz;\n        seg[k] = x;\n        while\
    \ (k >>= 1) seg[k] = M::f(seg[2*k], seg[2*k+1]);\n    }\n\n    T query(int a,\
    \ int b){\n        T l = M::e(), r = M::e();\n        for(a += sz, b += sz; a\
    \ < b; a >>=1, b>>=1){\n            if(a & 1) l = M::f(l, seg[a++]);\n       \
    \     if(b & 1) r = M::f(seg[--b], r);\n        }\n        return M::f(l, r);\n\
    \    }\n\n    template<class F>\n    int search_right(int l, F cond){\n      \
    \  if(l == n) return n;\n        T val = M::e();\n        l += sz;\n        do\
    \ {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val, seg[l]))){\n\
    \                while(l < sz) {\n                    l <<= 1;\n             \
    \       if (cond(M::f(val, seg[l]))){\n                        val = M::f(val,\
    \ seg[l]);\n                        l++;\n                    }\n            \
    \    }\n                return l - sz;\n            }\n            val = M::f(val,\
    \ seg[l]);\n            l++;\n        } while((l & -l) != l);\n        return\
    \ n;\n    }\n\n    template<class F>\n    int search_left(int r, F cond){\n  \
    \      if(r == 0) return 0;\n        T val = M::e();\n        r += sz;\n     \
    \   do {\n            while(r&1) r >>= 1;\n            if(!cond(M::f(seg[r], val))){\n\
    \                while(r < sz) {\n                    r = ((r << 1)|1);\n    \
    \                if (cond(M::f(seg[r], val))){\n                        val =\
    \ M::f(seg[r], val);\n                        r--;\n                    }\n  \
    \              }\n                return r + 1 - sz;\n            }\n        \
    \    val = M::f(seg[r], val);\n        } while((r & -r) != r);\n        return\
    \ 0;\n    }\n    T operator[](const int &k) const { return seg[k + sz]; }\n};\n\
    \n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n    static T f(T a, T b)\
    \ { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n*/\n"
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
    \ l += sz;\n        do {\n            while(!(l&1)) l >>= 1;\n            if(!cond(M::f(val,\
    \ seg[l]))){\n                while(l < sz) {\n                    l <<= 1;\n\
    \                    if (cond(M::f(val, seg[l]))){\n                        val\
    \ = M::f(val, seg[l]);\n                        l++;\n                    }\n\
    \                }\n                return l - sz;\n            }\n          \
    \  val = M::f(val, seg[l]);\n            l++;\n        } while((l & -l) != l);\n\
    \        return n;\n    }\n\n    template<class F>\n    int search_left(int r,\
    \ F cond){\n        if(r == 0) return 0;\n        T val = M::e();\n        r +=\
    \ sz;\n        do {\n            while(r&1) r >>= 1;\n            if(!cond(M::f(seg[r],\
    \ val))){\n                while(r < sz) {\n                    r = ((r << 1)|1);\n\
    \                    if (cond(M::f(seg[r], val))){\n                        val\
    \ = M::f(seg[r], val);\n                        r--;\n                    }\n\
    \                }\n                return r + 1 - sz;\n            }\n      \
    \      val = M::f(seg[r], val);\n        } while((r & -r) != r);\n        return\
    \ 0;\n    }\n    T operator[](const int &k) const { return seg[k + sz]; }\n};\n\
    \n/*\nstruct Monoid{\n    using T = array<mint, 2>;\n    static T f(T a, T b)\
    \ { return {a[0]*b[0], a[1]*b[0]+b[1]}; }\n    static T e() { return {1, 0}; }\n\
    };\n*/"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segtree.cpp
  requiredBy: []
  timestamp: '2020-10-27 21:25:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_set_range_composite.test.cpp
documentation_of: datastructure/segtree.cpp
layout: document
redirect_from:
- /library/datastructure/segtree.cpp
- /library/datastructure/segtree.cpp.html
title: datastructure/segtree.cpp
---
