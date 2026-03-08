---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_jump_on_tree.test.cpp
    title: test/yosupo_jump_on_tree.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/jump_on_tree.md
    document_title: Jump on Tree
    links: []
  bundledCode: "#line 1 \"tree/jump_on_tree.cpp\"\nclass JumpOnTree {\n    int logn;\n\
    \    vector<vector<int>> up;\n\npublic:\n    int n;\n    vector<vector<int>> G;\n\
    \    vector<int> depth;\n\n    explicit JumpOnTree(int n) : logn(0), n(n), G(n),\
    \ depth(n, -1) {}\n\n    void add_edge(int u, int v) {\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n\n    void build(int root = 0) {\n    \
    \    logn = 1;\n        while ((1 << logn) <= n) ++logn;\n        up.assign(logn,\
    \ vector<int>(n, -1));\n        vector<int> st = {root};\n        depth[root]\
    \ = 0;\n        while (!st.empty()) {\n            int v = st.back();\n      \
    \      st.pop_back();\n            for (int to : G[v]) {\n                if (to\
    \ == up[0][v]) continue;\n                up[0][to] = v;\n                depth[to]\
    \ = depth[v] + 1;\n                st.push_back(to);\n            }\n        }\n\
    \        for (int k = 0; k + 1 < logn; ++k) {\n            for (int v = 0; v <\
    \ n; ++v) {\n                int p = up[k][v];\n                up[k + 1][v] =\
    \ (p == -1 ? -1 : up[k][p]);\n            }\n        }\n    }\n\n    int ancestor(int\
    \ v, int k) const {\n        if (k > depth[v]) return -1;\n        for (int i\
    \ = 0; i < logn; ++i) {\n            if (k >> i & 1) v = up[i][v];\n        }\n\
    \        return v;\n    }\n\n    int lca(int u, int v) const {\n        if (depth[u]\
    \ < depth[v]) swap(u, v);\n        u = ancestor(u, depth[u] - depth[v]);\n   \
    \     if (u == v) return u;\n        for (int k = logn - 1; k >= 0; --k) {\n \
    \           if (up[k][u] == up[k][v]) continue;\n            u = up[k][u];\n \
    \           v = up[k][v];\n        }\n        return up[0][u];\n    }\n\n    int\
    \ dist(int u, int v) const {\n        int w = lca(u, v);\n        return depth[u]\
    \ + depth[v] - 2 * depth[w];\n    }\n\n    int jump(int s, int t, int k) const\
    \ {\n        int w = lca(s, t);\n        int a = depth[s] - depth[w];\n      \
    \  int b = depth[t] - depth[w];\n        if (k > a + b) return -1;\n        if\
    \ (k <= a) return ancestor(s, k);\n        return ancestor(t, a + b - k);\n  \
    \  }\n};\n\n/**\n * @brief Jump on Tree\n * @docs _md/jump_on_tree.md\n */\n"
  code: "class JumpOnTree {\n    int logn;\n    vector<vector<int>> up;\n\npublic:\n\
    \    int n;\n    vector<vector<int>> G;\n    vector<int> depth;\n\n    explicit\
    \ JumpOnTree(int n) : logn(0), n(n), G(n), depth(n, -1) {}\n\n    void add_edge(int\
    \ u, int v) {\n        G[u].emplace_back(v);\n        G[v].emplace_back(u);\n\
    \    }\n\n    void build(int root = 0) {\n        logn = 1;\n        while ((1\
    \ << logn) <= n) ++logn;\n        up.assign(logn, vector<int>(n, -1));\n     \
    \   vector<int> st = {root};\n        depth[root] = 0;\n        while (!st.empty())\
    \ {\n            int v = st.back();\n            st.pop_back();\n            for\
    \ (int to : G[v]) {\n                if (to == up[0][v]) continue;\n         \
    \       up[0][to] = v;\n                depth[to] = depth[v] + 1;\n          \
    \      st.push_back(to);\n            }\n        }\n        for (int k = 0; k\
    \ + 1 < logn; ++k) {\n            for (int v = 0; v < n; ++v) {\n            \
    \    int p = up[k][v];\n                up[k + 1][v] = (p == -1 ? -1 : up[k][p]);\n\
    \            }\n        }\n    }\n\n    int ancestor(int v, int k) const {\n \
    \       if (k > depth[v]) return -1;\n        for (int i = 0; i < logn; ++i) {\n\
    \            if (k >> i & 1) v = up[i][v];\n        }\n        return v;\n   \
    \ }\n\n    int lca(int u, int v) const {\n        if (depth[u] < depth[v]) swap(u,\
    \ v);\n        u = ancestor(u, depth[u] - depth[v]);\n        if (u == v) return\
    \ u;\n        for (int k = logn - 1; k >= 0; --k) {\n            if (up[k][u]\
    \ == up[k][v]) continue;\n            u = up[k][u];\n            v = up[k][v];\n\
    \        }\n        return up[0][u];\n    }\n\n    int dist(int u, int v) const\
    \ {\n        int w = lca(u, v);\n        return depth[u] + depth[v] - 2 * depth[w];\n\
    \    }\n\n    int jump(int s, int t, int k) const {\n        int w = lca(s, t);\n\
    \        int a = depth[s] - depth[w];\n        int b = depth[t] - depth[w];\n\
    \        if (k > a + b) return -1;\n        if (k <= a) return ancestor(s, k);\n\
    \        return ancestor(t, a + b - k);\n    }\n};\n\n/**\n * @brief Jump on Tree\n\
    \ * @docs _md/jump_on_tree.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/jump_on_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 19:26:24+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_jump_on_tree.test.cpp
documentation_of: tree/jump_on_tree.cpp
layout: document
redirect_from:
- /library/tree/jump_on_tree.cpp
- /library/tree/jump_on_tree.cpp.html
title: Jump on Tree
---
---
layout: post
title: Jump on Tree
date: 2026-03-08
category: 木
tags: 木
---

## 説明
木上の `k` 個先の頂点、LCA、祖先を doubling で求める。
前処理 `O(N log N)`、各クエリ `O(log N)`。

## できること
- `JumpOnTree jt(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  根 `root` で前処理する
- `int ancestor(int v, int k)`
  `v` の `k` 個上の祖先を返す。存在しなければ `-1`
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す
- `int dist(int u, int v)`
  `u` と `v` の距離を返す
- `int jump(int s, int t, int k)`
  `s` から `t` への最短路の `k` 番目の頂点を返す。存在しなければ `-1`

## 使い方
辺を張って `build(root)` を 1 回呼び、その後に `jump(s, t, k)` や `lca(u, v)` を使う。

```cpp
JumpOnTree jt(n);
for (auto [u, v] : edges) {
    jt.add_edge(u, v);
}
jt.build(0);

int x = jt.jump(s, t, k);
```

## 実装上の補足
`jump(s, t, k)` は `s -> lca(s, t)` 側と `lca(s, t) -> t` 側を分けて処理する。
