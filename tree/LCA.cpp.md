---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_lca.test.cpp
    title: test/yosupo_lca.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)"
    links: []
  bundledCode: "#line 1 \"datastructure/sparsetable.cpp\"\ntemplate <class F>\nstruct\
    \ SparseTable {\n    using T = typename F::T;\n    vector<vector<T>> table;\n\
    \    vector<int> u;\n    SparseTable() = default;\n    explicit SparseTable(const\
    \ vector<T> &v){ build(v); }\n \n    void build(const vector<T> &v){\n       \
    \ int n = v.size(), m = 1;\n        while((1<<m) <= n) m++;\n        table.assign(m,\
    \ vector<T>(n));\n        u.assign(n+1, 0);\n        for (int i = 2; i <= n; ++i)\
    \ {\n            u[i] = u[i>>1] + 1;\n        }\n        for (int i = 0; i < n;\
    \ ++i) {\n            table[0][i] = v[i];\n        }\n        for (int i = 1;\
    \ i < m; ++i) {\n            int x = (1<<(i-1));\n            for (int j = 0;\
    \ j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j], table[i-1][min(j+x,\
    \ n-1)]);\n            }\n        }\n    }\n \n    T query(int a, int b){\n  \
    \      int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n#line 2 \"tree/LCA.cpp\"\n\nstruct\
    \ LCA_MinDepth {\n    using T = pair<int, int>;\n    static T f(T a, T b) { return\
    \ min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\nclass LCA\
    \ {\n    SparseTable<LCA_MinDepth> table;\n\n    void dfs_euler(int v, int p,\
    \ int d, int &k) {\n        id[v] = k;\n        vs[k] = v;\n        depth[k++]\
    \ = d;\n        for (auto &&u : G[v]) {\n            if (u == p) continue;\n \
    \           dfs_euler(u, v, d + 1, k);\n            vs[k] = v;\n            depth[k++]\
    \ = d;\n        }\n    }\n\npublic:\n    int n;\n    vector<vector<int>> G;\n\
    \    vector<int> vs, depth, id;\n\n    explicit LCA(int n) : table(), n(n), G(n),\
    \ vs(2 * n - 1), depth(2 * n - 1), id(n) {}\n\n    void add_edge(int a, int b)\
    \ {\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n    }\n\n \
    \   void eulertour(int root = 0) {\n        int k = 0;\n        dfs_euler(root,\
    \ -1, 0, k);\n    }\n\n    void build(int root = 0) {\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2 * n - 1);\n        for (int i = 0; i < 2 *\
    \ n - 1; ++i) {\n            v[i] = make_pair(depth[i], i);\n        }\n     \
    \   table.build(v);\n    }\n\n    void buildLCA(int root = 0) {\n        build(root);\n\
    \    }\n\n    int lca(int u, int v) {\n        if (id[u] > id[v]) swap(u, v);\n\
    \        return vs[table.query(id[u], id[v] + 1).second];\n    }\n};\n\n/**\n\
    \ * @brief \u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)\n */\n"
  code: "#include \"../datastructure/sparsetable.cpp\"\n\nstruct LCA_MinDepth {\n\
    \    using T = pair<int, int>;\n    static T f(T a, T b) { return min(a, b); }\n\
    \    static T e() { return T{INF<int>, -1}; }\n};\n\nclass LCA {\n    SparseTable<LCA_MinDepth>\
    \ table;\n\n    void dfs_euler(int v, int p, int d, int &k) {\n        id[v] =\
    \ k;\n        vs[k] = v;\n        depth[k++] = d;\n        for (auto &&u : G[v])\
    \ {\n            if (u == p) continue;\n            dfs_euler(u, v, d + 1, k);\n\
    \            vs[k] = v;\n            depth[k++] = d;\n        }\n    }\n\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> vs, depth, id;\n\n  \
    \  explicit LCA(int n) : table(), n(n), G(n), vs(2 * n - 1), depth(2 * n - 1),\
    \ id(n) {}\n\n    void add_edge(int a, int b) {\n        G[a].emplace_back(b);\n\
    \        G[b].emplace_back(a);\n    }\n\n    void eulertour(int root = 0) {\n\
    \        int k = 0;\n        dfs_euler(root, -1, 0, k);\n    }\n\n    void build(int\
    \ root = 0) {\n        eulertour(root);\n        vector<pair<int, int>> v(2 *\
    \ n - 1);\n        for (int i = 0; i < 2 * n - 1; ++i) {\n            v[i] = make_pair(depth[i],\
    \ i);\n        }\n        table.build(v);\n    }\n\n    void buildLCA(int root\
    \ = 0) {\n        build(root);\n    }\n\n    int lca(int u, int v) {\n       \
    \ if (id[u] > id[v]) swap(u, v);\n        return vs[table.query(id[u], id[v] +\
    \ 1).second];\n    }\n};\n\n/**\n * @brief \u6700\u8FD1\u5171\u901A\u7956\u5148\
    (LCA)\n */\n"
  dependsOn:
  - datastructure/sparsetable.cpp
  isVerificationFile: false
  path: tree/LCA.cpp
  requiredBy: []
  timestamp: '2026-03-13 21:29:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_lca.test.cpp
documentation_of: tree/LCA.cpp
layout: document
title: "\u6700\u8FD1\u5171\u901A\u7956\u5148(LCA)"
---
## 説明
Euler Tour + Sparse Table で木上の LCA を求める。
前処理 $O(N log N)$、クエリ $O(1)$。

## できること
- `LCA lca(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  根 `root` で前処理をする
- `void buildLCA(int root = 0)`
  `build(root)` の別名
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す

## 使い方
木を張ったあと `build(root)` を 1 回呼び、以降 `lca(u, v)` を使う。

```cpp
LCA lca(n);
for (auto [u, v] : edges) {
    lca.add_edge(u, v);
}
lca.build(0);

int w = lca.lca(u, v);
```

## 実装上の補足
`id[v]` は Euler Tour 上での最初の出現位置を持つ。
RMQ には `SparseTable` を使うので、`INF<T>` が見える位置で include する必要がある。
