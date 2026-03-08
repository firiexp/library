---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_biconnected_components.test.cpp
    title: test/yosupo_biconnected_components.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n"
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
    \            }\n        }\n        return bcc_vertices.size();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/biconnected_components.cpp
  requiredBy: []
  timestamp: '2026-03-08 01:01:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_biconnected_components.test.cpp
documentation_of: graph/biconnected_components.cpp
layout: document
redirect_from:
- /library/graph/biconnected_components.cpp
- /library/graph/biconnected_components.cpp.html
title: graph/biconnected_components.cpp
---
