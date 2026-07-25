---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0349.test.cpp
    title: test/aoj0349.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_scc.test.cpp
    title: test/yosupo_scc.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)"
    links: []
  bundledCode: "#line 1 \"graph/SCC.cpp\"\nclass SCC {\n    struct CSR {\n       \
    \ vector<int> start, elist;\n\n        CSR() = default;\n\n        CSR(int n,\
    \ const vector<pair<int, int>> &edges, bool rev) : start(n + 1), elist(edges.size())\
    \ {\n            for (auto &&[a, b] : edges) {\n                ++start[(rev ?\
    \ b : a) + 1];\n            }\n            for (int i = 0; i < n; ++i) start[i\
    \ + 1] += start[i];\n            auto counter = start;\n            for (auto\
    \ &&[a, b] : edges) {\n                int from = rev ? b : a;\n             \
    \   int to = rev ? a : b;\n                elist[counter[from]++] = to;\n    \
    \        }\n        }\n    };\n\n    int n = 0;\n    vector<pair<int, int>> edges;\n\
    \npublic:\n    vector<vector<int>> G_out;\n    vector<int> vs, used, cmp, sz;\n\
    \    SCC() = default;\n    explicit SCC(int n) : n(n), used(n), cmp(n), sz(n)\
    \ {}\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a, b);\n\
    \    }\n\n    int build() {\n        CSR G(n, edges, false), G_r(n, edges, true);\n\
    \        vs.clear();\n        vs.reserve(n);\n        fill(used.begin(), used.end(),\
    \ 0);\n        auto dfs = [&](auto &&self, int v) -> void {\n            used[v]\
    \ = 1;\n            for (int ei = G.start[v]; ei < G.start[v + 1]; ++ei) {\n \
    \               int u = G.elist[ei];\n                if(!used[u]) self(self,\
    \ u);\n            }\n            vs.emplace_back(v);\n        };\n        for\
    \ (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs, i);\n        }\n\
    \        fill(used.begin(), used.end(), 0);\n        sz.resize(n);\n        fill(sz.begin(),\
    \ sz.end(), 0);\n        int k = 0;\n        auto dfs_r = [&](auto &&self, int\
    \ v, int c) -> void {\n            used[v] = 1;\n            cmp[v] = c;\n   \
    \         sz[c]++;\n            for (int ei = G_r.start[v]; ei < G_r.start[v +\
    \ 1]; ++ei) {\n                int u = G_r.elist[ei];\n                if(!used[u])\
    \ self(self, u, c);\n            }\n        };\n        for (int i = n - 1; i\
    \ >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(dfs_r, vs[i],\
    \ k++);\n            }\n        }\n        G_out.assign(k, {});\n        sz.resize(k);\n\
    \        for (auto &&[a, b] : edges) {\n            if(cmp[a] != cmp[b]){\n  \
    \              G_out[cmp[a]].emplace_back(cmp[b]);\n            }\n        }\n\
    \        for (auto &&l : G_out) {\n            sort(l.begin(), l.end());\n   \
    \         l.erase(unique(l.begin(), l.end()), l.end());\n        }\n        return\
    \ k;\n    }\n\n    int operator[](int k) const { return cmp[k]; }\n};\n\n/**\n\
    \ * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)\n */\n"
  code: "class SCC {\n    struct CSR {\n        vector<int> start, elist;\n\n    \
    \    CSR() = default;\n\n        CSR(int n, const vector<pair<int, int>> &edges,\
    \ bool rev) : start(n + 1), elist(edges.size()) {\n            for (auto &&[a,\
    \ b] : edges) {\n                ++start[(rev ? b : a) + 1];\n            }\n\
    \            for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n         \
    \   auto counter = start;\n            for (auto &&[a, b] : edges) {\n       \
    \         int from = rev ? b : a;\n                int to = rev ? a : b;\n   \
    \             elist[counter[from]++] = to;\n            }\n        }\n    };\n\
    \n    int n = 0;\n    vector<pair<int, int>> edges;\n\npublic:\n    vector<vector<int>>\
    \ G_out;\n    vector<int> vs, used, cmp, sz;\n    SCC() = default;\n    explicit\
    \ SCC(int n) : n(n), used(n), cmp(n), sz(n) {}\n\n    void add_edge(int a, int\
    \ b){\n        edges.emplace_back(a, b);\n    }\n\n    int build() {\n       \
    \ CSR G(n, edges, false), G_r(n, edges, true);\n        vs.clear();\n        vs.reserve(n);\n\
    \        fill(used.begin(), used.end(), 0);\n        auto dfs = [&](auto &&self,\
    \ int v) -> void {\n            used[v] = 1;\n            for (int ei = G.start[v];\
    \ ei < G.start[v + 1]; ++ei) {\n                int u = G.elist[ei];\n       \
    \         if(!used[u]) self(self, u);\n            }\n            vs.emplace_back(v);\n\
    \        };\n        for (int i = 0; i < n; ++i) {\n            if(!used[i]) dfs(dfs,\
    \ i);\n        }\n        fill(used.begin(), used.end(), 0);\n        sz.resize(n);\n\
    \        fill(sz.begin(), sz.end(), 0);\n        int k = 0;\n        auto dfs_r\
    \ = [&](auto &&self, int v, int c) -> void {\n            used[v] = 1;\n     \
    \       cmp[v] = c;\n            sz[c]++;\n            for (int ei = G_r.start[v];\
    \ ei < G_r.start[v + 1]; ++ei) {\n                int u = G_r.elist[ei];\n   \
    \             if(!used[u]) self(self, u, c);\n            }\n        };\n    \
    \    for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n     \
    \           dfs_r(dfs_r, vs[i], k++);\n            }\n        }\n        G_out.assign(k,\
    \ {});\n        sz.resize(k);\n        for (auto &&[a, b] : edges) {\n       \
    \     if(cmp[a] != cmp[b]){\n                G_out[cmp[a]].emplace_back(cmp[b]);\n\
    \            }\n        }\n        for (auto &&l : G_out) {\n            sort(l.begin(),\
    \ l.end());\n            l.erase(unique(l.begin(), l.end()), l.end());\n     \
    \   }\n        return k;\n    }\n\n    int operator[](int k) const { return cmp[k];\
    \ }\n};\n\n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/SCC.cpp
  requiredBy: []
  timestamp: '2026-04-11 14:07:08+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_scc.test.cpp
  - test/aoj0349.test.cpp
date: 2019-12-03
documentation_of: graph/SCC.cpp
layout: document
tags: "\u6709\u5411\u30B0\u30E9\u30D5"
title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)"
---

## 説明
有向グラフを強連結成分分解する。
Kosaraju 法で成分番号と縮約 DAG を作る。計算量は $O(N + M)$。

## できること
- `SCC scc(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int u, int v)`
  辺 `u -> v` を張る
- `int build()`
  強連結成分分解を実行して成分数を返す
- `int operator[](int v)`
  頂点 `v` の属する成分番号を返す
- `vector<int> cmp`
  各頂点の成分番号を持つ
- `vector<int> sz`
  各成分の頂点数を持つ
- `vector<vector<int>> G_out`
  成分 DAG を持つ。多重辺は除かれる

## 使い方
辺を張ってから `build()` を呼ぶ。
以後は `cmp[v]` や `scc[v]` で成分番号を見て、`G_out` を縮約 DAG として使う。

## 実装上の補足
成分番号は逆辺 DFS の訪問順で振られる。
`G_out` はトポロジカル順を保つとは限らないので、必要なら別に順序を取る。
