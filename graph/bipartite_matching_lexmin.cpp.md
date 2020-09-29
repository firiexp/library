---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.cpp
    title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\u30C1\u30F3\
      \u30B0"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0334.test.cpp
    title: test/aoj0334.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"graph/bipartite_matching.cpp\"\nclass Bipartite_Matching\
    \ {\nprotected:\n    vector<vector<int>> G;\n    vector<int> used, alive;\n  \
    \  int t;\n    int l, r;\npublic:\n    vector<int> match;\n    explicit Bipartite_Matching(int\
    \ l, int r): l(l), r(r), t(0), G(l+r), used(l+r, 0), alive(l+r, -1), match(l+r,\
    \ -1) {};\n\n    void add_edge(int a, int b){\n        G[a].emplace_back(b+l);\n\
    \        G[b+l].emplace_back(a);\n    }\n\n    bool dfs(int x){\n        used[x]\
    \ = t;\n        for (auto &&i : G[x]) {\n            int w = match[i];\n     \
    \       if(alive[i] == 0) continue;\n            if(w == -1 || (used[w] != t &&\
    \ dfs(w))){\n                match[x] = i;\n                match[i] = x;\n  \
    \              return true;\n            }\n        }\n        return false;\n\
    \    }\n\n    int matching() {\n        int ans = 0;\n        for (int i = 0;\
    \ i < G.size(); ++i) {\n            if(alive[i] == 0) continue;\n            if(match[i]\
    \ == -1) {\n                ++t;\n                ans += dfs(i);\n           \
    \ }\n        }\n        return ans;\n    }\n};\n\n/**\n * @brief \u4E8C\u90E8\u30B0\
    \u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0\n * @docs _md/bipartite_matching.md\n\
    \ */\n#line 2 \"graph/bipartite_matching_lexmin.cpp\"\nclass Bipartite_Matching_LexMin\
    \ : public Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() { // check sorted edge no\n        int res = matching();\n\
    \        for (int i = 0; i < l; ++i) {\n            if(!~match[i]) continue;\n\
    \            match[match[i]] = -1;\n            match[i] = -1;\n            ++t;\n\
    \            dfs(i);\n            alive[match[i]] = 0;\n            alive[i] =\
    \ 0;\n        }\n        return res;\n    }\n};\n"
  code: "#include \"./bipartite_matching.cpp\"\nclass Bipartite_Matching_LexMin :\
    \ public Bipartite_Matching {\npublic:\n    using Bipartite_Matching::Bipartite_Matching;\n\
    \n    int solve_LexMin() { // check sorted edge no\n        int res = matching();\n\
    \        for (int i = 0; i < l; ++i) {\n            if(!~match[i]) continue;\n\
    \            match[match[i]] = -1;\n            match[i] = -1;\n            ++t;\n\
    \            dfs(i);\n            alive[match[i]] = 0;\n            alive[i] =\
    \ 0;\n        }\n        return res;\n    }\n};"
  dependsOn:
  - graph/bipartite_matching.cpp
  isVerificationFile: false
  path: graph/bipartite_matching_lexmin.cpp
  requiredBy: []
  timestamp: '2020-06-18 18:23:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0334.test.cpp
documentation_of: graph/bipartite_matching_lexmin.cpp
layout: document
redirect_from:
- /library/graph/bipartite_matching_lexmin.cpp
- /library/graph/bipartite_matching_lexmin.cpp.html
title: graph/bipartite_matching_lexmin.cpp
---
