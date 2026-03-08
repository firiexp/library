---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_cartesian_tree.test.cpp
    title: test/yosupo_cartesian_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Cartesian Tree
    links: []
  bundledCode: "#line 1 \"tree/cartesian_tree.cpp\"\ntemplate<class T>\npair<vector<vector<int>>,\
    \ int> CartesianTree(const vector<T> &a) {\n    int n = a.size();\n    vector<vector<int>>\
    \ g(n);\n    vector<int> parent(n, -1), st;\n    st.reserve(n);\n    for (int\
    \ i = 0; i < n; ++i) {\n        int last = -1;\n        while (!st.empty() &&\
    \ a[i] < a[st.back()]) {\n            last = st.back();\n            st.pop_back();\n\
    \        }\n        if (last != -1) parent[last] = i;\n        if (!st.empty())\
    \ parent[i] = st.back();\n        st.push_back(i);\n    }\n    int root = -1;\n\
    \    for (int i = 0; i < n; ++i) {\n        if (parent[i] == -1) root = i;\n \
    \       else g[parent[i]].push_back(i);\n    }\n    return {g, root};\n}\n\n/**\n\
    \ * @brief Cartesian Tree\n */\n"
  code: "template<class T>\npair<vector<vector<int>>, int> CartesianTree(const vector<T>\
    \ &a) {\n    int n = a.size();\n    vector<vector<int>> g(n);\n    vector<int>\
    \ parent(n, -1), st;\n    st.reserve(n);\n    for (int i = 0; i < n; ++i) {\n\
    \        int last = -1;\n        while (!st.empty() && a[i] < a[st.back()]) {\n\
    \            last = st.back();\n            st.pop_back();\n        }\n      \
    \  if (last != -1) parent[last] = i;\n        if (!st.empty()) parent[i] = st.back();\n\
    \        st.push_back(i);\n    }\n    int root = -1;\n    for (int i = 0; i <\
    \ n; ++i) {\n        if (parent[i] == -1) root = i;\n        else g[parent[i]].push_back(i);\n\
    \    }\n    return {g, root};\n}\n\n/**\n * @brief Cartesian Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/cartesian_tree.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_cartesian_tree.test.cpp
documentation_of: tree/cartesian_tree.cpp
layout: document
title: Cartesian Tree
---
## 説明
数列から Cartesian tree を `O(N)` で構築する。
各区間の最小値の位置を根にした木で、同じ値があるときは左にある添字を優先する。

## できること
- `auto [g, root] = CartesianTree(a)`
  配列 `a` から木の子リスト `g` と根 `root` を返す

## 使い方
`g[v]` には頂点 `v` の子が入る。
親配列が欲しいときは `g` をなめて復元する。

```cpp
vector<int> a = {3, 1, 4, 1, 5};
auto [g, root] = CartesianTree(a);

vector<int> parent(a.size(), -1);
parent[root] = root;
for (int v = 0; v < (int)a.size(); ++v) {
    for (auto &&u : g[v]) parent[u] = v;
}
```

## 実装上の補足
スタックを使って最小 Cartesian tree を構築する。
`a[i] < a[j]` のときだけ pop するので、`a[i] == a[j]` なら小さい添字が祖先側に残る。
