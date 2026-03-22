---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: datastructure/sparsetable.cpp
    title: Sparse Table
  _extendedRequiredBy:
  - icon: ':x:'
    path: tree/virtual_tree_helper.cpp
    title: virtual_tree_helper
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj0439.test.cpp
    title: test/aoj0439.test.cpp
  - icon: ':x:'
    path: test/aoj0439_virtual_tree_helper.test.cpp
    title: test/aoj0439_virtual_tree_helper.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u88DC\u52A9\u6728(Aux Tree)"
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
    \    }\n};\n\n/**\n * @brief Sparse Table\n */\n#line 2 \"tree/auxtree.cpp\"\n\
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
    \ v)];\n    }\n};\n\n/**\n * @brief \u88DC\u52A9\u6728(Aux Tree)\n */\n"
  code: "#include \"../datastructure/sparsetable.cpp\"\n\nstruct F {\n    using T\
    \ = pair<int, int>;\n    static T f(T a, T b) { return min(a, b); }\n    static\
    \ T e() { return T{INF<int>, -1}; }\n};\n\nclass AuxTree {\n    SparseTable<F>\
    \ table;\n    void dfs_euler(int v, int p, int d, int &k, int &l){\n        id[v]\
    \ = k;\n        vs[k] = v;\n        depth[k++] = d;\n        dep[v] = d;\n   \
    \     fi[v] = l++;\n        for (auto &&u : G[v]) {\n            if(u != p){\n\
    \                dfs_euler(u, v, d+1, k, l);\n                vs[k] = v;\n   \
    \             depth[k++] = d;\n            }\n        }\n    }\npublic:\n    int\
    \ n;\n    vector<vector<int>> G, out;\n    vector<int> vs, depth, dep, id, fi;\n\
    \    explicit AuxTree(int n) : table(), n(n), G(n), out(n), vs(2*n-1), depth(2*n-1),\
    \ dep(n), id(n), fi(n) {};\n    void add_edge(int a, int b){\n        G[a].emplace_back(b);\n\
    \        G[b].emplace_back(a);\n    }\n\n    void eulertour(int root) {\n    \
    \    int k = 0, l = 0;\n        dfs_euler(root, -1, 0, k, l);\n    }\n\n    void\
    \ buildLCA(int root = 0){\n        eulertour(root);\n        vector<pair<int,\
    \ int>> v(2*n-1);\n        for (int i = 0; i < 2*n-1; ++i) {\n            v[i]\
    \ = make_pair(depth[i], vs[i]);\n        }\n        table.build(v);\n    }\n\n\
    \    void make(vector<int> &v){\n        sort(v.begin(),v.end(), [&](int a, int\
    \ b){ return fi[a] < fi[b]; });\n        v.erase(unique(v.begin(), v.end()), v.end());\n\
    \        int k = v.size();\n        stack<int> s;\n        s.emplace(v.front());\n\
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
    \ v)];\n    }\n};\n\n/**\n * @brief \u88DC\u52A9\u6728(Aux Tree)\n */\n"
  dependsOn:
  - datastructure/sparsetable.cpp
  isVerificationFile: false
  path: tree/auxtree.cpp
  requiredBy:
  - tree/virtual_tree_helper.cpp
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj0439.test.cpp
  - test/aoj0439_virtual_tree_helper.test.cpp
documentation_of: tree/auxtree.cpp
layout: document
title: "\u88DC\u52A9\u6728(Aux Tree)"
---
## 説明
必要な頂点集合だけを含む virtual tree を構築する。
LCA を自動で補い、元の木上での親子関係を保ったまま補助木 `out` に辺を張る。

## できること
- `AuxTree tr(n)`
  頂点数 `n` の木を作る
- `void add_edge(int a, int b)`
  木辺を張る
- `void buildLCA()`
  LCA と距離計算の前処理をする
- `void make(vector<int>& v)`
  頂点集合 `v` から補助木を作る。必要なら LCA 頂点も `v` に追加される
- `void clear(vector<int>& v)`
  `make` で使った頂点の `out` を消す
- `int LCA(int u, int v)`
  最近共通祖先を返す
- `int distance(int u, int v)`
  木上距離を返す

## 使い方
`buildLCA()` を先に呼び、その後でクエリごとに対象頂点を `v` に入れて `make(v)` を呼ぶ。
補助木の辺は `out` に無向辺として入る。

```cpp
AuxTree tr(n);
tr.add_edge(u, v);
tr.buildLCA();

vector<int> vs = query_vertices;
tr.make(vs);
for (int x : vs) {
    for (int y : tr.out[x]) {
        // virtual tree 上の辺
    }
}
tr.clear(vs);
```

## 実装上の補足
`make(v)` は引数 `v` を破壊的に変更し、LCA 頂点を追加する。
`clear(v)` は `make` 後の `v` をそのまま渡す前提である。
