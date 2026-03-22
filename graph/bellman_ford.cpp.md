---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj_grl_1_b_bellman_ford.test.cpp
    title: test/aoj_grl_1_b_bellman_ford.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Bellman-Ford\u6CD5"
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
    \ ();\n    }\n    return d;\n}\n\n/**\n * @brief Bellman-Ford\u6CD5\n */\n"
  code: "template <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\n\
    \    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const {return to;}\n};\n\ntemplate <typename T>\nvector<T> bellman_ford(int\
    \ s, int V,vector<edge<T> > &G){\n    const T INF = numeric_limits<T>::max();\n\
    \    vector<T> d(V, INF);\n    d[s] = 0;\n    for (int i = 0; i < V - 1; ++i)\
    \ {\n        for (auto &&e : G) {\n            if (d[e.from] == INF) continue;\n\
    \            d[e.to] = min(d[e.to], d[e.from] + e.cost);\n        }\n    }\n \
    \   for (auto &&e : G) {\n        if(d[e.from] == INF) continue;\n        if(d[e.from]\
    \ + e.cost < d[e.to]) return vector<T> ();\n    }\n    return d;\n}\n\n/**\n *\
    \ @brief Bellman-Ford\u6CD5\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj_grl_1_b_bellman_ford.test.cpp
documentation_of: graph/bellman_ford.cpp
layout: document
title: "Bellman-Ford\u6CD5"
---
## 説明
Bellman-Ford 法で単一始点最短路を求める。
負辺があっても使え、計算量は $O(VE)$。

## できること
- `vector<T> bellman_ford(int s, int n, vector<edge<T>> &es)`
  始点 `s` から各頂点への最短距離を返す。始点から到達可能な負閉路があるときは空 vector を返す

## 使い方
辺を `edge<T>(from, to, cost)` で列挙し、`bellman_ford(s, n, es)` を呼ぶ。

```cpp
vector<edge<long long>> es;
es.emplace_back(u, v, w);

auto dist = bellman_ford(0, n, es);
if (dist.empty()) {
    // reachable negative cycle
}
```

## 実装上の補足
未到達頂点の距離は `numeric_limits<T>::max()` のまま残る。
負閉路が欲しい場合や `-INF` 伝播が必要な場合は `bellman_ford_negative_loop.cpp` を使う。
