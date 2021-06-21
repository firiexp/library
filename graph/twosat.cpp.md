---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_twosat.test.cpp
    title: test/yosupo_twosat.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/twosat.cpp\"\nstruct SCC {\n    vector<vector<int>>\
    \ G, G_r, G_out;\n    vector<int> vs, used, cmp;\n    SCC() = default;\n    explicit\
    \ SCC(int n) : G(n), G_r(n), used(n), cmp(n) {}\n\n    void add_edge(int a, int\
    \ b){\n        G[a].emplace_back(b);\n        G_r[b].emplace_back(a);\n    }\n\
    \n    void dfs(int v){\n        used[v] = 1;\n        for (auto &&u : G[v]) if(!used[u])\
    \ dfs(u);\n        vs.emplace_back(v);\n    }\n\n    void dfs_r(int v, int k){\n\
    \        used[v] = 1;\n        cmp[v] = k;\n        for (auto &&u : G_r[v]) if(!used[u])\
    \ dfs_r(u, k);\n    }\n\n    int build() {\n        int n = G.size();\n      \
    \  for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(),\
    \ 0);\n        int k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n      \
    \      if(!used[vs[i]]){\n                dfs_r(vs[i], k++);\n            }\n\
    \        }\n        return k;\n    }\n\n    int operator[](int k) const { return\
    \ cmp[k]; }\n};\n\nstruct TwoSAT {\n    int n;\n    SCC scc;\n    explicit TwoSAT(int\
    \ n) : n(n), scc(n*2) {};\n    int negate(int v){\n        int ret = n+v;\n  \
    \      if(ret >= n*2) ret -= n*2;\n        return ret;\n    }\n\n    vector<int>\
    \ build() {\n        scc.build();\n        vector<int> res(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(scc[i] == scc[n+i]) return {};\n      \
    \      res[i] = scc[i] > scc[n+i];\n        }\n        return res;\n    }\n\n\
    \    void add_if(int u, int v){ // u -> v\n        scc.add_edge(u, v);\n     \
    \   scc.add_edge(negate(v), negate(u));\n    }\n\n    void add_or(int u, int v){\
    \ // u || v\n        add_if(negate(u), v);\n    }\n};\n"
  code: "struct SCC {\n    vector<vector<int>> G, G_r, G_out;\n    vector<int> vs,\
    \ used, cmp;\n    SCC() = default;\n    explicit SCC(int n) : G(n), G_r(n), used(n),\
    \ cmp(n) {}\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G_r[b].emplace_back(a);\n    }\n\n    void dfs(int v){\n        used[v]\
    \ = 1;\n        for (auto &&u : G[v]) if(!used[u]) dfs(u);\n        vs.emplace_back(v);\n\
    \    }\n\n    void dfs_r(int v, int k){\n        used[v] = 1;\n        cmp[v]\
    \ = k;\n        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);\n    }\n\n \
    \   int build() {\n        int n = G.size();\n        for (int i = 0; i < n; ++i)\
    \ if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(), 0);\n        int\
    \ k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n\
    \                dfs_r(vs[i], k++);\n            }\n        }\n        return\
    \ k;\n    }\n\n    int operator[](int k) const { return cmp[k]; }\n};\n\nstruct\
    \ TwoSAT {\n    int n;\n    SCC scc;\n    explicit TwoSAT(int n) : n(n), scc(n*2)\
    \ {};\n    int negate(int v){\n        int ret = n+v;\n        if(ret >= n*2)\
    \ ret -= n*2;\n        return ret;\n    }\n\n    vector<int> build() {\n     \
    \   scc.build();\n        vector<int> res(n);\n        for (int i = 0; i < n;\
    \ ++i) {\n            if(scc[i] == scc[n+i]) return {};\n            res[i] =\
    \ scc[i] > scc[n+i];\n        }\n        return res;\n    }\n\n    void add_if(int\
    \ u, int v){ // u -> v\n        scc.add_edge(u, v);\n        scc.add_edge(negate(v),\
    \ negate(u));\n    }\n\n    void add_or(int u, int v){ // u || v\n        add_if(negate(u),\
    \ v);\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: graph/twosat.cpp
  requiredBy: []
  timestamp: '2021-06-09 00:02:19+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_twosat.test.cpp
documentation_of: graph/twosat.cpp
layout: document
redirect_from:
- /library/graph/twosat.cpp
- /library/graph/twosat.cpp.html
title: graph/twosat.cpp
---
