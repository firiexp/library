---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_3_b.test.cpp
    title: test/aoj_grl_3_b.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/lowlink.cpp\"\nclass LowLink {\n    void dfs(int i,\
    \ int p, int &pos){\n        ord[i] = low[i] = pos++;\n        int ch = 0, mul\
    \ = 0;\n        bool is_art = false;\n        for (auto &&j : G[i]) {\n      \
    \      if(j == p && !mul){\n                mul = 1;\n                continue;\n\
    \            }\n            if(~ord[j]){\n                low[i] = min(low[i],\
    \ ord[j]);\n                continue;\n            }\n            par[j] = i;\n\
    \            ch++;\n            dfs(j, i, pos);\n            low[i] = min(low[i],\
    \ low[j]);\n            if(p != -1 && ord[i] <= low[j]) is_art = true;\n     \
    \       if(ord[i] < low[j]) bridge.emplace_back(min(i, j), max(i, j));\n     \
    \   }\n        if(p == -1 && ch > 1) is_art = true;\n        cut[i] = is_art;\n\
    \    }\npublic:\n    vector<int> ord, low, par, articulation;\n    vector<pair<int,\
    \ int>> bridge;\n    vector<char> cut;\n    vector<vector<int>> G;\n    LowLink()\
    \ = default;\n    explicit LowLink(int n): ord(n, -1), low(n), par(n, -1), cut(n),\
    \ G(n){}\n\n    void add_edge(int u, int v){\n        if(u != v){\n          \
    \  G[u].emplace_back(v);\n            G[v].emplace_back(u);\n        }\n    }\n\
    \n    void build(){\n        int n = G.size(), pos = 0;\n        fill(ord.begin(),\
    \ ord.end(), -1);\n        fill(par.begin(), par.end(), -1);\n        fill(cut.begin(),\
    \ cut.end(), 0);\n        articulation.clear();\n        bridge.clear();\n   \
    \     for (int i = 0; i < n; ++i) {\n            if(!~ord[i]) dfs(i, -1, pos);\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(cut[i]) articulation.emplace_back(i);\n\
    \        }\n        sort(bridge.begin(), bridge.end());\n    }\n\n    inline bool\
    \ is_bridge(int i, int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return\
    \ ord[i] < low[j];\n    }\n};\n"
  code: "class LowLink {\n    void dfs(int i, int p, int &pos){\n        ord[i] =\
    \ low[i] = pos++;\n        int ch = 0, mul = 0;\n        bool is_art = false;\n\
    \        for (auto &&j : G[i]) {\n            if(j == p && !mul){\n          \
    \      mul = 1;\n                continue;\n            }\n            if(~ord[j]){\n\
    \                low[i] = min(low[i], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = i;\n            ch++;\n            dfs(j, i,\
    \ pos);\n            low[i] = min(low[i], low[j]);\n            if(p != -1 &&\
    \ ord[i] <= low[j]) is_art = true;\n            if(ord[i] < low[j]) bridge.emplace_back(min(i,\
    \ j), max(i, j));\n        }\n        if(p == -1 && ch > 1) is_art = true;\n \
    \       cut[i] = is_art;\n    }\npublic:\n    vector<int> ord, low, par, articulation;\n\
    \    vector<pair<int, int>> bridge;\n    vector<char> cut;\n    vector<vector<int>>\
    \ G;\n    LowLink() = default;\n    explicit LowLink(int n): ord(n, -1), low(n),\
    \ par(n, -1), cut(n), G(n){}\n\n    void add_edge(int u, int v){\n        if(u\
    \ != v){\n            G[u].emplace_back(v);\n            G[v].emplace_back(u);\n\
    \        }\n    }\n\n    void build(){\n        int n = G.size(), pos = 0;\n \
    \       fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(), par.end(),\
    \ -1);\n        fill(cut.begin(), cut.end(), 0);\n        articulation.clear();\n\
    \        bridge.clear();\n        for (int i = 0; i < n; ++i) {\n            if(!~ord[i])\
    \ dfs(i, -1, pos);\n        }\n        for (int i = 0; i < n; ++i) {\n       \
    \     if(cut[i]) articulation.emplace_back(i);\n        }\n        sort(bridge.begin(),\
    \ bridge.end());\n    }\n\n    inline bool is_bridge(int i, int j){\n        if(ord[i]\
    \ > ord[j]) swap(i, j);\n        return ord[i] < low[j];\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/lowlink.cpp
  requiredBy: []
  timestamp: '2026-03-07 18:50:01+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_3_b.test.cpp
documentation_of: graph/lowlink.cpp
layout: document
redirect_from:
- /library/graph/lowlink.cpp
- /library/graph/lowlink.cpp.html
title: graph/lowlink.cpp
---
