---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
    title: test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "\u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)"
    links: []
  bundledCode: "#line 1 \"tree/tree_hash.cpp\"\nstruct TreeHash {\n    int n;\n  \
    \  vector<vector<int>> g;\n    vector<int> parent, order, hash_id;\n    int kind_count;\n\
    \n    explicit TreeHash(int n)\n        : n(n), g(n), parent(n, -1), hash_id(n,\
    \ -1), kind_count(0) {}\n\n    void add_edge(int u, int v) {\n        g[u].push_back(v);\n\
    \        g[v].push_back(u);\n    }\n\n    vector<int> build(int root = 0) {\n\
    \        order.clear();\n        order.reserve(n);\n        parent.assign(n, -1);\n\
    \        vector<int> st(1, root);\n        parent[root] = root;\n        while\
    \ (!st.empty()) {\n            int v = st.back();\n            st.pop_back();\n\
    \            order.push_back(v);\n            for (int to : g[v]) {\n        \
    \        if (to == parent[v]) continue;\n                parent[to] = v;\n   \
    \             st.push_back(to);\n            }\n        }\n\n        map<vector<int>,\
    \ int> ids;\n        for (int i = n - 1; i >= 0; --i) {\n            int v = order[i];\n\
    \            vector<int> ch;\n            ch.reserve(g[v].size() - (v != root));\n\
    \            for (int to : g[v]) {\n                if (to == parent[v]) continue;\n\
    \                ch.push_back(hash_id[to]);\n            }\n            sort(ch.begin(),\
    \ ch.end());\n            auto [it, inserted] = ids.emplace(ch, (int)ids.size());\n\
    \            hash_id[v] = it->second;\n        }\n        kind_count = ids.size();\n\
    \        return hash_id;\n    }\n\n    int operator[](int v) const {\n       \
    \ return hash_id[v];\n    }\n\n    int kinds() const {\n        return kind_count;\n\
    \    }\n};\n\n/**\n * @brief \u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)\n */\n"
  code: "struct TreeHash {\n    int n;\n    vector<vector<int>> g;\n    vector<int>\
    \ parent, order, hash_id;\n    int kind_count;\n\n    explicit TreeHash(int n)\n\
    \        : n(n), g(n), parent(n, -1), hash_id(n, -1), kind_count(0) {}\n\n   \
    \ void add_edge(int u, int v) {\n        g[u].push_back(v);\n        g[v].push_back(u);\n\
    \    }\n\n    vector<int> build(int root = 0) {\n        order.clear();\n    \
    \    order.reserve(n);\n        parent.assign(n, -1);\n        vector<int> st(1,\
    \ root);\n        parent[root] = root;\n        while (!st.empty()) {\n      \
    \      int v = st.back();\n            st.pop_back();\n            order.push_back(v);\n\
    \            for (int to : g[v]) {\n                if (to == parent[v]) continue;\n\
    \                parent[to] = v;\n                st.push_back(to);\n        \
    \    }\n        }\n\n        map<vector<int>, int> ids;\n        for (int i =\
    \ n - 1; i >= 0; --i) {\n            int v = order[i];\n            vector<int>\
    \ ch;\n            ch.reserve(g[v].size() - (v != root));\n            for (int\
    \ to : g[v]) {\n                if (to == parent[v]) continue;\n             \
    \   ch.push_back(hash_id[to]);\n            }\n            sort(ch.begin(), ch.end());\n\
    \            auto [it, inserted] = ids.emplace(ch, (int)ids.size());\n       \
    \     hash_id[v] = it->second;\n        }\n        kind_count = ids.size();\n\
    \        return hash_id;\n    }\n\n    int operator[](int v) const {\n       \
    \ return hash_id[v];\n    }\n\n    int kinds() const {\n        return kind_count;\n\
    \    }\n};\n\n/**\n * @brief \u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/tree_hash.cpp
  requiredBy: []
  timestamp: '2026-03-12 19:34:31+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_rooted_tree_isomorphism_classification_tree_hash.test.cpp
date: 2026-03-12
documentation_of: tree/tree_hash.cpp
layout: document
tags: "\u6728"
title: "\u6728\u30CF\u30C3\u30B7\u30E5(Tree Hash)"
---

## 説明
根付き木の各部分木を同型性で分類する。
各頂点 `v` について、その部分木の同型類 id を返す。

## できること
- `TreeHash th(n)`
  `n` 頂点の木を作る
- `void add_edge(int u, int v)`
  無向辺を追加する
- `vector<int> build(int root = 0)`
  `root` を根として部分木 id を構築して返す
- `int th[v]`
  頂点 `v` の部分木 id を返す
- `int kinds()`
  異なる部分木の個数を返す

## 使い方
辺をすべて追加してから `build(root)` を呼ぶ。
返る id は同じ `build` の中でのみ意味を持ち、`id[v] == id[u]` のときに限って
`v` と `u` の部分木は同型である。

```cpp
TreeHash th(n);
for (auto [u, v] : edges) th.add_edge(u, v);
auto id = th.build(0);
```

## 実装上の補足
- 子部分木の id をソートして辞書化することで canonical id を付ける
- 計算量はおおむね $O\left(\sum_v \deg(v)\log \deg(v)\right)$
