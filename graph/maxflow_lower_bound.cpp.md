---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/dinic.cpp
    title: "Dinic\u6CD5(Dinic)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
    title: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max\
      \ Flow with Lower Bounds)"
    links: []
  bundledCode: "#line 1 \"flow/dinic.cpp\"\ntemplate<class T, bool directed>\nclass\
    \ Dinic {\n    void bfs(int s){\n        fill(level.begin(),level.end(), -1);\n\
    \        queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n       \
    \ while(!Q.empty()){\n            int v = Q.front(); Q.pop();\n            for\
    \ (auto &&e : G[v]){\n                if(e.cap > 0 && level[e.to] < 0){\n    \
    \                level[e.to] = level[v] + 1;\n                    Q.emplace(e.to);\n\
    \                }\n            }\n        }\n    }\n \n    T dfs(int v, int t,\
    \ T f){\n        if(v == t) return f;\n        for(int &i = iter[v]; i < G[v].size();\
    \ i++){\n            edge &e = G[v][i];\n            if(e.cap > 0 && level[v]\
    \ < level[e.to]){\n                T d = dfs(e.to, t, min(f,  e.cap));\n     \
    \           if(d == 0) continue;\n                e.cap -= d;\n              \
    \  G[e.to][e.rev].cap += d;\n                return d;\n            }\n      \
    \  }\n        return 0;\n    }\npublic:\n    struct edge {\n        int to{};\
    \ T cap; int rev{};\n        edge() = default;\n        edge(int to, T cap, int\
    \ rev) : to(to), cap(cap), rev(rev) {}\n    };\n \n    vector<vector<edge>> G;\n\
    \    vector<int> level, iter;\n    Dinic() = default;\n    explicit Dinic(int\
    \ n) : G(n), level(n), iter(n) {}\n \n    void add_edge(int from, int to, T cap){\n\
    \        G[from].emplace_back(to, cap, G[to].size());\n        G[to].emplace_back(from,\
    \ directed ? 0 : cap,  G[from].size()-1);\n    }\n \n \n    T flow(int s, int\
    \ t, T lim = INF<T>){\n        T ret = 0;\n        while(true) {\n           \
    \ bfs(s);\n            if(level[t] < 0 || lim == 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(true){\n                T f = dfs(s, t, lim);\n     \
    \           if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n#line 2 \"graph/maxflow_lower_bound.cpp\"\n\ntemplate<class\
    \ T>\nclass MaxFlowLowerBound {\n\n    struct raw_edge {\n        int from{},\
    \ to{};\n        T lower{}, upper{};\n    };\n\npublic:\n    int n;\n    vector<raw_edge>\
    \ edges;\n    MaxFlowLowerBound() = default;\n    explicit MaxFlowLowerBound(int\
    \ n) : n(n) {}\n\n    void add_edge(int from, int to, T lower, T upper) {\n  \
    \      edges.push_back({from, to, lower, upper});\n    }\n\n    pair<bool, T>\
    \ max_flow(int s, int t) {\n        int ss = n, tt = n + 1;\n        Dinic<T,\
    \ true> mf(n + 2);\n        vector<T> b(n, 0);\n        auto add_edge = [&](int\
    \ from, int to, T cap) {\n            int idx = (int)mf.G[from].size();\n    \
    \        mf.add_edge(from, to, cap);\n            return pair<int, int>{from,\
    \ idx};\n        };\n\n        for(auto &&e : edges) {\n            mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower);\n            b[e.from] -= e.lower;\n            b[e.to]\
    \ += e.lower;\n        }\n\n        auto ts = add_edge(t, s, INF<T>);\n      \
    \  T req = 0;\n        vector<pair<int, int>> super_edges;\n        for(int v\
    \ = 0; v < n; ++v) {\n            if(b[v] > 0) {\n                req += b[v];\n\
    \                super_edges.emplace_back(add_edge(ss, v, b[v]));\n          \
    \  } else if(b[v] < 0) {\n                mf.add_edge(v, tt, -b[v]);\n       \
    \     }\n        }\n\n        if(mf.flow(ss, tt) != req) return {false, 0};\n\n\
    \        for(auto &&id : super_edges) {\n            if(mf.G[id.first][id.second].cap\
    \ != 0) return {false, 0};\n        }\n\n        int to = mf.G[ts.first][ts.second].to;\n\
    \        int rev = mf.G[ts.first][ts.second].rev;\n        T base = mf.G[to][rev].cap;\n\
    \        mf.G[ts.first][ts.second].cap = 0;\n        mf.G[to][rev].cap = 0;\n\n\
    \        T add = mf.flow(s, t);\n        return {true, base + add};\n    }\n};\n\
    \n/**\n * @brief \u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max\
    \ Flow with Lower Bounds)\n */\n"
  code: "#include \"../flow/dinic.cpp\"\n\ntemplate<class T>\nclass MaxFlowLowerBound\
    \ {\n\n    struct raw_edge {\n        int from{}, to{};\n        T lower{}, upper{};\n\
    \    };\n\npublic:\n    int n;\n    vector<raw_edge> edges;\n    MaxFlowLowerBound()\
    \ = default;\n    explicit MaxFlowLowerBound(int n) : n(n) {}\n\n    void add_edge(int\
    \ from, int to, T lower, T upper) {\n        edges.push_back({from, to, lower,\
    \ upper});\n    }\n\n    pair<bool, T> max_flow(int s, int t) {\n        int ss\
    \ = n, tt = n + 1;\n        Dinic<T, true> mf(n + 2);\n        vector<T> b(n,\
    \ 0);\n        auto add_edge = [&](int from, int to, T cap) {\n            int\
    \ idx = (int)mf.G[from].size();\n            mf.add_edge(from, to, cap);\n   \
    \         return pair<int, int>{from, idx};\n        };\n\n        for(auto &&e\
    \ : edges) {\n            mf.add_edge(e.from, e.to, e.upper - e.lower);\n    \
    \        b[e.from] -= e.lower;\n            b[e.to] += e.lower;\n        }\n\n\
    \        auto ts = add_edge(t, s, INF<T>);\n        T req = 0;\n        vector<pair<int,\
    \ int>> super_edges;\n        for(int v = 0; v < n; ++v) {\n            if(b[v]\
    \ > 0) {\n                req += b[v];\n                super_edges.emplace_back(add_edge(ss,\
    \ v, b[v]));\n            } else if(b[v] < 0) {\n                mf.add_edge(v,\
    \ tt, -b[v]);\n            }\n        }\n\n        if(mf.flow(ss, tt) != req)\
    \ return {false, 0};\n\n        for(auto &&id : super_edges) {\n            if(mf.G[id.first][id.second].cap\
    \ != 0) return {false, 0};\n        }\n\n        int to = mf.G[ts.first][ts.second].to;\n\
    \        int rev = mf.G[ts.first][ts.second].rev;\n        T base = mf.G[to][rev].cap;\n\
    \        mf.G[ts.first][ts.second].cap = 0;\n        mf.G[to][rev].cap = 0;\n\n\
    \        T add = mf.flow(s, t);\n        return {true, base + add};\n    }\n};\n\
    \n/**\n * @brief \u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max\
    \ Flow with Lower Bounds)\n */\n"
  dependsOn:
  - flow/dinic.cpp
  isVerificationFile: false
  path: graph/maxflow_lower_bound.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
date: 2026-03-07
documentation_of: graph/maxflow_lower_bound.cpp
layout: document
tags: "\u6700\u5927\u6D41"
title: "\u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max Flow with Lower\
  \ Bounds)"
---

## 説明

有向グラフの各辺に下限制約 `lower` と上限制約 `upper` を持つ
`s-t` 最大流を求める。

各辺 `e=(u,v)` の流量 `f_e` は

- `lower_e <= f_e <= upper_e`

を満たす。さらに（`s`,`t` 以外で）フロー保存を満たす中で、`s` から `t` への流量を最大化する。

## 計算量

- `max_flow(s, t)` : $O(V^2 E)$（Dinic ベース）

## 使い方

1. `MaxFlowLowerBound<long long> g(n);`
2. `add_edge(from, to, lower, upper)` で辺を追加
3. `auto [ok, ans] = g.max_flow(s, t);`
4. `ok == false` なら制約を満たす流れが存在しない

## 公開メンバ

- `int n` : 頂点数
- `void add_edge(int from, int to, T lower, T upper)` : 下限付き有向辺を追加
- `pair<bool, T> max_flow(int s, int t)` : 実行可能性判定と最大流量を返す

## 実装メモ

- 下限を需要に変換し、超始点 `ss`・超終点 `tt` と `t -> s` の無限辺を加えた可行循環で可否判定。
- 可行解が得られた後、`t -> s` 辺を消して残余グラフで `s -> t` の追加増加分を流し、最大流を得る。
