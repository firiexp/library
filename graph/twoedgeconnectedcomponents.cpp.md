---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/bridge_tree.cpp
    title: "\u6A4B\u6728(Bridge Tree)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0377.test.cpp
    title: test/aoj0377.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0415.test.cpp
    title: test/aoj0415.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_two_edge_connected_components.test.cpp
    title: test/yosupo_two_edge_connected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3(Two-Edge-Connected\
      \ Components)"
    links: []
  bundledCode: "#line 1 \"graph/twoedgeconnectedcomponents.cpp\"\nclass TwoEdgeConnectedComponents\
    \ {\n    struct CSR {\n        vector<int> start, elist;\n\n        CSR() = default;\n\
    \n        CSR(int n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size()\
    \ * 2) {\n            for (auto &&[u, v] : edges) {\n                ++start[u\
    \ + 1];\n                ++start[v + 1];\n            }\n            for (int\
    \ i = 0; i < n; ++i) start[i + 1] += start[i];\n            auto counter = start;\n\
    \            for (int id = 0; id < (int)edges.size(); ++id) {\n              \
    \  auto &&[u, v] = edges[id];\n                elist[counter[u]++] = id;\n   \
    \             elist[counter[v]++] = id;\n            }\n        }\n    };\n\n\
    \    int n = 0;\n\n    int other(int id, int v) const {\n        return edges[id].first\
    \ ^ edges[id].second ^ v;\n    }\n\n    void dfs(int i, int pe, const CSR &G,\
    \ int &pos){\n        ord[i] = low[i] = pos++;\n        for (int ei = G.start[i];\
    \ ei < G.start[i + 1]; ++ei) {\n            int id = G.elist[ei];\n          \
    \  if(id == pe) continue;\n            int j = other(id, i);\n            if(~ord[j]){\n\
    \                low[i] = min(low[i], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = i;\n            dfs(j, id, G, pos);\n     \
    \       size[i] += size[j];\n            low[i] = min(low[i], low[j]);\n     \
    \   }\n    }\n\n    void dfs2(int i, int c, const CSR &G){\n        bridge[i]\
    \ = c;\n        out[c].emplace_back(i);\n        for (int ei = G.start[i]; ei\
    \ < G.start[i + 1]; ++ei) {\n            int id = G.elist[ei];\n            if(is_bridge_edge(id))\
    \ continue;\n            int j = other(id, i);\n            if(~bridge[j]) continue;\n\
    \            dfs2(j, c, G);\n        }\n    }\npublic:\n    vector<int> ord, low,\
    \ par, bridge, size;\n    vector<pair<int, int>> edges;\n    vector<vector<int>>\
    \ out;\n    explicit TwoEdgeConnectedComponents(int n): n(n), ord(n, -1), low(n),\
    \ par(n, -1), bridge(n, -1), size(n, 1){}\n\n    inline bool is_bridge(int i,\
    \ int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return ord[i] < low[j];\n\
    \    }\n\n    bool is_bridge_edge(int id) const {\n        auto [u, v] = edges[id];\n\
    \        if(ord[u] > ord[v]) swap(u, v);\n        return ord[u] < low[v];\n  \
    \  }\n\n    void add_edge(int u, int v){\n        if(u == v) return;\n       \
    \ edges.emplace_back(u, v);\n    }\n\n    int build(){\n        CSR G(n, edges);\n\
    \        int pos = 0;\n        fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(),\
    \ par.end(), -1);\n        fill(bridge.begin(), bridge.end(), -1);\n        fill(size.begin(),\
    \ size.end(), 1);\n        out.clear();\n        for (int i = 0; i < n; ++i) {\n\
    \            if(ord[i] < 0) dfs(i, -1, G, pos);\n        }\n        int k = 0;\n\
    \        for (int i = 0; i < n; ++i) {\n            if(!~bridge[i]){\n       \
    \         out.emplace_back();\n                dfs2(i, k++, G);\n            }\n\
    \        }\n        return k;\n    }\n};\n\n/**\n * @brief \u4E8C\u8FBA\u9023\u7D50\
    \u6210\u5206\u5206\u89E3(Two-Edge-Connected Components)\n */\n"
  code: "class TwoEdgeConnectedComponents {\n    struct CSR {\n        vector<int>\
    \ start, elist;\n\n        CSR() = default;\n\n        CSR(int n, const vector<pair<int,\
    \ int>> &edges) : start(n + 1), elist(edges.size() * 2) {\n            for (auto\
    \ &&[u, v] : edges) {\n                ++start[u + 1];\n                ++start[v\
    \ + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i + 1] +=\
    \ start[i];\n            auto counter = start;\n            for (int id = 0; id\
    \ < (int)edges.size(); ++id) {\n                auto &&[u, v] = edges[id];\n \
    \               elist[counter[u]++] = id;\n                elist[counter[v]++]\
    \ = id;\n            }\n        }\n    };\n\n    int n = 0;\n\n    int other(int\
    \ id, int v) const {\n        return edges[id].first ^ edges[id].second ^ v;\n\
    \    }\n\n    void dfs(int i, int pe, const CSR &G, int &pos){\n        ord[i]\
    \ = low[i] = pos++;\n        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei)\
    \ {\n            int id = G.elist[ei];\n            if(id == pe) continue;\n \
    \           int j = other(id, i);\n            if(~ord[j]){\n                low[i]\
    \ = min(low[i], ord[j]);\n                continue;\n            }\n         \
    \   par[j] = i;\n            dfs(j, id, G, pos);\n            size[i] += size[j];\n\
    \            low[i] = min(low[i], low[j]);\n        }\n    }\n\n    void dfs2(int\
    \ i, int c, const CSR &G){\n        bridge[i] = c;\n        out[c].emplace_back(i);\n\
    \        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei) {\n            int\
    \ id = G.elist[ei];\n            if(is_bridge_edge(id)) continue;\n          \
    \  int j = other(id, i);\n            if(~bridge[j]) continue;\n            dfs2(j,\
    \ c, G);\n        }\n    }\npublic:\n    vector<int> ord, low, par, bridge, size;\n\
    \    vector<pair<int, int>> edges;\n    vector<vector<int>> out;\n    explicit\
    \ TwoEdgeConnectedComponents(int n): n(n), ord(n, -1), low(n), par(n, -1), bridge(n,\
    \ -1), size(n, 1){}\n\n    inline bool is_bridge(int i, int j){\n        if(ord[i]\
    \ > ord[j]) swap(i, j);\n        return ord[i] < low[j];\n    }\n\n    bool is_bridge_edge(int\
    \ id) const {\n        auto [u, v] = edges[id];\n        if(ord[u] > ord[v]) swap(u,\
    \ v);\n        return ord[u] < low[v];\n    }\n\n    void add_edge(int u, int\
    \ v){\n        if(u == v) return;\n        edges.emplace_back(u, v);\n    }\n\n\
    \    int build(){\n        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(),\
    \ ord.end(), -1);\n        fill(par.begin(), par.end(), -1);\n        fill(bridge.begin(),\
    \ bridge.end(), -1);\n        fill(size.begin(), size.end(), 1);\n        out.clear();\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1,\
    \ G, pos);\n        }\n        int k = 0;\n        for (int i = 0; i < n; ++i)\
    \ {\n            if(!~bridge[i]){\n                out.emplace_back();\n     \
    \           dfs2(i, k++, G);\n            }\n        }\n        return k;\n  \
    \  }\n};\n\n/**\n * @brief \u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3(Two-Edge-Connected\
    \ Components)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/twoedgeconnectedcomponents.cpp
  requiredBy:
  - graph/bridge_tree.cpp
  timestamp: '2026-04-11 14:49:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_two_edge_connected_components.test.cpp
  - test/aoj0377.test.cpp
  - test/aoj0415.test.cpp
date: 2020-03-25
documentation_of: graph/twoedgeconnectedcomponents.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3(Two-Edge-Connected Components)"
---

## 説明

無向グラフを二辺連結成分分解する。
