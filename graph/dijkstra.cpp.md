---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/yosupo_shortest_path.test.cpp
    title: test/yosupo_shortest_path.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    _deprecated_at_docs: _md/dijkstra.md
    document_title: "Dijkstra\u6CD5"
    links: []
  bundledCode: "#line 1 \"graph/dijkstra.cpp\"\ntemplate <typename T>\nstruct edge\
    \ {\n    int from, to; T cost;\n    edge(int to, T cost) : from(-1), to(to), cost(cost)\
    \ {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}\n\
    };\n\ntemplate <typename T>\nvector<T> dijkstra(int s,vector<vector<edge<T>>>\
    \ &G){\n    auto n = G.size();\n    vector<T> d(n, INF<T>);\n    priority_queue<pair<T,\
    \ int>,vector<pair<T, int>>,greater<>> Q;\n    d[s] = 0;\n    Q.emplace(0, s);\n\
    \    while(!Q.empty()){\n        T cost; int i;\n        tie(cost, i) = Q.top();\
    \ Q.pop();\n        if(d[i] < cost) continue;\n        for (auto &&e : G[i]) {\n\
    \            auto cost2 = cost + e.cost;\n            if(d[e.to] <= cost2) continue;\n\
    \            d[e.to] = cost2;\n            Q.emplace(d[e.to], e.to);\n       \
    \ }\n    }\n    return d;\n}\n\n/**\n * @brief Dijkstra\u6CD5\n * @docs _md/dijkstra.md\n\
    \ */\n"
  code: "template <typename T>\nstruct edge {\n    int from, to; T cost;\n    edge(int\
    \ to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T\
    \ cost) : from(from), to(to), cost(cost) {}\n};\n\ntemplate <typename T>\nvector<T>\
    \ dijkstra(int s,vector<vector<edge<T>>> &G){\n    auto n = G.size();\n    vector<T>\
    \ d(n, INF<T>);\n    priority_queue<pair<T, int>,vector<pair<T, int>>,greater<>>\
    \ Q;\n    d[s] = 0;\n    Q.emplace(0, s);\n    while(!Q.empty()){\n        T cost;\
    \ int i;\n        tie(cost, i) = Q.top(); Q.pop();\n        if(d[i] < cost) continue;\n\
    \        for (auto &&e : G[i]) {\n            auto cost2 = cost + e.cost;\n  \
    \          if(d[e.to] <= cost2) continue;\n            d[e.to] = cost2;\n    \
    \        Q.emplace(d[e.to], e.to);\n        }\n    }\n    return d;\n}\n\n/**\n\
    \ * @brief Dijkstra\u6CD5\n * @docs _md/dijkstra.md\n */"
  dependsOn: []
  isVerificationFile: false
  path: graph/dijkstra.cpp
  requiredBy: []
  timestamp: '2020-05-02 12:45:39+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/yosupo_shortest_path.test.cpp
documentation_of: graph/dijkstra.cpp
layout: document
redirect_from:
- /library/graph/dijkstra.cpp
- /library/graph/dijkstra.cpp.html
title: "Dijkstra\u6CD5"
---
## 説明
単一始点最短路を求める。負辺があると正しく動作しない。
$O(V \log E)$