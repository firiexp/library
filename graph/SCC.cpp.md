---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0349.test.cpp
    title: test/aoj0349.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_scc.test.cpp
    title: test/yosupo_scc.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/SCC.cpp\"\nclass SCC {\n    void dfs(int v){\n   \
    \     used[v] = 1;\n        for (auto &&u : G[v]) if(!used[u]) dfs(u);\n     \
    \   vs.emplace_back(v);\n    }\n\n    void dfs_r(int v, int k){\n        used[v]\
    \ = 1;\n        cmp[v] = k;\n        sz[k]++;\n        for (auto &&u : G_r[v])\
    \ if(!used[u]) dfs_r(u, k);\n    }\npublic:\n    vector<vector<int>> G, G_r, G_out;\n\
    \    vector<int> vs, used, cmp, sz;\n    SCC() = default;\n    explicit SCC(int\
    \ n) : G(n), G_r(n), G_out(n), used(n), cmp(n), sz(n) {}\n\n    void add_edge(int\
    \ a, int b){\n        G[a].emplace_back(b);\n        G_r[b].emplace_back(a);\n\
    \    }\n\n    int build() {\n        int n = G.size();\n        for (int i = 0;\
    \ i < n; ++i) if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(), 0);\n\
    \        int k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n\
    \                dfs_r(vs[i], k++);\n            }\n        }\n        G_out.resize(k);\n\
    \        sz.resize(k);\n        for (int i = 0; i < n; ++i) {\n            for\
    \ (auto &&j : G[i]) {\n                if(cmp[i] != cmp[j]){\n               \
    \     G_out[cmp[i]].emplace_back(cmp[j]);\n                }\n            }\n\
    \        }\n        for (auto &&l : G_out) {\n            sort(l.begin(), l.end());\n\
    \            l.erase(unique(l.begin(), l.end()), l.end());\n        }\n      \
    \  return k;\n    }\n\n    int operator[](int k) const { return cmp[k]; }\n};\n"
  code: "class SCC {\n    void dfs(int v){\n        used[v] = 1;\n        for (auto\
    \ &&u : G[v]) if(!used[u]) dfs(u);\n        vs.emplace_back(v);\n    }\n\n   \
    \ void dfs_r(int v, int k){\n        used[v] = 1;\n        cmp[v] = k;\n     \
    \   sz[k]++;\n        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);\n    }\n\
    public:\n    vector<vector<int>> G, G_r, G_out;\n    vector<int> vs, used, cmp,\
    \ sz;\n    SCC() = default;\n    explicit SCC(int n) : G(n), G_r(n), G_out(n),\
    \ used(n), cmp(n), sz(n) {}\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G_r[b].emplace_back(a);\n    }\n\n    int build() {\n        int n =\
    \ G.size();\n        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n      \
    \  fill(used.begin(),used.end(), 0);\n        int k = 0;\n        for (int i =\
    \ n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(vs[i],\
    \ k++);\n            }\n        }\n        G_out.resize(k);\n        sz.resize(k);\n\
    \        for (int i = 0; i < n; ++i) {\n            for (auto &&j : G[i]) {\n\
    \                if(cmp[i] != cmp[j]){\n                    G_out[cmp[i]].emplace_back(cmp[j]);\n\
    \                }\n            }\n        }\n        for (auto &&l : G_out) {\n\
    \            sort(l.begin(), l.end());\n            l.erase(unique(l.begin(),\
    \ l.end()), l.end());\n        }\n        return k;\n    }\n\n    int operator[](int\
    \ k) const { return cmp[k]; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/SCC.cpp
  requiredBy: []
  timestamp: '2020-06-09 14:40:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_scc.test.cpp
  - test/aoj0349.test.cpp
documentation_of: graph/SCC.cpp
layout: document
redirect_from:
- /library/graph/SCC.cpp
- /library/graph/SCC.cpp.html
title: graph/SCC.cpp
---
