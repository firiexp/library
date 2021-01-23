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
  bundledCode: "#line 1 \"graph/bellman_ford.cpp\"\ntemplate <typename T>\nstruct\
    \ edge {\n    int from, to;\n    T cost;\n\n    edge(int to, T cost) : from(-1),\
    \ to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from), to(to),\
    \ cost(cost) {}\n\n    explicit operator int() const {return to;}\n};\n\ntemplate\
    \ <typename T>\nvector<T> bellman_ford(int s, int V,vector<edge<T> > &G){\n  \
    \  const T INF = numeric_limits<T>::max();\n    vector<T> d(V, INF);\n    d[s]\
    \ = 0;\n    for (int i = 0; i < V - 1; ++i) {\n        for (auto &&e : G) {\n\
    \            if (d[e.from] == INF) continue;\n            d[e.to] = min(d[e.to],\
    \ d[e.from] + e.cost);\n        }\n    }\n    for (auto &&e : G) {\n        if(d[e.from]\
    \ == INF) continue;\n        if(d[e.from] + e.cost < d[e.to]) return vector<T>\
    \ ();\n    }\n    return d;\n}\n"
  code: "template <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\n\
    \    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const {return to;}\n};\n\ntemplate <typename T>\nvector<T> bellman_ford(int\
    \ s, int V,vector<edge<T> > &G){\n    const T INF = numeric_limits<T>::max();\n\
    \    vector<T> d(V, INF);\n    d[s] = 0;\n    for (int i = 0; i < V - 1; ++i)\
    \ {\n        for (auto &&e : G) {\n            if (d[e.from] == INF) continue;\n\
    \            d[e.to] = min(d[e.to], d[e.from] + e.cost);\n        }\n    }\n \
    \   for (auto &&e : G) {\n        if(d[e.from] == INF) continue;\n        if(d[e.from]\
    \ + e.cost < d[e.to]) return vector<T> ();\n    }\n    return d;\n}"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/bellman_ford.cpp
layout: document
redirect_from:
- /library/graph/bellman_ford.cpp
- /library/graph/bellman_ford.cpp.html
title: graph/bellman_ford.cpp
---
