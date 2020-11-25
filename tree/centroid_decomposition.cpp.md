---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0452.test.cpp
    title: test/aoj0452.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/centroid_decomposition.cpp\"\nclass CentroidDecomposition\
    \ {\n    int dfs(int x, int par){\n        sz[x] = 1;\n        for (auto &&i :\
    \ G[x]) {\n            if(i == par || v[i]) continue;\n            sz[x] += dfs(i,\
    \ x);\n        }\n        return sz[x];\n    }\n\n    int search_centroid(int\
    \ x, int p, const int mid){\n        for (auto &&i : G[x]) {\n            if(i\
    \ == p || v[i]) continue;\n            if(sz[i] > mid) return search_centroid(i,\
    \ x, mid);\n        }\n        return x;\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G, out;\n    vector<int> sz, v;\n    CentroidDecomposition(int n) : n(n), G(n),\
    \ out(n), sz(n), v(n) {}\n    void add_edge(int l, int r){\n        G[l].emplace_back(r);\n\
    \        G[r].emplace_back(l);\n    }\n    int get(int x){\n        int centroid\
    \ = search_centroid(x, -1, dfs(x, -1)/2);\n        v[centroid] = true;\n     \
    \   for (auto &&i : G[centroid]) {\n            if(!v[i]) out[centroid].emplace_back(get(i));\n\
    \        }\n        v[centroid] = false;\n        return centroid;\n    }\n};\n"
  code: "class CentroidDecomposition {\n    int dfs(int x, int par){\n        sz[x]\
    \ = 1;\n        for (auto &&i : G[x]) {\n            if(i == par || v[i]) continue;\n\
    \            sz[x] += dfs(i, x);\n        }\n        return sz[x];\n    }\n\n\
    \    int search_centroid(int x, int p, const int mid){\n        for (auto &&i\
    \ : G[x]) {\n            if(i == p || v[i]) continue;\n            if(sz[i] >\
    \ mid) return search_centroid(i, x, mid);\n        }\n        return x;\n    }\n\
    public:\n    int n;\n    vector<vector<int>> G, out;\n    vector<int> sz, v;\n\
    \    CentroidDecomposition(int n) : n(n), G(n), out(n), sz(n), v(n) {}\n    void\
    \ add_edge(int l, int r){\n        G[l].emplace_back(r);\n        G[r].emplace_back(l);\n\
    \    }\n    int get(int x){\n        int centroid = search_centroid(x, -1, dfs(x,\
    \ -1)/2);\n        v[centroid] = true;\n        for (auto &&i : G[centroid]) {\n\
    \            if(!v[i]) out[centroid].emplace_back(get(i));\n        }\n      \
    \  v[centroid] = false;\n        return centroid;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: tree/centroid_decomposition.cpp
  requiredBy: []
  timestamp: '2020-11-25 11:16:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0452.test.cpp
documentation_of: tree/centroid_decomposition.cpp
layout: document
redirect_from:
- /library/tree/centroid_decomposition.cpp
- /library/tree/centroid_decomposition.cpp.html
title: tree/centroid_decomposition.cpp
---
