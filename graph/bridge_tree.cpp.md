---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/twoedgeconnectedcomponents.cpp
    title: "\u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3(Two-Edge-Connected Components)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0377.test.cpp
    title: test/aoj0377.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0415.test.cpp
    title: test/aoj0415.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6A4B\u6728(Bridge Tree)"
    links: []
  bundledCode: "#line 1 \"graph/bridge_tree.cpp\"\nusing namespace std;\n\n#line 1\
    \ \"graph/twoedgeconnectedcomponents.cpp\"\nclass TwoEdgeConnectedComponents {\n\
    \    struct CSR {\n        vector<int> start, elist;\n\n        CSR() = default;\n\
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
    \u6210\u5206\u5206\u89E3(Two-Edge-Connected Components)\n */\n#line 4 \"graph/bridge_tree.cpp\"\
    \n\nstruct BridgeTree {\n    int n, component_count;\n    TwoEdgeConnectedComponents\
    \ tecc;\n    vector<vector<int>> tree, nodes;\n    vector<pair<int, int>> edges;\n\
    \    vector<int> id;\n\n    explicit BridgeTree(int n) : n(n), component_count(0),\
    \ tecc(n), id(n, -1) {}\n\n    void add_edge(int u, int v) {\n        tecc.add_edge(u,\
    \ v);\n    }\n\n    int build() {\n        component_count = tecc.build();\n \
    \       id = tecc.bridge;\n        nodes = tecc.out;\n        tree.assign(component_count,\
    \ {});\n        edges.clear();\n        for (int i = 0; i < (int)tecc.edges.size();\
    \ ++i) {\n            if (!tecc.is_bridge_edge(i)) continue;\n            auto\
    \ [a, b] = tecc.edges[i];\n            int u = id[a], v = id[b];\n           \
    \ tree[u].push_back(v);\n            tree[v].push_back(u);\n            edges.emplace_back(u,\
    \ v);\n        }\n        return component_count;\n    }\n};\n\n/**\n * @brief\
    \ \u6A4B\u6728(Bridge Tree)\n */\n"
  code: "using namespace std;\n\n#include \"twoedgeconnectedcomponents.cpp\"\n\nstruct\
    \ BridgeTree {\n    int n, component_count;\n    TwoEdgeConnectedComponents tecc;\n\
    \    vector<vector<int>> tree, nodes;\n    vector<pair<int, int>> edges;\n   \
    \ vector<int> id;\n\n    explicit BridgeTree(int n) : n(n), component_count(0),\
    \ tecc(n), id(n, -1) {}\n\n    void add_edge(int u, int v) {\n        tecc.add_edge(u,\
    \ v);\n    }\n\n    int build() {\n        component_count = tecc.build();\n \
    \       id = tecc.bridge;\n        nodes = tecc.out;\n        tree.assign(component_count,\
    \ {});\n        edges.clear();\n        for (int i = 0; i < (int)tecc.edges.size();\
    \ ++i) {\n            if (!tecc.is_bridge_edge(i)) continue;\n            auto\
    \ [a, b] = tecc.edges[i];\n            int u = id[a], v = id[b];\n           \
    \ tree[u].push_back(v);\n            tree[v].push_back(u);\n            edges.emplace_back(u,\
    \ v);\n        }\n        return component_count;\n    }\n};\n\n/**\n * @brief\
    \ \u6A4B\u6728(Bridge Tree)\n */\n"
  dependsOn:
  - graph/twoedgeconnectedcomponents.cpp
  isVerificationFile: false
  path: graph/bridge_tree.cpp
  requiredBy: []
  timestamp: '2026-04-11 14:49:21+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0377.test.cpp
  - test/aoj0415.test.cpp
date: 2026-03-11
documentation_of: graph/bridge_tree.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u6A4B\u6728(Bridge Tree)"
---

## 説明
無向グラフの二辺連結成分を縮約して、橋だけを辺に持つ森を作る。
連結グラフなら木、非連結グラフなら森になる。

## できること
- `BridgeTree g(n)`
  頂点数 `n` の graph builder を作る
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは内部で無視される
- `int build()`
  bridge tree を構築し、成分数を返す

## 使い方
`build()` 後は `tree`、`nodes`、`edges`、`id` を参照する。

- `tree[k]`
  bridge tree 上で成分 `k` に隣接する成分番号列
- `nodes[k]`
  成分 `k` に含まれる元グラフ頂点集合
- `edges`
  bridge tree の辺集合。各要素は成分番号の組
- `id[v]`
  元頂点 `v` が属する成分番号

`tecc` に内部の `TwoEdgeConnectedComponents` を保持しているので、必要なら `ord` や `low` も参照できる。
