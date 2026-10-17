---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_1_b_negative_loop.test.cpp
    title: test/aoj_grl_1_b_negative_loop.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_bellman_ford.test.cpp
    title: test/yosupo_aplusb_bellman_ford.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)"
    links: []
  bundledCode: "#line 1 \"graph/bellman_ford_negative_loop.cpp\"\ntemplate <typename\
    \ T>\nstruct edge {\n    int from, to;\n    T cost;\n \n    edge(int to, T cost)\
    \ : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T cost) : from(from),\
    \ to(to), cost(cost) {}\n \n    explicit operator int() const {return to;}\n};\n\
    \ \ntemplate <typename T>\nvector<T> bellman_ford(int s, int N,vector<edge<T>\
    \ > &G){\n    vector<T> dist(N, INF<T>);\n    dist[s] = 0;\n    for (int i = 0;\
    \ i < N - 1; ++ i) {\n        bool updated = false;\n        for (auto &&e : G)\
    \ {\n            if(dist[e.from] == INF<T>) continue;\n            if(dist[e.to]\
    \ > dist[e.from]+ e.cost){\n                dist[e.to] = dist[e.from]+ e.cost;\n\
    \                updated = true;\n            }\n        }\n        if (!updated)\
    \ return dist;\n    }\n \n    vector<char> negative(N);\n    vector<int> q;\n\
    \    for (auto &&e : G) {\n        if (dist[e.from] == INF<T> || negative[e.to])\
    \ continue;\n        if (dist[e.to] > dist[e.from] + e.cost) {\n            negative[e.to]\
    \ = true;\n            q.push_back(e.to);\n        }\n    }\n    if (q.empty())\
    \ return dist;\n    vector<vector<int>> next(N);\n    for (auto &&e : G) next[e.from].push_back(e.to);\n\
    \    for (size_t i = 0; i < q.size(); ++i) {\n        for (int to : next[q[i]])\
    \ {\n            if (negative[to]) continue;\n            negative[to] = true;\n\
    \            q.push_back(to);\n        }\n    }\n    for (int i = 0; i < N; ++i)\
    \ {\n        if(negative[i]) dist[i] = -INF<T>;\n    }\n    return dist;\n}\n\n\
    /**\n * @brief Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)\n */\n"
  code: "template <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n \n\
    \    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n \n    explicit operator\
    \ int() const {return to;}\n};\n \ntemplate <typename T>\nvector<T> bellman_ford(int\
    \ s, int N,vector<edge<T> > &G){\n    vector<T> dist(N, INF<T>);\n    dist[s]\
    \ = 0;\n    for (int i = 0; i < N - 1; ++ i) {\n        bool updated = false;\n\
    \        for (auto &&e : G) {\n            if(dist[e.from] == INF<T>) continue;\n\
    \            if(dist[e.to] > dist[e.from]+ e.cost){\n                dist[e.to]\
    \ = dist[e.from]+ e.cost;\n                updated = true;\n            }\n  \
    \      }\n        if (!updated) return dist;\n    }\n \n    vector<char> negative(N);\n\
    \    vector<int> q;\n    for (auto &&e : G) {\n        if (dist[e.from] == INF<T>\
    \ || negative[e.to]) continue;\n        if (dist[e.to] > dist[e.from] + e.cost)\
    \ {\n            negative[e.to] = true;\n            q.push_back(e.to);\n    \
    \    }\n    }\n    if (q.empty()) return dist;\n    vector<vector<int>> next(N);\n\
    \    for (auto &&e : G) next[e.from].push_back(e.to);\n    for (size_t i = 0;\
    \ i < q.size(); ++i) {\n        for (int to : next[q[i]]) {\n            if (negative[to])\
    \ continue;\n            negative[to] = true;\n            q.push_back(to);\n\
    \        }\n    }\n    for (int i = 0; i < N; ++i) {\n        if(negative[i])\
    \ dist[i] = -INF<T>;\n    }\n    return dist;\n}\n\n/**\n * @brief Bellman-Ford\u6CD5\
    (\u8CA0\u9589\u8DEF\u4F1D\u64AD)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bellman_ford_negative_loop.cpp
  requiredBy: []
  timestamp: '2026-10-17 20:27:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_bellman_ford.test.cpp
  - test/aoj_grl_1_b_negative_loop.test.cpp
documentation_of: graph/bellman_ford_negative_loop.cpp
layout: document
title: "Bellman-Ford\u6CD5(\u8CA0\u9589\u8DEF\u4F1D\u64AD)"
---
## 説明
負辺を含む単一始点最短路を求め、始点から到達できる負閉路の影響下にある頂点を `-INF` にする。
時間計算量は $O(VE)$、追加領域は $O(V + E)$。

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
最大 $V-1$ 回の緩和後、まだ改善できる辺の行き先から到達判定を行う。負閉路の影響を伝える処理は $O(V+E)$ で、距離の数値更新は行わない。
緩和で更新が止まればその時点で終了する。改善できる辺がなければ、到達判定用の隣接リストは作らない。
このファイル単体では `INF<T>`、`ll`、`vector` を外側で用意する前提である。
