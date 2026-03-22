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
    \n    int n;\n    vector<Node> nodes;\n    vector<int> push_stack;\n\n    explicit\
    \ LinkCutTree(int n) : n(n), nodes(n), push_stack() {\n        push_stack.reserve(64);\n\
    \    }\n\n    bool is_root(int x) const {\n        int p = nodes[x].p;\n     \
    \   return p == -1 || (nodes[p].l != x && nodes[p].r != x);\n    }\n\n    void\
    \ reverse(int x) {\n        if (x == -1) return;\n        Node &nx = nodes[x];\n\
    \        swap(nx.l, nx.r);\n        swap(nx.sum, nx.rsum);\n        nx.rev ^=\
    \ 1;\n    }\n\n    void push(int x) {\n        if (x == -1 || !nodes[x].rev) return;\n\
    \        reverse(nodes[x].l);\n        reverse(nodes[x].r);\n        nodes[x].rev\
    \ = false;\n    }\n\n    void pull(int x) {\n        Node &nx = nodes[x];\n  \
    \      nx.sz = 1;\n        nx.sum = nx.val;\n        nx.rsum = nx.val;\n     \
    \   if (nx.l != -1) {\n            int y = nx.l;\n            nx.sz += nodes[y].sz;\n\
    \            nx.sum = M::f(nodes[y].sum, nx.sum);\n            nx.rsum = M::f(nx.rsum,\
    \ nodes[y].rsum);\n        }\n        if (nx.r != -1) {\n            int y = nx.r;\n\
    \            nx.sz += nodes[y].sz;\n            nx.sum = M::f(nx.sum, nodes[y].sum);\n\
    \            nx.rsum = M::f(nodes[y].rsum, nx.rsum);\n        }\n    }\n\n   \
    \ void rotate(int x) {\n        Node &nx = nodes[x];\n        int p = nx.p;\n\
    \        Node &np = nodes[p];\n        int g = np.p;\n        if (np.l == x) {\n\
    \            int b = nx.r;\n            nx.r = p;\n            np.l = b;\n   \
    \         if (b != -1) nodes[b].p = p;\n        } else {\n            int b =\
    \ nx.l;\n            nx.l = p;\n            np.r = b;\n            if (b != -1)\
    \ nodes[b].p = p;\n        }\n        np.p = x;\n        nx.p = g;\n        if\
    \ (g != -1) {\n            Node &ng = nodes[g];\n            if (ng.l == p) {\n\
    \                ng.l = x;\n            } else if (ng.r == p) {\n            \
    \    ng.r = x;\n            }\n        }\n        pull(p);\n        pull(x);\n\
    \    }\n\n    void splay(int x) {\n        push_stack.clear();\n        push_stack.emplace_back(x);\n\
    \        for (int y = x; !is_root(y); y = nodes[y].p) push_stack.emplace_back(nodes[y].p);\n\
    \        for (int i = (int)push_stack.size() - 1; i >= 0; --i) {\n           \
    \ push(push_stack[i]);\n        }\n        while (!is_root(x)) {\n           \
    \ int p = nodes[x].p;\n            int g = nodes[p].p;\n            if (!is_root(p))\
    \ {\n                bool zigzig = (nodes[p].l == x) == (nodes[g].l == p);\n \
    \               rotate(zigzig ? p : x);\n            }\n            rotate(x);\n\
    \        }\n    }\n\n    int expose(int x) {\n        int rp = -1;\n        for\
    \ (int cur = x; cur != -1; cur = nodes[cur].p) {\n            splay(cur);\n  \
    \          nodes[cur].r = rp;\n            pull(cur);\n            rp = cur;\n\
    \        }\n        splay(x);\n        return rp;\n    }\n\n    void evert(int\
    \ x) {\n        expose(x);\n        reverse(x);\n    }\n\n    int get_root(int\
    \ x) {\n        expose(x);\n        while (nodes[x].l != -1) {\n            push(x);\n\
    \            x = nodes[x].l;\n        }\n        splay(x);\n        return x;\n\
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
  code: "template <class M>\nstruct LinkCutTree {\n    using T = typename M::T;\n\n\
    \    struct Node {\n        int l, r, p, sz;\n        bool rev;\n        T val,\
    \ sum, rsum;\n        Node() : l(-1), r(-1), p(-1), sz(1), rev(false), val(M::e()),\
    \ sum(M::e()), rsum(M::e()) {}\n    };\n\n    int n;\n    vector<Node> nodes;\n\
    \    vector<int> push_stack;\n\n    explicit LinkCutTree(int n) : n(n), nodes(n),\
    \ push_stack() {\n        push_stack.reserve(64);\n    }\n\n    bool is_root(int\
    \ x) const {\n        int p = nodes[x].p;\n        return p == -1 || (nodes[p].l\
    \ != x && nodes[p].r != x);\n    }\n\n    void reverse(int x) {\n        if (x\
    \ == -1) return;\n        Node &nx = nodes[x];\n        swap(nx.l, nx.r);\n  \
    \      swap(nx.sum, nx.rsum);\n        nx.rev ^= 1;\n    }\n\n    void push(int\
    \ x) {\n        if (x == -1 || !nodes[x].rev) return;\n        reverse(nodes[x].l);\n\
    \        reverse(nodes[x].r);\n        nodes[x].rev = false;\n    }\n\n    void\
    \ pull(int x) {\n        Node &nx = nodes[x];\n        nx.sz = 1;\n        nx.sum\
    \ = nx.val;\n        nx.rsum = nx.val;\n        if (nx.l != -1) {\n          \
    \  int y = nx.l;\n            nx.sz += nodes[y].sz;\n            nx.sum = M::f(nodes[y].sum,\
    \ nx.sum);\n            nx.rsum = M::f(nx.rsum, nodes[y].rsum);\n        }\n \
    \       if (nx.r != -1) {\n            int y = nx.r;\n            nx.sz += nodes[y].sz;\n\
    \            nx.sum = M::f(nx.sum, nodes[y].sum);\n            nx.rsum = M::f(nodes[y].rsum,\
    \ nx.rsum);\n        }\n    }\n\n    void rotate(int x) {\n        Node &nx =\
    \ nodes[x];\n        int p = nx.p;\n        Node &np = nodes[p];\n        int\
    \ g = np.p;\n        if (np.l == x) {\n            int b = nx.r;\n           \
    \ nx.r = p;\n            np.l = b;\n            if (b != -1) nodes[b].p = p;\n\
    \        } else {\n            int b = nx.l;\n            nx.l = p;\n        \
    \    np.r = b;\n            if (b != -1) nodes[b].p = p;\n        }\n        np.p\
    \ = x;\n        nx.p = g;\n        if (g != -1) {\n            Node &ng = nodes[g];\n\
    \            if (ng.l == p) {\n                ng.l = x;\n            } else if\
    \ (ng.r == p) {\n                ng.r = x;\n            }\n        }\n       \
    \ pull(p);\n        pull(x);\n    }\n\n    void splay(int x) {\n        push_stack.clear();\n\
    \        push_stack.emplace_back(x);\n        for (int y = x; !is_root(y); y =\
    \ nodes[y].p) push_stack.emplace_back(nodes[y].p);\n        for (int i = (int)push_stack.size()\
    \ - 1; i >= 0; --i) {\n            push(push_stack[i]);\n        }\n        while\
    \ (!is_root(x)) {\n            int p = nodes[x].p;\n            int g = nodes[p].p;\n\
    \            if (!is_root(p)) {\n                bool zigzig = (nodes[p].l ==\
    \ x) == (nodes[g].l == p);\n                rotate(zigzig ? p : x);\n        \
    \    }\n            rotate(x);\n        }\n    }\n\n    int expose(int x) {\n\
    \        int rp = -1;\n        for (int cur = x; cur != -1; cur = nodes[cur].p)\
    \ {\n            splay(cur);\n            nodes[cur].r = rp;\n            pull(cur);\n\
    \            rp = cur;\n        }\n        splay(x);\n        return rp;\n   \
    \ }\n\n    void evert(int x) {\n        expose(x);\n        reverse(x);\n    }\n\
    \n    int get_root(int x) {\n        expose(x);\n        while (nodes[x].l !=\
    \ -1) {\n            push(x);\n            x = nodes[x].l;\n        }\n      \
    \  splay(x);\n        return x;\n    }\n\n    bool connected(int u, int v) {\n\
    \        return get_root(u) == get_root(v);\n    }\n\n    bool link(int u, int\
    \ v) {\n        evert(u);\n        if (get_root(v) == u) return false;\n     \
    \   expose(v);\n        nodes[u].p = v;\n        nodes[v].r = u;\n        pull(v);\n\
    \        return true;\n    }\n\n    bool cut(int u, int v) {\n        evert(u);\n\
    \        expose(v);\n        if (nodes[v].l != u || nodes[u].r != -1) return false;\n\
    \        nodes[v].l = -1;\n        nodes[u].p = -1;\n        pull(v);\n      \
    \  return true;\n    }\n\n    int lca(int u, int v) {\n        if (!connected(u,\
    \ v)) return -1;\n        expose(u);\n        return expose(v);\n    }\n\n   \
    \ int parent(int x) {\n        expose(x);\n        if (nodes[x].l == -1) return\
    \ -1;\n        x = nodes[x].l;\n        push(x);\n        while (nodes[x].r !=\
    \ -1) {\n            x = nodes[x].r;\n            push(x);\n        }\n      \
    \  splay(x);\n        return x;\n    }\n\n    void set(int x, const T &val) {\n\
    \        expose(x);\n        nodes[x].val = val;\n        pull(x);\n    }\n\n\
    \    T get(int x) {\n        expose(x);\n        return nodes[x].val;\n    }\n\
    \n    T fold(int u, int v) {\n        evert(u);\n        expose(v);\n        return\
    \ nodes[v].sum;\n    }\n\n    int dist(int u, int v) {\n        evert(u);\n  \
    \      expose(v);\n        return nodes[v].sz - 1;\n    }\n};\n\n/**\n * @brief\
    \ Link-Cut Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/link_cut_tree.cpp
  requiredBy: []
  timestamp: '2026-03-13 21:57:37+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_dynamic_tree_vertex_set_path_composite.test.cpp
date: 2026-03-08
documentation_of: tree/link_cut_tree.cpp
layout: document
tags: "\u6728"
title: Link-Cut Tree
---

## 説明
動的森に対して、辺の追加・削除、根の付け替え、パス上の集約を扱う。
各操作は償却 $O(log N)$。

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
