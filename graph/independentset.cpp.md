---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/independentset.cpp\"\nclass IndependentSet {\n   \
    \ int n;\n    vector<vector<int>> G;\n    void dfs(int x, vector<bool> &visited,\
    \ vector<bool> &gcan, vector<bool> &alive){\n        stack<int> s;\n        s.emplace(x);\n\
    \        while(!s.empty()){\n            int y = s.top();\n            visited[y]\
    \ = true;\n            gcan[y] = true;\n            s.pop();\n            for\
    \ (auto &&i : G[y]) {\n                if(!visited[i] && alive[i]) s.emplace(i);\n\
    \            }\n        }\n    }\n\n    int ConnectedCase(vector<bool> can) {\n\
    \        int pMax = -1, pMin = -1, Max = -1, Min = n+1, num = 0;\n        for\
    \ (int i = 0; i < n; ++i) {\n            if(!can[i]) continue;\n            ++num;\n\
    \            int tnum = 0;\n            for (auto &&j : G[i]) if(can[j]) ++tnum;\n\
    \            if(Max < tnum) Max = tnum, pMax = i;\n            if(Min > tnum)\
    \ Min = tnum, pMin = i;\n        }\n        if(num == 1) return 1;\n        if(Max\
    \ <= 2){\n            if(Min == 1) return (num+1)/2;\n            else return\
    \ num/2;\n        }\n        int ans = 0;\n        vector<bool> ncan = can;\n\
    \        if(Min < 2){\n            ncan[pMin] = false;\n            for (auto\
    \ &&i : G[pMin]) ncan[i] = false;\n            ans = max(ans, GeneralCase(ncan)\
    \ + 1);\n        }else {\n            ncan[pMax] = false;\n            for (auto\
    \ &&i : G[pMax]) ncan[i] = false;\n            int temp = GeneralCase(ncan);\n\
    \            ans = max(ans, temp+1);\n            ncan = can;\n            ncan[pMax]\
    \ = false;\n            ans = max(ans, GeneralCase(ncan));\n        }\n      \
    \  return ans;\n    }\n\n    int GeneralCase(vector<bool> alive) {\n        if(n\
    \ <= 1) return n;\n        vector<bool> visited(n, 0);\n        int res = 0;\n\
    \        for (int i = 0; i < n; ++i) {\n            if(!visited[i] && alive[i]){\n\
    \                vector<bool> gcan(n, false);\n                dfs(i, visited,\
    \ gcan, alive);\n                res += ConnectedCase(gcan);\n            }\n\
    \        }\n        return res;\n    }\npublic:\n    explicit IndependentSet(int\
    \ n): n(n), G(n) {}\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n\
    \        G[v].emplace_back(u);\n    }\n    int stable_set() {\n        vector<bool>\
    \ alive(n, true);\n        return GeneralCase(alive);\n    }\n};\n"
  code: "class IndependentSet {\n    int n;\n    vector<vector<int>> G;\n    void\
    \ dfs(int x, vector<bool> &visited, vector<bool> &gcan, vector<bool> &alive){\n\
    \        stack<int> s;\n        s.emplace(x);\n        while(!s.empty()){\n  \
    \          int y = s.top();\n            visited[y] = true;\n            gcan[y]\
    \ = true;\n            s.pop();\n            for (auto &&i : G[y]) {\n       \
    \         if(!visited[i] && alive[i]) s.emplace(i);\n            }\n        }\n\
    \    }\n\n    int ConnectedCase(vector<bool> can) {\n        int pMax = -1, pMin\
    \ = -1, Max = -1, Min = n+1, num = 0;\n        for (int i = 0; i < n; ++i) {\n\
    \            if(!can[i]) continue;\n            ++num;\n            int tnum =\
    \ 0;\n            for (auto &&j : G[i]) if(can[j]) ++tnum;\n            if(Max\
    \ < tnum) Max = tnum, pMax = i;\n            if(Min > tnum) Min = tnum, pMin =\
    \ i;\n        }\n        if(num == 1) return 1;\n        if(Max <= 2){\n     \
    \       if(Min == 1) return (num+1)/2;\n            else return num/2;\n     \
    \   }\n        int ans = 0;\n        vector<bool> ncan = can;\n        if(Min\
    \ < 2){\n            ncan[pMin] = false;\n            for (auto &&i : G[pMin])\
    \ ncan[i] = false;\n            ans = max(ans, GeneralCase(ncan) + 1);\n     \
    \   }else {\n            ncan[pMax] = false;\n            for (auto &&i : G[pMax])\
    \ ncan[i] = false;\n            int temp = GeneralCase(ncan);\n            ans\
    \ = max(ans, temp+1);\n            ncan = can;\n            ncan[pMax] = false;\n\
    \            ans = max(ans, GeneralCase(ncan));\n        }\n        return ans;\n\
    \    }\n\n    int GeneralCase(vector<bool> alive) {\n        if(n <= 1) return\
    \ n;\n        vector<bool> visited(n, 0);\n        int res = 0;\n        for (int\
    \ i = 0; i < n; ++i) {\n            if(!visited[i] && alive[i]){\n           \
    \     vector<bool> gcan(n, false);\n                dfs(i, visited, gcan, alive);\n\
    \                res += ConnectedCase(gcan);\n            }\n        }\n     \
    \   return res;\n    }\npublic:\n    explicit IndependentSet(int n): n(n), G(n)\
    \ {}\n    void add_edge(int u, int v){\n        G[u].emplace_back(v);\n      \
    \  G[v].emplace_back(u);\n    }\n    int stable_set() {\n        vector<bool>\
    \ alive(n, true);\n        return GeneralCase(alive);\n    }\n};"
  dependsOn: []
  isVerificationFile: false
  path: graph/independentset.cpp
  requiredBy: []
  timestamp: '2020-04-26 17:42:59+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/independentset.cpp
layout: document
redirect_from:
- /library/graph/independentset.cpp
- /library/graph/independentset.cpp.html
title: graph/independentset.cpp
---
