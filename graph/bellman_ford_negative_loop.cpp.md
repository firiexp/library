---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: test/aoj_grl_1_b_negative_loop.test.cpp
    title: test/aoj_grl_1_b_negative_loop.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    document_title: "Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)"
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
    \ dist[i] = -INF<T>;\n    }\n    return dist;\n}\n\n/**\n * @brief Bellman-Ford\u6CD5\
    (\u8CA0\u9589\u8DEF\u4F1D\u64AD)\n */\n"
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
    \        if(negative[i]) dist[i] = -INF<T>;\n    }\n    return dist;\n}\n\n/**\n\
    \ * @brief Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford_negative_loop.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - test/aoj_grl_1_b_negative_loop.test.cpp
documentation_of: graph/bellman_ford_negative_loop.cpp
layout: document
title: "Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)"
---
## 説明
負辺を含む単一始点最短路を求め、始点から到達できる負閉路の影響下にある頂点を `-INF` にする。
計算量は $O(VE)$。

## できること
- `vector<T> bellman_ford(int s, int n, vector<edge<T>>& es)`
  始点 `s` から各頂点への距離を返す。未到達は `INF<T>`、負閉路の影響下は `-INF<T>`

## 使い方
`edge<T>` の列を用意して呼ぶ。
`T` は加算と比較ができる数値型を想定している。

```cpp
vector<edge<long long>> es;
es.emplace_back(u, v, w);
auto dist = bellman_ford(0, n, es);
if (dist[v] == INF<long long>) {
    // unreachable
} else if (dist[v] == -INF<long long>) {
    // affected by a negative cycle
}
```

## 実装上の補足
負閉路そのものに乗る頂点だけでなく、そこから到達できる頂点も `-INF` にする。
このファイル単体では `INF<T>`、`ll`、`vector` を外側で用意する前提である。
