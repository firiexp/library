---
category: "\u6728"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  - icon: ':heavy_check_mark:'
    path: tree/auxtree.cpp
    title: "\u88DC\u52A9\u6728(Aux Tree)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0439_virtual_tree_helper.test.cpp
    title: test/aoj0439_virtual_tree_helper.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Virtual Tree Helper
    links: []
  bundledCode: "#line 1 \"tree/auxtree.cpp\"\n#include <stack>\n\n#line 1 \"datastructure/sparsetable.cpp\"\
    \ntemplate <class F>\nstruct SparseTable {\n    using T = typename F::T;\n   \
    \ vector<vector<T>> table;\n    vector<int> u;\n    SparseTable() = default;\n\
    \    explicit SparseTable(const vector<T> &v){ build(v); }\n \n    void build(const\
    \ vector<T> &v){\n        int n = v.size(), m = 1;\n        while((1<<m) <= n)\
    \ m++;\n        table.assign(m, vector<T>(n));\n        u.assign(n+1, 0);\n  \
    \      for (int i = 2; i <= n; ++i) {\n            u[i] = u[i>>1] + 1;\n     \
    \   }\n        for (int i = 0; i < n; ++i) {\n            table[0][i] = v[i];\n\
    \        }\n        for (int i = 1; i < m; ++i) {\n            int x = (1<<(i-1));\n\
    \            for (int j = 0; j < n; ++j) {\n                table[i][j] = F::f(table[i-1][j],\
    \ table[i-1][min(j+x, n-1)]);\n            }\n        }\n    }\n \n    T query(int\
    \ a, int b){\n        int l = b-a;\n        return F::f(table[u[l]][a], table[u[l]][b-(1<<u[l])]);\n\
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n#line 4 \"tree/auxtree.cpp\"\n\
    \nstruct F {\n    using T = pair<int, int>;\n    static T f(T a, T b) { return\
    \ min(a, b); }\n    static T e() { return T{INF<int>, -1}; }\n};\n\nclass AuxTree\
    \ {\n    SparseTable<F> table;\n    void dfs_euler(int v, int p, int d, int &k,\
    \ int &l){\n        id[v] = k;\n        vs[k] = v;\n        depth[k++] = d;\n\
    \        dep[v] = d;\n        fi[v] = l++;\n        for (auto &&u : G[v]) {\n\
    \            if(u != p){\n                dfs_euler(u, v, d+1, k, l);\n      \
    \          vs[k] = v;\n                depth[k++] = d;\n            }\n      \
    \  }\n    }\npublic:\n    int n;\n    vector<vector<int>> G, out;\n    vector<int>\
    \ vs, depth, dep, id, fi;\n    explicit AuxTree(int n) : table(), n(n), G(n),\
    \ out(n), vs(2*n-1), depth(2*n-1), dep(n), id(n), fi(n) {};\n    void add_edge(int\
    \ a, int b){\n        G[a].emplace_back(b);\n        G[b].emplace_back(a);\n \
    \   }\n\n    void eulertour(int root) {\n        int k = 0, l = 0;\n        dfs_euler(root,\
    \ -1, 0, k, l);\n    }\n\n    void buildLCA(int root = 0){\n        eulertour(root);\n\
    \        vector<pair<int, int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1;\
    \ ++i) {\n            v[i] = make_pair(depth[i], vs[i]);\n        }\n        table.build(v);\n\
    \    }\n\n    void make(vector<int> &v){\n        sort(v.begin(),v.end(), [&](int\
    \ a, int b){ return fi[a] < fi[b]; });\n        v.erase(unique(v.begin(), v.end()),\
    \ v.end());\n        int k = v.size();\n        stack<int> s;\n        s.emplace(v.front());\n\
    \        for (int i = 0; i+1 < k; ++i) {\n            int w = LCA(v[i], v[i+1]);\n\
    \            if(w != v[i]){\n                int u = s.top(); s.pop();\n     \
    \           while(!s.empty() && dep[w] < dep[s.top()]){\n                    out[s.top()].emplace_back(u);\n\
    \                    out[u].emplace_back(s.top());\n                    u = s.top();\
    \ s.pop();\n                }\n                if(s.empty() || s.top() != w){\n\
    \                    s.emplace(w);\n                    v.emplace_back(w);\n \
    \               }\n                out[w].emplace_back(u);\n                out[u].emplace_back(w);\n\
    \            }\n            s.emplace(v[i+1]);\n        }\n        while(s.size()\
    \ > 1){\n            int u = s.top(); s.pop();\n            out[s.top()].emplace_back(u);\n\
    \            out[u].emplace_back(s.top());\n        }\n    }\n\n    void clear(vector<int>\
    \ &v){\n        for (auto &&i : v) {\n            out[i].clear();\n          \
    \  out[i].shrink_to_fit();\n        }\n    }\n\n    int LCA(int u, int v){\n \
    \       if(id[u] > id[v]) swap(u, v);\n        return table.query(id[u], id[v]+1).second;\n\
    \    }\n\n    int distance(int u, int v){\n        return dep[u]+dep[v]-2*dep[LCA(u,\
    \ v)];\n    }\n};\n\n/**\n * @brief \u88DC\u52A9\u6728(Aux Tree)\n */\n#line 2\
    \ \"tree/virtual_tree_helper.cpp\"\n\nstruct VirtualTree {\n    int root;\n  \
    \  vector<int> vertices;\n    vector<int> parent;\n};\n\nclass VirtualTreeHelper\
    \ {\n    AuxTree aux;\n    vector<int> mark, parent_buf;\n    int stamp = 0;\n\
    \npublic:\n    explicit VirtualTreeHelper(int n) : aux(n), mark(n, 0), parent_buf(n,\
    \ -1) {}\n\n    void add_edge(int u, int v) {\n        aux.add_edge(u, v);\n \
    \   }\n\n    void build(int root = 0) {\n        aux.buildLCA(root);\n    }\n\n\
    \    int lca(int u, int v) {\n        return aux.LCA(u, v);\n    }\n\n    int\
    \ distance(int u, int v) {\n        return aux.distance(u, v);\n    }\n\n    VirtualTree\
    \ make(vector<int> vertices) {\n        aux.make(vertices);\n        sort(vertices.begin(),\
    \ vertices.end(), [&](int a, int b) { return aux.fi[a] < aux.fi[b]; });\n    \
    \    vertices.erase(unique(vertices.begin(), vertices.end()), vertices.end());\n\
    \n        VirtualTree res;\n        res.root = vertices.front();\n        ++stamp;\n\
    \        vector<int> st = {res.root};\n        mark[res.root] = stamp;\n     \
    \   parent_buf[res.root] = -1;\n\n        while (!st.empty()) {\n            int\
    \ v = st.back();\n            st.pop_back();\n            res.vertices.emplace_back(v);\n\
    \            res.parent.emplace_back(parent_buf[v]);\n            for (auto &&u\
    \ : aux.out[v]) {\n                if (mark[u] == stamp) continue;\n         \
    \       mark[u] = stamp;\n                parent_buf[u] = v;\n               \
    \ st.emplace_back(u);\n            }\n        }\n\n        aux.clear(vertices);\n\
    \        return res;\n    }\n};\n\n/**\n * @brief Virtual Tree Helper\n */\n"
  code: "#include \"./auxtree.cpp\"\n\nstruct VirtualTree {\n    int root;\n    vector<int>\
    \ vertices;\n    vector<int> parent;\n};\n\nclass VirtualTreeHelper {\n    AuxTree\
    \ aux;\n    vector<int> mark, parent_buf;\n    int stamp = 0;\n\npublic:\n   \
    \ explicit VirtualTreeHelper(int n) : aux(n), mark(n, 0), parent_buf(n, -1) {}\n\
    \n    void add_edge(int u, int v) {\n        aux.add_edge(u, v);\n    }\n\n  \
    \  void build(int root = 0) {\n        aux.buildLCA(root);\n    }\n\n    int lca(int\
    \ u, int v) {\n        return aux.LCA(u, v);\n    }\n\n    int distance(int u,\
    \ int v) {\n        return aux.distance(u, v);\n    }\n\n    VirtualTree make(vector<int>\
    \ vertices) {\n        aux.make(vertices);\n        sort(vertices.begin(), vertices.end(),\
    \ [&](int a, int b) { return aux.fi[a] < aux.fi[b]; });\n        vertices.erase(unique(vertices.begin(),\
    \ vertices.end()), vertices.end());\n\n        VirtualTree res;\n        res.root\
    \ = vertices.front();\n        ++stamp;\n        vector<int> st = {res.root};\n\
    \        mark[res.root] = stamp;\n        parent_buf[res.root] = -1;\n\n     \
    \   while (!st.empty()) {\n            int v = st.back();\n            st.pop_back();\n\
    \            res.vertices.emplace_back(v);\n            res.parent.emplace_back(parent_buf[v]);\n\
    \            for (auto &&u : aux.out[v]) {\n                if (mark[u] == stamp)\
    \ continue;\n                mark[u] = stamp;\n                parent_buf[u] =\
    \ v;\n                st.emplace_back(u);\n            }\n        }\n\n      \
    \  aux.clear(vertices);\n        return res;\n    }\n};\n\n/**\n * @brief Virtual\
    \ Tree Helper\n */\n"
  dependsOn:
  - tree/auxtree.cpp
  - datastructure/sparsetable.cpp
  isVerificationFile: false
  path: tree/virtual_tree_helper.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0439_virtual_tree_helper.test.cpp
date: 2026-03-08
documentation_of: tree/virtual_tree_helper.cpp
layout: post
tags: "\u6728"
title: virtual_tree_helper
---

## 説明
`AuxTree` の `make / clear / out` 管理を隠して、DP しやすい形で virtual tree を返す補助ラッパ。
各クエリごとに、必要頂点と補われた LCA 頂点からなる根付き木を作る。

## できること
- `VirtualTreeHelper vt(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  LCA 前処理をする
- `int lca(int u, int v)`
  最近共通祖先を返す
- `int distance(int u, int v)`
  木上距離を返す
- `VirtualTree make(vector<int> vertices)`
  virtual tree を返す

## 使い方
`make` の返り値は `vertices[i]` とその親 `parent[i]` を持つ。
`parent[i] = -1` の頂点が根で、`i` は親が子より先に出る。
部分木 DP は `vertices` を逆順に走査すればよい。

```cpp
auto tr = vt.make(query_vertices);
for (int i = (int)tr.vertices.size() - 1; i >= 0; --i) {
    int v = tr.vertices[i];
    int p = tr.parent[i];
    if (p != -1) {
        // v -> p に畳み込む
    }
}
```

## 実装上の補足
返り値の頂点列には元の query 頂点に加えて必要な LCA 頂点も入る。
内部では `AuxTree` を使い、各クエリ後の `clear` は helper 側で処理する。
