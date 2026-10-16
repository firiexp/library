---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_k_shortest_walk.test.cpp
    title: test/yosupo_aplusb_k_shortest_walk.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_k_shortest_walk.test.cpp
    title: test/yosupo_k_shortest_walk.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "K\u756A\u76EE\u306E\u6700\u77ED\u30A6\u30A9\u30FC\u30AF"
    links: []
  bundledCode: "#line 1 \"graph/k_shortest_walk.cpp\"\n\n\n\n#line 1 \"graph/edge.cpp\"\
    \n\n\n\ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\
    \n    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const { return to; }\n};\n\n\n#line 5 \"graph/k_shortest_walk.cpp\"\n\n\
    template <class T>\nvector<T> k_shortest_walk(int s, int t, int k, const vector<vector<edge<T>>>\
    \ &g) {\n    int n = (int)g.size();\n    assert(0 <= s && s < n && 0 <= t && t\
    \ < n && k >= 0);\n    if (k == 0) return {};\n    vector<vector<pair<int, int>>>\
    \ reverse_graph(n);\n    size_t m = 0;\n    for (int v = 0; v < n; ++v) {\n  \
    \      m += g[v].size();\n        for (int i = 0; i < (int)g[v].size(); ++i) {\n\
    \            const auto &e = g[v][i];\n            assert(0 <= e.to && e.to <\
    \ n && e.cost >= 0);\n            reverse_graph[e.to].emplace_back(v, i);\n  \
    \      }\n    }\n    vector<T> dist(n);\n    vector<char> reached(n);\n    vector<int>\
    \ parent_edge(n, -1), order;\n    priority_queue<pair<T, int>, vector<pair<T,\
    \ int>>, greater<>> queue;\n    reached[t] = true;\n    queue.emplace(T(0), t);\n\
    \    while (!queue.empty()) {\n        auto [value, v] = queue.top();\n      \
    \  queue.pop();\n        if (value != dist[v]) continue;\n        order.push_back(v);\n\
    \        for (auto [u, i] : reverse_graph[v]) {\n            T next = value +\
    \ g[u][i].cost;\n            if (reached[u] && dist[u] <= next) continue;\n  \
    \          reached[u] = true;\n            dist[u] = next;\n            parent_edge[u]\
    \ = i;\n            queue.emplace(next, u);\n        }\n    }\n    if (!reached[s])\
    \ return {};\n    vector<T> result{dist[s]};\n    if (k == 1) return result;\n\
    \n    struct Node { T delta; int to, left, right, rank; };\n    vector<Node> nodes{\
    \ { T(0), -1, 0, 0, 0 } };\n    nodes.reserve(m + 1);\n    auto meld = [&](auto\
    \ &&self, int a, int b, bool persistent) -> int {\n        if (!a) return b;\n\
    \        if (!b) return a;\n        if (nodes[b].delta < nodes[a].delta) swap(a,\
    \ b);\n        if (persistent) {\n            Node copy = nodes[a];\n        \
    \    a = (int)nodes.size();\n            nodes.push_back(copy);\n        }\n \
    \       int right = self(self, nodes[a].right, b, persistent);\n        nodes[a].right\
    \ = right;\n        if (nodes[nodes[a].left].rank < nodes[right].rank) swap(nodes[a].left,\
    \ nodes[a].right);\n        nodes[a].rank = nodes[nodes[a].right].rank + 1;\n\
    \        return a;\n    };\n    vector<int> roots(n);\n    for (int v : order)\
    \ {\n        int heap = 0;\n        for (int i = 0; i < (int)g[v].size(); ++i)\
    \ {\n            const auto &e = g[v][i];\n            if (i == parent_edge[v]\
    \ || !reached[e.to]) continue;\n            int id = (int)nodes.size();\n    \
    \        nodes.push_back({e.cost + dist[e.to] - dist[v], e.to, 0, 0, 1});\n  \
    \          heap = meld(meld, heap, id, false);\n        }\n        if (parent_edge[v]\
    \ != -1) {\n            int parent = g[v][parent_edge[v]].to;\n            heap\
    \ = meld(meld, heap, roots[parent], true);\n        }\n        roots[v] = heap;\n\
    \    }\n    if (roots[s]) queue.emplace(dist[s] + nodes[roots[s]].delta, roots[s]);\n\
    \    while (!queue.empty() && (int)result.size() < k) {\n        auto [value,\
    \ id] = queue.top();\n        queue.pop();\n        result.push_back(value);\n\
    \        if ((int)result.size() == k) break;\n        const auto &node = nodes[id];\n\
    \        for (int child : {node.left, node.right}) {\n            if (child) queue.emplace(value\
    \ - node.delta + nodes[child].delta, child);\n        }\n        int next = roots[node.to];\n\
    \        if (next) queue.emplace(value + nodes[next].delta, next);\n    }\n  \
    \  return result;\n}\n\n\n\n/**\n * @brief K\u756A\u76EE\u306E\u6700\u77ED\u30A6\
    \u30A9\u30FC\u30AF\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_K_SHORTEST_WALK_CPP\n#define FIRIEXP_LIBRARY_GRAPH_K_SHORTEST_WALK_CPP\n\
    \n#include \"edge.cpp\"\n\ntemplate <class T>\nvector<T> k_shortest_walk(int s,\
    \ int t, int k, const vector<vector<edge<T>>> &g) {\n    int n = (int)g.size();\n\
    \    assert(0 <= s && s < n && 0 <= t && t < n && k >= 0);\n    if (k == 0) return\
    \ {};\n    vector<vector<pair<int, int>>> reverse_graph(n);\n    size_t m = 0;\n\
    \    for (int v = 0; v < n; ++v) {\n        m += g[v].size();\n        for (int\
    \ i = 0; i < (int)g[v].size(); ++i) {\n            const auto &e = g[v][i];\n\
    \            assert(0 <= e.to && e.to < n && e.cost >= 0);\n            reverse_graph[e.to].emplace_back(v,\
    \ i);\n        }\n    }\n    vector<T> dist(n);\n    vector<char> reached(n);\n\
    \    vector<int> parent_edge(n, -1), order;\n    priority_queue<pair<T, int>,\
    \ vector<pair<T, int>>, greater<>> queue;\n    reached[t] = true;\n    queue.emplace(T(0),\
    \ t);\n    while (!queue.empty()) {\n        auto [value, v] = queue.top();\n\
    \        queue.pop();\n        if (value != dist[v]) continue;\n        order.push_back(v);\n\
    \        for (auto [u, i] : reverse_graph[v]) {\n            T next = value +\
    \ g[u][i].cost;\n            if (reached[u] && dist[u] <= next) continue;\n  \
    \          reached[u] = true;\n            dist[u] = next;\n            parent_edge[u]\
    \ = i;\n            queue.emplace(next, u);\n        }\n    }\n    if (!reached[s])\
    \ return {};\n    vector<T> result{dist[s]};\n    if (k == 1) return result;\n\
    \n    struct Node { T delta; int to, left, right, rank; };\n    vector<Node> nodes{\
    \ { T(0), -1, 0, 0, 0 } };\n    nodes.reserve(m + 1);\n    auto meld = [&](auto\
    \ &&self, int a, int b, bool persistent) -> int {\n        if (!a) return b;\n\
    \        if (!b) return a;\n        if (nodes[b].delta < nodes[a].delta) swap(a,\
    \ b);\n        if (persistent) {\n            Node copy = nodes[a];\n        \
    \    a = (int)nodes.size();\n            nodes.push_back(copy);\n        }\n \
    \       int right = self(self, nodes[a].right, b, persistent);\n        nodes[a].right\
    \ = right;\n        if (nodes[nodes[a].left].rank < nodes[right].rank) swap(nodes[a].left,\
    \ nodes[a].right);\n        nodes[a].rank = nodes[nodes[a].right].rank + 1;\n\
    \        return a;\n    };\n    vector<int> roots(n);\n    for (int v : order)\
    \ {\n        int heap = 0;\n        for (int i = 0; i < (int)g[v].size(); ++i)\
    \ {\n            const auto &e = g[v][i];\n            if (i == parent_edge[v]\
    \ || !reached[e.to]) continue;\n            int id = (int)nodes.size();\n    \
    \        nodes.push_back({e.cost + dist[e.to] - dist[v], e.to, 0, 0, 1});\n  \
    \          heap = meld(meld, heap, id, false);\n        }\n        if (parent_edge[v]\
    \ != -1) {\n            int parent = g[v][parent_edge[v]].to;\n            heap\
    \ = meld(meld, heap, roots[parent], true);\n        }\n        roots[v] = heap;\n\
    \    }\n    if (roots[s]) queue.emplace(dist[s] + nodes[roots[s]].delta, roots[s]);\n\
    \    while (!queue.empty() && (int)result.size() < k) {\n        auto [value,\
    \ id] = queue.top();\n        queue.pop();\n        result.push_back(value);\n\
    \        if ((int)result.size() == k) break;\n        const auto &node = nodes[id];\n\
    \        for (int child : {node.left, node.right}) {\n            if (child) queue.emplace(value\
    \ - node.delta + nodes[child].delta, child);\n        }\n        int next = roots[node.to];\n\
    \        if (next) queue.emplace(value + nodes[next].delta, next);\n    }\n  \
    \  return result;\n}\n\n#endif\n\n/**\n * @brief K\u756A\u76EE\u306E\u6700\u77ED\
    \u30A6\u30A9\u30FC\u30AF\n */\n"
  dependsOn:
  - graph/edge.cpp
  isVerificationFile: false
  path: graph/k_shortest_walk.cpp
  requiredBy: []
  timestamp: '2026-10-17 02:52:31+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_k_shortest_walk.test.cpp
  - test/yosupo_k_shortest_walk.test.cpp
documentation_of: graph/k_shortest_walk.cpp
layout: document
title: "K\u756A\u76EE\u306E\u6700\u77ED\u30A6\u30A9\u30FC\u30AF"
---

## 説明
非負重みの有向グラフで、始点から終点へのウォークのコストを小さい順に最大 $K$ 個返す。
頂点・辺の繰り返しを許し、異なる辺列は同じコストでも別々に数える。
多重辺・自己ループ・重み0の閉路に対応する。

## できること
頂点数を $N$、辺数を $M$ とする。

- `vector<T> k_shortest_walk(int s, int t, int k, const vector<vector<edge<T>>>& g)`
  `s` から `t` へのコストを非減少順で最大 `k` 個返す。足りなければ存在する分だけ返す
  時間 $O((N+M)\log(N+M+1)+K\log(K+1))$、空間 $O(N+M+N\log(M+1)+K)$
- 到達不能または `k == 0` なら空。`s == t` では長さ0の空ウォークも1本に数える
- `t` を途中で通って再び戻るウォークも数える
- 辺列の復元機能はない

## 使い方
頂点は0-indexed、`s`, `t` は有効な頂点、`k >= 0` とする。
`T` は整数型を使い、通常は `long long` とする。
辺重みは非負で、距離と辺重みの和、追加コスト、列挙候補のコストを含む中間値が `T` に収まることを前提とする。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto costs = k_shortest_walk(s, t, k, g);
```

## 実装上の補足
逆向きDijkstra法で終点への最短路木を作り、木以外の辺の追加コストをleftist heapで管理する。
各頂点のheap構築は破壊的に行い、最短路木の親から引き継ぐmeldだけを永続化する。
