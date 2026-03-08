---
category: "\u6728"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/hld.cpp
    title: "\u91CD\u8EFD\u5206\u89E3"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_hld_edge.test.cpp
    title: test/yosupo_many_aplusb_hld_edge.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki650_hld_edge.test.cpp
    title: test/yuki650_hld_edge.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)"
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
    \ HL\u5206\u89E3(HL Decomposition)\n */\n#line 2 \"tree/hld_edge.cpp\"\n\nstruct\
    \ HeavyLightDecompositionEdge {\n    HeavyLightDecomposition hld;\n\n    explicit\
    \ HeavyLightDecompositionEdge(int n) : hld(n) {}\n    explicit HeavyLightDecompositionEdge(vector<vector<int>>\
    \ &g) : hld(g) {}\n\n    void add_edge(int u, int v) {\n        hld.add_edge(u,\
    \ v);\n    }\n\n    void build(vector<int> roots = {0}) {\n        hld.build(roots);\n\
    \    }\n\n    int lca(int u, int v) {\n        return hld.lca(u, v);\n    }\n\n\
    \    int parent(int v) const {\n        return hld.parent(v);\n    }\n\n    int\
    \ ancestor(int v, int k) {\n        return hld.ancestor(v, k);\n    }\n\n    int\
    \ distance(int u, int v) {\n        return hld.distance(u, v);\n    }\n\n    int\
    \ edge_index(int v) const {\n        if (hld.par[v] == -1) return -1;\n      \
    \  return hld.id[v];\n    }\n\n    pair<int, int> subtree(int v) const {\n   \
    \     return hld.subtree(v, true);\n    }\n\n    template<typename F>\n    void\
    \ path(int u, int v, const F &f) {\n        hld.path(u, v, f, true);\n    }\n\n\
    \    template<typename F>\n    void apply_subtree(int v, const F &f) {\n     \
    \   hld.apply_subtree(v, f, true);\n    }\n\n    template<typename T, typename\
    \ Q, typename F>\n    T path_query(int u, int v, const T &e, const Q &q, const\
    \ F &f) {\n        return hld.path_query(u, v, e, q, f, true);\n    }\n\n    template<typename\
    \ T, typename QL, typename QR, typename F>\n    T path_query_ordered(int u, int\
    \ v, const T &e, const QL &ql, const QR &qr, const F &f) {\n        return hld.path_query_ordered(u,\
    \ v, e, ql, qr, f, true);\n    }\n\n    template<typename T, typename Q>\n   \
    \ T subtree_query(int v, const Q &q) {\n        return hld.subtree_query<T>(v,\
    \ q, true);\n    }\n};\n\n/**\n * @brief HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA\
    )\n */\n"
  code: "#include \"hld.cpp\"\n\nstruct HeavyLightDecompositionEdge {\n    HeavyLightDecomposition\
    \ hld;\n\n    explicit HeavyLightDecompositionEdge(int n) : hld(n) {}\n    explicit\
    \ HeavyLightDecompositionEdge(vector<vector<int>> &g) : hld(g) {}\n\n    void\
    \ add_edge(int u, int v) {\n        hld.add_edge(u, v);\n    }\n\n    void build(vector<int>\
    \ roots = {0}) {\n        hld.build(roots);\n    }\n\n    int lca(int u, int v)\
    \ {\n        return hld.lca(u, v);\n    }\n\n    int parent(int v) const {\n \
    \       return hld.parent(v);\n    }\n\n    int ancestor(int v, int k) {\n   \
    \     return hld.ancestor(v, k);\n    }\n\n    int distance(int u, int v) {\n\
    \        return hld.distance(u, v);\n    }\n\n    int edge_index(int v) const\
    \ {\n        if (hld.par[v] == -1) return -1;\n        return hld.id[v];\n   \
    \ }\n\n    pair<int, int> subtree(int v) const {\n        return hld.subtree(v,\
    \ true);\n    }\n\n    template<typename F>\n    void path(int u, int v, const\
    \ F &f) {\n        hld.path(u, v, f, true);\n    }\n\n    template<typename F>\n\
    \    void apply_subtree(int v, const F &f) {\n        hld.apply_subtree(v, f,\
    \ true);\n    }\n\n    template<typename T, typename Q, typename F>\n    T path_query(int\
    \ u, int v, const T &e, const Q &q, const F &f) {\n        return hld.path_query(u,\
    \ v, e, q, f, true);\n    }\n\n    template<typename T, typename QL, typename\
    \ QR, typename F>\n    T path_query_ordered(int u, int v, const T &e, const QL\
    \ &ql, const QR &qr, const F &f) {\n        return hld.path_query_ordered(u, v,\
    \ e, ql, qr, f, true);\n    }\n\n    template<typename T, typename Q>\n    T subtree_query(int\
    \ v, const Q &q) {\n        return hld.subtree_query<T>(v, q, true);\n    }\n\
    };\n\n/**\n * @brief HL\u5206\u89E3(\u8FBA\u30AF\u30A8\u30EA)\n */\n"
  dependsOn:
  - tree/hld.cpp
  isVerificationFile: false
  path: tree/hld_edge.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_hld_edge.test.cpp
  - test/yuki650_hld_edge.test.cpp
date: 2026-03-08
documentation_of: tree/hld_edge.cpp
layout: document
tags: "\u6728"
title: HLD Edge
---

## 説明
辺を子頂点側の位置に載せる重軽分解である。
根の位置には辺がないので、`edge_index(root)` は `-1` を返す。
パスクエリ・パス更新は `O(log^2 N)`。

## できること
- `HeavyLightDecompositionEdge hld(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(vector<int> roots = {0})`
  前処理をする。森にも対応する
- `int edge_index(int v)`
  `parent(v) - v` の辺が載る位置を返す。根なら `-1`
- `pair<int, int> subtree(int v)`
  部分木の辺集合に対応する半開区間 `[l, r)` を返す
- `void path(int u, int v, F f)`
  `u - v` パス上の辺を被覆する各区間へ `f(l, r)` を呼ぶ
- `T path_query(int u, int v, T e, Q q, F f)`
  可換向け辺パスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f)`
  非可換向け順序付き辺パスクエリ
- `void apply_subtree(int v, F f)`
  部分木の辺区間へ `f(l, r)` を呼ぶ
- `T subtree_query(int v, Q q)`
  部分木の辺区間クエリ

## 使い方
各辺の値は子頂点側に置く。
`parent(v) - v` の辺を更新したいときは `edge_index(v)` を使う。
パス順序が必要なときは `path_query_ordered` を使う。

```cpp
HeavyLightDecompositionEdge hld(n);
hld.add_edge(u, v);
hld.build();

int p = hld.edge_index(v);
seg.update(p, x);

auto ans = hld.path_query_ordered(a, b, Monoid::e(), ql, qr, Monoid::f);
```

## 実装上の補足
内部では頂点版 HLD の `edge = true` を使っている。
`subtree(v)` は `v` 自身へ入る辺を含まないので、根の部分木では木全体の辺区間になる。
