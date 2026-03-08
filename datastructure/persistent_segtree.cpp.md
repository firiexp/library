---
category: "\u30C7\u30FC\u30BF\u69CB\u9020"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_point_add_range_sum_persistent.test.cpp
    title: test/yosupo_point_add_range_sum_persistent.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\u30C8\u6728(Persistent Segment\
      \ Tree)"
    links: []
  bundledCode: "#line 1 \"datastructure/persistent_segtree.cpp\"\ntemplate <class\
    \ M>\nstruct PersistentSegmentTree{\n    using T = typename M::T;\n    struct\
    \ Node{\n        T val;\n        int l, r;\n    };\n\n    int n{};\n    vector<Node>\
    \ node;\n    vector<int> root;\n\n    explicit PersistentSegmentTree(int n): n(n){\n\
    \        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n        \
    \    root.push_back(0);\n        }else{\n            root.push_back(build(0, n));\n\
    \        }\n    }\n    explicit PersistentSegmentTree(const vector<T> &v): n(v.size()){\n\
    \        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n        \
    \    root.push_back(0);\n        }else{\n            root.push_back(build(0, n,\
    \ v));\n        }\n    }\n\n    int latest_version() const { return root.size()-1;\
    \ }\n    int versions() const { return root.size(); }\n\n    int update(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(update_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int update(int k,\
    \ const T &x){ return update(latest_version(), k, x); }\n\n    int add(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(add_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int add(int k, const\
    \ T &x){ return add(latest_version(), k, x); }\n\n    T query(int t, int a, int\
    \ b) const {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root[t],\
    \ a, b, 0, n);\n    }\n    T query(int a, int b) const { return query(latest_version(),\
    \ a, b); }\n\n    T get(int t, int k) const { return query(t, k, k+1); }\n   \
    \ T operator[](const int &k) const { return get(latest_version(), k); }\n\nprivate:\n\
    \    int make_node(const T &v, int l, int r){\n        node.push_back({v, l, r});\n\
    \        return node.size()-1;\n    }\n\n    int build(int l, int r){\n      \
    \  if(l+1 == r) return make_node(M::e(), -1, -1);\n        int m = (l+r)>>1;\n\
    \        int ll = build(l, m), rr = build(m, r);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n    int build(int l, int r, const vector<T>\
    \ &v){\n        if(l+1 == r) return make_node(v[l], -1, -1);\n        int m =\
    \ (l+r)>>1;\n        int ll = build(l, m, v), rr = build(m, r, v);\n        return\
    \ make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n    int update_(int\
    \ id, int k, const T &x, int l, int r){\n        if(l+1 == r) return make_node(x,\
    \ -1, -1);\n        int m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n\
    \        if(k < m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr,\
    \ k, x, m, r);\n        return make_node(M::f(node[ll].val, node[rr].val), ll,\
    \ rr);\n    }\n\n    int add_(int id, int k, const T &x, int l, int r){\n    \
    \    if(l+1 == r) return make_node(M::f(node[id].val, x), -1, -1);\n        int\
    \ m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n        if(k <\
    \ m) ll = add_(ll, k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n   \
    \     return make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n \
    \   T query_(int id, int a, int b, int l, int r) const {\n        if(r <= a ||\
    \ b <= l) return M::e();\n        if(a <= l && r <= b) return node[id].val;\n\
    \        int m = (l+r)>>1;\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n};\n\n/*\nstruct Monoid{\n    using\
    \ T = long long;\n    static T f(T a, T b) { return a + b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief \u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Persistent Segment Tree)\n */\n"
  code: "template <class M>\nstruct PersistentSegmentTree{\n    using T = typename\
    \ M::T;\n    struct Node{\n        T val;\n        int l, r;\n    };\n\n    int\
    \ n{};\n    vector<Node> node;\n    vector<int> root;\n\n    explicit PersistentSegmentTree(int\
    \ n): n(n){\n        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n\
    \            root.push_back(0);\n        }else{\n            root.push_back(build(0,\
    \ n));\n        }\n    }\n    explicit PersistentSegmentTree(const vector<T> &v):\
    \ n(v.size()){\n        if(n == 0){\n            node.push_back({M::e(), -1, -1});\n\
    \            root.push_back(0);\n        }else{\n            root.push_back(build(0,\
    \ n, v));\n        }\n    }\n\n    int latest_version() const { return root.size()-1;\
    \ }\n    int versions() const { return root.size(); }\n\n    int update(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(update_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int update(int k,\
    \ const T &x){ return update(latest_version(), k, x); }\n\n    int add(int t,\
    \ int k, const T &x){\n        if(n == 0){\n            root.push_back(root[t]);\n\
    \            return latest_version();\n        }\n        root.push_back(add_(root[t],\
    \ k, x, 0, n));\n        return latest_version();\n    }\n    int add(int k, const\
    \ T &x){ return add(latest_version(), k, x); }\n\n    T query(int t, int a, int\
    \ b) const {\n        if(n == 0 || b <= a) return M::e();\n        return query_(root[t],\
    \ a, b, 0, n);\n    }\n    T query(int a, int b) const { return query(latest_version(),\
    \ a, b); }\n\n    T get(int t, int k) const { return query(t, k, k+1); }\n   \
    \ T operator[](const int &k) const { return get(latest_version(), k); }\n\nprivate:\n\
    \    int make_node(const T &v, int l, int r){\n        node.push_back({v, l, r});\n\
    \        return node.size()-1;\n    }\n\n    int build(int l, int r){\n      \
    \  if(l+1 == r) return make_node(M::e(), -1, -1);\n        int m = (l+r)>>1;\n\
    \        int ll = build(l, m), rr = build(m, r);\n        return make_node(M::f(node[ll].val,\
    \ node[rr].val), ll, rr);\n    }\n    int build(int l, int r, const vector<T>\
    \ &v){\n        if(l+1 == r) return make_node(v[l], -1, -1);\n        int m =\
    \ (l+r)>>1;\n        int ll = build(l, m, v), rr = build(m, r, v);\n        return\
    \ make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n    int update_(int\
    \ id, int k, const T &x, int l, int r){\n        if(l+1 == r) return make_node(x,\
    \ -1, -1);\n        int m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n\
    \        if(k < m) ll = update_(ll, k, x, l, m);\n        else rr = update_(rr,\
    \ k, x, m, r);\n        return make_node(M::f(node[ll].val, node[rr].val), ll,\
    \ rr);\n    }\n\n    int add_(int id, int k, const T &x, int l, int r){\n    \
    \    if(l+1 == r) return make_node(M::f(node[id].val, x), -1, -1);\n        int\
    \ m = (l+r)>>1;\n        int ll = node[id].l, rr = node[id].r;\n        if(k <\
    \ m) ll = add_(ll, k, x, l, m);\n        else rr = add_(rr, k, x, m, r);\n   \
    \     return make_node(M::f(node[ll].val, node[rr].val), ll, rr);\n    }\n\n \
    \   T query_(int id, int a, int b, int l, int r) const {\n        if(r <= a ||\
    \ b <= l) return M::e();\n        if(a <= l && r <= b) return node[id].val;\n\
    \        int m = (l+r)>>1;\n        return M::f(query_(node[id].l, a, b, l, m),\
    \ query_(node[id].r, a, b, m, r));\n    }\n};\n\n/*\nstruct Monoid{\n    using\
    \ T = long long;\n    static T f(T a, T b) { return a + b; }\n    static T e()\
    \ { return 0; }\n};\n*/\n\n/**\n * @brief \u6C38\u7D9A\u30BB\u30B0\u30E1\u30F3\
    \u30C8\u6728(Persistent Segment Tree)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: datastructure/persistent_segtree.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_point_add_range_sum_persistent.test.cpp
date: 2026-03-08
documentation_of: datastructure/persistent_segtree.cpp
layout: document
tags: "\u30C7\u30FC\u30BF\u69CB\u9020"
title: Persistent Segment Tree
---

## 概要

永続セグメント木。
各更新は新しいバージョンを生成し、過去バージョンへのクエリも可能。

## 計算量

- 構築 : `O(n)`
- `update/add` (1点更新) : `O(log n)`
- `query` (区間積) : `O(log n)`

## 使い方

1. `PersistentSegmentTree<Monoid> seg(n)` または `seg(v)` で初期化
2. `update(version, k, x)` または `add(version, k, x)` で新バージョンを生成
3. `query(version, l, r)` で任意バージョンの区間クエリ

## 提供された機能

- `latest_version()` : 最新バージョン番号
- `versions()` : 保持中バージョン数
- `update(...)` : 点代入で新バージョン作成
- `add(...)` : 点加算（`f(old, x)`）で新バージョン作成
- `query(...)` : 区間クエリ
- `get(t, k)` : バージョン `t` の `k` 番目の値
