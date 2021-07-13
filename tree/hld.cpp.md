---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_set_path_composite.test.cpp
    title: test/yosupo_vertex_set_path_composite.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/hld.cpp\"\nclass HeavyLightDecomposition {\n    void\
    \ dfs_sz(int v){\n        for (auto &&u : G[v]) {\n            if(u == par[v])\
    \ continue;\n            par[u] = v; dep[u] = dep[v] + 1;\n            dfs_sz(u);\n\
    \            sub_size[v] += sub_size[u];\n            if(sub_size[u] > sub_size[G[v][0]])\
    \ swap(u, G[v][0]);\n        }\n    }\n    void dfs_hld(int v, int c, int &pos){\n\
    \        id[v] = pos++;\n        id_inv[id[v]]= v;\n        tree_id[v] = c;\n\
    \        for (auto &&u : G[v]) {\n            if(u == par[v]) continue;\n    \
    \        head[u] = (u == G[v][0] ? head[v] : u);\n            dfs_hld(u, c, pos);\n\
    \        }\n    }\npublic:\n    int n;\n    vector<vector<int>> G;\n    vector<int>\
    \ par, dep, sub_size, id, id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int\
    \ n) : n(n), G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n),\
    \ head(n){}\n    explicit HeavyLightDecomposition(vector<vector<int>> &G) :G(G),\
    \ n(G.size()), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n)\
    \ {}\n\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n    \
    \    G[v].emplace_back(u);\n    }\n\n    void build(vector<int> roots = {0}){\n\
    \        int c = 0, pos = 0;\n        for (auto &&i : roots) {\n            dfs_sz(i);\n\
    \            head[i] = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\
    \n    int lca(int u, int v){\n        while(true){\n            if(id[u] > id[v])\
    \ swap(u, v);\n            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int distance(int u, int v){ return dep[u] + dep[v] -\
    \ 2*dep[lca(u, v)]; }\n\n    template<typename F>\n    void add(int u, int v,\
    \ const F &f, bool edge){\n        while (head[u] != head[v]){\n            if(id[u]\
    \ > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n            v =\
    \ par[head[v]];\n        }\n        f(id[u]+edge, id[v]+1);\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q,\
    \ const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]],\
    \ id[v]+1));\n            v = par[head[v]];\n        }\n        return f(q(id[u]+edge,\
    \ id[v]+1), f(l, r));\n    }\n\n    template<typename T, typename QL, typename\
    \ QR, typename F>\n    T query_order(int u, int v, const T &e, const QL &ql, const\
    \ QR &qr, const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u]\
    \ != head[v]){\n            if(id[u] > id[v]) {\n                l = f(l, qr(id[head[u]],\
    \ id[u]+1));\n                u = par[head[u]];\n            }else {\n       \
    \         r = f(ql(id[head[v]], id[v]+1), r);\n                v = par[head[v]];\n\
    \            }\n        }\n        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1)\
    \ : ql(id[u]+edge, id[v]+1));\n        return f(f(l, mid), r);\n    }\n};\n"
  code: "class HeavyLightDecomposition {\n    void dfs_sz(int v){\n        for (auto\
    \ &&u : G[v]) {\n            if(u == par[v]) continue;\n            par[u] = v;\
    \ dep[u] = dep[v] + 1;\n            dfs_sz(u);\n            sub_size[v] += sub_size[u];\n\
    \            if(sub_size[u] > sub_size[G[v][0]]) swap(u, G[v][0]);\n        }\n\
    \    }\n    void dfs_hld(int v, int c, int &pos){\n        id[v] = pos++;\n  \
    \      id_inv[id[v]]= v;\n        tree_id[v] = c;\n        for (auto &&u : G[v])\
    \ {\n            if(u == par[v]) continue;\n            head[u] = (u == G[v][0]\
    \ ? head[v] : u);\n            dfs_hld(u, c, pos);\n        }\n    }\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> par, dep, sub_size, id,\
    \ id_inv, tree_id, head;\n    explicit HeavyLightDecomposition(int n) : n(n),\
    \ G(n), par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n){}\n\
    \    explicit HeavyLightDecomposition(vector<vector<int>> &G) :G(G), n(G.size()),\
    \ par(n), dep(n), sub_size(n, 1), id(n), id_inv(n), tree_id(n), head(n) {}\n\n\
    \    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n        G[v].emplace_back(u);\n\
    \    }\n\n    void build(vector<int> roots = {0}){\n        int c = 0, pos = 0;\n\
    \        for (auto &&i : roots) {\n            dfs_sz(i);\n            head[i]\
    \ = i;\n            dfs_hld(i, c++, pos);\n        }\n    }\n\n    int lca(int\
    \ u, int v){\n        while(true){\n            if(id[u] > id[v]) swap(u, v);\n\
    \            if(head[u] == head[v]) return u;\n            v = par[head[v]];\n\
    \        }\n    }\n\n    int distance(int u, int v){ return dep[u] + dep[v] -\
    \ 2*dep[lca(u, v)]; }\n\n    template<typename F>\n    void add(int u, int v,\
    \ const F &f, bool edge){\n        while (head[u] != head[v]){\n            if(id[u]\
    \ > id[v]) swap(u, v);\n            f(id[head[v]], id[v]+1);\n            v =\
    \ par[head[v]];\n        }\n        f(id[u]+edge, id[v]+1);\n    }\n\n    template<typename\
    \ T, typename Q, typename F>\n    T query(int u, int v, const T &e, const Q &q,\
    \ const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u] != head[v]){\n\
    \            if(id[u] > id[v]) swap(u, v), swap(l, r);\n            l = f(l, q(id[head[v]],\
    \ id[v]+1));\n            v = par[head[v]];\n        }\n        return f(q(id[u]+edge,\
    \ id[v]+1), f(l, r));\n    }\n\n    template<typename T, typename QL, typename\
    \ QR, typename F>\n    T query_order(int u, int v, const T &e, const QL &ql, const\
    \ QR &qr, const F &f, bool edge){\n        T l = e, r = e;\n        while(head[u]\
    \ != head[v]){\n            if(id[u] > id[v]) {\n                l = f(l, qr(id[head[u]],\
    \ id[u]+1));\n                u = par[head[u]];\n            }else {\n       \
    \         r = f(ql(id[head[v]], id[v]+1), r);\n                v = par[head[v]];\n\
    \            }\n        }\n        T mid = (id[u] > id[v] ? qr(id[v]+edge, id[u]+1)\
    \ : ql(id[u]+edge, id[v]+1));\n        return f(f(l, mid), r);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/hld.cpp
  requiredBy: []
  timestamp: '2021-07-13 20:01:02+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_vertex_set_path_composite.test.cpp
documentation_of: tree/hld.cpp
layout: document
redirect_from:
- /library/tree/hld.cpp
- /library/tree/hld.cpp.html
title: tree/hld.cpp
---
