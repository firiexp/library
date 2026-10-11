---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra_common.cpp
    title: graph/dijkstra_common.cpp
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
    title: test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
    title: test/yosupo_aplusb_dijkstra_from_distances.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u591A\u59CB\u70B9Dijkstra\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra_from_distances.cpp\"\n\n\n\n#line 1 \"graph/dijkstra.cpp\"\
    \n\n\n\n#line 1 \"graph/dijkstra_common.cpp\"\n\n\n\n#line 1 \"graph/edge.cpp\"\
    \n\n\n\ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\
    \n    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const { return to; }\n};\n\n\n#line 5 \"graph/dijkstra_common.cpp\"\n\n\
    template <typename T>\nstruct DijkstraPriorityQueue {\n    priority_queue<pair<T,\
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
    }\n\n\n\n/**\n * @brief Dijkstra\u6CD5\n */\n#line 5 \"graph/dijkstra_from_distances.cpp\"\
    \n\ntemplate <typename T>\nvector<T> dijkstra_from_distances(vector<T> initial,\
    \ const vector<vector<edge<T>>>& G) {\n    DijkstraPriorityQueue<T> Q;\n    for\
    \ (int v = 0; v < (int)initial.size(); ++v) {\n        if (initial[v] != INF<T>)\
    \ Q.push(initial[v], v);\n    }\n    dijkstra_relax(initial, G, Q, [](int, const\
    \ edge<T>&) {});\n    return initial;\n}\n\n\n\n/**\n * @brief \u591A\u59CB\u70B9\
    Dijkstra\u6CD5\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_FROM_DISTANCES_CPP\n#define FIRIEXP_LIBRARY_GRAPH_DIJKSTRA_FROM_DISTANCES_CPP\n\
    \n#include \"dijkstra.cpp\"\n\ntemplate <typename T>\nvector<T> dijkstra_from_distances(vector<T>\
    \ initial, const vector<vector<edge<T>>>& G) {\n    DijkstraPriorityQueue<T> Q;\n\
    \    for (int v = 0; v < (int)initial.size(); ++v) {\n        if (initial[v] !=\
    \ INF<T>) Q.push(initial[v], v);\n    }\n    dijkstra_relax(initial, G, Q, [](int,\
    \ const edge<T>&) {});\n    return initial;\n}\n\n#endif\n\n/**\n * @brief \u591A\
    \u59CB\u70B9Dijkstra\u6CD5\n */\n"
  dependsOn:
  - graph/dijkstra.cpp
  - graph/dijkstra_common.cpp
  - graph/edge.cpp
  isVerificationFile: false
  path: graph/dijkstra_from_distances.cpp
  requiredBy: []
  timestamp: '2026-10-11 20:32:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_1_a_dijkstra_from_distances.test.cpp
  - test/yosupo_aplusb_dijkstra_from_distances.test.cpp
documentation_of: graph/dijkstra_from_distances.cpp
layout: document
title: "\u591A\u59CB\u70B9Dijkstra\u6CD5"
---

## 説明
Dijkstra 法を応用して、初期費用を持つ複数始点から各頂点への最小費用を求める。
辺重みは非負とする。初期費用には負の値も使える。

## できること
- `vector<T> dijkstra_from_distances(vector<T> initial, const vector<vector<edge<T>>>& g)`
  各頂点 $v$ への最小費用 $\min_s(\mathrm{initial}[s]+\mathrm{dist}(s,v))$ を返す。`initial[s] == INF<T>` の頂点は始点候補から除く。未到達は `INF<T>`。有限の初期値の個数を $S$ として $O(V+(E+S)\log(V+E+1))$ 時間、$O(V+E)$ 補助領域

## 使い方
`initial` の長さは頂点数に合わせ、始点候補の初期費用を設定する。
通常の多始点最短路では始点だけを `0`、それ以外を `INF<T>` にする。

```cpp
vector<long long> initial(n, INF<long long>);
initial[a] = cost_a;
initial[b] = cost_b;
auto dist = dijkstra_from_distances(initial, g);
```

有限の初期費用と緩和中の和は、型 `T` の範囲に収まる `INF<T>` 未満の値を前提とする。
初期配列を保持する場合はそのまま渡し、領域を再利用する場合は `std::move(initial)` を渡す。
