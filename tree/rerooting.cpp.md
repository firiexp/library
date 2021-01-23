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
  bundledCode: "#line 1 \"tree/rerooting.cpp\"\ntemplate<typename M>\nclass ReRooting\
    \ {\npublic:\n    using T = typename M::T;\n    using U = typename M::U;\n   \
    \ struct Node {\n        int to, rev;\n        U val;\n        Node(int u, int\
    \ v, U val) : to(u), rev(v), val(val) {};\n    };\n    int n;\n    vector<vector<Node>>\
    \ G;\n    vector<vector<T>> dpl, dpr;\n    vector<int> l, r;\n\n    explicit ReRooting(int\
    \ n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {};\n\n    void add_edge(int u,\
    \ int v, const U &x) {\n        G[u].emplace_back(v, G[v].size(), x);\n      \
    \  G[v].emplace_back(u, G[u].size()-1, x);\n    }\n    void add_edge(int u, int\
    \ v, const U &x, const U &y) {\n        G[u].emplace_back(v, G[v].size(), x);\n\
    \        G[v].emplace_back(u, G[u].size()-1, y);\n    }\n\n    T dfs(int i, int\
    \ par){\n        while(l[i] != par && l[i] < G[i].size()){\n            auto &e\
    \ = G[i][l[i]];\n            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to,\
    \ e.rev), e.val));\n            ++l[i];\n        }\n        while(r[i] != par\
    \ && r[i] >= 0){\n            auto &e = G[i][r[i]];\n            dpr[i][r[i]]\
    \ = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));\n            --r[i];\n\
    \        }\n        if(par < 0) return dpr[i].front();\n        return M::f(dpl[i][par],\
    \ dpr[i][par+1]);\n    }\n\n    vector<T> solve(){\n        for (int i = 0; i\
    \ < n; ++i) {\n            dpl[i].assign(G[i].size()+1, M::e());\n           \
    \ dpr[i].assign(G[i].size()+1, M::e());\n            l[i] = 0;\n            r[i]\
    \ = (int)G[i].size() - 1;\n        }\n        vector<T> ans(n);\n        for (int\
    \ i = 0; i < n; ++i) {\n            ans[i] = dfs(i, -1);\n        }\n        return\
    \ ans;\n    }\n};\n\nstruct M {\n    using T = mint;\n    using U = mint;\n  \
    \  static T f(T a, T b) { return a*b; }\n    static T g(T a, U b) {\n        return\
    \ a+b;\n    }\n    static T e() { return {1}; }\n};\n"
  code: "template<typename M>\nclass ReRooting {\npublic:\n    using T = typename\
    \ M::T;\n    using U = typename M::U;\n    struct Node {\n        int to, rev;\n\
    \        U val;\n        Node(int u, int v, U val) : to(u), rev(v), val(val) {};\n\
    \    };\n    int n;\n    vector<vector<Node>> G;\n    vector<vector<T>> dpl, dpr;\n\
    \    vector<int> l, r;\n\n    explicit ReRooting(int n) : n(n), G(n), dpl(n),\
    \ dpr(n), l(n), r(n) {};\n\n    void add_edge(int u, int v, const U &x) {\n  \
    \      G[u].emplace_back(v, G[v].size(), x);\n        G[v].emplace_back(u, G[u].size()-1,\
    \ x);\n    }\n    void add_edge(int u, int v, const U &x, const U &y) {\n    \
    \    G[u].emplace_back(v, G[v].size(), x);\n        G[v].emplace_back(u, G[u].size()-1,\
    \ y);\n    }\n\n    T dfs(int i, int par){\n        while(l[i] != par && l[i]\
    \ < G[i].size()){\n            auto &e = G[i][l[i]];\n            dpl[i][l[i]\
    \ + 1] = M::f(dpl[i][l[i]], M::g(dfs(e.to, e.rev), e.val));\n            ++l[i];\n\
    \        }\n        while(r[i] != par && r[i] >= 0){\n            auto &e = G[i][r[i]];\n\
    \            dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));\n\
    \            --r[i];\n        }\n        if(par < 0) return dpr[i].front();\n\
    \        return M::f(dpl[i][par], dpr[i][par+1]);\n    }\n\n    vector<T> solve(){\n\
    \        for (int i = 0; i < n; ++i) {\n            dpl[i].assign(G[i].size()+1,\
    \ M::e());\n            dpr[i].assign(G[i].size()+1, M::e());\n            l[i]\
    \ = 0;\n            r[i] = (int)G[i].size() - 1;\n        }\n        vector<T>\
    \ ans(n);\n        for (int i = 0; i < n; ++i) {\n            ans[i] = dfs(i,\
    \ -1);\n        }\n        return ans;\n    }\n};\n\nstruct M {\n    using T =\
    \ mint;\n    using U = mint;\n    static T f(T a, T b) { return a*b; }\n    static\
    \ T g(T a, U b) {\n        return a+b;\n    }\n    static T e() { return {1};\
    \ }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/rerooting.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/rerooting.cpp
layout: document
redirect_from:
- /library/tree/rerooting.cpp
- /library/tree/rerooting.cpp.html
title: tree/rerooting.cpp
---
