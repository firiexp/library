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
  bundledCode: "#line 1 \"graph/SCC.cpp\"\nclass SCC {\n    void dfs(int v){\n   \
    \     used[v] = 1;\n        for (auto &&u : G[v]) if(!used[u]) dfs(u);\n     \
    \   vs.emplace_back(v);\n    }\n\n    void dfs_r(int v, int k){\n        used[v]\
    \ = 1;\n        cmp[v] = k;\n        sz[k]++;\n        for (auto &&u : G_r[v])\
    \ if(!used[u]) dfs_r(u, k);\n    }\npublic:\n    vector<vector<int>> G, G_r, G_out;\n\
    \    vector<int> vs, used, cmp, sz;\n    SCC() = default;\n    explicit SCC(int\
    \ n) : G(n), G_r(n), G_out(n), used(n), cmp(n), sz(n) {}\n\n    void add_edge(int\
    \ a, int b){\n        G[a].emplace_back(b);\n        G_r[b].emplace_back(a);\n\
    \    }\n\n    int build() {\n        int n = G.size();\n        for (int i = 0;\
    \ i < n; ++i) if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(), 0);\n\
    \        int k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n\
    \                dfs_r(vs[i], k++);\n            }\n        }\n        G_out.resize(k);\n\
    \        sz.resize(k);\n        for (int i = 0; i < n; ++i) {\n            for\
    \ (auto &&j : G[i]) {\n                if(cmp[i] != cmp[j]){\n               \
    \     G_out[cmp[i]].emplace_back(cmp[j]);\n                }\n            }\n\
    \        }\n        for (auto &&l : G_out) {\n            sort(l.begin(), l.end());\n\
    \            l.erase(unique(l.begin(), l.end()), l.end());\n        }\n      \
    \  return k;\n    }\n\n    int operator[](int k) const { return cmp[k]; }\n};\n\
    \n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(SCC)\n */\n"
  code: "class SCC {\n    void dfs(int v){\n        used[v] = 1;\n        for (auto\
    \ &&u : G[v]) if(!used[u]) dfs(u);\n        vs.emplace_back(v);\n    }\n\n   \
    \ void dfs_r(int v, int k){\n        used[v] = 1;\n        cmp[v] = k;\n     \
    \   sz[k]++;\n        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);\n    }\n\
    public:\n    vector<vector<int>> G, G_r, G_out;\n    vector<int> vs, used, cmp,\
    \ sz;\n    SCC() = default;\n    explicit SCC(int n) : G(n), G_r(n), G_out(n),\
    \ used(n), cmp(n), sz(n) {}\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G_r[b].emplace_back(a);\n    }\n\n    int build() {\n        int n =\
    \ G.size();\n        for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n      \
    \  fill(used.begin(),used.end(), 0);\n        int k = 0;\n        for (int i =\
    \ n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n                dfs_r(vs[i],\
    \ k++);\n            }\n        }\n        G_out.resize(k);\n        sz.resize(k);\n\
    \        for (int i = 0; i < n; ++i) {\n            for (auto &&j : G[i]) {\n\
    \                if(cmp[i] != cmp[j]){\n                    G_out[cmp[i]].emplace_back(cmp[j]);\n\
    \                }\n            }\n        }\n        for (auto &&l : G_out) {\n\
    \            sort(l.begin(), l.end());\n            l.erase(unique(l.begin(),\
    \ l.end()), l.end());\n        }\n        return k;\n    }\n\n    int operator[](int\
    \ k) const { return cmp[k]; }\n};\n\n/**\n * @brief \u5F37\u9023\u7D50\u6210\u5206\
    \u5206\u89E3(SCC)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/SCC.cpp
  requiredBy: []
  timestamp: '2026-03-13 21:29:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_scc.test.cpp
  - test/aoj0349.test.cpp
date: 2019-12-03
documentation_of: graph/SCC.cpp
layout: document
tags: "\u6709\u5411\u30B0\u30E9\u30D5"
title: "\u5F37\u9023\u7D50\u6210\u5206\u5206\u89E3(Strongly-Connected-Components,\
  \ SCC)"
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
