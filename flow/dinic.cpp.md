---
category: "\u30D5\u30ED\u30FC"
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':x:'
    path: flow/project_selection_problem.cpp
    title: ProjectSelectionProblem
  - icon: ':heavy_check_mark:'
    path: graph/maxflow_lower_bound.cpp
    title: MaxFlowLowerBound
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0396.test.cpp
    title: test/aoj0396.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
    title: test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  - icon: ':x:'
    path: test/yuki957.test.cpp
    title: test/yuki957.test.cpp
  - icon: ':x:'
    path: test/yuki957_project_selection_problem.test.cpp
    title: test/yuki957_project_selection_problem.test.cpp
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':question:'
  attributes:
    document_title: "Dinic\u6CD5(Dinic)"
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
    \ Dinic\u6CD5(Dinic)\n */\n"
  code: "template<class T, bool directed>\nclass Dinic {\n    void bfs(int s){\n \
    \       fill(level.begin(),level.end(), -1);\n        queue<int> Q;\n        level[s]\
    \ = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n            int v =\
    \ Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n                if(e.cap\
    \ > 0 && level[e.to] < 0){\n                    level[e.to] = level[v] + 1;\n\
    \                    Q.emplace(e.to);\n                }\n            }\n    \
    \    }\n    }\n \n    T dfs(int v, int t, T f){\n        if(v == t) return f;\n\
    \        for(int &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n\
    \            if(e.cap > 0 && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, min(f,  e.cap));\n                if(d == 0) continue;\n                e.cap\
    \ -= d;\n                G[e.to][e.rev].cap += d;\n                return d;\n\
    \            }\n        }\n        return 0;\n    }\npublic:\n    struct edge\
    \ {\n        int to{}; T cap; int rev{};\n        edge() = default;\n        edge(int\
    \ to, T cap, int rev) : to(to), cap(cap), rev(rev) {}\n    };\n \n    vector<vector<edge>>\
    \ G;\n    vector<int> level, iter;\n    Dinic() = default;\n    explicit Dinic(int\
    \ n) : G(n), level(n), iter(n) {}\n \n    void add_edge(int from, int to, T cap){\n\
    \        G[from].emplace_back(to, cap, G[to].size());\n        G[to].emplace_back(from,\
    \ directed ? 0 : cap,  G[from].size()-1);\n    }\n \n \n    T flow(int s, int\
    \ t, T lim = INF<T>){\n        T ret = 0;\n        while(true) {\n           \
    \ bfs(s);\n            if(level[t] < 0 || lim == 0) break;\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            while(true){\n                T f = dfs(s, t, lim);\n     \
    \           if(f == 0) break;\n                ret += f;\n                lim\
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n\n/**\n * @brief\
    \ Dinic\u6CD5(Dinic)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/dinic.cpp
  requiredBy:
  - graph/maxflow_lower_bound.cpp
  - flow/project_selection_problem.cpp
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_SOME_WA
  verifiedWith:
  - test/yuki957.test.cpp
  - test/aoj_grl_6_a_maxflow_lower_bound.test.cpp
  - test/aoj0396.test.cpp
  - test/yuki957_project_selection_problem.test.cpp
date: 2019-07-31
documentation_of: flow/dinic.cpp
layout: document
tags: "\u6700\u5927\u6D41"
title: "Dinic(\u6700\u5927\u6D41)"
---

## 説明
Dinic による最大流。
理論計算量は $O(EV^2)$ だが、ほとんどの場合で高速に動作する。
