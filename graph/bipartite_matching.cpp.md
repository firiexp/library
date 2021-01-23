---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching_lexmin.cpp
    title: graph/bipartite_matching_lexmin.cpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0334.test.cpp
    title: test/aoj0334.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/bipartite_matching.md
    document_title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\u30C1\
      \u30F3\u30B0"
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
    \ */\n"
  code: "class Bipartite_Matching {\nprotected:\n    vector<vector<int>> G;\n    vector<int>\
    \ used, alive;\n    int t;\n    int l, r;\npublic:\n    vector<int> match;\n \
    \   explicit Bipartite_Matching(int l, int r): l(l), r(r), t(0), G(l+r), used(l+r,\
    \ 0), alive(l+r, -1), match(l+r, -1) {};\n\n    void add_edge(int a, int b){\n\
    \        G[a].emplace_back(b+l);\n        G[b+l].emplace_back(a);\n    }\n\n \
    \   bool dfs(int x){\n        used[x] = t;\n        for (auto &&i : G[x]) {\n\
    \            int w = match[i];\n            if(alive[i] == 0) continue;\n    \
    \        if(w == -1 || (used[w] != t && dfs(w))){\n                match[x] =\
    \ i;\n                match[i] = x;\n                return true;\n          \
    \  }\n        }\n        return false;\n    }\n\n    int matching() {\n      \
    \  int ans = 0;\n        for (int i = 0; i < G.size(); ++i) {\n            if(alive[i]\
    \ == 0) continue;\n            if(match[i] == -1) {\n                ++t;\n  \
    \              ans += dfs(i);\n            }\n        }\n        return ans;\n\
    \    }\n};\n\n/**\n * @brief \u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\
    \u30C3\u30C1\u30F3\u30B0\n * @docs _md/bipartite_matching.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_matching.cpp
  requiredBy:
  - graph/bipartite_matching_lexmin.cpp
  timestamp: '2020-06-18 18:23:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0334.test.cpp
documentation_of: graph/bipartite_matching.cpp
layout: document
redirect_from:
- /library/graph/bipartite_matching.cpp
- /library/graph/bipartite_matching.cpp.html
title: "\u4E8C\u90E8\u30B0\u30E9\u30D5\u306E\u6700\u5927\u30DE\u30C3\u30C1\u30F3\u30B0"
---
## 説明
最大流アルゴリズムを応用し、二部グラフの最大マッチングを求める。$O(VE)$
