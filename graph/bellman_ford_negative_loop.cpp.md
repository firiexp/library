---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bellman_ford_negative_loop.cpp\"\ntemplate <typename\
    \ T>\nstruct edge {\n    int from, to;\n    T cost;\n \n    edge(int to, T cost)\
    \ : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from),\
    \ to(to), cost(cost) {}\n \n    explicit operator int() const {return to;}\n};\n\
    \ \ntemplate <typename T>\nvector<T> bellman_ford(int s, int N,vector<edge<T>\
    \ > &G){\n    vector<T> dist(N, INF<T>);\n    vector<bool> negative(N);\n    dist[s]\
    \ = 0;\n    for (int i = 0; i < N - 1; ++ i) {\n        for (auto &&e : G) {\n\
    \            if(dist[e.from] == INF<T>) continue;\n            if(dist[e.to] >\
    \ dist[e.from]+ e.cost){\n                dist[e.to] = dist[e.from]+ e.cost;\n\
    \            }\n        }\n    }\n \n    ll ans = dist[N - 1];\n \n    for (int\
    \ i = 0; i < N ; ++i) {\n        for (auto &&e : G) {\n            if(dist[e.from]\
    \ == INF<T>) continue;\n            if(dist[e.to] > dist[e.from] + e.cost){\n\
    \                dist[e.to] = dist[e.from] + e.cost;\n                negative[e.to]\
    \ = true;\n            }\n            if(negative[e.from]) negative[e.to] = true;\n\
    \        }\n    }\n    for (int i = 0; i < N; ++i) {\n        if(negative[i])\
    \ dist[i] = -INF<T>;\n    }\n    return dist;\n}\n"
  code: "template <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n \n\
    \    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n \n    explicit operator\
    \ int() const {return to;}\n};\n \ntemplate <typename T>\nvector<T> bellman_ford(int\
    \ s, int N,vector<edge<T> > &G){\n    vector<T> dist(N, INF<T>);\n    vector<bool>\
    \ negative(N);\n    dist[s] = 0;\n    for (int i = 0; i < N - 1; ++ i) {\n   \
    \     for (auto &&e : G) {\n            if(dist[e.from] == INF<T>) continue;\n\
    \            if(dist[e.to] > dist[e.from]+ e.cost){\n                dist[e.to]\
    \ = dist[e.from]+ e.cost;\n            }\n        }\n    }\n \n    ll ans = dist[N\
    \ - 1];\n \n    for (int i = 0; i < N ; ++i) {\n        for (auto &&e : G) {\n\
    \            if(dist[e.from] == INF<T>) continue;\n            if(dist[e.to] >\
    \ dist[e.from] + e.cost){\n                dist[e.to] = dist[e.from] + e.cost;\n\
    \                negative[e.to] = true;\n            }\n            if(negative[e.from])\
    \ negative[e.to] = true;\n        }\n    }\n    for (int i = 0; i < N; ++i) {\n\
    \        if(negative[i]) dist[i] = -INF<T>;\n    }\n    return dist;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford_negative_loop.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/bellman_ford_negative_loop.cpp
layout: document
redirect_from:
- /library/graph/bellman_ford_negative_loop.cpp
- /library/graph/bellman_ford_negative_loop.cpp.html
title: graph/bellman_ford_negative_loop.cpp
---
