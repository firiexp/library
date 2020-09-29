---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/LCA.cpp\"\n template <class F>\nstruct SparseTable\
    \ {\n    using T = typename F::T;\n    vector<vector<T>> table;\n    vector<int>\
    \ u;\n    SparseTable() = default;\n    explicit SparseTable(const vector<T> &v){\
    \ build(v); }\n \n    void build(const vector<T> &v){\n        int n = v.size(),\
    \ m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m, vector<T>(n));\n\
    \        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i) {\n         \
    \   u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n; ++i) {\n  \
    \          table[0][i] = v[i];\n        }\n        for (int i = 1; i < m; ++i)\
    \ {\n            int x = (1<<(i-1));\n            for (int j = 0; j < n; ++j)\
    \ {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x, n-1)]);\n\
    \            }\n        }\n    }\n \n    T query(int a, int b){\n        int l\
    \ = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n   \
    \ }\n};\n \n \nstruct F {\n    using T = pair<int, int>;\n    static T f(T a,\
    \ T b) { return min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\
    \ \nclass Graph {\n    SparseTable<F> table;\n    void dfs_euler(int v, int p,\
    \ int d, int &k){\n        id[v] = k;\n        vs[k] = v;\n        depth[k++]\
    \ = d;\n        for (auto &&u : G[v]) {\n            if(u != p){\n           \
    \     dfs_euler(u, v, d+1, k);\n                vs[k] = v;\n                depth[k++]\
    \ = d;\n            }\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G;\n    vector<int> vs, depth, id;\n    explicit Graph(int n) : n(n), G(n),\
    \ vs(2*n-1), depth(2*n-1), id(n), table() {};\n    void add_edge(int a, int b){\n\
    \        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n    }\n \n    void\
    \ eulertour(int root) {\n        int k = 0;\n        dfs_euler(root, -1, 0, k);\n\
    \    }\n \n    void buildLCA(){\n        eulertour(0);\n        vector<pair<int,\
    \ int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1; ++i) {\n            v[i]\
    \ = make_pair(depth[i], i);\n        }\n        table.build(v);\n    }\n \n  \
    \  int LCA(int u, int v){\n        if(id[u] > id[v]) swap(u, v);\n        return\
    \ table.query(id[u], id[v]+1).second;\n    }\n};\n"
  code: " template <class F>\nstruct SparseTable {\n    using T = typename F::T;\n\
    \    vector<vector<T>> table;\n    vector<int> u;\n    SparseTable() = default;\n\
    \    explicit SparseTable(const vector<T> &v){ build(v); }\n \n    void build(const\
    \ vector<T> &v){\n        int n = v.size(), m = 1;\n        while((1<<m) <= n)\
    \ m++;\n        table.assign(m, vector<T>(n));\n        u.assign(n+1, 0);\n  \
    \      for (int i = 2; i <= n; ++i) {\n            u[i] = u[i>>1] + 1;\n     \
    \   }\n        for (int i = 0; i < n; ++i) {\n            table[0][i] = v[i];\n\
    \        }\n        for (int i = 1; i < m; ++i) {\n            int x = (1<<(i-1));\n\
    \            for (int j = 0; j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j],\
    \ table[i-1][min(j+x, n-1)]);\n            }\n        }\n    }\n \n    T query(int\
    \ a, int b){\n        int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n \n \nstruct F {\n    using T = pair<int, int>;\n    static T f(T\
    \ a, T b) { return min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n\
    };\n \nclass Graph {\n    SparseTable<F> table;\n    void dfs_euler(int v, int\
    \ p, int d, int &k){\n        id[v] = k;\n        vs[k] = v;\n        depth[k++]\
    \ = d;\n        for (auto &&u : G[v]) {\n            if(u != p){\n           \
    \     dfs_euler(u, v, d+1, k);\n                vs[k] = v;\n                depth[k++]\
    \ = d;\n            }\n        }\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G;\n    vector<int> vs, depth, id;\n    explicit Graph(int n) : n(n), G(n),\
    \ vs(2*n-1), depth(2*n-1), id(n), table() {};\n    void add_edge(int a, int b){\n\
    \        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n    }\n \n    void\
    \ eulertour(int root) {\n        int k = 0;\n        dfs_euler(root, -1, 0, k);\n\
    \    }\n \n    void buildLCA(){\n        eulertour(0);\n        vector<pair<int,\
    \ int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1; ++i) {\n            v[i]\
    \ = make_pair(depth[i], i);\n        }\n        table.build(v);\n    }\n \n  \
    \  int LCA(int u, int v){\n        if(id[u] > id[v]) swap(u, v);\n        return\
    \ table.query(id[u], id[v]+1).second;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: tree/LCA.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/LCA.cpp
layout: document
redirect_from:
- /library/tree/LCA.cpp
- /library/tree/LCA.cpp.html
title: tree/LCA.cpp
---
