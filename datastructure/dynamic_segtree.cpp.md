---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
    title: test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"datastructure/dynamic_segtree.cpp\"\ntemplate <class M>\n\
    struct DynamicSegmentTree{\n    using T = typename M::T;\n    struct Node{\n \
    \       T val;\n        int l, r;\n    };\n\n    long long n{};\n    vector<Node>\
    \ node;\n    int root;\n\n    explicit DynamicSegmentTree(long long n): n(n),\
    \ root(-1) {}\n\n    void update(long long k, const T &x){\n        if(n == 0)\
    \ return;\n        root = update_(root, k, x, 0, n);\n    }\n\n    void add(long\
    \ long k, const T &x){\n        if(n == 0) return;\n        root = add_(root,\
    \ k, x, 0, n);\n    }\n\n    T query(long long a, long long b) const {\n     \
    \   if(n == 0 || b <= a) return M::e();\n        return query_(root, a, b, 0,\
    \ n);\n    }\n\n    T get(long long k) const { return query(k, k+1); }\n    T\
    \ operator[](const long long &k) const { return get(k); }\n\nprivate:\n    int\
    \ make_node(const T &v, int l, int r){\n        node.push_back({v, l, r});\n \
    \       return node.size()-1;\n    }\n\n    int update_(int id, long long k, const\
    \ T &x, long long l, long long r){\n        if(l+1 == r) return make_node(x, -1,\
    \ -1);\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        long long\
    \ m = l + ((r-l)>>1);\n        int ll = node[id].l, rr = node[id].r;\n       \
    \ if(k < m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr, k, x,\
    \ m, r);\n        return make_node(M::f(value(ll), value(rr)), ll, rr);\n    }\n\
    \n    int add_(int id, long long k, const T &x, long long l, long long r){\n \
    \       if(l+1 == r) return make_node(M::f(value(id), x), -1, -1);\n        if(id\
    \ == -1) id = make_node(M::e(), -1, -1);\n        long long m = l + ((r-l)>>1);\n\
    \        int ll = node[id].l, rr = node[id].r;\n        if(k < m) ll = add_(ll,\
    \ k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n        return make_node(M::f(value(ll),\
    \ value(rr)), ll, rr);\n    }\n\n    T query_(int id, long long a, long long b,\
    \ long long l, long long r) const {\n        if(id == -1 || r <= a || b <= l)\
    \ return M::e();\n        if(a <= l && r <= b) return node[id].val;\n        long\
    \ long m = l + ((r-l)>>1);\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n\n    T value(int id) const {\n   \
    \     return id == -1 ? M::e() : node[id].val;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n*/\n"
  code: "template <class M>\nstruct DynamicSegmentTree{\n    using T = typename M::T;\n\
    \    struct Node{\n        T val;\n        int l, r;\n    };\n\n    long long\
    \ n{};\n    vector<Node> node;\n    int root;\n\n    explicit DynamicSegmentTree(long\
    \ long n): n(n), root(-1) {}\n\n    void update(long long k, const T &x){\n  \
    \      if(n == 0) return;\n        root = update_(root, k, x, 0, n);\n    }\n\n\
    \    void add(long long k, const T &x){\n        if(n == 0) return;\n        root\
    \ = add_(root, k, x, 0, n);\n    }\n\n    T query(long long a, long long b) const\
    \ {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root,\
    \ a, b, 0, n);\n    }\n\n    T get(long long k) const { return query(k, k+1);\
    \ }\n    T operator[](const long long &k) const { return get(k); }\n\nprivate:\n\
    \    int make_node(const T &v, int l, int r){\n        node.push_back({v, l, r});\n\
    \        return node.size()-1;\n    }\n\n    int update_(int id, long long k,\
    \ const T &x, long long l, long long r){\n        if(l+1 == r) return make_node(x,\
    \ -1, -1);\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        long\
    \ long m = l + ((r-l)>>1);\n        int ll = node[id].l, rr = node[id].r;\n  \
    \      if(k < m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr,\
    \ k, x, m, r);\n        return make_node(M::f(value(ll), value(rr)), ll, rr);\n\
    \    }\n\n    int add_(int id, long long k, const T &x, long long l, long long\
    \ r){\n        if(l+1 == r) return make_node(M::f(value(id), x), -1, -1);\n  \
    \      if(id == -1) id = make_node(M::e(), -1, -1);\n        long long m = l +\
    \ ((r-l)>>1);\n        int ll = node[id].l, rr = node[id].r;\n        if(k < m)\
    \ ll = add_(ll, k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n      \
    \  return make_node(M::f(value(ll), value(rr)), ll, rr);\n    }\n\n    T query_(int\
    \ id, long long a, long long b, long long l, long long r) const {\n        if(id\
    \ == -1 || r <= a || b <= l) return M::e();\n        if(a <= l && r <= b) return\
    \ node[id].val;\n        long long m = l + ((r-l)>>1);\n        return M::f(query_(node[id].l,\
    \ a, b, l, m), query_(node[id].r, a, b, m, r));\n    }\n\n    T value(int id)\
    \ const {\n        return id == -1 ? M::e() : node[id].val;\n    }\n};\n\n/*\n\
    struct Monoid{\n    using T = long long;\n    static T f(T a, T b) { return a\
    \ + b; }\n    static T e() { return 0; }\n};\n*/\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/dynamic_segtree.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:18:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
documentation_of: datastructure/dynamic_segtree.cpp
layout: document
redirect_from:
- /library/datastructure/dynamic_segtree.cpp
- /library/datastructure/dynamic_segtree.cpp.html
title: datastructure/dynamic_segtree.cpp
---
