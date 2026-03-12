---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_minimum_spanning_tree.test.cpp
    title: test/yosupo_minimum_spanning_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Kruskal\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/kruskal.cpp\"\ntemplate <class T>\nstruct edge {\n\
    \    int from, to, idx;\n    T cost;\n\n    edge(int from, int to, T cost, int\
    \ idx = -1) : from(from), to(to), idx(idx), cost(cost) {}\n};\n\nclass KruskalUnionFind\
    \ {\n    vector<int> p;\n\npublic:\n    explicit KruskalUnionFind(int n) : p(n,\
    \ -1) {}\n\n    int root(int x) {\n        if (p[x] < 0) return x;\n        return\
    \ p[x] = root(p[x]);\n    }\n\n    bool unite(int a, int b) {\n        a = root(a);\n\
    \        b = root(b);\n        if (a == b) return false;\n        if (p[a] > p[b])\
    \ swap(a, b);\n        p[a] += p[b];\n        p[b] = a;\n        return true;\n\
    \    }\n};\n\ntemplate <class T>\nstruct KruskalResult {\n    bool exists;\n \
    \   T cost;\n    vector<int> edge_id;\n};\n\ntemplate <class T>\nKruskalResult<T>\
    \ kruskal(vector<edge<T>> edges, int n) {\n    for (int i = 0; i < (int)edges.size();\
    \ ++i) {\n        if (edges[i].idx == -1) edges[i].idx = i;\n    }\n    sort(edges.begin(),\
    \ edges.end(), [](const edge<T> &a, const edge<T> &b) {\n        if (a.cost !=\
    \ b.cost) return a.cost < b.cost;\n        return a.idx < b.idx;\n    });\n\n\
    \    KruskalUnionFind uf(n);\n    T cost = T(0);\n    vector<int> edge_id;\n \
    \   edge_id.reserve(max(0, n - 1));\n    for (auto &&e : edges) {\n        if\
    \ (!uf.unite(e.from, e.to)) continue;\n        cost += e.cost;\n        edge_id.push_back(e.idx);\n\
    \    }\n    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};\n\
    \    return {true, cost, edge_id};\n}\n\n/**\n * @brief Kruskal\u6CD5\n */\n"
  code: "template <class T>\nstruct edge {\n    int from, to, idx;\n    T cost;\n\n\
    \    edge(int from, int to, T cost, int idx = -1) : from(from), to(to), idx(idx),\
    \ cost(cost) {}\n};\n\nclass KruskalUnionFind {\n    vector<int> p;\n\npublic:\n\
    \    explicit KruskalUnionFind(int n) : p(n, -1) {}\n\n    int root(int x) {\n\
    \        if (p[x] < 0) return x;\n        return p[x] = root(p[x]);\n    }\n\n\
    \    bool unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n\
    \        if (a == b) return false;\n        if (p[a] > p[b]) swap(a, b);\n   \
    \     p[a] += p[b];\n        p[b] = a;\n        return true;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct KruskalResult {\n    bool exists;\n    T cost;\n    vector<int>\
    \ edge_id;\n};\n\ntemplate <class T>\nKruskalResult<T> kruskal(vector<edge<T>>\
    \ edges, int n) {\n    for (int i = 0; i < (int)edges.size(); ++i) {\n       \
    \ if (edges[i].idx == -1) edges[i].idx = i;\n    }\n    sort(edges.begin(), edges.end(),\
    \ [](const edge<T> &a, const edge<T> &b) {\n        if (a.cost != b.cost) return\
    \ a.cost < b.cost;\n        return a.idx < b.idx;\n    });\n\n    KruskalUnionFind\
    \ uf(n);\n    T cost = T(0);\n    vector<int> edge_id;\n    edge_id.reserve(max(0,\
    \ n - 1));\n    for (auto &&e : edges) {\n        if (!uf.unite(e.from, e.to))\
    \ continue;\n        cost += e.cost;\n        edge_id.push_back(e.idx);\n    }\n\
    \    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};\n   \
    \ return {true, cost, edge_id};\n}\n\n/**\n * @brief Kruskal\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/kruskal.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_minimum_spanning_tree.test.cpp
documentation_of: graph/kruskal.cpp
layout: document
title: "Kruskal\u6CD5"
---
## 説明
無向重み付きグラフの最小全域木を求める。
辺を重み順にソートし、閉路にならないものだけ採用する。計算量は $O(M log M)$。

## できること
- `edge<T>(int from, int to, T cost, int idx = -1)`
  無向辺を作る。`idx = -1` のときは入力順の番号を自動で振る
- `KruskalResult<T> kruskal(vector<edge<T>> edges, int n)`
  頂点数 `n` のグラフに対する最小全域木を求める。非連結なら `exists = false`

## 使い方
`edge_id` には採用した辺の番号が入る。Yosupo `minimum_spanning_tree` の出力にそのまま使える。

```cpp
vector<edge<long long>> edges;
for (int i = 0; i < m; ++i) {
    int u, v;
    long long w;
    edges.emplace_back(u, v, w, i);
}

auto res = kruskal(edges, n);
if (res.exists) {
    long long cost = res.cost;
    vector<int> ids = res.edge_id;
}
```

## 実装上の補足
`idx` を明示しない場合でも、`kruskal` 内で入力順の番号を付ける。
返る `edge_id` の順序は、辺を採用した順である。
