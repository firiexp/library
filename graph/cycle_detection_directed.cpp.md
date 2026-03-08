---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_cycle_detection_directed.test.cpp
    title: test/yosupo_cycle_detection_directed.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/cycle_detection_directed.md
    document_title: Cycle detection (directed)
    links: []
  bundledCode: "#line 1 \"graph/cycle_detection_directed.cpp\"\nvector<int> cycle_detection_directed(const\
    \ vector<vector<pair<int, int>>> &g) {\n    int n = g.size();\n    vector<int>\
    \ state(n), st_v, st_e;\n    vector<int> cycle;\n    auto dfs = [&](auto &&self,\
    \ int v) -> bool {\n        state[v] = 1;\n        st_v.emplace_back(v);\n   \
    \     for (auto &&[to, id] : g[v]) {\n            st_e.emplace_back(id);\n   \
    \         if (state[to] == 0) {\n                if (self(self, to)) return true;\n\
    \            } else if (state[to] == 1) {\n                cycle.emplace_back(id);\n\
    \                for (int i = (int)st_v.size() - 1; st_v[i] != to; --i) {\n  \
    \                  cycle.emplace_back(st_e[i - 1]);\n                }\n     \
    \           reverse(cycle.begin(), cycle.end());\n                return true;\n\
    \            }\n            st_e.pop_back();\n        }\n        st_v.pop_back();\n\
    \        state[v] = 2;\n        return false;\n    };\n    for (int i = 0; i <\
    \ n; ++i) {\n        if (state[i] == 0 && dfs(dfs, i)) return cycle;\n    }\n\
    \    return {};\n}\n\n/**\n * @brief Cycle detection (directed)\n * @docs _md/cycle_detection_directed.md\n\
    \ */\n"
  code: "vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>>\
    \ &g) {\n    int n = g.size();\n    vector<int> state(n), st_v, st_e;\n    vector<int>\
    \ cycle;\n    auto dfs = [&](auto &&self, int v) -> bool {\n        state[v] =\
    \ 1;\n        st_v.emplace_back(v);\n        for (auto &&[to, id] : g[v]) {\n\
    \            st_e.emplace_back(id);\n            if (state[to] == 0) {\n     \
    \           if (self(self, to)) return true;\n            } else if (state[to]\
    \ == 1) {\n                cycle.emplace_back(id);\n                for (int i\
    \ = (int)st_v.size() - 1; st_v[i] != to; --i) {\n                    cycle.emplace_back(st_e[i\
    \ - 1]);\n                }\n                reverse(cycle.begin(), cycle.end());\n\
    \                return true;\n            }\n            st_e.pop_back();\n \
    \       }\n        st_v.pop_back();\n        state[v] = 2;\n        return false;\n\
    \    };\n    for (int i = 0; i < n; ++i) {\n        if (state[i] == 0 && dfs(dfs,\
    \ i)) return cycle;\n    }\n    return {};\n}\n\n/**\n * @brief Cycle detection\
    \ (directed)\n * @docs _md/cycle_detection_directed.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/cycle_detection_directed.cpp
  requiredBy: []
  timestamp: '2026-03-08 16:57:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_cycle_detection_directed.test.cpp
documentation_of: graph/cycle_detection_directed.cpp
layout: document
redirect_from:
- /library/graph/cycle_detection_directed.cpp
- /library/graph/cycle_detection_directed.cpp.html
title: Cycle detection (directed)
---
---
layout: post
title: Cycle Detection Directed
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフから 1 つサイクルを見つける。
見つからなければ空配列を返す。
計算量は `O(N + M)`。

## できること
- `vector<int> cycle_detection_directed(const vector<vector<pair<int, int>>>& g)`
  辺番号列としてサイクルを返す。存在しなければ空配列を返す

## 使い方
`g[v]` に `(to, edge_id)` を入れて使う。
返る辺番号列は順に辿ると有向サイクルになる。
