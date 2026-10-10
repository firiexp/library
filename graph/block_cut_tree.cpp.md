---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/biconnected_components.cpp
    title: "\u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3(Biconnected Components)"
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/vertex_failure_connectivity.cpp
    title: "\u9802\u70B9\u9664\u53BB\u5F8C\u306E\u9023\u7D50\u5224\u5B9A"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition.test.cpp
    title: test/yosupo_aplusb_library_composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition_reverse.test.cpp
    title: test/yosupo_aplusb_library_composition_reverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
    title: test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki1326_block_cut_tree.test.cpp
    title: test/yuki1326_block_cut_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
    links: []
  bundledCode: "#line 1 \"graph/block_cut_tree.cpp\"\nusing namespace std;\n\n#line\
    \ 1 \"graph/biconnected_components.cpp\"\n\n\n\nclass BiconnectedComponents {\n\
    \    struct CSR {\n        vector<int> start, elist;\n\n        CSR() = default;\n\
    \n        CSR(int n, const vector<pair<int, int>> &edges) : start(n + 1), elist(edges.size()\
    \ * 2) {\n            for (auto &&[u, v] : edges) {\n                ++start[u\
    \ + 1];\n                ++start[v + 1];\n            }\n            for (int\
    \ i = 0; i < n; ++i) start[i + 1] += start[i];\n            auto counter = start;\n\
    \            for (int id = 0; id < (int)edges.size(); ++id) {\n              \
    \  auto &&[u, v] = edges[id];\n                elist[counter[u]++] = id;\n   \
    \             elist[counter[v]++] = id;\n            }\n        }\n    };\n\n\
    \    int n = 0;\n    vector<int> st;\n\n    struct Frame {\n        int v, parent_edge,\
    \ next;\n    };\n\n    int other(int id, int v) const {\n        return edges[id].first\
    \ ^ edges[id].second ^ v;\n    }\n\n    void dfs(int i, const CSR &G, int &pos,\
    \ vector<Frame> &stack){\n        ord[i] = low[i] = pos++;\n        stack.push_back({i,\
    \ -1, G.start[i]});\n        while (!stack.empty()) {\n            auto &frame\
    \ = stack.back();\n            int v = frame.v;\n            if (frame.next ==\
    \ G.start[v + 1]) {\n                int pe = frame.parent_edge, p = par[v];\n\
    \                stack.pop_back();\n                if (p == -1) continue;\n \
    \               low[p] = min(low[p], low[v]);\n                if (ord[p] <= low[v])\
    \ {\n                    bcc_edges.emplace_back();\n                    while\
    \ (true) {\n                        int k = st.back();\n                     \
    \   st.pop_back();\n                        bcc_edges.back().emplace_back(min(edges[k].first,\
    \ edges[k].second), max(edges[k].first, edges[k].second));\n                 \
    \       if (k == pe) break;\n                    }\n                }\n      \
    \          continue;\n            }\n            int id = G.elist[frame.next++];\n\
    \            if (id == frame.parent_edge) continue;\n            int j = other(id,\
    \ v);\n            if(ord[j] < ord[v]) st.emplace_back(id);\n            if(~ord[j]){\n\
    \                low[v] = min(low[v], ord[j]);\n                continue;\n  \
    \          }\n            par[j] = v;\n            ord[j] = low[j] = pos++;\n\
    \            stack.push_back({j, id, G.start[j]});\n        }\n    }\npublic:\n\
    \    vector<int> ord, low, par;\n    vector<pair<int, int>> edges;\n    vector<vector<pair<int,\
    \ int>>> bcc_edges;\n    vector<vector<int>> bcc_vertices;\n    explicit BiconnectedComponents(int\
    \ n): n(n), ord(n, -1), low(n), par(n, -1){}\n\n    void add_edge(int u, int v){\n\
    \        if(u == v) return;\n        edges.emplace_back(u, v);\n    }\n\n    int\
    \ build(){\n        CSR G(n, edges);\n        int pos = 0;\n        fill(ord.begin(),\
    \ ord.end(), -1);\n        fill(par.begin(), par.end(), -1);\n        bcc_edges.clear();\n\
    \        bcc_vertices.clear();\n        st.clear();\n        vector<Frame> stack;\n\
    \        for (int i = 0; i < n; ++i) {\n            if(ord[i] < 0) dfs(i, G, pos,\
    \ stack);\n        }\n        vector<int> seen(n, -1);\n        bcc_vertices.reserve(bcc_edges.size());\n\
    \        for (int i = 0; i < (int)bcc_edges.size(); ++i) {\n            vector<int>\
    \ now;\n            for (auto &&e : bcc_edges[i]) {\n                if(seen[e.first]\
    \ != i){\n                    seen[e.first] = i;\n                    now.emplace_back(e.first);\n\
    \                }\n                if(seen[e.second] != i){\n               \
    \     seen[e.second] = i;\n                    now.emplace_back(e.second);\n \
    \               }\n            }\n            bcc_vertices.emplace_back(std::move(now));\n\
    \        }\n        for (int i = 0; i < n; ++i) {\n            if(G.start[i] ==\
    \ G.start[i + 1]){\n                bcc_edges.emplace_back();\n              \
    \  bcc_vertices.push_back({i});\n            }\n        }\n        return bcc_vertices.size();\n\
    \    }\n};\n\n/**\n * @brief \u4E8C\u91CD\u9023\u7D50\u6210\u5206\u5206\u89E3\
    (Biconnected Components)\n */\n\n\n#line 4 \"graph/block_cut_tree.cpp\"\n\nstruct\
    \ BlockCutTree {\n    int n, block_count;\n    BiconnectedComponents bcc;\n  \
    \  vector<vector<int>> tree, nodes;\n    vector<int> id, rev;\n    vector<char>\
    \ is_articulation;\n\n    explicit BlockCutTree(int n) : n(n), block_count(0),\
    \ bcc(n), id(n, -1), is_articulation(n, 0) {}\n\n    void add_edge(int u, int\
    \ v) {\n        bcc.add_edge(u, v);\n    }\n\n    int build() {\n        block_count\
    \ = bcc.build();\n        vector<int> cnt(n);\n        for (auto &&vs : bcc.bcc_vertices)\
    \ {\n            for (auto &&v : vs) ++cnt[v];\n        }\n\n        int m = block_count;\n\
    \        id.assign(n, -1);\n        is_articulation.assign(n, 0);\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (cnt[v] > 1) {\n                is_articulation[v]\
    \ = 1;\n                id[v] = m++;\n            }\n        }\n\n        tree.assign(m,\
    \ {});\n        nodes.assign(m, {});\n        rev.assign(m, -1);\n        for\
    \ (int i = 0; i < block_count; ++i) {\n            nodes[i] = bcc.bcc_vertices[i];\n\
    \            for (auto &&v : bcc.bcc_vertices[i]) {\n                if (cnt[v]\
    \ > 1) {\n                    tree[i].push_back(id[v]);\n                    tree[id[v]].push_back(i);\n\
    \                } else {\n                    id[v] = i;\n                }\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ if (is_articulation[v]) {\n                nodes[id[v]].push_back(v);\n    \
    \            rev[id[v]] = v;\n            }\n        }\n        return m;\n  \
    \  }\n};\n\n/**\n * @brief \u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut\
    \ Tree)\n */\n"
  code: "using namespace std;\n\n#include \"biconnected_components.cpp\"\n\nstruct\
    \ BlockCutTree {\n    int n, block_count;\n    BiconnectedComponents bcc;\n  \
    \  vector<vector<int>> tree, nodes;\n    vector<int> id, rev;\n    vector<char>\
    \ is_articulation;\n\n    explicit BlockCutTree(int n) : n(n), block_count(0),\
    \ bcc(n), id(n, -1), is_articulation(n, 0) {}\n\n    void add_edge(int u, int\
    \ v) {\n        bcc.add_edge(u, v);\n    }\n\n    int build() {\n        block_count\
    \ = bcc.build();\n        vector<int> cnt(n);\n        for (auto &&vs : bcc.bcc_vertices)\
    \ {\n            for (auto &&v : vs) ++cnt[v];\n        }\n\n        int m = block_count;\n\
    \        id.assign(n, -1);\n        is_articulation.assign(n, 0);\n        for\
    \ (int v = 0; v < n; ++v) {\n            if (cnt[v] > 1) {\n                is_articulation[v]\
    \ = 1;\n                id[v] = m++;\n            }\n        }\n\n        tree.assign(m,\
    \ {});\n        nodes.assign(m, {});\n        rev.assign(m, -1);\n        for\
    \ (int i = 0; i < block_count; ++i) {\n            nodes[i] = bcc.bcc_vertices[i];\n\
    \            for (auto &&v : bcc.bcc_vertices[i]) {\n                if (cnt[v]\
    \ > 1) {\n                    tree[i].push_back(id[v]);\n                    tree[id[v]].push_back(i);\n\
    \                } else {\n                    id[v] = i;\n                }\n\
    \            }\n        }\n        for (int v = 0; v < n; ++v) {\n           \
    \ if (is_articulation[v]) {\n                nodes[id[v]].push_back(v);\n    \
    \            rev[id[v]] = v;\n            }\n        }\n        return m;\n  \
    \  }\n};\n\n/**\n * @brief \u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut\
    \ Tree)\n */\n"
  dependsOn:
  - graph/biconnected_components.cpp
  isVerificationFile: false
  path: graph/block_cut_tree.cpp
  requiredBy:
  - graph/vertex_failure_connectivity.cpp
  timestamp: '2026-10-10 19:54:48+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_vertex_failure_connectivity.test.cpp
  - test/yosupo_aplusb_library_composition.test.cpp
  - test/yuki1326_block_cut_tree.test.cpp
  - test/yosupo_aplusb_library_composition_reverse.test.cpp
date: 2026-03-11
documentation_of: graph/block_cut_tree.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u30D6\u30ED\u30C3\u30AF\u30AB\u30C3\u30C8\u6728(Block-Cut Tree)"
---

## 説明
無向グラフの二重連結成分と関節点から block-cut tree を作る。
成分ノードと関節点ノードの二部森になる。

## できること
- `BlockCutTree g(n)`
  頂点数 `n` の graph builder を作る
- `void add_edge(int u, int v)`
  無向辺を追加する。自己ループは内部で無視される
- `int build()`
  block-cut tree を構築し、ノード数を返す

## 使い方
`build()` 後は `tree`、`nodes`、`id`、`rev`、`is_articulation` を参照する。

- `tree[k]`
  block-cut tree 上の隣接ノード
- `nodes[k]`
  そのノードに対応する元グラフ頂点集合。成分ノードなら二重連結成分、関節点ノードなら 1 頂点だけ持つ
- `id[v]`
  元頂点 `v` が対応する block-cut tree ノード番号。関節点なら専用ノード、そうでなければ属する成分ノード
- `rev[k]`
  `k` が関節点ノードなら元頂点番号、成分ノードなら `-1`
- `is_articulation[v]`
  `v` が関節点なら `true`
