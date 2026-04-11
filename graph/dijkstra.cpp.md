---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  _extendedRequiredBy: []
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
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Dijkstra\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra_common.cpp\"\n\n\n\ntemplate <typename T>\n\
    struct edge {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1),\
    \ to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to),\
    \ cost(cost) {}\n};\n\ntemplate <typename T>\nstruct DijkstraPriorityQueue {\n\
    \    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> q;\n\n    bool\
    \ empty() const { return q.empty(); }\n\n    void push(T cost, int v) {\n    \
    \    q.emplace(cost, v);\n    }\n\n    pair<T, int> pop() {\n        auto res\
    \ = q.top();\n        q.pop();\n        return res;\n    }\n};\n\ntemplate <typename\
    \ T, class Queue, class OnRelax>\nvector<T> dijkstra_internal(int s, const vector<vector<edge<T>>>\
    \ &G, Queue &Q, OnRelax on_relax) {\n    int n = (int)G.size();\n    vector<T>\
    \ dist(n, INF<T>);\n    dist[s] = 0;\n    Q.push(T(0), s);\n    while (!Q.empty())\
    \ {\n        auto [cost, v] = Q.pop();\n        if (dist[v] < cost) continue;\n\
    \        for (auto &&e : G[v]) {\n            T nxt = cost + e.cost;\n       \
    \     if (dist[e.to] <= nxt) continue;\n            dist[e.to] = nxt;\n      \
    \      on_relax(v, e);\n            Q.push(nxt, e.to);\n        }\n    }\n   \
    \ return dist;\n}\n\ntemplate <typename T, class Queue>\nvector<T> dijkstra_internal(int\
    \ s, const vector<vector<edge<T>>> &G, Queue &Q) {\n    return dijkstra_internal(s,\
    \ G, Q, [](int, const edge<T> &) {});\n}\n\n\n#line 2 \"graph/dijkstra.cpp\"\n\
    \ntemplate <typename T>\nvector<T> dijkstra(int s, const vector<vector<edge<T>>>\
    \ &G) {\n    DijkstraPriorityQueue<T> Q;\n    return dijkstra_internal(s, G, Q);\n\
    }\n\n/**\n * @brief Dijkstra\u6CD5\n */\n"
  code: "#include \"dijkstra_common.cpp\"\n\ntemplate <typename T>\nvector<T> dijkstra(int\
    \ s, const vector<vector<edge<T>>> &G) {\n    DijkstraPriorityQueue<T> Q;\n  \
    \  return dijkstra_internal(s, G, Q);\n}\n\n/**\n * @brief Dijkstra\u6CD5\n */\n"
  dependsOn:
  - graph/dijkstra_common.cpp
  isVerificationFile: false
  path: graph/dijkstra.cpp
  requiredBy: []
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0275_static_bitset.test.cpp
  - test/aoj_grl_1_a_dijkstra.test.cpp
  - test/aoj0275_dynamic_bitset.test.cpp
documentation_of: graph/dijkstra.cpp
layout: document
title: "Dijkstra\u6CD5"
---

## 説明
単一始点最短路を求める。
辺重みが非負のときに使う。
計算量は $O((V + E) log V)$。

## できること
- `vector<T> dijkstra(int s, const vector<vector<edge<T>>>& g)`
  始点 `s` から各頂点への最短距離を返す。未到達は `INF<T>`

## 使い方
`edge<T>` の隣接リストを作って `dijkstra` を呼ぶ。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto dist = dijkstra(0, g);
```

## 実装上の補足
到達不能頂点の距離は `INF<T>` のまま残る。
同じ長さの最短路が複数あっても、距離だけを返す。
