---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"flow/costscalingdinic.cpp\"\ntemplate<class T, bool directed>\n\
    class CostScalingDinic {\n    void bfs(int s, T x){\n        fill(level.begin(),level.end(),\
    \ -1);\n        queue<int> Q;\n        level[s] = 0;\n        Q.emplace(s);\n\
    \        while(!Q.empty()){\n            int v = Q.front(); Q.pop();\n       \
    \     for (auto &&e : G[v]){\n                if(e.cap >= x && level[e.to] < 0){\n\
    \                    level[e.to] = level[v] + 1;\n                    Q.emplace(e.to);\n\
    \                }\n            }\n        }\n    }\n\n    T dfs(int v, int t,\
    \ T x, T f){\n        if(v == t) return f;\n        T res = 0;\n        for(int\
    \ &i = iter[v]; i < G[v].size(); i++){\n            edge &e = G[v][i];\n     \
    \       if(e.cap >= x && level[v] < level[e.to]){\n                T d = dfs(e.to,\
    \ t, x, min(f-res,  e.cap));\n                if(d == 0) continue;\n         \
    \       e.cap -= d;\n                G[e.to][e.rev].cap += d;\n              \
    \  res += d;\n                if(f - res < x) break;\n            }\n        }\n\
    \        return res;\n    }\npublic:\n    struct edge {\n        int to{}; T cap;\
    \ int rev{};\n        edge() = default;\n        edge(int to, T cap, int rev)\
    \ : to(to), cap(cap), rev(rev) {}\n    };\n\n    vector<vector<edge>> G;\n   \
    \ vector<int> level, iter;\n    CostScalingDinic() = default;\n    explicit CostScalingDinic(int\
    \ n) : G(n), level(n), iter(n) {}\n\n    void add_edge(int from, int to, int cap){\n\
    \        if(!cap) return;\n        G[from].emplace_back(to, cap, G[to].size());\n\
    \        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);\n  \
    \  }\n\n    T flow(int s, int t, T lim = INF<T>){\n        T ret = 0;\n      \
    \  T cap = 1; while(cap<<1 <= lim) cap <<= 1;\n        while(cap) {\n        \
    \    bfs(s, cap);\n            if(level[t] < 0){\n                cap >>= 1;\n\
    \                continue;\n            }\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            ret += dfs(s, t, cap, INF<T>);\n        }\n        return ret;\n\
    \    }\n};\n"
  code: "template<class T, bool directed>\nclass CostScalingDinic {\n    void bfs(int\
    \ s, T x){\n        fill(level.begin(),level.end(), -1);\n        queue<int> Q;\n\
    \        level[s] = 0;\n        Q.emplace(s);\n        while(!Q.empty()){\n  \
    \          int v = Q.front(); Q.pop();\n            for (auto &&e : G[v]){\n \
    \               if(e.cap >= x && level[e.to] < 0){\n                    level[e.to]\
    \ = level[v] + 1;\n                    Q.emplace(e.to);\n                }\n \
    \           }\n        }\n    }\n\n    T dfs(int v, int t, T x, T f){\n      \
    \  if(v == t) return f;\n        T res = 0;\n        for(int &i = iter[v]; i <\
    \ G[v].size(); i++){\n            edge &e = G[v][i];\n            if(e.cap >=\
    \ x && level[v] < level[e.to]){\n                T d = dfs(e.to, t, x, min(f-res,\
    \  e.cap));\n                if(d == 0) continue;\n                e.cap -= d;\n\
    \                G[e.to][e.rev].cap += d;\n                res += d;\n       \
    \         if(f - res < x) break;\n            }\n        }\n        return res;\n\
    \    }\npublic:\n    struct edge {\n        int to{}; T cap; int rev{};\n    \
    \    edge() = default;\n        edge(int to, T cap, int rev) : to(to), cap(cap),\
    \ rev(rev) {}\n    };\n\n    vector<vector<edge>> G;\n    vector<int> level, iter;\n\
    \    CostScalingDinic() = default;\n    explicit CostScalingDinic(int n) : G(n),\
    \ level(n), iter(n) {}\n\n    void add_edge(int from, int to, int cap){\n    \
    \    if(!cap) return;\n        G[from].emplace_back(to, cap, G[to].size());\n\
    \        G[to].emplace_back(from, directed ? 0 : cap,  G[from].size()-1);\n  \
    \  }\n\n    T flow(int s, int t, T lim = INF<T>){\n        T ret = 0;\n      \
    \  T cap = 1; while(cap<<1 <= lim) cap <<= 1;\n        while(cap) {\n        \
    \    bfs(s, cap);\n            if(level[t] < 0){\n                cap >>= 1;\n\
    \                continue;\n            }\n            fill(iter.begin(),iter.end(),\
    \ 0);\n            ret += dfs(s, t, cap, INF<T>);\n        }\n        return ret;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/costscalingdinic.cpp
  requiredBy: []
  timestamp: '2020-04-27 18:41:45+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: flow/costscalingdinic.cpp
layout: document
redirect_from:
- /library/flow/costscalingdinic.cpp
- /library/flow/costscalingdinic.cpp.html
title: flow/costscalingdinic.cpp
---
