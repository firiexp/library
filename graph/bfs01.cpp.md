---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj2945_bfs01.test.cpp
    title: test/aoj2945_bfs01.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: 01-BFS
    links: []
  bundledCode: "#line 1 \"graph/bfs01.cpp\"\ntemplate <typename T>\nstruct edge {\n\
    \    int from, to; T cost;\n    edge(int to, T cost) : from(-1), to(to), cost(cost)\
    \ {}\n    edge(int from, int to, T cost) : from(from), to(to), cost(cost) {}\n\
    };\n\ntemplate <typename T>\nvector<T> bfs01(int s, vector<vector<edge<T>>> &G)\
    \ {\n    int n = G.size();\n    vector<T> d(n, INF<T>);\n    deque<int> q;\n \
    \   d[s] = 0;\n    q.push_front(s);\n    while (!q.empty()) {\n        int v =\
    \ q.front();\n        q.pop_front();\n        for (auto &&e : G[v]) {\n      \
    \      T nd = d[v] + e.cost;\n            if (d[e.to] <= nd) continue;\n     \
    \       d[e.to] = nd;\n            if (e.cost == T(0)) {\n                q.push_front(e.to);\n\
    \            } else {\n                assert(e.cost == T(1));\n             \
    \   q.push_back(e.to);\n            }\n        }\n    }\n    return d;\n}\n\n\
    /**\n * @brief 01-BFS\n */\n"
  code: "template <typename T>\nstruct edge {\n    int from, to; T cost;\n    edge(int\
    \ to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from, int to, T\
    \ cost) : from(from), to(to), cost(cost) {}\n};\n\ntemplate <typename T>\nvector<T>\
    \ bfs01(int s, vector<vector<edge<T>>> &G) {\n    int n = G.size();\n    vector<T>\
    \ d(n, INF<T>);\n    deque<int> q;\n    d[s] = 0;\n    q.push_front(s);\n    while\
    \ (!q.empty()) {\n        int v = q.front();\n        q.pop_front();\n       \
    \ for (auto &&e : G[v]) {\n            T nd = d[v] + e.cost;\n            if (d[e.to]\
    \ <= nd) continue;\n            d[e.to] = nd;\n            if (e.cost == T(0))\
    \ {\n                q.push_front(e.to);\n            } else {\n             \
    \   assert(e.cost == T(1));\n                q.push_back(e.to);\n            }\n\
    \        }\n    }\n    return d;\n}\n\n/**\n * @brief 01-BFS\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bfs01.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj2945_bfs01.test.cpp
date: 2026-03-08
documentation_of: graph/bfs01.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: 0-1 BFS
---

## 説明
辺重みが `0` または `1` のグラフで単一始点最短路を求める。
計算量は $O(V + E)$。

## できること
- `vector<T> bfs01(int s, vector<vector<edge<T>>>& G)`
  始点 `s` から各頂点への最短距離を返す
- 到達不能な頂点
  `INF<T>` のまま返す

## 使い方
`#include "../graph/bfs01.cpp"` を読み込む。
隣接リスト `G` を作り、各辺のコストに `0` か `1` を入れて `bfs01(s, G)` を呼ぶ。

```cpp
vector<vector<edge<int>>> G(n);
G[u].emplace_back(v, 0);
G[v].emplace_back(u, 1);
auto dist = bfs01(0, G);
```

## 実装上の補足
`edge<T>` は `dijkstra.cpp` と同じ形を使う。
重み `0` の遷移は deque の前、重み `1` の遷移は後ろへ積む。
