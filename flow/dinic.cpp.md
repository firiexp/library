---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0396.test.cpp
    title: test/aoj0396.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
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
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};\n"
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
    \ -= f;\n            }\n        }\n        return ret;\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: flow/dinic.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0396.test.cpp
documentation_of: flow/dinic.cpp
layout: document
redirect_from:
- /library/flow/dinic.cpp
- /library/flow/dinic.cpp.html
title: flow/dinic.cpp
---
