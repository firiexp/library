---
category: "\u30B0\u30E9\u30D5"
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
    document_title: LowLink
    links: []
  bundledCode: "#line 1 \"graph/lowlink.cpp\"\nclass LowLink {\n    struct CSR {\n\
    \        vector<int> start, elist;\n\n        CSR() = default;\n\n        CSR(int\
    \ n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size() *\
    \ 2) {\n            for (auto &&[u, v] : edges) {\n                ++start[u +\
    \ 1];\n                ++start[v + 1];\n            }\n            for (int i\
    \ = 0; i < n; ++i) start[i + 1] += start[i];\n            auto counter = start;\n\
    \            for (int id = 0; id < (int)edges.size(); ++id) {\n              \
    \  auto &&[u, v] = edges[id];\n                elist[counter[u]++] = id;\n   \
    \             elist[counter[v]++] = id;\n            }\n        }\n    };\n\n\
    \    int n = 0;\n    int other(int id, int v) const {\n        return edges[id].first\
    \ ^ edges[id].second ^ v;\n    }\n\n    void dfs(int i, int pe, const CSR &G,\
    \ int &pos){\n        ord[i] = low[i] = pos++;\n        int ch = 0;\n        bool\
    \ is_art = false;\n        for (int ei = G.start[i]; ei < G.start[i + 1]; ++ei)\
    \ {\n            int id = G.elist[ei];\n            if(id == pe) continue;\n \
    \           int j = other(id, i);\n            if(~ord[j]){\n                low[i]\
    \ = min(low[i], ord[j]);\n                continue;\n            }\n         \
    \   par[j] = i;\n            ch++;\n            dfs(j, id, G, pos);\n        \
    \    low[i] = min(low[i], low[j]);\n            if(pe != -1 && ord[i] <= low[j])\
    \ is_art = true;\n            if(ord[i] < low[j]) bridge.emplace_back(min(i, j),\
    \ max(i, j));\n        }\n        if(pe == -1 && ch > 1) is_art = true;\n    \
    \    cut[i] = is_art;\n    }\npublic:\n    vector<int> ord, low, par, articulation;\n\
    \    vector<pair<int, int>> bridge;\n    vector<pair<int, int>> edges;\n    vector<char>\
    \ cut;\n    LowLink() = default;\n    explicit LowLink(int n): n(n), ord(n, -1),\
    \ low(n), par(n, -1), cut(n){}\n\n    void add_edge(int u, int v){\n        if(u\
    \ == v) return;\n        edges.emplace_back(u, v);\n    }\n\n    void build(){\n\
    \        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(), ord.end(),\
    \ -1);\n        fill(par.begin(), par.end(), -1);\n        fill(cut.begin(), cut.end(),\
    \ 0);\n        articulation.clear();\n        bridge.clear();\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(!~ord[i]) dfs(i, -1, G, pos);\n       \
    \ }\n        for (int i = 0; i < n; ++i) {\n            if(cut[i]) articulation.emplace_back(i);\n\
    \        }\n        sort(bridge.begin(), bridge.end());\n    }\n\n    inline bool\
    \ is_bridge(int i, int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return\
    \ ord[i] < low[j];\n    }\n};\n\n/**\n * @brief LowLink\n */\n"
  code: "class LowLink {\n    struct CSR {\n        vector<int> start, elist;\n\n\
    \        CSR() = default;\n\n        CSR(int n, const vector<pair<int, int>> &edges)\
    \ : start(n + 1), elist(edges.size() * 2) {\n            for (auto &&[u, v] :\
    \ edges) {\n                ++start[u + 1];\n                ++start[v + 1];\n\
    \            }\n            for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n\
    \            auto counter = start;\n            for (int id = 0; id < (int)edges.size();\
    \ ++id) {\n                auto &&[u, v] = edges[id];\n                elist[counter[u]++]\
    \ = id;\n                elist[counter[v]++] = id;\n            }\n        }\n\
    \    };\n\n    int n = 0;\n    int other(int id, int v) const {\n        return\
    \ edges[id].first ^ edges[id].second ^ v;\n    }\n\n    void dfs(int i, int pe,\
    \ const CSR &G, int &pos){\n        ord[i] = low[i] = pos++;\n        int ch =\
    \ 0;\n        bool is_art = false;\n        for (int ei = G.start[i]; ei < G.start[i\
    \ + 1]; ++ei) {\n            int id = G.elist[ei];\n            if(id == pe) continue;\n\
    \            int j = other(id, i);\n            if(~ord[j]){\n               \
    \ low[i] = min(low[i], ord[j]);\n                continue;\n            }\n  \
    \          par[j] = i;\n            ch++;\n            dfs(j, id, G, pos);\n \
    \           low[i] = min(low[i], low[j]);\n            if(pe != -1 && ord[i] <=\
    \ low[j]) is_art = true;\n            if(ord[i] < low[j]) bridge.emplace_back(min(i,\
    \ j), max(i, j));\n        }\n        if(pe == -1 && ch > 1) is_art = true;\n\
    \        cut[i] = is_art;\n    }\npublic:\n    vector<int> ord, low, par, articulation;\n\
    \    vector<pair<int, int>> bridge;\n    vector<pair<int, int>> edges;\n    vector<char>\
    \ cut;\n    LowLink() = default;\n    explicit LowLink(int n): n(n), ord(n, -1),\
    \ low(n), par(n, -1), cut(n){}\n\n    void add_edge(int u, int v){\n        if(u\
    \ == v) return;\n        edges.emplace_back(u, v);\n    }\n\n    void build(){\n\
    \        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(), ord.end(),\
    \ -1);\n        fill(par.begin(), par.end(), -1);\n        fill(cut.begin(), cut.end(),\
    \ 0);\n        articulation.clear();\n        bridge.clear();\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(!~ord[i]) dfs(i, -1, G, pos);\n       \
    \ }\n        for (int i = 0; i < n; ++i) {\n            if(cut[i]) articulation.emplace_back(i);\n\
    \        }\n        sort(bridge.begin(), bridge.end());\n    }\n\n    inline bool\
    \ is_bridge(int i, int j){\n        if(ord[i] > ord[j]) swap(i, j);\n        return\
    \ ord[i] < low[j];\n    }\n};\n\n/**\n * @brief LowLink\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/lowlink.cpp
  requiredBy: []
  timestamp: '2026-04-11 14:49:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_3_b.test.cpp
date: 2026-03-07
documentation_of: graph/lowlink.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: LowLink
---

## 説明

無向グラフの LowLink。
DFS 木の順序 `ord` と到達可能な最小順序 `low` を用いて、次を列挙する。

- 関節点 (articulation points)
- 橋 (bridges)

連結でないグラフにも対応する。

## 計算量

- `build()` : $O(V + E)$

## 使い方

1. `LowLink g(n);`
2. `add_edge(u, v)` で無向辺を追加
3. `build()` を呼ぶ
4. 結果を `articulation`, `bridge` などから参照

## 公開メンバ

- `vector<int> ord` : DFS 訪問順（未訪問は `-1`）
- `vector<int> low` : `lowlink` 値
- `vector<int> par` : DFS 木での親（根は `-1`）
- `vector<int> articulation` : 関節点の頂点番号一覧
- `vector<pair<int, int>> bridge` : 橋の一覧（`(min(u,v), max(u,v))` 形式、昇順ソート済み）

## 補足

- 多重辺を考慮している。
- 自己ループは `add_edge` で無視する実装。
- `is_bridge(i, j)` は `build()` 後に使用する。
