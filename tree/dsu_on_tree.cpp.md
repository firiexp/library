---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
    title: test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/dsu_on_tree.md
    document_title: DSU on Tree
    links: []
  bundledCode: "#line 1 \"tree/dsu_on_tree.cpp\"\ntemplate<class G>\nstruct DSUonTree\
    \ {\n    G &g;\n    int n, root, ord;\n    vector<int> sub_size, euler, down,\
    \ up;\n\n    explicit DSUonTree(G &g, int root = 0)\n        : g(g), n(g.size()),\
    \ root(root), ord(0),\n          sub_size(n), euler(n), down(n), up(n) {\n   \
    \     dfs_sz(root, -1);\n        dfs_euler(root, -1);\n    }\n\n    int idx(int\
    \ v) const {\n        return down[v];\n    }\n\n    int begin(int v) const {\n\
    \        return down[v];\n    }\n\n    int end(int v) const {\n        return\
    \ up[v];\n    }\n\n    template<class UPDATE, class QUERY, class CLEAR, class\
    \ RESET>\n    void run(UPDATE update, QUERY query, CLEAR clear, RESET reset) {\n\
    \        auto dfs = [&](auto &&self, int v, int p, bool keep) -> void {\n    \
    \        int heavy = (g[v].empty() || g[v][0] == p ? -1 : g[v][0]);\n        \
    \    for (auto &&u : g[v]) {\n                if (u == p || u == heavy) continue;\n\
    \                self(self, u, v, false);\n            }\n            if (heavy\
    \ != -1) self(self, heavy, v, true);\n            for (auto &&u : g[v]) {\n  \
    \              if (u == p || u == heavy) continue;\n                for (int i\
    \ = down[u]; i < up[u]; ++i) update(euler[i]);\n            }\n            update(v);\n\
    \            query(v);\n            if (!keep) {\n                for (int i =\
    \ down[v]; i < up[v]; ++i) clear(euler[i]);\n                reset();\n      \
    \      }\n        };\n        dfs(dfs, root, -1, false);\n    }\n\nprivate:\n\
    \    void dfs_sz(int v, int p) {\n        sub_size[v] = 1;\n        int heavy_idx\
    \ = -1;\n        for (int i = 0; i < (int)g[v].size(); ++i) {\n            int\
    \ u = g[v][i];\n            if (u == p) continue;\n            dfs_sz(u, v);\n\
    \            sub_size[v] += sub_size[u];\n            if (heavy_idx == -1 || sub_size[u]\
    \ > sub_size[g[v][heavy_idx]]) {\n                heavy_idx = i;\n           \
    \ }\n        }\n        if (heavy_idx > 0) swap(g[v][0], g[v][heavy_idx]);\n \
    \   }\n\n    void dfs_euler(int v, int p) {\n        down[v] = ord;\n        euler[ord++]\
    \ = v;\n        for (auto &&u : g[v]) {\n            if (u == p) continue;\n \
    \           dfs_euler(u, v);\n        }\n        up[v] = ord;\n    }\n};\n\n/**\n\
    \ * @brief DSU on Tree\n * @docs _md/dsu_on_tree.md\n */\n"
  code: "template<class G>\nstruct DSUonTree {\n    G &g;\n    int n, root, ord;\n\
    \    vector<int> sub_size, euler, down, up;\n\n    explicit DSUonTree(G &g, int\
    \ root = 0)\n        : g(g), n(g.size()), root(root), ord(0),\n          sub_size(n),\
    \ euler(n), down(n), up(n) {\n        dfs_sz(root, -1);\n        dfs_euler(root,\
    \ -1);\n    }\n\n    int idx(int v) const {\n        return down[v];\n    }\n\n\
    \    int begin(int v) const {\n        return down[v];\n    }\n\n    int end(int\
    \ v) const {\n        return up[v];\n    }\n\n    template<class UPDATE, class\
    \ QUERY, class CLEAR, class RESET>\n    void run(UPDATE update, QUERY query, CLEAR\
    \ clear, RESET reset) {\n        auto dfs = [&](auto &&self, int v, int p, bool\
    \ keep) -> void {\n            int heavy = (g[v].empty() || g[v][0] == p ? -1\
    \ : g[v][0]);\n            for (auto &&u : g[v]) {\n                if (u == p\
    \ || u == heavy) continue;\n                self(self, u, v, false);\n       \
    \     }\n            if (heavy != -1) self(self, heavy, v, true);\n          \
    \  for (auto &&u : g[v]) {\n                if (u == p || u == heavy) continue;\n\
    \                for (int i = down[u]; i < up[u]; ++i) update(euler[i]);\n   \
    \         }\n            update(v);\n            query(v);\n            if (!keep)\
    \ {\n                for (int i = down[v]; i < up[v]; ++i) clear(euler[i]);\n\
    \                reset();\n            }\n        };\n        dfs(dfs, root, -1,\
    \ false);\n    }\n\nprivate:\n    void dfs_sz(int v, int p) {\n        sub_size[v]\
    \ = 1;\n        int heavy_idx = -1;\n        for (int i = 0; i < (int)g[v].size();\
    \ ++i) {\n            int u = g[v][i];\n            if (u == p) continue;\n  \
    \          dfs_sz(u, v);\n            sub_size[v] += sub_size[u];\n          \
    \  if (heavy_idx == -1 || sub_size[u] > sub_size[g[v][heavy_idx]]) {\n       \
    \         heavy_idx = i;\n            }\n        }\n        if (heavy_idx > 0)\
    \ swap(g[v][0], g[v][heavy_idx]);\n    }\n\n    void dfs_euler(int v, int p) {\n\
    \        down[v] = ord;\n        euler[ord++] = v;\n        for (auto &&u : g[v])\
    \ {\n            if (u == p) continue;\n            dfs_euler(u, v);\n       \
    \ }\n        up[v] = ord;\n    }\n};\n\n/**\n * @brief DSU on Tree\n * @docs _md/dsu_on_tree.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/dsu_on_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 14:46:28+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_vertex_add_subtree_sum_dsu_on_tree.test.cpp
documentation_of: tree/dsu_on_tree.cpp
layout: document
redirect_from:
- /library/tree/dsu_on_tree.cpp
- /library/tree/dsu_on_tree.cpp.html
title: DSU on Tree
---
## 説明
各頂点を根とする部分木について、追加・削除可能なデータ構造を使ってクエリを処理する。
全体計算量は、`update` と `clear` が `O(1)` なら `O(N log N)`。

## できること
- `DSUonTree<G> dsu(g, root)`
  根 `root` を持つ木 `g` を前処理する
- `int idx(int v)`
  Euler Tour での `v` の位置を返す
- `int begin(int v)`
  部分木 `v` の Euler Tour 区間の左端を返す
- `int end(int v)`
  部分木 `v` の Euler Tour 区間の右端を返す
- `void run(update, query, clear, reset)`
  `update(v)` で頂点を追加し、`query(v)` で部分木 `v` の答えを確定する
  `keep == false` の片付け時には、部分木内の各頂点に `clear(v)` を呼んだあと `reset()` を呼ぶ

## 使い方
`update` は頂点 1 個を現在のデータ構造へ反映する。
`query` は「現在のデータ構造がちょうど頂点 `v` の部分木を表している」タイミングで呼ばれる。
削除が重い場合は `clear` を空にして、`reset` で全体を初期化してもよい。

```cpp
vector<int> ans(n);
auto update = [&](int v) {
    // 頂点 v を追加
};
auto query = [&](int v) {
    // 部分木 v の答えを記録
};
auto clear = [&](int v) {
    // 頂点 v を削除
};
auto reset = [&]() {
    // 全体を初期状態へ戻す
};

DSUonTree dsu(g, 0);
dsu.run(update, query, clear, reset);
```

## 実装上の補足
`g[v][0]` が heavy child になるように隣接順を並べ替えるので、`g` は破壊的に変更される。
