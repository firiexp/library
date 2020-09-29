---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0274.test.cpp
    title: test/aoj0274.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/primaldual.md
    document_title: "\u6700\u5C0F\u8CBB\u7528\u6D41(primal-dual)"
    links: []
  bundledCode: "#line 1 \"flow/primaldual.cpp\"\ntemplate<typename F, typename C>\n\
    struct PrimalDual {\n    struct edge {\n        int to; F cap; C cost; int rev;\n\
    \        edge() = default;\n        edge(int to, F cap, C cost, int rev):to(to),\
    \ cap(cap), cost(cost), rev(rev) {};\n    };\n    vector<vector<edge>> G;\n  \
    \  vector<C> potential, min_cost;\n    vector<int> prevv, preve;\n\n    explicit\
    \ PrimalDual(int n) : G(n), potential(n), min_cost(n), prevv(n), preve(n) {}\n\
    \n    void add_edge(int u, int v, F cap, C cost){\n        G[u].emplace_back(v,\
    \ cap, cost, G[v].size());\n        G[v].emplace_back(u, 0, -cost, G[u].size()-1);\n\
    \    }\n\n    struct P{\n        C first; int second;\n        P(C first,int second):first(first),second(second){}\n\
    \        bool operator<(const P&a) const{return a.first<first;}\n    };\n    void\
    \ dijkstra(int s){\n\n        priority_queue<P> Q;\n        fill(min_cost.begin(),min_cost.end(),\
    \ INF<C>);\n        min_cost[s] = 0;\n        Q.emplace(0, s);\n        while(!Q.empty()){\n\
    \            P p = Q.top(); Q.pop();\n            int v = p.second;\n        \
    \    if(min_cost[v] < p.first) continue;\n            for(int i = 0; i < G[v].size();\
    \ ++i){\n                edge &e=G[v][i];\n                if(e.cap==0) continue;\n\
    \                if(min_cost[v]+e.cost+potential[v]-potential[e.to] < min_cost[e.to]){\n\
    \                    min_cost[e.to] = min_cost[v]+e.cost+potential[v]-potential[e.to];\n\
    \                    prevv[e.to] = v;\n                    preve[e.to] = i;\n\
    \                    Q.emplace(min_cost[e.to], e.to);\n                }\n   \
    \         }\n        }\n    }\n\n    C flow(int s, int t, F fl, int &ok){\n  \
    \      C res = 0;\n        fill(potential.begin(),potential.end(), 0);\n     \
    \   while(fl > 0){\n            dijkstra(s);\n            if(min_cost[t] == INF<C>){\n\
    \                ok = 0;\n                return res;\n            }\n       \
    \     for (int i = 0; i < potential.size(); ++i) {\n                if(min_cost[i]\
    \ < INF<C>) potential[i] += min_cost[i];\n            }\n\n            F d = fl;\n\
    \            for(int v = t; v != s; v = prevv[v]){\n                d = min(d,\
    \ G[prevv[v]][preve[v]].cap);\n            }\n            fl -= d;\n         \
    \   res += potential[t]*d;\n            for(int v = t; v != s; v = prevv[v]){\n\
    \                G[prevv[v]][preve[v]].cap -= d;\n                G[v][G[prevv[v]][preve[v]].rev].cap\
    \ += d;\n            }\n        }\n        ok = 1;\n        return res;\n    }\n\
    };\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528\u6D41(primal-dual)\n * @docs _md/primaldual.md\n\
    \ */\n"
  code: "template<typename F, typename C>\nstruct PrimalDual {\n    struct edge {\n\
    \        int to; F cap; C cost; int rev;\n        edge() = default;\n        edge(int\
    \ to, F cap, C cost, int rev):to(to), cap(cap), cost(cost), rev(rev) {};\n   \
    \ };\n    vector<vector<edge>> G;\n    vector<C> potential, min_cost;\n    vector<int>\
    \ prevv, preve;\n\n    explicit PrimalDual(int n) : G(n), potential(n), min_cost(n),\
    \ prevv(n), preve(n) {}\n\n    void add_edge(int u, int v, F cap, C cost){\n \
    \       G[u].emplace_back(v, cap, cost, G[v].size());\n        G[v].emplace_back(u,\
    \ 0, -cost, G[u].size()-1);\n    }\n\n    struct P{\n        C first; int second;\n\
    \        P(C first,int second):first(first),second(second){}\n        bool operator<(const\
    \ P&a) const{return a.first<first;}\n    };\n    void dijkstra(int s){\n\n   \
    \     priority_queue<P> Q;\n        fill(min_cost.begin(),min_cost.end(), INF<C>);\n\
    \        min_cost[s] = 0;\n        Q.emplace(0, s);\n        while(!Q.empty()){\n\
    \            P p = Q.top(); Q.pop();\n            int v = p.second;\n        \
    \    if(min_cost[v] < p.first) continue;\n            for(int i = 0; i < G[v].size();\
    \ ++i){\n                edge &e=G[v][i];\n                if(e.cap==0) continue;\n\
    \                if(min_cost[v]+e.cost+potential[v]-potential[e.to] < min_cost[e.to]){\n\
    \                    min_cost[e.to] = min_cost[v]+e.cost+potential[v]-potential[e.to];\n\
    \                    prevv[e.to] = v;\n                    preve[e.to] = i;\n\
    \                    Q.emplace(min_cost[e.to], e.to);\n                }\n   \
    \         }\n        }\n    }\n\n    C flow(int s, int t, F fl, int &ok){\n  \
    \      C res = 0;\n        fill(potential.begin(),potential.end(), 0);\n     \
    \   while(fl > 0){\n            dijkstra(s);\n            if(min_cost[t] == INF<C>){\n\
    \                ok = 0;\n                return res;\n            }\n       \
    \     for (int i = 0; i < potential.size(); ++i) {\n                if(min_cost[i]\
    \ < INF<C>) potential[i] += min_cost[i];\n            }\n\n            F d = fl;\n\
    \            for(int v = t; v != s; v = prevv[v]){\n                d = min(d,\
    \ G[prevv[v]][preve[v]].cap);\n            }\n            fl -= d;\n         \
    \   res += potential[t]*d;\n            for(int v = t; v != s; v = prevv[v]){\n\
    \                G[prevv[v]][preve[v]].cap -= d;\n                G[v][G[prevv[v]][preve[v]].rev].cap\
    \ += d;\n            }\n        }\n        ok = 1;\n        return res;\n    }\n\
    };\n\n/**\n * @brief \u6700\u5C0F\u8CBB\u7528\u6D41(primal-dual)\n * @docs _md/primaldual.md\n\
    \ */\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/primaldual.cpp
  requiredBy: []
  timestamp: '2020-05-19 17:07:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0274.test.cpp
documentation_of: flow/primaldual.cpp
layout: document
redirect_from:
- /library/flow/primaldual.cpp
- /library/flow/primaldual.cpp.html
title: "\u6700\u5C0F\u8CBB\u7528\u6D41(primal-dual)"
---
## 説明
あとで書く