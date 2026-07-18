---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dsu_on_tree.test.cpp
    title: test/yosupo_aplusb_dsu_on_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: DSU on Tree
    links: []
  bundledCode: "#line 1 \"tree/dsu_on_tree.cpp\"\nstruct DSUonTree {\n    int n, root;\n\
    \    vector<pair<int, int>> edges;\n    vector<int> start, to;\n    vector<int>\
    \ sub_size, heavy;\n    vector<int> order, dfn;\n\n    explicit DSUonTree(int\
    \ n = 0) : n(n), root(0) {\n        edges.reserve(max(0, n - 1));\n    }\n\n \
    \   template<class G>\n    explicit DSUonTree(const vector<vector<G>> &g, int\
    \ root = 0) : DSUonTree((int)g.size()) {\n        vector<int> parent(n, -2);\n\
    \        vector<int> st(1, root);\n        parent[root] = -1;\n        while (!st.empty())\
    \ {\n            int v = st.back();\n            st.pop_back();\n            for\
    \ (auto &&u : g[v]) {\n                if (u == parent[v] || parent[u] != -2)\
    \ continue;\n                parent[u] = v;\n                edges.emplace_back(v,\
    \ u);\n                st.push_back(u);\n            }\n        }\n        build(root);\n\
    \    }\n\n    void add_edge(int u, int v) {\n        edges.emplace_back(u, v);\n\
    \    }\n\n    void build(int root = 0) {\n        this->root = root;\n       \
    \ start.assign(n + 1, 0);\n        to.assign(edges.size() * 2, 0);\n        for\
    \ (auto &&[u, v] : edges) {\n            ++start[u + 1];\n            ++start[v\
    \ + 1];\n        }\n        for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n\
    \        auto counter = start;\n        for (auto &&[u, v] : edges) {\n      \
    \      to[counter[u]++] = v;\n            to[counter[v]++] = u;\n        }\n \
    \       build_dfs();\n    }\n\n    int idx(int v) const {\n        return dfn[v];\n\
    \    }\n\n    int begin(int v) const {\n        return dfn[v];\n    }\n\n    int\
    \ end(int v) const {\n        return dfn[v] + sub_size[v];\n    }\n\n    template<class\
    \ ADD, class QUERY, class REMOVE>\n    void run_add_remove(ADD add, QUERY query,\
    \ REMOVE remove) const {\n        auto dfs = [&](auto &&self, int v, int p, bool\
    \ keep) -> void {\n            for (int ei = start[v]; ei < start[v + 1]; ++ei)\
    \ {\n                int u = to[ei];\n                if (u == p || u == heavy[v])\
    \ continue;\n                self(self, u, v, false);\n            }\n       \
    \     if (heavy[v] != -1) self(self, heavy[v], v, true);\n            for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n\
    \                if (u == p || u == heavy[v]) continue;\n                for (int\
    \ i = dfn[u]; i < dfn[u] + sub_size[u]; ++i) add(order[i]);\n            }\n \
    \           add(v);\n            query(v);\n            if (!keep) {\n       \
    \         for (int i = dfn[v]; i < dfn[v] + sub_size[v]; ++i) remove(order[i]);\n\
    \            }\n        };\n        dfs(dfs, root, -1, false);\n    }\n\n    template<class\
    \ ADD, class QUERY, class RESET>\n    void run_add_reset(ADD add, QUERY query,\
    \ RESET reset) const {\n        int L = 0, R = 0;\n        for (int i = n - 1;\
    \ i >= 0; --i) {\n            int v = order[i];\n            if (sub_size[v] ==\
    \ 1) {\n                reset();\n                L = R = dfn[v];\n          \
    \  }\n            while (L > dfn[v]) add(order[--L]);\n            while (R <\
    \ dfn[v] + sub_size[v]) add(order[R++]);\n            query(v);\n        }\n \
    \       reset();\n    }\n\nprivate:\n    void build_dfs() {\n        sub_size.assign(n,\
    \ 0);\n        heavy.assign(n, -1);\n        auto dfs_size = [&](auto &&self,\
    \ int v, int p) -> void {\n            sub_size[v] = 1;\n            for (int\
    \ ei = start[v]; ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n\
    \                if (u == p) continue;\n                self(self, u, v);\n  \
    \              sub_size[v] += sub_size[u];\n                if (heavy[v] == -1\
    \ || sub_size[u] > sub_size[heavy[v]]) {\n                    heavy[v] = u;\n\
    \                }\n            }\n        };\n        dfs_size(dfs_size, root,\
    \ -1);\n        dfn.assign(n, 0);\n        order.clear();\n        order.reserve(n);\n\
    \        auto dfs_order = [&](auto &&self, int v, int p) -> void {\n         \
    \   dfn[v] = (int)order.size();\n            order.push_back(v);\n           \
    \ if (heavy[v] != -1) self(self, heavy[v], v);\n            for (int ei = start[v];\
    \ ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n              \
    \  if (u == p || u == heavy[v]) continue;\n                self(self, u, v);\n\
    \            }\n        };\n        dfs_order(dfs_order, root, -1);\n    }\n};\n\
    \n/**\n * @brief DSU on Tree\n */\n"
  code: "struct DSUonTree {\n    int n, root;\n    vector<pair<int, int>> edges;\n\
    \    vector<int> start, to;\n    vector<int> sub_size, heavy;\n    vector<int>\
    \ order, dfn;\n\n    explicit DSUonTree(int n = 0) : n(n), root(0) {\n       \
    \ edges.reserve(max(0, n - 1));\n    }\n\n    template<class G>\n    explicit\
    \ DSUonTree(const vector<vector<G>> &g, int root = 0) : DSUonTree((int)g.size())\
    \ {\n        vector<int> parent(n, -2);\n        vector<int> st(1, root);\n  \
    \      parent[root] = -1;\n        while (!st.empty()) {\n            int v =\
    \ st.back();\n            st.pop_back();\n            for (auto &&u : g[v]) {\n\
    \                if (u == parent[v] || parent[u] != -2) continue;\n          \
    \      parent[u] = v;\n                edges.emplace_back(v, u);\n           \
    \     st.push_back(u);\n            }\n        }\n        build(root);\n    }\n\
    \n    void add_edge(int u, int v) {\n        edges.emplace_back(u, v);\n    }\n\
    \n    void build(int root = 0) {\n        this->root = root;\n        start.assign(n\
    \ + 1, 0);\n        to.assign(edges.size() * 2, 0);\n        for (auto &&[u, v]\
    \ : edges) {\n            ++start[u + 1];\n            ++start[v + 1];\n     \
    \   }\n        for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n       \
    \ auto counter = start;\n        for (auto &&[u, v] : edges) {\n            to[counter[u]++]\
    \ = v;\n            to[counter[v]++] = u;\n        }\n        build_dfs();\n \
    \   }\n\n    int idx(int v) const {\n        return dfn[v];\n    }\n\n    int\
    \ begin(int v) const {\n        return dfn[v];\n    }\n\n    int end(int v) const\
    \ {\n        return dfn[v] + sub_size[v];\n    }\n\n    template<class ADD, class\
    \ QUERY, class REMOVE>\n    void run_add_remove(ADD add, QUERY query, REMOVE remove)\
    \ const {\n        auto dfs = [&](auto &&self, int v, int p, bool keep) -> void\
    \ {\n            for (int ei = start[v]; ei < start[v + 1]; ++ei) {\n        \
    \        int u = to[ei];\n                if (u == p || u == heavy[v]) continue;\n\
    \                self(self, u, v, false);\n            }\n            if (heavy[v]\
    \ != -1) self(self, heavy[v], v, true);\n            for (int ei = start[v]; ei\
    \ < start[v + 1]; ++ei) {\n                int u = to[ei];\n                if\
    \ (u == p || u == heavy[v]) continue;\n                for (int i = dfn[u]; i\
    \ < dfn[u] + sub_size[u]; ++i) add(order[i]);\n            }\n            add(v);\n\
    \            query(v);\n            if (!keep) {\n                for (int i =\
    \ dfn[v]; i < dfn[v] + sub_size[v]; ++i) remove(order[i]);\n            }\n  \
    \      };\n        dfs(dfs, root, -1, false);\n    }\n\n    template<class ADD,\
    \ class QUERY, class RESET>\n    void run_add_reset(ADD add, QUERY query, RESET\
    \ reset) const {\n        int L = 0, R = 0;\n        for (int i = n - 1; i >=\
    \ 0; --i) {\n            int v = order[i];\n            if (sub_size[v] == 1)\
    \ {\n                reset();\n                L = R = dfn[v];\n            }\n\
    \            while (L > dfn[v]) add(order[--L]);\n            while (R < dfn[v]\
    \ + sub_size[v]) add(order[R++]);\n            query(v);\n        }\n        reset();\n\
    \    }\n\nprivate:\n    void build_dfs() {\n        sub_size.assign(n, 0);\n \
    \       heavy.assign(n, -1);\n        auto dfs_size = [&](auto &&self, int v,\
    \ int p) -> void {\n            sub_size[v] = 1;\n            for (int ei = start[v];\
    \ ei < start[v + 1]; ++ei) {\n                int u = to[ei];\n              \
    \  if (u == p) continue;\n                self(self, u, v);\n                sub_size[v]\
    \ += sub_size[u];\n                if (heavy[v] == -1 || sub_size[u] > sub_size[heavy[v]])\
    \ {\n                    heavy[v] = u;\n                }\n            }\n   \
    \     };\n        dfs_size(dfs_size, root, -1);\n        dfn.assign(n, 0);\n \
    \       order.clear();\n        order.reserve(n);\n        auto dfs_order = [&](auto\
    \ &&self, int v, int p) -> void {\n            dfn[v] = (int)order.size();\n \
    \           order.push_back(v);\n            if (heavy[v] != -1) self(self, heavy[v],\
    \ v);\n            for (int ei = start[v]; ei < start[v + 1]; ++ei) {\n      \
    \          int u = to[ei];\n                if (u == p || u == heavy[v]) continue;\n\
    \                self(self, u, v);\n            }\n        };\n        dfs_order(dfs_order,\
    \ root, -1);\n    }\n};\n\n/**\n * @brief DSU on Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/dsu_on_tree.cpp
  requiredBy: []
  timestamp: '2026-04-19 01:08:03+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  - test/yosupo_aplusb_dsu_on_tree.test.cpp
documentation_of: tree/dsu_on_tree.cpp
layout: document
title: DSU on Tree
---
## 説明
各頂点を根とする部分木について、DSU on Tree を使って部分木クエリを処理する。

用途ごとに `add-remove` 型と `add-reset` 型を分けている。

`run_add_remove` は木を辿りながら頂点を追加・削除する。追加・削除は全体で $ O(N \log N) $ 回行われる

`run_add_reset` は　heavy path を 1 単位として状態を使い回す。同じ heavy path 上の頂点は葉から順にクエリが呼ばれ、順次頂点が追加される。別の heavy path へ移るときに `reset()` を呼んで状態を捨てる。

## できること
- `DSUonTree dsu(n)`
  頂点数 `n` の木を作る。`add_edge` のあと `build(root)` を呼ぶ
- `DSUonTree dsu(g, root)`
  根 `root` を持つ木 `g` を前処理する
- `void add_edge(int u, int v)`
  辺 `u` - `v` を追加する
- `void build(int root = 0)`
  追加した辺から根 `root` を持つ木を前処理する
- `int idx(int v)`
  Euler Tour での `v` の位置を返す
- `int begin(int v)`
  部分木 `v` の Euler Tour 区間の左端を返す
- `int end(int v)`
  部分木 `v` の Euler Tour 区間の右端を返す
- `void run_add_remove(add, query, remove)`
  `add(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  片付け時は部分木内の各頂点に `remove(v)` を呼ぶ
- `void run_add_reset(add, query, reset)`
  `add(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  不要になった状態は `reset()` でまとめて捨てる

## 使い方
`add` は頂点 1 個の追加を反映する操作
`query` は「現在 ちょうど頂点 `v` の部分木を表している」タイミングで呼ばれる。

辺を自分で張る場合は次のように使う。

```cpp
DSUonTree dsu(n);
for (auto &&[u, v] : edges) dsu.add_edge(u, v);
dsu.build(0);
```

`add-remove` 型は次のように使う。

```cpp
vector<int> ans(n);
auto add = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto remove = [&](int v) {
    // 頂点 v を削除
};
DSUonTree dsu(g, 0);
dsu.run_add_remove(add, query, remove);
```

`add-reset` 型は次のように使う。
`reset()` は現在のデータ構造全体を初期状態へ戻す。
touch した位置だけを戻すか、世代管理でまとめて無効化する形を想定している。

```cpp
vector<int> ans(n);
auto add = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto reset = [&]() {
    // 全体を初期状態へ戻す
};

DSUonTree dsu(g, 0);
dsu.run_add_reset(add, query, reset);
```

