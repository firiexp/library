---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_twosat.test.cpp
    title: test/yosupo_twosat.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 2-SAT
    links: []
  bundledCode: "#line 1 \"graph/twosat.cpp\"\nstruct SCC {\n    vector<vector<int>>\
    \ G, G_r, G_out;\n    vector<int> vs, used, cmp;\n    SCC() = default;\n    explicit\
    \ SCC(int n) : G(n), G_r(n), used(n), cmp(n) {}\n\n    void add_edge(int a, int\
    \ b){\n        G[a].emplace_back(b);\n        G_r[b].emplace_back(a);\n    }\n\
    \n    void dfs(int v){\n        used[v] = 1;\n        for (auto &&u : G[v]) if(!used[u])\
    \ dfs(u);\n        vs.emplace_back(v);\n    }\n\n    void dfs_r(int v, int k){\n\
    \        used[v] = 1;\n        cmp[v] = k;\n        for (auto &&u : G_r[v]) if(!used[u])\
    \ dfs_r(u, k);\n    }\n\n    int build() {\n        int n = G.size();\n      \
    \  for (int i = 0; i < n; ++i) if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(),\
    \ 0);\n        int k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n      \
    \      if(!used[vs[i]]){\n                dfs_r(vs[i], k++);\n            }\n\
    \        }\n        return k;\n    }\n\n    int operator[](int k) const { return\
    \ cmp[k]; }\n};\n\nstruct TwoSAT {\n    int n;\n    SCC scc;\n    explicit TwoSAT(int\
    \ n) : n(n), scc(n*2) {};\n    int negate(int v){\n        int ret = n+v;\n  \
    \      if(ret >= n*2) ret -= n*2;\n        return ret;\n    }\n\n    vector<int>\
    \ build() {\n        scc.build();\n        vector<int> res(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(scc[i] == scc[n+i]) return {};\n      \
    \      res[i] = scc[i] > scc[n+i];\n        }\n        return res;\n    }\n\n\
    \    void add_if(int u, int v){ // u -> v\n        scc.add_edge(u, v);\n     \
    \   scc.add_edge(negate(v), negate(u));\n    }\n\n    void add_or(int u, int v){\
    \ // u || v\n        add_if(negate(u), v);\n    }\n};\n\n/**\n * @brief 2-SAT\n\
    \ */\n"
  code: "struct SCC {\n    vector<vector<int>> G, G_r, G_out;\n    vector<int> vs,\
    \ used, cmp;\n    SCC() = default;\n    explicit SCC(int n) : G(n), G_r(n), used(n),\
    \ cmp(n) {}\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G_r[b].emplace_back(a);\n    }\n\n    void dfs(int v){\n        used[v]\
    \ = 1;\n        for (auto &&u : G[v]) if(!used[u]) dfs(u);\n        vs.emplace_back(v);\n\
    \    }\n\n    void dfs_r(int v, int k){\n        used[v] = 1;\n        cmp[v]\
    \ = k;\n        for (auto &&u : G_r[v]) if(!used[u]) dfs_r(u, k);\n    }\n\n \
    \   int build() {\n        int n = G.size();\n        for (int i = 0; i < n; ++i)\
    \ if(!used[i]) dfs(i);\n        fill(used.begin(),used.end(), 0);\n        int\
    \ k = 0;\n        for (int i = n - 1; i >= 0; --i) {\n            if(!used[vs[i]]){\n\
    \                dfs_r(vs[i], k++);\n            }\n        }\n        return\
    \ k;\n    }\n\n    int operator[](int k) const { return cmp[k]; }\n};\n\nstruct\
    \ TwoSAT {\n    int n;\n    SCC scc;\n    explicit TwoSAT(int n) : n(n), scc(n*2)\
    \ {};\n    int negate(int v){\n        int ret = n+v;\n        if(ret >= n*2)\
    \ ret -= n*2;\n        return ret;\n    }\n\n    vector<int> build() {\n     \
    \   scc.build();\n        vector<int> res(n);\n        for (int i = 0; i < n;\
    \ ++i) {\n            if(scc[i] == scc[n+i]) return {};\n            res[i] =\
    \ scc[i] > scc[n+i];\n        }\n        return res;\n    }\n\n    void add_if(int\
    \ u, int v){ // u -> v\n        scc.add_edge(u, v);\n        scc.add_edge(negate(v),\
    \ negate(u));\n    }\n\n    void add_or(int u, int v){ // u || v\n        add_if(negate(u),\
    \ v);\n    }\n};\n\n/**\n * @brief 2-SAT\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/twosat.cpp
  requiredBy: []
  timestamp: '2026-03-13 21:29:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_twosat.test.cpp
date: 2019-12-03
documentation_of: graph/twosat.cpp
layout: document
tags: "\u6709\u5411\u30B0\u30E9\u30D5"
title: 2-SAT
---

## 説明
2-SAT を SCC で解く。
各変数 $x_i$ とその否定を 2 頂点に対応させ、含意グラフを作る。

## できること
- `TwoSAT sat(n)`
  変数数 `n` の 2-SAT を作る
- `int negate(int v)`
  リテラル `v` の否定を返す
- `void add_if(int u, int v)`
  含意 `u -> v` を加える
- `void add_or(int u, int v)`
  節 `u or v` を加える
- `vector<int> build()`
  充足する代入を返す。充足不能なら空配列

## 使い方
正リテラルを `0..n-1`、負リテラルを `negate(i)` で表す。
制約を追加したあと `build()` を呼び、返り値 `res[i]` を変数 `i` の真偽として使う。

## 実装上の補足
`build()` で $x_i$ と $\lnot x_i$ が同じ SCC に入ったら充足不能と判定する。
代入は SCC 番号の大小で決めている。
