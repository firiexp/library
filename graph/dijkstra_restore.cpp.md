---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/dijkstra.cpp
    title: "Dijkstra\u6CD5"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_shortest_path.test.cpp
    title: test/yosupo_shortest_path.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D4C\u8DEF\u5FA9\u5143\u4ED8\u304DDijkstra\u6CD5"
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
    \ }\n    }\n    return d;\n}\n\n/**\n * @brief Dijkstra\u6CD5\n */\n#line 2 \"\
    graph/dijkstra_restore.cpp\"\n\ntemplate <typename T>\nstruct DijkstraRestoreResult\
    \ {\n    vector<T> dist;\n    vector<int> parent;\n};\n\ntemplate <typename T>\n\
    DijkstraRestoreResult<T> dijkstra_restore(int s, vector<vector<edge<T>>> &G) {\n\
    \    int n = (int)G.size();\n    vector<T> dist(n, INF<T>);\n    vector<int> parent(n,\
    \ -1);\n    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> Q;\n\
    \    dist[s] = 0;\n    Q.emplace(0, s);\n    while (!Q.empty()) {\n        T cost;\n\
    \        int v;\n        tie(cost, v) = Q.top();\n        Q.pop();\n        if\
    \ (dist[v] < cost) continue;\n        for (auto &&e : G[v]) {\n            T nxt\
    \ = cost + e.cost;\n            if (dist[e.to] <= nxt) continue;\n           \
    \ dist[e.to] = nxt;\n            parent[e.to] = v;\n            Q.emplace(nxt,\
    \ e.to);\n        }\n    }\n    return {dist, parent};\n}\n\nvector<int> restore_path(int\
    \ s, int t, const vector<int> &parent) {\n    vector<int> path;\n    if (t < 0\
    \ || t >= (int)parent.size()) return path;\n    int v = t;\n    while (v != -1)\
    \ {\n        path.push_back(v);\n        if (v == s) {\n            reverse(path.begin(),\
    \ path.end());\n            return path;\n        }\n        v = parent[v];\n\
    \    }\n    path.clear();\n    return path;\n}\n\n/**\n * @brief \u7D4C\u8DEF\u5FA9\
    \u5143\u4ED8\u304DDijkstra\u6CD5\n */\n"
  code: "#include \"dijkstra.cpp\"\n\ntemplate <typename T>\nstruct DijkstraRestoreResult\
    \ {\n    vector<T> dist;\n    vector<int> parent;\n};\n\ntemplate <typename T>\n\
    DijkstraRestoreResult<T> dijkstra_restore(int s, vector<vector<edge<T>>> &G) {\n\
    \    int n = (int)G.size();\n    vector<T> dist(n, INF<T>);\n    vector<int> parent(n,\
    \ -1);\n    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<>> Q;\n\
    \    dist[s] = 0;\n    Q.emplace(0, s);\n    while (!Q.empty()) {\n        T cost;\n\
    \        int v;\n        tie(cost, v) = Q.top();\n        Q.pop();\n        if\
    \ (dist[v] < cost) continue;\n        for (auto &&e : G[v]) {\n            T nxt\
    \ = cost + e.cost;\n            if (dist[e.to] <= nxt) continue;\n           \
    \ dist[e.to] = nxt;\n            parent[e.to] = v;\n            Q.emplace(nxt,\
    \ e.to);\n        }\n    }\n    return {dist, parent};\n}\n\nvector<int> restore_path(int\
    \ s, int t, const vector<int> &parent) {\n    vector<int> path;\n    if (t < 0\
    \ || t >= (int)parent.size()) return path;\n    int v = t;\n    while (v != -1)\
    \ {\n        path.push_back(v);\n        if (v == s) {\n            reverse(path.begin(),\
    \ path.end());\n            return path;\n        }\n        v = parent[v];\n\
    \    }\n    path.clear();\n    return path;\n}\n\n/**\n * @brief \u7D4C\u8DEF\u5FA9\
    \u5143\u4ED8\u304DDijkstra\u6CD5\n */\n"
  dependsOn:
  - graph/dijkstra.cpp
  isVerificationFile: false
  path: graph/dijkstra_restore.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_shortest_path.test.cpp
date: 2026-03-08
documentation_of: graph/dijkstra_restore.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: Dijkstra Restore
---

## 説明
単一始点最短路と最短路木の親を求める。
辺重みが非負のときに使う。
計算量は `O((V + E) log V)`。

## できること
- `DijkstraRestoreResult<T> dijkstra_restore(int s, vector<vector<edge<T>>>& g)`
  始点 `s` からの最短距離と親配列を返す。未到達頂点の距離は `INF<T>`、親は `-1`
- `vector<int> restore_path(int s, int t, const vector<int>& parent)`
  親配列から `s -> t` の頂点列を復元して返す。復元できなければ空配列

## 使い方
`edge<T>` の隣接リストを作って `dijkstra_restore` を呼ぶ。
頂点列が必要なら返ってきた `parent` を `restore_path` に渡す。

```cpp
vector<vector<edge<long long>>> g(n);
g[u].emplace_back(v, w);
auto res = dijkstra_restore(0, g);
auto path = restore_path(0, t, res.parent);
```

## 実装上の補足
同じ距離の候補が複数あるとき、親は更新しない。
返る経路は最短路のひとつであり、一意性は保証しない。
