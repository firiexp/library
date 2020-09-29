---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0415.test.cpp
    title: test/aoj0415.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/twoedgeconnectedcomponents.cpp\"\nclass TwoEdgeConnectedComponents\
    \ {\n    void dfs(int i, int &pos){\n        ord[i] = low[i] = pos++;\n      \
    \  int mul = 0;\n        for (auto &&j : G[i]) {\n            if(j == par[i] &&\
    \ !mul){\n                mul = 1;\n                continue;\n            }\n\
    \            if(~ord[j]){\n                low[i] = min(low[i], ord[j]);\n   \
    \             continue;\n            }\n            par[j] = i;\n            dfs(j,\
    \ pos);\n            size[i] += size[j];\n            low[i] = min(low[i], low[j]);\n\
    \        }\n    }\n\n    void dfs2(int i){\n        out[bridge[i]].emplace_back(i);\n\
    \        for (auto &&j : G[i]) {\n            if(~bridge[j] || is_bridge(i, j))\
    \ continue;\n            bridge[j] = bridge[i];\n            dfs2(j);\n      \
    \  }\n    }\npublic:\n    vector<int> ord, low, par, bridge, size;\n    vector<vector<int>>\
    \ G, out;\n    explicit TwoEdgeConnectedComponents(int n): ord(n, -1), low(n),\
    \ par(n, -1), bridge(n, -1), size(n, 1), G(n){}\n\n    inline bool is_bridge(int\
    \ i, int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return ord[i] <\
    \ low[j];\n    }\n\n    void add_edge(int u, int v){\n        if(u != v){\n  \
    \          G[u].emplace_back(v);\n            G[v].emplace_back(u);\n        }\n\
    \    }\n\n    int build(){\n        int n = G.size(), pos = 0;\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, pos);\n        }\n \
    \       int k = 0;\n        for (int i = 0; i < n; ++i) {\n            if(!~bridge[i]){\n\
    \                bridge[i] = k++;\n                out.emplace_back();\n     \
    \           dfs2(i);\n            }\n        }\n        return k;\n    }\n};\n"
  code: "class TwoEdgeConnectedComponents {\n    void dfs(int i, int &pos){\n    \
    \    ord[i] = low[i] = pos++;\n        int mul = 0;\n        for (auto &&j : G[i])\
    \ {\n            if(j == par[i] && !mul){\n                mul = 1;\n        \
    \        continue;\n            }\n            if(~ord[j]){\n                low[i]\
    \ = min(low[i], ord[j]);\n                continue;\n            }\n         \
    \   par[j] = i;\n            dfs(j, pos);\n            size[i] += size[j];\n \
    \           low[i] = min(low[i], low[j]);\n        }\n    }\n\n    void dfs2(int\
    \ i){\n        out[bridge[i]].emplace_back(i);\n        for (auto &&j : G[i])\
    \ {\n            if(~bridge[j] || is_bridge(i, j)) continue;\n            bridge[j]\
    \ = bridge[i];\n            dfs2(j);\n        }\n    }\npublic:\n    vector<int>\
    \ ord, low, par, bridge, size;\n    vector<vector<int>> G, out;\n    explicit\
    \ TwoEdgeConnectedComponents(int n): ord(n, -1), low(n), par(n, -1), bridge(n,\
    \ -1), size(n, 1), G(n){}\n\n    inline bool is_bridge(int i, int j){\n      \
    \  if(ord[i] > ord[j]) swap(i, j);\n        return ord[i] < low[j];\n    }\n\n\
    \    void add_edge(int u, int v){\n        if(u != v){\n            G[u].emplace_back(v);\n\
    \            G[v].emplace_back(u);\n        }\n    }\n\n    int build(){\n   \
    \     int n = G.size(), pos = 0;\n        for (int i = 0; i < n; ++i) {\n    \
    \        if(ord[i] < 0) dfs(i, pos);\n        }\n        int k = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if(!~bridge[i]){\n                bridge[i]\
    \ = k++;\n                out.emplace_back();\n                dfs2(i);\n    \
    \        }\n        }\n        return k;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/twoedgeconnectedcomponents.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0415.test.cpp
documentation_of: graph/twoedgeconnectedcomponents.cpp
layout: document
redirect_from:
- /library/graph/twoedgeconnectedcomponents.cpp
- /library/graph/twoedgeconnectedcomponents.cpp.html
title: graph/twoedgeconnectedcomponents.cpp
---
