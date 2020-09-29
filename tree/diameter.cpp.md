---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"tree/diameter.cpp\"\nint diameter(vector<vector<int>> &G){\n\
    \    vector<int> dist(G.size());\n    int s = 0;\n    auto dfs = [&](int x, int\
    \ par, auto &&f) -> void {\n        for (auto &&i : G[x]) {\n            if(i\
    \ != par){\n                dist[i] = dist[x] + 1;\n                if(dist[s]\
    \ < dist[i]) s = i;\n                f(i, x, f);\n            }\n        }\n \
    \   };\n    dist[s] = 0;\n    dfs(s, -1, dfs);\n    dist[s] = 0;\n    dfs(s, -1,\
    \ dfs);\n    return dist[s];\n}\n"
  code: "int diameter(vector<vector<int>> &G){\n    vector<int> dist(G.size());\n\
    \    int s = 0;\n    auto dfs = [&](int x, int par, auto &&f) -> void {\n    \
    \    for (auto &&i : G[x]) {\n            if(i != par){\n                dist[i]\
    \ = dist[x] + 1;\n                if(dist[s] < dist[i]) s = i;\n             \
    \   f(i, x, f);\n            }\n        }\n    };\n    dist[s] = 0;\n    dfs(s,\
    \ -1, dfs);\n    dist[s] = 0;\n    dfs(s, -1, dfs);\n    return dist[s];\n}"
  dependsOn: []
  isVerificationFile: false
  path: tree/diameter.cpp
  requiredBy: []
  timestamp: '2020-09-03 13:29:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tree/diameter.cpp
layout: document
redirect_from:
- /library/tree/diameter.cpp
- /library/tree/diameter.cpp.html
title: tree/diameter.cpp
---
