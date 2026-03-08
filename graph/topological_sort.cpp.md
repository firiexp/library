---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_topological_sort.test.cpp
    title: test/yosupo_topological_sort.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/topological_sort.md
    document_title: Topological sort
    links: []
  bundledCode: "#line 1 \"graph/topological_sort.cpp\"\nvector<int> topological_sort(const\
    \ vector<vector<int>> &g) {\n    int n = g.size();\n    vector<int> state(n),\
    \ ord;\n    ord.reserve(n);\n    auto dfs = [&](auto &&self, int v) -> bool {\n\
    \        state[v] = 1;\n        for (auto &&to : g[v]) {\n            if (state[to]\
    \ == 1) return false;\n            if (state[to] == 0 && !self(self, to)) return\
    \ false;\n        }\n        state[v] = 2;\n        ord.emplace_back(v);\n   \
    \     return true;\n    };\n    for (int i = 0; i < n; ++i) {\n        if (state[i]\
    \ == 0 && !dfs(dfs, i)) return {};\n    }\n    reverse(ord.begin(), ord.end());\n\
    \    return ord;\n}\n\n/**\n * @brief Topological sort\n * @docs _md/topological_sort.md\n\
    \ */\n"
  code: "vector<int> topological_sort(const vector<vector<int>> &g) {\n    int n =\
    \ g.size();\n    vector<int> state(n), ord;\n    ord.reserve(n);\n    auto dfs\
    \ = [&](auto &&self, int v) -> bool {\n        state[v] = 1;\n        for (auto\
    \ &&to : g[v]) {\n            if (state[to] == 1) return false;\n            if\
    \ (state[to] == 0 && !self(self, to)) return false;\n        }\n        state[v]\
    \ = 2;\n        ord.emplace_back(v);\n        return true;\n    };\n    for (int\
    \ i = 0; i < n; ++i) {\n        if (state[i] == 0 && !dfs(dfs, i)) return {};\n\
    \    }\n    reverse(ord.begin(), ord.end());\n    return ord;\n}\n\n/**\n * @brief\
    \ Topological sort\n * @docs _md/topological_sort.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/topological_sort.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_topological_sort.test.cpp
documentation_of: graph/topological_sort.cpp
layout: document
redirect_from:
- /library/graph/topological_sort.cpp
- /library/graph/topological_sort.cpp.html
title: Topological sort
---
---
layout: post
title: Topological Sort
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフのトポロジカル順序を求める。
閉路があるときは空配列を返す。
計算量は `O(N + M)`。

## できること
- `vector<int> topological_sort(const vector<vector<int>>& g)`
  `g` のトポロジカル順序を返す。DAG でなければ空配列を返す

## 使い方
`g[v]` に `v -> to` を入れて使う。
順序は DFS の帰りがけ順を反転したものになる。
