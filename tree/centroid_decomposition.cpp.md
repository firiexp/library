---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0452.test.cpp
    title: test/aoj0452.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/centroid_decomposition.md
    document_title: "\u91CD\u5FC3\u5206\u89E3(Centroid Decomposition)"
    links: []
  bundledCode: "#line 1 \"tree/centroid_decomposition.cpp\"\nclass CentroidDecomposition\
    \ {\n    int dfs(int x, int par){\n        sz[x] = 1;\n        for (auto &&i :\
    \ G[x]) {\n            if(i == par || v[i]) continue;\n            sz[x] += dfs(i,\
    \ x);\n        }\n        return sz[x];\n    }\n\n    int search_centroid(int\
    \ x, int p, const int mid){\n        for (auto &&i : G[x]) {\n            if(i\
    \ == p || v[i]) continue;\n            if(sz[i] > mid) return search_centroid(i,\
    \ x, mid);\n        }\n        return x;\n    }\npublic:\n    int n;\n    vector<vector<int>>\
    \ G, out;\n    vector<int> sz, v;\n    CentroidDecomposition(int n) : n(n), G(n),\
    \ out(n), sz(n), v(n) {}\n    void add_edge(int l, int r){\n        G[l].emplace_back(r);\n\
    \        G[r].emplace_back(l);\n    }\n    int get(int x){\n        int centroid\
    \ = search_centroid(x, -1, dfs(x, -1)/2);\n        v[centroid] = true;\n     \
    \   for (auto &&i : G[centroid]) {\n            if(!v[i]) out[centroid].emplace_back(get(i));\n\
    \        }\n        v[centroid] = false;\n        return centroid;\n    }\n};\n\
    \n/**\n * @brief \u91CD\u5FC3\u5206\u89E3(Centroid Decomposition)\n * @docs _md/centroid_decomposition.md\n\
    \ */\n"
  code: "class CentroidDecomposition {\n    int dfs(int x, int par){\n        sz[x]\
    \ = 1;\n        for (auto &&i : G[x]) {\n            if(i == par || v[i]) continue;\n\
    \            sz[x] += dfs(i, x);\n        }\n        return sz[x];\n    }\n\n\
    \    int search_centroid(int x, int p, const int mid){\n        for (auto &&i\
    \ : G[x]) {\n            if(i == p || v[i]) continue;\n            if(sz[i] >\
    \ mid) return search_centroid(i, x, mid);\n        }\n        return x;\n    }\n\
    public:\n    int n;\n    vector<vector<int>> G, out;\n    vector<int> sz, v;\n\
    \    CentroidDecomposition(int n) : n(n), G(n), out(n), sz(n), v(n) {}\n    void\
    \ add_edge(int l, int r){\n        G[l].emplace_back(r);\n        G[r].emplace_back(l);\n\
    \    }\n    int get(int x){\n        int centroid = search_centroid(x, -1, dfs(x,\
    \ -1)/2);\n        v[centroid] = true;\n        for (auto &&i : G[centroid]) {\n\
    \            if(!v[i]) out[centroid].emplace_back(get(i));\n        }\n      \
    \  v[centroid] = false;\n        return centroid;\n    }\n};\n\n/**\n * @brief\
    \ \u91CD\u5FC3\u5206\u89E3(Centroid Decomposition)\n * @docs _md/centroid_decomposition.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/centroid_decomposition.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0452.test.cpp
documentation_of: tree/centroid_decomposition.cpp
layout: document
redirect_from:
- /library/tree/centroid_decomposition.cpp
- /library/tree/centroid_decomposition.cpp.html
title: "\u91CD\u5FC3\u5206\u89E3(Centroid Decomposition)"
---
## 説明
木を重心分解し、重心木を構築する。
各部分木を重心で再帰的に分割し、`out` に重心木の子を持つ。

## できること
- `CentroidDecomposition cd(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `int get(int root)`
  `root` を含む連結成分を重心分解し、重心木の根を返す

## 使い方
木を張ったあと `get(0)` のように呼ぶと、`out` に重心木が構築される。

```cpp
CentroidDecomposition cd(n);
cd.add_edge(u, v);
int root = cd.get(0);
for (int to : cd.out[root]) {
    // 重心木の子
}
```

## 実装上の補足
`out` は有向木として張られ、親から子への辺だけを持つ。
`get` は内部で訪問印 `v` を使うが、処理後には元に戻す。
