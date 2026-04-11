---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_radix_heap.cpp
    title: "Dijkstra\u6CD5(Radix Heap)"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_restore.cpp
    title: "\u7D4C\u8DEF\u5FA9\u5143\u4ED8\u304DDijkstra\u6CD5"
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
    path: test/yosupo_shortest_path.test.cpp
    title: test/yosupo_shortest_path.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path_radix_heap.test.cpp
    title: test/yosupo_shortest_path_radix_heap.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \ G, Q, [](int, const edge<T> &) {});\n}\n\n\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_COMMON_CPP\n#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_COMMON_CPP\n\
    \ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\n   \
    \ edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int\
    \ to, T cost) : from(from), to(to), cost(cost) {}\n};\n\ntemplate <typename T>\n\
    struct DijkstraPriorityQueue {\n    priority_queue<pair<T, int>, vector<pair<T,\
    \ int>>, greater<>> q;\n\n    bool empty() const { return q.empty(); }\n\n   \
    \ void push(T cost, int v) {\n        q.emplace(cost, v);\n    }\n\n    pair<T,\
    \ int> pop() {\n        auto res = q.top();\n        q.pop();\n        return\
    \ res;\n    }\n};\n\ntemplate <typename T, class Queue, class OnRelax>\nvector<T>\
    \ dijkstra_internal(int s, const vector<vector<edge<T>>> &G, Queue &Q, OnRelax\
    \ on_relax) {\n    int n = (int)G.size();\n    vector<T> dist(n, INF<T>);\n  \
    \  dist[s] = 0;\n    Q.push(T(0), s);\n    while (!Q.empty()) {\n        auto\
    \ [cost, v] = Q.pop();\n        if (dist[v] < cost) continue;\n        for (auto\
    \ &&e : G[v]) {\n            T nxt = cost + e.cost;\n            if (dist[e.to]\
    \ <= nxt) continue;\n            dist[e.to] = nxt;\n            on_relax(v, e);\n\
    \            Q.push(nxt, e.to);\n        }\n    }\n    return dist;\n}\n\ntemplate\
    \ <typename T, class Queue>\nvector<T> dijkstra_internal(int s, const vector<vector<edge<T>>>\
    \ &G, Queue &Q) {\n    return dijkstra_internal(s, G, Q, [](int, const edge<T>\
    \ &) {});\n}\n\n#endif\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/dijkstra_common.cpp
  requiredBy:
  - graph/dijkstra_radix_heap.cpp
  - graph/dijkstra_restore.cpp
  - graph/dijkstra.cpp
  timestamp: '2026-03-12 14:17:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path_radix_heap.test.cpp
  - test/aoj0275_static_bitset.test.cpp
  - test/aoj_grl_1_a_dijkstra.test.cpp
  - test/aoj0275_dynamic_bitset.test.cpp
  - test/yosupo_shortest_path.test.cpp
documentation_of: graph/dijkstra_common.cpp
layout: document
redirect_from:
- /library/graph/dijkstra_common.cpp
- /library/graph/dijkstra_common.cpp.html
title: graph/dijkstra_common.cpp
---
