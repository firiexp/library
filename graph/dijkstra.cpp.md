---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_from_distances.cpp
    title: "\u591A\u59CB\u70B9Dijkstra\u6CD5"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_dynamic_bitset.test.cpp
    title: test/aoj0275_dynamic_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj0275_static_bitset.test.cpp
    title: test/aoj0275_static_bitset.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_a_dijkstra.test.cpp
    title: test/aoj_grl_1_a_dijkstra.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
    title: test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_bfs01.test.cpp
    title: test/yosupo_aplusb_bfs01.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
    title: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
    title: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition.test.cpp
    title: test/yosupo_aplusb_library_composition.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_library_composition_reverse.test.cpp
    title: test/yosupo_aplusb_library_composition_reverse.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_range_edge_graph.test.cpp
    title: test/yosupo_aplusb_range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Dijkstra\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra.cpp\"\n\n\n\n#line 1 \"graph/dijkstra_common.cpp\"\
    \n\n\n\n#line 1 \"graph/edge.cpp\"\n\n\n\ntemplate <typename T>\nstruct edge {\n\
    \    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1), to(to),\
    \ cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost)\
    \ {}\n\n    explicit operator int() const { return to; }\n};\n\n\n#line 5 \"graph/dijkstra_common.cpp\"\
    \n\ntemplate <typename T>\nstruct DijkstraPriorityQueue {\n    priority_queue<pair<T,\
    \ int>, vector<pair<T, int>>, greater<>> q;\n\n    bool empty() const { return\
    \ q.empty(); }\n\n    void push(T cost, int v) {\n        q.emplace(cost, v);\n\
    \    }\n\n    pair<T, int> pop() {\n        auto res = q.top();\n        q.pop();\n\
    \        return res;\n    }\n};\n\ntemplate <typename T, class Queue, class OnRelax>\n\
    void dijkstra_relax(vector<T>& dist, const vector<vector<edge<T>>>& G, Queue&\
    \ Q, OnRelax on_relax) {\n    while (!Q.empty()) {\n        auto [cost, v] = Q.pop();\n\
    \        if (dist[v] < cost) continue;\n        for (auto &&e : G[v]) {\n    \
    \        T nxt = cost + e.cost;\n            if (dist[e.to] <= nxt) continue;\n\
    \            dist[e.to] = nxt;\n            on_relax(v, e);\n            Q.push(nxt,\
    \ e.to);\n        }\n    }\n}\n\ntemplate <typename T, class Queue, class OnRelax>\n\
    vector<T> dijkstra_internal(int s, const vector<vector<edge<T>>> &G, Queue &Q,\
    \ OnRelax on_relax) {\n    int n = (int)G.size();\n    vector<T> dist(n, INF<T>);\n\
    \    dist[s] = 0;\n    Q.push(T(0), s);\n    dijkstra_relax(dist, G, Q, std::move(on_relax));\n\
    \    return dist;\n}\n\ntemplate <typename T, class Queue>\nvector<T> dijkstra_internal(int\
    \ s, const vector<vector<edge<T>>> &G, Queue &Q) {\n    return dijkstra_internal(s,\
    \ G, Q, [](int, const edge<T> &) {});\n}\n\n\n#line 5 \"graph/dijkstra.cpp\"\n\
    \ntemplate <typename T>\nvector<T> dijkstra(int s, const vector<vector<edge<T>>>\
    \ &G) {\n    DijkstraPriorityQueue<T> Q;\n    return dijkstra_internal(s, G, Q);\n\
    }\n\n\n\n/**\n * @brief Dijkstra\u6CD5\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_CPP\n#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_CPP\n\
    \n#include \"dijkstra_common.cpp\"\n\ntemplate <typename T>\nvector<T> dijkstra(int\
    \ s, const vector<vector<edge<T>>> &G) {\n    DijkstraPriorityQueue<T> Q;\n  \
    \  return dijkstra_internal(s, G, Q);\n}\n\n#endif\n\n/**\n * @brief Dijkstra\u6CD5\
    \n */\n"
  dependsOn:
  - graph/dijkstra_common.cpp
  - graph/edge.cpp
  isVerificationFile: false
  path: graph/dijkstra.cpp
  requiredBy:
  - graph/dijkstra_from_distances.cpp
  timestamp: '2026-10-11 20:32:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_1_a_dijkstra.test.cpp
  - test/aoj0275_static_bitset.test.cpp
  - test/yosupo_aplusb_library_composition.test.cpp
  - test/aoj0275_dynamic_bitset.test.cpp
  - test/yosupo_aplusb_range_edge_graph.test.cpp
  - test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
  - test/yosupo_aplusb_bfs01.test.cpp
  - test/yosupo_aplusb_dijkstra_from_distances.test.cpp
  - test/yosupo_aplusb_dijkstra_from_distances.test.cpp
  - test/yosupo_aplusb_library_composition_reverse.test.cpp
documentation_of: graph/dijkstra.cpp
layout: document
title: "Dijkstra\u6CD5"
---

## 説明
単一始点最短路を求める。
これを応用して、初期費用を持つ複数始点からの最小費用も求めることができる。
辺重みが非負のときに使う。

## できること
- `vector<T> dijkstra(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`。時間 $O((V+E)\log(V+E+1))$、補助領域 $O(V+E)$

## 使い方
`edge<T>` の隣接リストを作って `dijkstra` を呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

初期費用を持つ複数始点を扱う場合は、`graph/dijkstra_from_distances.cpp` の `dijkstra_from_distances` を使う。

## 実装上の補足
到達不能頂点の距離は `INF<T>` のまま残る。
同じ長さの最短路が複数あっても、距離だけを返す。
