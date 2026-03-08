---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':question:'
    path: tree/hld_edge.cpp
    title: "\u8FBA\u30AF\u30A8\u30EA\u5411\u3051\u91CD\u8EFD\u5206\u89E3"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_hld_edge.test.cpp
    title: test/yosupo_many_aplusb_hld_edge.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_hld.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_set_path_composite.test.cpp
    title: test/yosupo_vertex_set_path_composite.test.cpp
  - icon: ':x:'
    path: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
    title: test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - icon: ':x:'
    path: test/yuki650_hld_edge.test.cpp
    title: test/yuki650_hld_edge.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
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
    \ [l, r] = subtree(v, edge);\n        return q(l, r);\n    }\n};\n"
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
    \ = subtree(v, edge);\n        return q(l, r);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/hld.cpp
  requiredBy:
  - tree/hld_edge.cpp
  timestamp: '2026-03-08 17:42:36+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yosupo_many_aplusb_hld_edge.test.cpp
  - test/yosupo_vertex_add_subtree_sum_hld.test.cpp
  - test/yosupo_vertex_set_path_composite_hld_helper.test.cpp
  - test/yuki650_hld_edge.test.cpp
  - test/yosupo_vertex_set_path_composite.test.cpp
documentation_of: tree/hld.cpp
layout: document
redirect_from:
- /library/tree/hld.cpp
- /library/tree/hld.cpp.html
title: tree/hld.cpp
---
