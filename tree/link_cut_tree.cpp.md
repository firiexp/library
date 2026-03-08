---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
    title: test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: Link-Cut Tree
    links: []
  bundledCode: "#line 1 \"tree/link_cut_tree.cpp\"\ntemplate <class M>\nstruct LinkCutTree\
    \ {\n    using T = typename M::T;\n\n    struct Node {\n        int l, r, p, sz;\n\
    \        bool rev;\n        T val, sum, rsum;\n        Node() : l(-1), r(-1),\
    \ p(-1), sz(1), rev(false), val(M::e()), sum(M::e()), rsum(M::e()) {}\n    };\n\
    \n    int n;\n    vector<Node> nodes;\n\n    explicit LinkCutTree(int n) : n(n),\
    \ nodes(n) {}\n\n    bool is_root(int x) const {\n        int p = nodes[x].p;\n\
    \        return p == -1 || (nodes[p].l != x && nodes[p].r != x);\n    }\n\n  \
    \  void reverse(int x) {\n        if (x == -1) return;\n        swap(nodes[x].l,\
    \ nodes[x].r);\n        swap(nodes[x].sum, nodes[x].rsum);\n        nodes[x].rev\
    \ ^= 1;\n    }\n\n    void push(int x) {\n        if (x == -1 || !nodes[x].rev)\
    \ return;\n        reverse(nodes[x].l);\n        reverse(nodes[x].r);\n      \
    \  nodes[x].rev = false;\n    }\n\n    void pull(int x) {\n        nodes[x].sz\
    \ = 1;\n        nodes[x].sum = nodes[x].val;\n        nodes[x].rsum = nodes[x].val;\n\
    \        if (nodes[x].l != -1) {\n            int y = nodes[x].l;\n          \
    \  nodes[x].sz += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[y].sum,\
    \ nodes[x].sum);\n            nodes[x].rsum = M::f(nodes[x].rsum, nodes[y].rsum);\n\
    \        }\n        if (nodes[x].r != -1) {\n            int y = nodes[x].r;\n\
    \            nodes[x].sz += nodes[y].sz;\n            nodes[x].sum = M::f(nodes[x].sum,\
    \ nodes[y].sum);\n            nodes[x].rsum = M::f(nodes[y].rsum, nodes[x].rsum);\n\
    \        }\n    }\n\n    void rotate(int x) {\n        int p = nodes[x].p;\n \
    \       int g = nodes[p].p;\n        if (nodes[p].l == x) {\n            int b\
    \ = nodes[x].r;\n            nodes[x].r = p;\n            nodes[p].l = b;\n  \
    \          if (b != -1) nodes[b].p = p;\n        } else {\n            int b =\
    \ nodes[x].l;\n            nodes[x].l = p;\n            nodes[p].r = b;\n    \
    \        if (b != -1) nodes[b].p = p;\n        }\n        nodes[p].p = x;\n  \
    \      nodes[x].p = g;\n        if (g != -1) {\n            if (nodes[g].l ==\
    \ p) nodes[g].l = x;\n            if (nodes[g].r == p) nodes[g].r = x;\n     \
    \   }\n        pull(p);\n        pull(x);\n    }\n\n    void splay(int x) {\n\
    \        vector<int> st(1, x);\n        for (int y = x; !is_root(y); y = nodes[y].p)\
    \ st.emplace_back(nodes[y].p);\n        while (!st.empty()) {\n            push(st.back());\n\
    \            st.pop_back();\n        }\n        while (!is_root(x)) {\n      \
    \      int p = nodes[x].p;\n            int g = nodes[p].p;\n            if (!is_root(p))\
    \ {\n                bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);\n \
    \               rotate(zigzig ? p : x);\n            }\n            rotate(x);\n\
    \        }\n    }\n\n    int expose(int x) {\n        int rp = -1;\n        for\
    \ (int cur = x; cur != -1; cur = nodes[cur].p) {\n            splay(cur);\n  \
    \          nodes[cur].r = rp;\n            pull(cur);\n            rp = cur;\n\
    \        }\n        splay(x);\n        return rp;\n    }\n\n    void evert(int\
    \ x) {\n        expose(x);\n        reverse(x);\n        push(x);\n    }\n\n \
    \   int get_root(int x) {\n        expose(x);\n        while (nodes[x].l != -1)\
    \ {\n            push(x);\n            x = nodes[x].l;\n        }\n        splay(x);\n\
    \        return x;\n    }\n\n    bool connected(int u, int v) {\n        return\
    \ get_root(u) == get_root(v);\n    }\n\n    bool link(int u, int v) {\n      \
    \  evert(u);\n        if (get_root(v) == u) return false;\n        expose(v);\n\
    \        nodes[u].p = v;\n        nodes[v].r = u;\n        pull(v);\n        return\
    \ true;\n    }\n\n    bool cut(int u, int v) {\n        evert(u);\n        expose(v);\n\
    \        if (nodes[v].l != u || nodes[u].r != -1) return false;\n        nodes[v].l\
    \ = -1;\n        nodes[u].p = -1;\n        pull(v);\n        return true;\n  \
    \  }\n\n    int lca(int u, int v) {\n        if (!connected(u, v)) return -1;\n\
    \        expose(u);\n        return expose(v);\n    }\n\n    int parent(int x)\
    \ {\n        expose(x);\n        if (nodes[x].l == -1) return -1;\n        x =\
    \ nodes[x].l;\n        push(x);\n        while (nodes[x].r != -1) {\n        \
    \    x = nodes[x].r;\n            push(x);\n        }\n        splay(x);\n   \
    \     return x;\n    }\n\n    void set(int x, const T &val) {\n        expose(x);\n\
    \        nodes[x].val = val;\n        pull(x);\n    }\n\n    T get(int x) {\n\
    \        expose(x);\n        return nodes[x].val;\n    }\n\n    T fold(int u,\
    \ int v) {\n        evert(u);\n        expose(v);\n        return nodes[v].sum;\n\
    \    }\n\n    int dist(int u, int v) {\n        evert(u);\n        expose(v);\n\
    \        return nodes[v].sz - 1;\n    }\n};\n\n/**\n * @brief Link-Cut Tree\n\
    \ */\n"
  code: "template <class M>\nstruct LinkCutTree {\n    using T = typename M::T;\n\n\
    \    struct Node {\n        int l, r, p, sz;\n        bool rev;\n        T val,\
    \ sum, rsum;\n        Node() : l(-1), r(-1), p(-1), sz(1), rev(false), val(M::e()),\
    \ sum(M::e()), rsum(M::e()) {}\n    };\n\n    int n;\n    vector<Node> nodes;\n\
    \n    explicit LinkCutTree(int n) : n(n), nodes(n) {}\n\n    bool is_root(int\
    \ x) const {\n        int p = nodes[x].p;\n        return p == -1 || (nodes[p].l\
    \ != x && nodes[p].r != x);\n    }\n\n    void reverse(int x) {\n        if (x\
    \ == -1) return;\n        swap(nodes[x].l, nodes[x].r);\n        swap(nodes[x].sum,\
    \ nodes[x].rsum);\n        nodes[x].rev ^= 1;\n    }\n\n    void push(int x) {\n\
    \        if (x == -1 || !nodes[x].rev) return;\n        reverse(nodes[x].l);\n\
    \        reverse(nodes[x].r);\n        nodes[x].rev = false;\n    }\n\n    void\
    \ pull(int x) {\n        nodes[x].sz = 1;\n        nodes[x].sum = nodes[x].val;\n\
    \        nodes[x].rsum = nodes[x].val;\n        if (nodes[x].l != -1) {\n    \
    \        int y = nodes[x].l;\n            nodes[x].sz += nodes[y].sz;\n      \
    \      nodes[x].sum = M::f(nodes[y].sum, nodes[x].sum);\n            nodes[x].rsum\
    \ = M::f(nodes[x].rsum, nodes[y].rsum);\n        }\n        if (nodes[x].r !=\
    \ -1) {\n            int y = nodes[x].r;\n            nodes[x].sz += nodes[y].sz;\n\
    \            nodes[x].sum = M::f(nodes[x].sum, nodes[y].sum);\n            nodes[x].rsum\
    \ = M::f(nodes[y].rsum, nodes[x].rsum);\n        }\n    }\n\n    void rotate(int\
    \ x) {\n        int p = nodes[x].p;\n        int g = nodes[p].p;\n        if (nodes[p].l\
    \ == x) {\n            int b = nodes[x].r;\n            nodes[x].r = p;\n    \
    \        nodes[p].l = b;\n            if (b != -1) nodes[b].p = p;\n        }\
    \ else {\n            int b = nodes[x].l;\n            nodes[x].l = p;\n     \
    \       nodes[p].r = b;\n            if (b != -1) nodes[b].p = p;\n        }\n\
    \        nodes[p].p = x;\n        nodes[x].p = g;\n        if (g != -1) {\n  \
    \          if (nodes[g].l == p) nodes[g].l = x;\n            if (nodes[g].r ==\
    \ p) nodes[g].r = x;\n        }\n        pull(p);\n        pull(x);\n    }\n\n\
    \    void splay(int x) {\n        vector<int> st(1, x);\n        for (int y =\
    \ x; !is_root(y); y = nodes[y].p) st.emplace_back(nodes[y].p);\n        while\
    \ (!st.empty()) {\n            push(st.back());\n            st.pop_back();\n\
    \        }\n        while (!is_root(x)) {\n            int p = nodes[x].p;\n \
    \           int g = nodes[p].p;\n            if (!is_root(p)) {\n            \
    \    bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);\n                rotate(zigzig\
    \ ? p : x);\n            }\n            rotate(x);\n        }\n    }\n\n    int\
    \ expose(int x) {\n        int rp = -1;\n        for (int cur = x; cur != -1;\
    \ cur = nodes[cur].p) {\n            splay(cur);\n            nodes[cur].r = rp;\n\
    \            pull(cur);\n            rp = cur;\n        }\n        splay(x);\n\
    \        return rp;\n    }\n\n    void evert(int x) {\n        expose(x);\n  \
    \      reverse(x);\n        push(x);\n    }\n\n    int get_root(int x) {\n   \
    \     expose(x);\n        while (nodes[x].l != -1) {\n            push(x);\n \
    \           x = nodes[x].l;\n        }\n        splay(x);\n        return x;\n\
    \    }\n\n    bool connected(int u, int v) {\n        return get_root(u) == get_root(v);\n\
    \    }\n\n    bool link(int u, int v) {\n        evert(u);\n        if (get_root(v)\
    \ == u) return false;\n        expose(v);\n        nodes[u].p = v;\n        nodes[v].r\
    \ = u;\n        pull(v);\n        return true;\n    }\n\n    bool cut(int u, int\
    \ v) {\n        evert(u);\n        expose(v);\n        if (nodes[v].l != u ||\
    \ nodes[u].r != -1) return false;\n        nodes[v].l = -1;\n        nodes[u].p\
    \ = -1;\n        pull(v);\n        return true;\n    }\n\n    int lca(int u, int\
    \ v) {\n        if (!connected(u, v)) return -1;\n        expose(u);\n       \
    \ return expose(v);\n    }\n\n    int parent(int x) {\n        expose(x);\n  \
    \      if (nodes[x].l == -1) return -1;\n        x = nodes[x].l;\n        push(x);\n\
    \        while (nodes[x].r != -1) {\n            x = nodes[x].r;\n           \
    \ push(x);\n        }\n        splay(x);\n        return x;\n    }\n\n    void\
    \ set(int x, const T &val) {\n        expose(x);\n        nodes[x].val = val;\n\
    \        pull(x);\n    }\n\n    T get(int x) {\n        expose(x);\n        return\
    \ nodes[x].val;\n    }\n\n    T fold(int u, int v) {\n        evert(u);\n    \
    \    expose(v);\n        return nodes[v].sum;\n    }\n\n    int dist(int u, int\
    \ v) {\n        evert(u);\n        expose(v);\n        return nodes[v].sz - 1;\n\
    \    }\n};\n\n/**\n * @brief Link-Cut Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/link_cut_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
date: 2026-03-08
documentation_of: tree/link_cut_tree.cpp
layout: post
tags: "\u6728"
title: Link-Cut Tree
---

## 説明
動的森に対して、辺の追加・削除、根の付け替え、パス上の集約を扱う。
各操作は償却 `O(log N)`。

## できること
- `LinkCutTree<M> lct(n)`
  頂点数 `n` の森を作る
- `bool link(int u, int v)`
  `u` と `v` の間に辺を張る。同じ連結成分なら `false`
- `bool cut(int u, int v)`
  `u` - `v` 間の辺を削除する。存在しなければ `false`
- `void evert(int v)`
  `v` を根にする
- `bool connected(int u, int v)`
  同じ木にあるかを返す
- `int get_root(int v)`
  `v` が属する木の根を返す
- `int lca(int u, int v)`
  現在の根に対する LCA を返す。非連結なら `-1`
- `int parent(int v)`
  現在の根に対する親を返す。根なら `-1`
- `void set(int v, T x)`
  頂点 `v` の値を `x` にする
- `T get(int v)`
  頂点 `v` の値を返す
- `T fold(int u, int v)`
  パス `u -> v` 上の値を順番通りに集約する
- `int dist(int u, int v)`
  パス長を返す

## 使い方
`LinkCutTree<M> lct(n);` を作り、`M` に `using T`、`static T f(T, T)`、`static T e()` を定義する。
頂点値は `set(v, x)` で更新し、`fold(u, v)` で `u` から `v` への順序付きパス集約を取る。
辺操作は `link(u, v)`、`cut(u, v)` を使う。

`M` は次を持てばよい。

```cpp
struct Monoid {
    using T = ...;
    static T f(T a, T b);
    static T e();
};
```

`fold(u, v)` は順序を保つので、非可換モノイドでも使える。
