---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/block_cut_tree.cpp
    title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_biconnected_components.test.cpp
    title: test/yosupo_biconnected_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki1326_block_cut_tree.test.cpp
    title: test/yuki1326_block_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected\
      \ Components)"
    links: []
  bundledCode: "#line 1 \"graph/biconnected_components.cpp\"\nclass BiconnectedComponents\
    \ {\n    vector<int> st;\n    void dfs(int i, int pe, int &pos){\n        ord[i]\
    \ = low[i] = pos++;\n        for (auto &&e : G[i]) {\n            int j = e.first,\
    \ id = e.second;\n            if(id == pe) continue;\n            if(ord[j] <\
    \ ord[i]) st.emplace_back(id);\n            if(~ord[j]){\n                low[i]\
    \ = min(low[i], ord[j]);\n                continue;\n            }\n         \
    \   par[j] = i;\n            dfs(j, id, pos);\n            low[i] = min(low[i],\
    \ low[j]);\n            if(ord[i] <= low[j]){\n                bcc_edges.emplace_back();\n\
    \                while(true){\n                    int k = st.back();\n      \
    \              st.pop_back();\n                    bcc_edges.back().emplace_back(min(edges[k].first,\
    \ edges[k].second), max(edges[k].first, edges[k].second));\n                 \
    \   if(k == id) break;\n                }\n            }\n        }\n    }\npublic:\n\
    \    vector<int> ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> G;\n    vector<vector<pair<int, int>>> bcc_edges;\n    vector<vector<int>>\
    \ bcc_vertices;\n    explicit BiconnectedComponents(int n): ord(n, -1), low(n),\
    \ par(n, -1), G(n){}\n\n    void add_edge(int u, int v){\n        if(u != v){\n\
    \            int id = edges.size();\n            edges.emplace_back(u, v);\n \
    \           G[u].emplace_back(v, id);\n            G[v].emplace_back(u, id);\n\
    \        }\n    }\n\n    int build(){\n        int n = G.size(), pos = 0;\n  \
    \      fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(), par.end(),\
    \ -1);\n        bcc_edges.clear();\n        bcc_vertices.clear();\n        st.clear();\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1,\
    \ pos);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(now);\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G[i].empty()){\n\
    \                bcc_edges.emplace_back();\n                bcc_vertices.push_back({i});\n\
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n\n\
    /**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)\n\
    \ */\n"
  code: "class BiconnectedComponents {\n    vector<int> st;\n    void dfs(int i, int\
    \ pe, int &pos){\n        ord[i] = low[i] = pos++;\n        for (auto &&e : G[i])\
    \ {\n            int j = e.first, id = e.second;\n            if(id == pe) continue;\n\
    \            if(ord[j] < ord[i]) st.emplace_back(id);\n            if(~ord[j]){\n\
    \                low[i] = min(low[i], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = i;\n            dfs(j, id, pos);\n        \
    \    low[i] = min(low[i], low[j]);\n            if(ord[i] <= low[j]){\n      \
    \          bcc_edges.emplace_back();\n                while(true){\n         \
    \           int k = st.back();\n                    st.pop_back();\n         \
    \           bcc_edges.back().emplace_back(min(edges[k].first, edges[k].second),\
    \ max(edges[k].first, edges[k].second));\n                    if(k == id) break;\n\
    \                }\n            }\n        }\n    }\npublic:\n    vector<int>\
    \ ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> G;\n    vector<vector<pair<int, int>>> bcc_edges;\n    vector<vector<int>>\
    \ bcc_vertices;\n    explicit BiconnectedComponents(int n): ord(n, -1), low(n),\
    \ par(n, -1), G(n){}\n\n    void add_edge(int u, int v){\n        if(u != v){\n\
    \            int id = edges.size();\n            edges.emplace_back(u, v);\n \
    \           G[u].emplace_back(v, id);\n            G[v].emplace_back(u, id);\n\
    \        }\n    }\n\n    int build(){\n        int n = G.size(), pos = 0;\n  \
    \      fill(ord.begin(), ord.end(), -1);\n        fill(par.begin(), par.end(),\
    \ -1);\n        bcc_edges.clear();\n        bcc_vertices.clear();\n        st.clear();\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, -1,\
    \ pos);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(now);\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G[i].empty()){\n\
    \                bcc_edges.emplace_back();\n                bcc_vertices.push_back({i});\n\
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n\n\
    /**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/biconnected_components.cpp
  requiredBy:
  - graph/block_cut_tree.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yuki1326_block_cut_tree.test.cpp
  - test/yosupo_biconnected_components.test.cpp
date: 2026-03-08
documentation_of: graph/biconnected_components.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u5206\u89E3"
---

## 概要

無向グラフを二重頂点連結成分 (biconnected components) に分解する。
`build()` 後に、各成分の辺集合 `bcc_edges` と頂点集合 `bcc_vertices` を参照できる。

- `bcc_edges[i]` : `i` 番目の二重頂点連結成分に含まれる辺の一覧。各辺は `(min(u, v), max(u, v))` の形で入る。
- `bcc_vertices[i]` : `bcc_edges[i]` に含まれる辺の端点として現れる頂点を重複なく集めたもの。

特に、孤立頂点については対応する成分の `bcc_edges[i]` は空で、`bcc_vertices[i] = {v}` となる。

## 計算量

- `build()` : $O(V + E)$

## 使い方

1. `BiconnectedComponents g(n);`
2. `add_edge(u, v)` で無向辺を追加
3. `build()` を呼ぶ
4. 結果を `bcc_vertices` / `bcc_edges` から参照

## 実装上の補足

- 多重辺を考慮している。
- 自己ループは `add_edge` で無視する。
- 孤立頂点は 1 頂点のみの成分として `bcc_vertices` に含める。
