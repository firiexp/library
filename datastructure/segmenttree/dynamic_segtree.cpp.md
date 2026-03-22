---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
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
    document_title: "\u52D5\u7684\u30BB\u30B0\u30E1\u30F3\u30C8\u6728"
    links: []
  bundledCode: "#line 1 \"datastructure/segmenttree/dynamic_segtree.cpp\"\ntemplate\
    \ <class M>\nstruct DynamicSegmentTree{\n    using T = typename M::T;\n    struct\
    \ Node{\n        T val;\n        int l, r;\n    };\n\n    long long n{};\n   \
    \ vector<Node> node;\n    int root;\n\n    explicit DynamicSegmentTree(long long\
    \ n): n(n), root(-1) {}\n\n    void reserve(size_t sz){\n        node.reserve(sz);\n\
    \    }\n\n    void update(long long k, const T &x){\n        if(n == 0) return;\n\
    \        update_(root, k, x, 0, n);\n    }\n\n    void add(long long k, const\
    \ T &x){\n        if(n == 0) return;\n        add_(root, k, x, 0, n);\n    }\n\
    \n    T query(long long a, long long b) const {\n        if(n == 0 || b <= a)\
    \ return M::e();\n        return query_(root, a, b, 0, n);\n    }\n\n    T get(long\
    \ long k) const { return query(k, k+1); }\n    T operator[](const long long &k)\
    \ const { return get(k); }\n\nprivate:\n    int make_node(const T &v, int l, int\
    \ r){\n        node.push_back({v, l, r});\n        return (int)node.size()-1;\n\
    \    }\n\n    void update_(int &id, long long k, const T &x, long long l, long\
    \ long r){\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        if(l+1\
    \ == r){\n            node[id].val = x;\n            return;\n        }\n    \
    \    long long m = l + ((r-l)>>1);\n        if(k < m){\n            int child\
    \ = node[id].l;\n            update_(child, k, x, l, m);\n            node[id].l\
    \ = child;\n        }else{\n            int child = node[id].r;\n            update_(child,\
    \ k, x, m, r);\n            node[id].r = child;\n        }\n        node[id].val\
    \ = M::f(value(node[id].l), value(node[id].r));\n    }\n\n    void add_(int &id,\
    \ long long k, const T &x, long long l, long long r){\n        if(id == -1) id\
    \ = make_node(M::e(), -1, -1);\n        if(l+1 == r){\n            node[id].val\
    \ = M::f(node[id].val, x);\n            return;\n        }\n        long long\
    \ m = l + ((r-l)>>1);\n        if(k < m){\n            int child = node[id].l;\n\
    \            add_(child, k, x, l, m);\n            node[id].l = child;\n     \
    \   }else{\n            int child = node[id].r;\n            add_(child, k, x,\
    \ m, r);\n            node[id].r = child;\n        }\n        node[id].val = M::f(value(node[id].l),\
    \ value(node[id].r));\n    }\n\n    T query_(int id, long long a, long long b,\
    \ long long l, long long r) const {\n        if(id == -1 || r <= a || b <= l)\
    \ return M::e();\n        if(a <= l && r <= b) return node[id].val;\n        long\
    \ long m = l + ((r-l)>>1);\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n\n    T value(int id) const {\n   \
    \     return id == -1 ? M::e() : node[id].val;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u52D5\u7684\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\n */\n"
  code: "template <class M>\nstruct DynamicSegmentTree{\n    using T = typename M::T;\n\
    \    struct Node{\n        T val;\n        int l, r;\n    };\n\n    long long\
    \ n{};\n    vector<Node> node;\n    int root;\n\n    explicit DynamicSegmentTree(long\
    \ long n): n(n), root(-1) {}\n\n    void reserve(size_t sz){\n        node.reserve(sz);\n\
    \    }\n\n    void update(long long k, const T &x){\n        if(n == 0) return;\n\
    \        update_(root, k, x, 0, n);\n    }\n\n    void add(long long k, const\
    \ T &x){\n        if(n == 0) return;\n        add_(root, k, x, 0, n);\n    }\n\
    \n    T query(long long a, long long b) const {\n        if(n == 0 || b <= a)\
    \ return M::e();\n        return query_(root, a, b, 0, n);\n    }\n\n    T get(long\
    \ long k) const { return query(k, k+1); }\n    T operator[](const long long &k)\
    \ const { return get(k); }\n\nprivate:\n    int make_node(const T &v, int l, int\
    \ r){\n        node.push_back({v, l, r});\n        return (int)node.size()-1;\n\
    \    }\n\n    void update_(int &id, long long k, const T &x, long long l, long\
    \ long r){\n        if(id == -1) id = make_node(M::e(), -1, -1);\n        if(l+1\
    \ == r){\n            node[id].val = x;\n            return;\n        }\n    \
    \    long long m = l + ((r-l)>>1);\n        if(k < m){\n            int child\
    \ = node[id].l;\n            update_(child, k, x, l, m);\n            node[id].l\
    \ = child;\n        }else{\n            int child = node[id].r;\n            update_(child,\
    \ k, x, m, r);\n            node[id].r = child;\n        }\n        node[id].val\
    \ = M::f(value(node[id].l), value(node[id].r));\n    }\n\n    void add_(int &id,\
    \ long long k, const T &x, long long l, long long r){\n        if(id == -1) id\
    \ = make_node(M::e(), -1, -1);\n        if(l+1 == r){\n            node[id].val\
    \ = M::f(node[id].val, x);\n            return;\n        }\n        long long\
    \ m = l + ((r-l)>>1);\n        if(k < m){\n            int child = node[id].l;\n\
    \            add_(child, k, x, l, m);\n            node[id].l = child;\n     \
    \   }else{\n            int child = node[id].r;\n            add_(child, k, x,\
    \ m, r);\n            node[id].r = child;\n        }\n        node[id].val = M::f(value(node[id].l),\
    \ value(node[id].r));\n    }\n\n    T query_(int id, long long a, long long b,\
    \ long long l, long long r) const {\n        if(id == -1 || r <= a || b <= l)\
    \ return M::e();\n        if(a <= l && r <= b) return node[id].val;\n        long\
    \ long m = l + ((r-l)>>1);\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n\n    T value(int id) const {\n   \
    \     return id == -1 ? M::e() : node[id].val;\n    }\n};\n\n/*\nstruct Monoid{\n\
    \    using T = long long;\n    static T f(T a, T b) { return a + b; }\n    static\
    \ T e() { return 0; }\n};\n*/\n\n/**\n * @brief \u52D5\u7684\u30BB\u30B0\u30E1\
    \u30F3\u30C8\u6728\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/segmenttree/dynamic_segtree.cpp
  requiredBy: []
  timestamp: '2026-03-22 19:39:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_add_range_sum_dynamic_segtree.test.cpp
date: 2026-03-08
documentation_of: datastructure/segmenttree/dynamic_segtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Dynamic Segment Tree
---

## 説明
必要なノードだけ作る動的セグメント木。
大きい座標範囲に対する 1 点更新と区間積を扱う。
各操作は生成ノード数に応じて $O(log N)$。

## できること
- `DynamicSegmentTree<M> seg(n)`
  長さ `n`、初期値がすべて `M::e()` の動的セグメント木を作る
- `void reserve(size_t sz)`
  ノード配列を `sz` 個ぶん予約する
- `void update(long long k, T x)`
  位置 `k` を `x` に置き換える
- `void add(long long k, T x)`
  位置 `k` を `M::f(old, x)` で更新する
- `T query(long long l, long long r)`
  半開区間 `[l, r)` の積を返す。空区間なら `M::e()`
- `T get(long long k)`
  位置 `k` の値を返す
- `T operator[](long long k)`
  `get(k)` の短縮形

## 使い方
`M` に `using T`、`static T f(T, T)`、`static T e()` を定義して使う。

```cpp
struct Monoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

DynamicSegmentTree<Monoid> seg((long long)1e9);
seg.add(123456789, 5);
seg.update(987654321, 7);
long long ans = seg.query(100000000, 900000000);
```

## 実装上の補足
未生成ノードは単位元として扱う。
大量の更新を先に見積もれるときは `reserve()` で再確保を減らせる。
この実装は初期配列をまとめて与える構築は持たず、必要な位置だけ更新して使う。
