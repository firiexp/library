---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: tree/hld_edge.cpp
    title: "HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite.test.cpp
    title: test/yosupo_vertex_set_path_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
    title: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki1326_block_cut_tree.test.cpp
    title: test/yuki1326_block_cut_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki650_hld_edge.test.cpp
    title: test/yuki650_hld_edge.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "HL\u5206\u89E3(HL Decomposition)"
    links: []
  bundledCode: "#line 1 \"tree/hld.cpp\"\n\nclass HeavyLightDecomposition {\n    void\
    \ dfs_sz(int v){\n        int heavy = -1;\n        for (auto &&u : G[v]) {\n \
    \           if(u == par[v]) continue;\n            par[u] = v; dep[u] = dep[v]\
    \ + 1;\n            dfs_sz(u);\n            sub_size[v] += sub_size[u];\n    \
    \        if(heavy == -1 || sub_size[u] > sub_size[heavy]) heavy = u;\n       \
    \ }\n        if (heavy != -1 && G[v][0] != heavy) {\n            for (auto &&u\
    \ : G[v]) {\n                if (u == heavy) {\n                    swap(u, G[v][0]);\n\
    \                    break;\n                }\n            }\n        }\n   \
    \ }\n    void dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n     \
    \   id_inv[id[v]]= v;\n        tree_id[v] = c;\n        for (auto &&u : G[v])\
    \ {\n            if(u == par[v]) continue;\n            head[u] = (u == G[v][0]\
    \ ? head[v] : u);\n            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> par, dep, sub_size, id,\
    \ id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int n) : n(n),\
    \ G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n){}\n\
    \    explicit HeavyLightDecomposition(vector<vector<int>> &G) : n(G.size()), G(G),\
    \ par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n) {}\n\n\
    \    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n        G[v].emplace_back(u);\n\
    \    }\n\n    void build(vector<int> roots = {0}){\n        fill(par.begin(),\
    \ par.end(), -1);\n        fill(dep.begin(), dep.end(), 0);\n        fill(sub_size.begin(),\
    \ sub_size.end(), 1);\n        int c = 0, pos = 0;\n        for (auto &&i : roots)\
    \ {\n            dfs_sz(i);\n            head[i] = i;\n            dfs_hld(i,\
    \ c++, pos);\n        }\n    }\n\n    int lca(int u, int v){\n        while(true){\n\
    \            if(id[u] > id[v]) swap(u, v);\n            if(head[u] == head[v])\
    \ return u;\n            v = par[head[v]];\n        }\n    }\n\n    int parent(int\
    \ v) const {\n        return par[v];\n    }\n\n    int ancestor(int v, int k)\
    \ {\n        if(dep[v] < k) return -1;\n        while(true) {\n            int\
    \ u = head[v];\n            if(id[v] - k >= id[u]) return id_inv[id[v] - k];\n\
    \            k -= id[v]-id[u]+1;\n            v = par[u];\n        }\n    }\n\n\
    \    int distance(int u, int v){ return dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\
    \n    pair<int, int> subtree(int v, bool edge = false) const {\n        return\
    \ {id[v] + edge, id[v] + sub_size[v]};\n    }\n\n    template<typename F>\n  \
    \  void add(int u, int v, const F &f, bool edge){\n        while (head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n\
    \            v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v);\n\
    \        f(id[u]+edge, id[v]+1);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f, bool edge = false){\n        add(u, v, f, edge);\n\
    \    }\n\n    template<typename F>\n    void apply_subtree(int v, const F &f,\
    \ bool edge = false){\n        auto [l, r] = subtree(v, edge);\n        f(l, r);\n\
    \    }\n\n    template<typename T, typename Q, typename F>\n    T query(int u,\
    \ int v, const T &e, const Q &q, const F &f, bool edge){\n        T l = e, r =\
    \ e;\n        while(head[u] != head[v]){\n            if(id[u] > id[v]) swap(u,\
    \ v), swap(l, r);\n            l = f(l, q(id[head[v]], id[v]+1));\n          \
    \  v = par[head[v]];\n        }\n        if(id[u] > id[v]) swap(u, v), swap(l,\
    \ r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T path_query(int u, int v, const T &e, const\
    \ Q &q, const F &f, bool edge = false){\n        return query(u, v, e, q, f, edge);\n\
    \    }\n\n    template<typename T, typename QL, typename QR, typename F>\n   \
    \ T query_order(int u, int v, const T &e, const QL &ql, const QR &qr, const F\
    \ &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) {\n                l = f(l, qr(id[head[u]], id[u]+1));\n\
    \                u = par[head[u]];\n            }else {\n                r = f(ql(id[head[v]],\
    \ id[v]+1), r);\n                v = par[head[v]];\n            }\n        }\n\
    \        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n\
    \        return f(f(l, mid), r);\n    }\n\n    template<typename T, typename QL,\
    \ typename QR, typename F>\n    T path_query_ordered(int u, int v, const T &e,\
    \ const QL &ql, const QR &qr, const F &f, bool edge = false){\n        return\
    \ query_order(u, v, e, ql, qr, f, edge);\n    }\n\n    template<typename T, typename\
    \ Q>\n    T subtree_query(int v, const Q &q, bool edge = false){\n        auto\
    \ [l, r] = subtree(v, edge);\n        return q(l, r);\n    }\n};\n\n/**\n * @brief\
    \ HL\u5206\u89E3(HL Decomposition)\n */\n"
  code: "\nclass HeavyLightDecomposition {\n    void dfs_sz(int v){\n        int heavy\
    \ = -1;\n        for (auto &&u : G[v]) {\n            if(u == par[v]) continue;\n\
    \            par[u] = v; dep[u] = dep[v] + 1;\n            dfs_sz(u);\n      \
    \      sub_size[v] += sub_size[u];\n            if(heavy == -1 || sub_size[u]\
    \ > sub_size[heavy]) heavy = u;\n        }\n        if (heavy != -1 && G[v][0]\
    \ != heavy) {\n            for (auto &&u : G[v]) {\n                if (u == heavy)\
    \ {\n                    swap(u, G[v][0]);\n                    break;\n     \
    \           }\n            }\n        }\n    }\n    void dfs_hld(int v, int c,\
    \ int &pos){\n        id[v] = pos++;\n        id_inv[id[v]]= v;\n        tree_id[v]\
    \ = c;\n        for (auto &&u : G[v]) {\n            if(u == par[v]) continue;\n\
    \            head[u] = (u == G[v][0] ? head[v] : u);\n            dfs_hld(u, c,\
    \ pos);\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>> G;\n \
    \   vector<int> par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int\
    \ n) : n(n), G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>> &G) : n(G.size()),\
    \ G(G), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n)\
    \ {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n    \
    \    G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        fill(par.begin(), par.end(), -1);\n        fill(dep.begin(), dep.end(),\
    \ 0);\n        fill(sub_size.begin(), sub_size.end(), 1);\n        int c = 0,\
    \ pos = 0;\n        for (auto &&i : roots) {\n            dfs_sz(i);\n       \
    \     head[i] = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\n  \
    \  int lca(int u, int v){\n        while(true){\n            if(id[u] > id[v])\
    \ swap(u, v);\n            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int parent(int v) const {\n        return par[v];\n \
    \   }\n\n    int ancestor(int v, int k) {\n        if(dep[v] < k) return -1;\n\
    \        while(true) {\n            int u = head[v];\n            if(id[v] - k\
    \ >= id[u]) return id_inv[id[v] - k];\n            k -= id[v]-id[u]+1;\n     \
    \       v = par[u];\n        }\n    }\n\n    int distance(int u, int v){ return\
    \ dep[u] + dep[v] - 2*dep[lca(u, v)]; }\n\n    pair<int, int> subtree(int v, bool\
    \ edge = false) const {\n        return {id[v] + edge, id[v] + sub_size[v]};\n\
    \    }\n\n    template<typename F>\n    void add(int u, int v, const F &f, bool\
    \ edge){\n        while (head[u] != head[v]){\n            if(id[u] > id[v]) swap(u,\
    \ v);\n            f(id[head[v]], id[v]+1);\n            v = par[head[v]];\n \
    \       }\n        if(id[u] > id[v]) swap(u, v);\n        f(id[u]+edge, id[v]+1);\n\
    \    }\n\n    template<typename F>\n    void path(int u, int v, const F &f, bool\
    \ edge = false){\n        add(u, v, f, edge);\n    }\n\n    template<typename\
    \ F>\n    void apply_subtree(int v, const F &f, bool edge = false){\n        auto\
    \ [l, r] = subtree(v, edge);\n        f(l, r);\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q,\
    \ const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]],\
    \ id[v]+1));\n            v = par[head[v]];\n        }\n        if(id[u] > id[v])\
    \ swap(u, v), swap(l, r);\n        return f(q(id[u]+edge, id[v]+1), f(l, r));\n\
    \    }\n\n    template<typename T, typename Q, typename F>\n    T path_query(int\
    \ u, int v, const T &e, const Q &q, const F &f, bool edge = false){\n        return\
    \ query(u, v, e, q, f, edge);\n    }\n\n    template<typename T, typename QL,\
    \ typename QR, typename F>\n    T query_order(int u, int v, const T &e, const\
    \ QL &ql, const QR &qr, const F &f, bool edge){\n        T l = e, r = e;\n   \
    \     while(head[u] != head[v]){\n            if(id[u] > id[v]) {\n          \
    \      l = f(l, qr(id[head[u]], id[u]+1));\n                u = par[head[u]];\n\
    \            }else {\n                r = f(ql(id[head[v]], id[v]+1), r);\n  \
    \              v = par[head[v]];\n            }\n        }\n        T mid = (id[u]\
    \ > id[v] ? qr(id[v]+edge, id[u]+1) : ql(id[u]+edge, id[v]+1));\n        return\
    \ f(f(l, mid), r);\n    }\n\n    template<typename T, typename QL, typename QR,\
    \ typename F>\n    T path_query_ordered(int u, int v, const T &e, const QL &ql,\
    \ const QR &qr, const F &f, bool edge = false){\n        return query_order(u,\
    \ v, e, ql, qr, f, edge);\n    }\n\n    template<typename T, typename Q>\n   \
    \ T subtree_query(int v, const Q &q, bool edge = false){\n        auto [l, r]\
    \ = subtree(v, edge);\n        return q(l, r);\n    }\n};\n\n/**\n * @brief HL\u5206\
    \u89E3(HL Decomposition)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/hld.cpp
  requiredBy:
  - tree/hld_edge.cpp
  timestamp: '2026-03-13 21:29:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yuki1326_block_cut_tree.test.cpp
  - test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - test/yuki650_hld_edge.test.cpp
  - test/yosupo_vertex_set_path_composite.test.cpp
  - test/yosupo_vertex_add_subtree_sum_hld.test.cpp
date: 2019-10-10
documentation_of: tree/hld.cpp
layout: document
tags: "\u6728"
title: "HL\u5206\u89E3(HL Decomposition)"
---

## 説明
根つき木を Euler Tour 順の連続区間へ写し、パスや部分木を少数個の区間に分解する。
パスクエリ・パス更新は $O(log^2 N)$、部分木クエリは $O(f(N))$ で扱える。

## できること
- `HeavyLightDecomposition hld(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(vector<int> roots = {0})`
  前処理をする。森にも対応する
- `int lca(int u, int v)`
  最近共通祖先を返す
- `int parent(int v)`
  親を返す。根なら `-1`
- `int ancestor(int v, int k)`
  `k` 個上の祖先を返す。存在しなければ `-1`
- `int distance(int u, int v)`
  木上距離を返す
- `pair<int, int> subtree(int v, bool edge = false)`
  部分木に対応する半開区間 `[l, r)` を返す
- `void path(int u, int v, F f, bool edge = false)`
  パスを被覆する各区間へ `f(l, r)` を呼ぶ
- `T path_query(int u, int v, T e, Q q, F f, bool edge = false)`
  可換向けパスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f, bool edge = false)`
  非可換向け順序付きパスクエリ
- `void apply_subtree(int v, F f, bool edge = false)`
  部分木区間へ `f(l, r)` を呼ぶ
- `T subtree_query(int v, Q q, bool edge = false)`
  部分木区間クエリ

## 使い方
`id[v]` を頂点 `v` の 1 次元位置としてセグ木や BIT に載せる。
部分木は `subtree(v)` の区間 1 本で取れる。
パスは `path` / `path_query` / `path_query_ordered` を使う。

```cpp
HeavyLightDecomposition hld(n);
hld.add_edge(u, v);
hld.build();

auto [l, r] = hld.subtree(v);
auto sub = seg.query(l, r);

auto ans = hld.path_query_ordered(a, b, Monoid::e(), ql, qr, Monoid::f, false);
```

## 実装上の補足
`edge = true` にすると、LCA 側の頂点を除いた辺クエリ区間になる。
`path_query_ordered` は `u -> v` の向きを保つ。
