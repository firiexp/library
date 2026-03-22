---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: graph/twoedgeconnectedcomponents.cpp
    title: "\u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj0377.test.cpp
    title: test/aoj0377.test.cpp
  - icon: ':x:'
    path: test/aoj0415.test.cpp
    title: test/aoj0415.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u6A4B\u6728(Bridge Tree)"
    links: []
  bundledCode: "#line 1 \"graph/bridge_tree.cpp\"\nusing namespace std;\n\n#line 1\
    \ \"graph/twoedgeconnectedcomponents.cpp\"\nclass TwoEdgeConnectedComponents {\n\
    \    void dfs(int i, int &pos){\n        ord[i] = low[i] = pos++;\n        int\
    \ mul = 0;\n        for (auto &&j : G[i]) {\n            if(j == par[i] && !mul){\n\
    \                mul = 1;\n                continue;\n            }\n        \
    \    if(~ord[j]){\n                low[i] = min(low[i], ord[j]);\n           \
    \     continue;\n            }\n            par[j] = i;\n            dfs(j, pos);\n\
    \            size[i] += size[j];\n            low[i] = min(low[i], low[j]);\n\
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
    \           dfs2(i);\n            }\n        }\n        return k;\n    }\n};\n\
    \n/**\n * @brief \u4E8C\u8FBA\u9023\u7D50\u6210\u5206\u5206\u89E3(Two-Edge-Connected\
    \ Components)\n */\n#line 4 \"graph/bridge_tree.cpp\"\n\nstruct BridgeTree {\n\
    \    int n, component_count;\n    TwoEdgeConnectedComponents tecc;\n    vector<vector<int>>\
    \ tree, nodes;\n    vector<pair<int, int>> edges;\n    vector<int> id;\n\n   \
    \ explicit BridgeTree(int n) : n(n), component_count(0), tecc(n), id(n, -1) {}\n\
    \n    void add_edge(int u, int v) {\n        tecc.add_edge(u, v);\n    }\n\n \
    \   int build() {\n        component_count = tecc.build();\n        id = tecc.bridge;\n\
    \        nodes = tecc.out;\n        tree.assign(component_count, {});\n      \
    \  edges.clear();\n        for (int i = 0; i < n; ++i) {\n            for (auto\
    \ &&j : tecc.G[i]) {\n                if (i < j && tecc.is_bridge(i, j)) {\n \
    \                   int u = id[i], v = id[j];\n                    tree[u].push_back(v);\n\
    \                    tree[v].push_back(u);\n                    edges.emplace_back(u,\
    \ v);\n                }\n            }\n        }\n        return component_count;\n\
    \    }\n};\n\n/**\n * @brief \u6A4B\u6728(Bridge Tree)\n */\n"
  code: "using namespace std;\n\n#include \"twoedgeconnectedcomponents.cpp\"\n\nstruct\
    \ BridgeTree {\n    int n, component_count;\n    TwoEdgeConnectedComponents tecc;\n\
    \    vector<vector<int>> tree, nodes;\n    vector<pair<int, int>> edges;\n   \
    \ vector<int> id;\n\n    explicit BridgeTree(int n) : n(n), component_count(0),\
    \ tecc(n), id(n, -1) {}\n\n    void add_edge(int u, int v) {\n        tecc.add_edge(u,\
    \ v);\n    }\n\n    int build() {\n        component_count = tecc.build();\n \
    \       id = tecc.bridge;\n        nodes = tecc.out;\n        tree.assign(component_count,\
    \ {});\n        edges.clear();\n        for (int i = 0; i < n; ++i) {\n      \
    \      for (auto &&j : tecc.G[i]) {\n                if (i < j && tecc.is_bridge(i,\
    \ j)) {\n                    int u = id[i], v = id[j];\n                    tree[u].push_back(v);\n\
    \                    tree[v].push_back(u);\n                    edges.emplace_back(u,\
    \ v);\n                }\n            }\n        }\n        return component_count;\n\
    \    }\n};\n\n/**\n * @brief \u6A4B\u6728(Bridge Tree)\n */\n"
  dependsOn:
  - graph/twoedgeconnectedcomponents.cpp
  isVerificationFile: false
  path: graph/bridge_tree.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj0415.test.cpp
  - test/aoj0377.test.cpp
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
