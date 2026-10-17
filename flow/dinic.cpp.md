---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: flow/project_selection_problem.cpp
    title: Project Selection Problem
  - icon: ':heavy_check_mark:'
    path: graph/maxflow_lower_bound.cpp
    title: "\u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max Flow with\
      \ Lower Bounds)"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0396.test.cpp
    title: test/aoj0396.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
    title: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_flow_boundaries.test.cpp
    title: test/yosupo_aplusb_flow_boundaries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_maxflow_lower_bound.test.cpp
    title: test/yosupo_aplusb_maxflow_lower_bound.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_project_selection_pair_profit.test.cpp
    title: test/yosupo_aplusb_project_selection_pair_profit.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki957.test.cpp
    title: test/yuki957.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yuki957_project_selection_problem.test.cpp
    title: test/yuki957_project_selection_problem.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "Dinic\u6CD5(Dinic)"
    links: []
  bundledCode: "#line 1 \"flow/dinic.cpp\"\ntemplate<class T, bool directed>\nclass\
    \ Dinic {\n    static_assert(directed || numeric_limits<T>::is_signed,\n     \
    \             \"undirected flow requires a signed capacity type\");\n    struct\
    \ input_edge {\n        int from, index;\n        T capacity;\n    };\n    vector<input_edge>\
    \ positions;\n\n    void bfs(int s, int t){\n        fill(level.begin(),level.end(),\
    \ -1);\n        queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n\
    \        while(!Q.empty()){\n            int v = Q.front(); Q.pop();\n       \
    \     for (auto &&e : G[v]){\n                if(e.cap > 0 && level[e.to] < 0){\n\
    \                    level[e.to] = level[v] + 1;\n                    if(e.to\
    \ == t) return;\n                    Q.emplace(e.to);\n                }\n   \
    \         }\n        }\n    }\n \n    T dfs(int v, int t, T f){\n        if(v\
    \ == t) return f;\n        for(int &i = iter[v]; i < G[v].size(); i++){\n    \
    \        edge &e = G[v][i];\n            if(e.cap > 0 && level[v] < level[e.to]){\n\
    \                T d = dfs(e.to, t, min(f,  e.cap));\n                if(d ==\
    \ 0) continue;\n                e.cap -= d;\n                G[e.to][e.rev].cap\
    \ += d;\n                return d;\n            }\n        }\n        return 0;\n\
    \    }\npublic:\n    struct Edge {\n        int from, to;\n        T capacity,\
    \ flow;\n    };\n\n    struct edge {\n        int to{}; T cap; int rev{};\n  \
    \      edge() = default;\n        edge(int to, T cap, int rev) : to(to), cap(cap),\
    \ rev(rev) {}\n    };\n \n    vector<vector<edge>> G;\n    vector<int> level,\
    \ iter;\n    Dinic() = default;\n    explicit Dinic(int n) : G(n), level(n), iter(n)\
    \ {}\n \n    int add_edge(int from, int to, T cap){\n        int from_id = G[from].size(),\
    \ to_id = G[to].size();\n        int id = positions.size();\n        positions.push_back({from,\
    \ from_id, cap});\n        if(from == to) ++to_id;\n        G[from].emplace_back(to,\
    \ cap, to_id);\n        G[to].emplace_back(from, directed ? 0 : cap, from_id);\n\
    \        return id;\n    }\n\n    Edge get_edge(int id) const {\n        const\
    \ auto &p = positions[id];\n        const auto &e = G[p.from][p.index];\n    \
    \    return {p.from, e.to, p.capacity, T(p.capacity - e.cap)};\n    }\n\n    vector<Edge>\
    \ edges() const {\n        vector<Edge> result;\n        result.reserve(positions.size());\n\
    \        for(int id = 0; id < int(positions.size()); ++id)\n            result.push_back(get_edge(id));\n\
    \        return result;\n    }\n\n    vector<char> min_cut(int s) const {\n  \
    \      vector<char> reachable(G.size(), false);\n        queue<int> q;\n     \
    \   reachable[s] = true;\n        q.emplace(s);\n        while(!q.empty()) {\n\
    \            int v = q.front(); q.pop();\n            for(const auto &e : G[v])\
    \ {\n                if(e.cap <= 0 || reachable[e.to]) continue;\n           \
    \     reachable[e.to] = true;\n                q.emplace(e.to);\n            }\n\
    \        }\n        return reachable;\n    }\n \n \n    T flow(int s, int t, T\
    \ lim = INF<T>){\n        T ret = 0;\n        while(lim > 0) {\n            bfs(s,\
    \ t);\n            if(level[t] < 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(lim > 0){\n                T f = dfs(s, t, lim);\n  \
    \              if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n"
  code: "template<class T, bool directed>\nclass Dinic {\n    static_assert(directed\
    \ || numeric_limits<T>::is_signed,\n                  \"undirected flow requires\
    \ a signed capacity type\");\n    struct input_edge {\n        int from, index;\n\
    \        T capacity;\n    };\n    vector<input_edge> positions;\n\n    void bfs(int\
    \ s, int t){\n        fill(level.begin(),level.end(), -1);\n        queue<int>\
    \ Q;\n        level[s] = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n\
    \            int v = Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n\
    \                if(e.cap > 0 && level[e.to] < 0){\n                    level[e.to]\
    \ = level[v] + 1;\n                    if(e.to == t) return;\n               \
    \     Q.emplace(e.to);\n                }\n            }\n        }\n    }\n \n\
    \    T dfs(int v, int t, T f){\n        if(v == t) return f;\n        for(int\
    \ &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n     \
    \       if(e.cap > 0 && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, min(f,  e.cap));\n                if(d == 0) continue;\n                e.cap\
    \ -= d;\n                G[e.to][e.rev].cap += d;\n                return d;\n\
    \            }\n        }\n        return 0;\n    }\npublic:\n    struct Edge\
    \ {\n        int from, to;\n        T capacity, flow;\n    };\n\n    struct edge\
    \ {\n        int to{}; T cap; int rev{};\n        edge() = default;\n        edge(int\
    \ to, T cap, int rev) : to(to), cap(cap), rev(rev) {}\n    };\n \n    vector<vector<edge>>\
    \ G;\n    vector<int> level, iter;\n    Dinic() = default;\n    explicit Dinic(int\
    \ n) : G(n), level(n), iter(n) {}\n \n    int add_edge(int from, int to, T cap){\n\
    \        int from_id = G[from].size(), to_id = G[to].size();\n        int id =\
    \ positions.size();\n        positions.push_back({from, from_id, cap});\n    \
    \    if(from == to) ++to_id;\n        G[from].emplace_back(to, cap, to_id);\n\
    \        G[to].emplace_back(from, directed ? 0 : cap, from_id);\n        return\
    \ id;\n    }\n\n    Edge get_edge(int id) const {\n        const auto &p = positions[id];\n\
    \        const auto &e = G[p.from][p.index];\n        return {p.from, e.to, p.capacity,\
    \ T(p.capacity - e.cap)};\n    }\n\n    vector<Edge> edges() const {\n       \
    \ vector<Edge> result;\n        result.reserve(positions.size());\n        for(int\
    \ id = 0; id < int(positions.size()); ++id)\n            result.push_back(get_edge(id));\n\
    \        return result;\n    }\n\n    vector<char> min_cut(int s) const {\n  \
    \      vector<char> reachable(G.size(), false);\n        queue<int> q;\n     \
    \   reachable[s] = true;\n        q.emplace(s);\n        while(!q.empty()) {\n\
    \            int v = q.front(); q.pop();\n            for(const auto &e : G[v])\
    \ {\n                if(e.cap <= 0 || reachable[e.to]) continue;\n           \
    \     reachable[e.to] = true;\n                q.emplace(e.to);\n            }\n\
    \        }\n        return reachable;\n    }\n \n \n    T flow(int s, int t, T\
    \ lim = INF<T>){\n        T ret = 0;\n        while(lim > 0) {\n            bfs(s,\
    \ t);\n            if(level[t] < 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(lim > 0){\n                T f = dfs(s, t, lim);\n  \
    \              if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/dinic.cpp
  requiredBy:
  - graph/maxflow_lower_bound.cpp
  - flow/project_selection_problem.cpp
  timestamp: '2026-10-18 00:20:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_flow_boundaries.test.cpp
  - test/yuki957_project_selection_problem.test.cpp
  - test/yosupo_aplusb_project_selection_pair_profit.test.cpp
  - test/aoj0396.test.cpp
  - test/yuki957.test.cpp
  - test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  - test/yosupo_aplusb_maxflow_lower_bound.test.cpp
date: 2019-07-31
documentation_of: flow/dinic.cpp
layout: document
tags: "\u6700\u5927\u6D41"
title: "Dinic\u6CD5(Dinic)"
---

## 説明
Dinic による最大流。
理論計算量は $O(EV^2)$ だが、ほとんどの場合で高速に動作する。
辺 ID と登録時の容量の保持を含め、領域は $O(V+E)$。

## できること
- `Dinic<T, directed> mf(n)` : 頂点数 `n` のグラフを作る。`directed=false` なら無向辺
- `int add_edge(int from, int to, T cap)` : 容量 `cap` の辺を追加し、0からの追加順の ID を返す。償却 $O(1)$
- `T flow(int s, int t, T lim = INF<T>)` : 現在の残余グラフで最大 `lim` だけ流し、今回追加した流量を返す
- `Edge get_edge(int id) const` : `from, to, capacity, flow` を返す。`capacity` は登録時の容量、`flow` は登録方向への正味流量。$O(1)$
- `vector<Edge> edges() const` : 追加順で全辺の情報を返す。逆辺は含めない。時間・返却領域 $O(E)$
- `vector<char> min_cut(int s) const` : 現在の残余グラフで `s` から到達できる頂点を `true` で返す。時間 $O(V+E)$、追加領域 $O(V)$

## 使い方
```cpp
Dinic<long long, true> mf(n);
int id = mf.add_edge(u, v, capacity);
long long value = mf.flow(s, t);
auto e = mf.get_edge(id);
auto source_side = mf.min_cut(s);
```

## 実装上の補足
`s != t`、`cap >= 0`、`lim >= 0` とし、流量と計算中の残余容量は `T` に収める。
無向版の `T` は符号付き型を使う。流量は `-capacity` から `capacity` の範囲を取り、残余容量は元容量の2倍になる場合がある。
辺情報の取得は、対象辺の登録容量と残余容量の対応が保たれていることを前提とする。
`min_cut(s)` は終点が到達不能になったとき最小カットの始点側を表す。流量上限による途中停止では、最小カットとは限らない。
BFS は終点の距離が決まった時点で終了する。この時点で終点の1つ前までの層はすべて距離が決まっており、同じ最短距離の増加路を続けて探せる。
流量上限 `lim` を使い切った場合は、次の BFS を行わずに終了する。再実行では前回の残余グラフを引き継ぐ。
