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
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_maxflow_lower_bound.test.cpp
    title: test/yosupo_aplusb_maxflow_lower_bound.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max\
      \ Flow with Lower Bounds)"
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
    \ Dinic\u6CD5(Dinic)\n */\n#line 2 \"graph/maxflow_lower_bound.cpp\"\n\ntemplate<class\
    \ T>\nclass MaxFlowLowerBound {\n\n    struct raw_edge {\n        int from{},\
    \ to{};\n        T lower{}, upper{};\n    };\n\npublic:\n    struct Result {\n\
    \        bool exists;\n        T value;\n        vector<T> edge_flow;\n    };\n\
    \n    int n;\n    vector<raw_edge> edges;\n    MaxFlowLowerBound() = default;\n\
    \    explicit MaxFlowLowerBound(int n) : n(n) {}\n\n    void add_edge(int from,\
    \ int to, T lower, T upper) {\n        edges.push_back({from, to, lower, upper});\n\
    \    }\n\n    pair<bool, T> max_flow(int s, int t) {\n        auto result = max_flow_with_edges(s,\
    \ t);\n        return {result.exists, result.value};\n    }\n\n    Result max_flow_with_edges(int\
    \ s, int t) {\n        int ss = n, tt = n + 1;\n        Dinic<T, true> mf(n +\
    \ 2);\n        vector<T> b(n, 0);\n        vector<int> edge_ids;\n        edge_ids.reserve(edges.size());\n\
    \        for(auto &&e : edges) {\n            edge_ids.push_back(mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower));\n            b[e.from] -= e.lower;\n            b[e.to]\
    \ += e.lower;\n        }\n\n        int ts_index = mf.G[t].size();\n        int\
    \ ts = mf.add_edge(t, s, INF<T>);\n        T req = 0;\n        vector<int> super_edges;\n\
    \        for(int v = 0; v < n; ++v) {\n            if(b[v] > 0) {\n          \
    \      req += b[v];\n                super_edges.push_back(mf.add_edge(ss, v,\
    \ b[v]));\n            } else if(b[v] < 0) {\n                mf.add_edge(v, tt,\
    \ -b[v]);\n            }\n        }\n\n        if(mf.flow(ss, tt) != req) return\
    \ {false, 0, {}};\n\n        for(int id : super_edges) {\n            auto e =\
    \ mf.get_edge(id);\n            if(e.flow != e.capacity) return {false, 0, {}};\n\
    \        }\n\n        T base = mf.get_edge(ts).flow;\n        auto &aux = mf.G[t][ts_index];\n\
    \        mf.G[aux.to][aux.rev].cap = 0;\n        aux.cap = 0;\n\n        T add\
    \ = mf.flow(s, t);\n        Result result{true, base + add, {}};\n        result.edge_flow.reserve(edges.size());\n\
    \        for(size_t i = 0; i < edges.size(); ++i) {\n            result.edge_flow.push_back(edges[i].lower\
    \ + mf.get_edge(edge_ids[i]).flow);\n        }\n        return result;\n    }\n\
    };\n\n/**\n * @brief \u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41\
    \ (Max Flow with Lower Bounds)\n */\n"
  code: "#include \"../flow/dinic.cpp\"\n\ntemplate<class T>\nclass MaxFlowLowerBound\
    \ {\n\n    struct raw_edge {\n        int from{}, to{};\n        T lower{}, upper{};\n\
    \    };\n\npublic:\n    struct Result {\n        bool exists;\n        T value;\n\
    \        vector<T> edge_flow;\n    };\n\n    int n;\n    vector<raw_edge> edges;\n\
    \    MaxFlowLowerBound() = default;\n    explicit MaxFlowLowerBound(int n) : n(n)\
    \ {}\n\n    void add_edge(int from, int to, T lower, T upper) {\n        edges.push_back({from,\
    \ to, lower, upper});\n    }\n\n    pair<bool, T> max_flow(int s, int t) {\n \
    \       auto result = max_flow_with_edges(s, t);\n        return {result.exists,\
    \ result.value};\n    }\n\n    Result max_flow_with_edges(int s, int t) {\n  \
    \      int ss = n, tt = n + 1;\n        Dinic<T, true> mf(n + 2);\n        vector<T>\
    \ b(n, 0);\n        vector<int> edge_ids;\n        edge_ids.reserve(edges.size());\n\
    \        for(auto &&e : edges) {\n            edge_ids.push_back(mf.add_edge(e.from,\
    \ e.to, e.upper - e.lower));\n            b[e.from] -= e.lower;\n            b[e.to]\
    \ += e.lower;\n        }\n\n        int ts_index = mf.G[t].size();\n        int\
    \ ts = mf.add_edge(t, s, INF<T>);\n        T req = 0;\n        vector<int> super_edges;\n\
    \        for(int v = 0; v < n; ++v) {\n            if(b[v] > 0) {\n          \
    \      req += b[v];\n                super_edges.push_back(mf.add_edge(ss, v,\
    \ b[v]));\n            } else if(b[v] < 0) {\n                mf.add_edge(v, tt,\
    \ -b[v]);\n            }\n        }\n\n        if(mf.flow(ss, tt) != req) return\
    \ {false, 0, {}};\n\n        for(int id : super_edges) {\n            auto e =\
    \ mf.get_edge(id);\n            if(e.flow != e.capacity) return {false, 0, {}};\n\
    \        }\n\n        T base = mf.get_edge(ts).flow;\n        auto &aux = mf.G[t][ts_index];\n\
    \        mf.G[aux.to][aux.rev].cap = 0;\n        aux.cap = 0;\n\n        T add\
    \ = mf.flow(s, t);\n        Result result{true, base + add, {}};\n        result.edge_flow.reserve(edges.size());\n\
    \        for(size_t i = 0; i < edges.size(); ++i) {\n            result.edge_flow.push_back(edges[i].lower\
    \ + mf.get_edge(edge_ids[i]).flow);\n        }\n        return result;\n    }\n\
    };\n\n/**\n * @brief \u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41\
    \ (Max Flow with Lower Bounds)\n */\n"
  dependsOn:
  - flow/dinic.cpp
  isVerificationFile: false
  path: graph/maxflow_lower_bound.cpp
  requiredBy: []
  timestamp: '2026-10-18 00:20:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  - test/yosupo_aplusb_maxflow_lower_bound.test.cpp
date: 2026-03-07
documentation_of: graph/maxflow_lower_bound.cpp
layout: document
tags: "\u6700\u5927\u6D41"
title: "\u4E0B\u9650\u5236\u7D04\u4ED8\u304Ds-t\u6700\u5927\u6D41 (Max Flow with Lower\
  \ Bounds)"
---

## 説明
有向グラフの各辺に下限・上限を持つ `s-t` 最大流を求める。
各辺の上下限と、`s`, `t` 以外の頂点の流量保存を満たす非負の `s-t` 流を対象とする。
時間は $O(V^2 E)$、各辺の流量復元は追加で $O(E)$、領域は $O(V+E)$。

## できること
- `MaxFlowLowerBound<T> g(n)`
  頂点数 `n` のグラフを作る
- `void add_edge(int from, int to, T lower, T upper)`
  下限・上限付き有向辺を追加する。自己ループ・平行辺も扱う
- `pair<bool, T> max_flow(int s, int t)`
  実行可能性と最大流量を返す。実行不能なら `{false, 0}`
- `Result max_flow_with_edges(int s, int t)`
  `exists`, `value`, `edge_flow` を返す。`edge_flow[i]` は追加順での各辺の流量
  実行不能なら `exists=false`, `value=0`、`edge_flow` は空

## 使い方
```cpp
MaxFlowLowerBound<long long> g(n);
g.add_edge(u, v, lower, upper);
auto result = g.max_flow_with_edges(s, t);
if (result.exists) {
    long long maximum = result.value;
    vector<long long> flows = result.edge_flow;
}
```

## 実装上の補足
`0 <= lower <= upper`、`s != t` が必要で、容量・需要の合計・中間計算は `T` と `INF<T>` の範囲に収める。
負の正味 `s-t` 流だけが存在する場合は実行不能とする。
下限を需要に変換し、超始点・超終点と `t -> s` の辺で実行可能性を調べる。
元の辺の流量は下限に `Dinic::get_edge(id).flow` を足して復元する。
どちらの API も登録した辺を変更せず、再実行できる。
