---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_eulerian_trail_directed.test.cpp
    title: test/yosupo_eulerian_trail_directed.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_eulerian_trail_undirected.test.cpp
    title: test/yosupo_eulerian_trail_undirected.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/eulerian_trail.md
    document_title: "\u30AA\u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)"
    links: []
  bundledCode: "#line 1 \"graph/eulerian_trail.cpp\"\ntemplate<bool directed>\nstruct\
    \ EulerianTrail {\n    struct Edge {\n        int from, to;\n    };\n\n    struct\
    \ Result {\n        bool exists;\n        vector<int> vertices;\n        vector<int>\
    \ edge_ids;\n    };\n\n    int n;\n    vector<Edge> edges;\n    vector<vector<pair<int,\
    \ int>>> g;\n\n    explicit EulerianTrail(int n) : n(n), g(n) {}\n\n    int add_edge(int\
    \ from, int to) {\n        int id = (int)edges.size();\n        edges.push_back({from,\
    \ to});\n        g[from].push_back({to, id});\n        if constexpr (!directed)\
    \ g[to].push_back({from, id});\n        return id;\n    }\n\n    Result solve()\
    \ const {\n        int m = edges.size();\n        if (m == 0) {\n            return\
    \ {true, {0}, {}};\n        }\n\n        vector<int> indeg(n), outdeg(n), deg(n);\n\
    \        for (auto&& e : edges) {\n            ++outdeg[e.from];\n           \
    \ ++indeg[e.to];\n            ++deg[e.from];\n            ++deg[e.to];\n     \
    \   }\n\n        int start = -1, plus = 0, minus = 0;\n        if constexpr (directed)\
    \ {\n            for (int v = 0; v < n; ++v) {\n                int diff = outdeg[v]\
    \ - indeg[v];\n                if (diff == 1) {\n                    start = v;\n\
    \                    ++plus;\n                } else if (diff == -1) {\n     \
    \               ++minus;\n                } else if (diff != 0) {\n          \
    \          return {false, {}, {}};\n                }\n            }\n       \
    \     if (!((plus == 1 && minus == 1) || (plus == 0 && minus == 0))) {\n     \
    \           return {false, {}, {}};\n            }\n            if (start == -1)\
    \ {\n                for (int v = 0; v < n; ++v) {\n                    if (outdeg[v]\
    \ > 0) {\n                        start = v;\n                        break;\n\
    \                    }\n                }\n            }\n        } else {\n \
    \           int odd = 0;\n            for (int v = 0; v < n; ++v) {\n        \
    \        if (deg[v] & 1) {\n                    start = v;\n                 \
    \   ++odd;\n                }\n            }\n            if (!(odd == 0 || odd\
    \ == 2)) return {false, {}, {}};\n            if (start == -1) {\n           \
    \     for (int v = 0; v < n; ++v) {\n                    if (deg[v] > 0) {\n \
    \                       start = v;\n                        break;\n         \
    \           }\n                }\n            }\n        }\n\n        vector<int>\
    \ ptr(n), used(m);\n        vector<int> st_v{start}, st_e{-1};\n        vector<int>\
    \ vs, es;\n        while (!st_v.empty()) {\n            int v = st_v.back();\n\
    \            while (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].second]) ++ptr[v];\n\
    \            if (ptr[v] == (int)g[v].size()) {\n                vs.push_back(v);\n\
    \                st_v.pop_back();\n                int id = st_e.back();\n   \
    \             st_e.pop_back();\n                if (id != -1) es.push_back(id);\n\
    \                continue;\n            }\n            auto [to, id] = g[v][ptr[v]++];\n\
    \            if (used[id]) continue;\n            used[id] = 1;\n            st_v.push_back(to);\n\
    \            st_e.push_back(id);\n        }\n\n        if ((int)es.size() != m)\
    \ return {false, {}, {}};\n        reverse(vs.begin(), vs.end());\n        reverse(es.begin(),\
    \ es.end());\n        return {true, vs, es};\n    }\n};\n\n/**\n * @brief \u30AA\
    \u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)\n * @docs _md/eulerian_trail.md\n */\n"
  code: "template<bool directed>\nstruct EulerianTrail {\n    struct Edge {\n    \
    \    int from, to;\n    };\n\n    struct Result {\n        bool exists;\n    \
    \    vector<int> vertices;\n        vector<int> edge_ids;\n    };\n\n    int n;\n\
    \    vector<Edge> edges;\n    vector<vector<pair<int, int>>> g;\n\n    explicit\
    \ EulerianTrail(int n) : n(n), g(n) {}\n\n    int add_edge(int from, int to) {\n\
    \        int id = (int)edges.size();\n        edges.push_back({from, to});\n \
    \       g[from].push_back({to, id});\n        if constexpr (!directed) g[to].push_back({from,\
    \ id});\n        return id;\n    }\n\n    Result solve() const {\n        int\
    \ m = edges.size();\n        if (m == 0) {\n            return {true, {0}, {}};\n\
    \        }\n\n        vector<int> indeg(n), outdeg(n), deg(n);\n        for (auto&&\
    \ e : edges) {\n            ++outdeg[e.from];\n            ++indeg[e.to];\n  \
    \          ++deg[e.from];\n            ++deg[e.to];\n        }\n\n        int\
    \ start = -1, plus = 0, minus = 0;\n        if constexpr (directed) {\n      \
    \      for (int v = 0; v < n; ++v) {\n                int diff = outdeg[v] - indeg[v];\n\
    \                if (diff == 1) {\n                    start = v;\n          \
    \          ++plus;\n                } else if (diff == -1) {\n               \
    \     ++minus;\n                } else if (diff != 0) {\n                    return\
    \ {false, {}, {}};\n                }\n            }\n            if (!((plus\
    \ == 1 && minus == 1) || (plus == 0 && minus == 0))) {\n                return\
    \ {false, {}, {}};\n            }\n            if (start == -1) {\n          \
    \      for (int v = 0; v < n; ++v) {\n                    if (outdeg[v] > 0) {\n\
    \                        start = v;\n                        break;\n        \
    \            }\n                }\n            }\n        } else {\n         \
    \   int odd = 0;\n            for (int v = 0; v < n; ++v) {\n                if\
    \ (deg[v] & 1) {\n                    start = v;\n                    ++odd;\n\
    \                }\n            }\n            if (!(odd == 0 || odd == 2)) return\
    \ {false, {}, {}};\n            if (start == -1) {\n                for (int v\
    \ = 0; v < n; ++v) {\n                    if (deg[v] > 0) {\n                \
    \        start = v;\n                        break;\n                    }\n \
    \               }\n            }\n        }\n\n        vector<int> ptr(n), used(m);\n\
    \        vector<int> st_v{start}, st_e{-1};\n        vector<int> vs, es;\n   \
    \     while (!st_v.empty()) {\n            int v = st_v.back();\n            while\
    \ (ptr[v] < (int)g[v].size() && used[g[v][ptr[v]].second]) ++ptr[v];\n       \
    \     if (ptr[v] == (int)g[v].size()) {\n                vs.push_back(v);\n  \
    \              st_v.pop_back();\n                int id = st_e.back();\n     \
    \           st_e.pop_back();\n                if (id != -1) es.push_back(id);\n\
    \                continue;\n            }\n            auto [to, id] = g[v][ptr[v]++];\n\
    \            if (used[id]) continue;\n            used[id] = 1;\n            st_v.push_back(to);\n\
    \            st_e.push_back(id);\n        }\n\n        if ((int)es.size() != m)\
    \ return {false, {}, {}};\n        reverse(vs.begin(), vs.end());\n        reverse(es.begin(),\
    \ es.end());\n        return {true, vs, es};\n    }\n};\n\n/**\n * @brief \u30AA\
    \u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)\n * @docs _md/eulerian_trail.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/eulerian_trail.cpp
  requiredBy: []
  timestamp: '2026-03-08 20:56:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_eulerian_trail_directed.test.cpp
  - test/yosupo_eulerian_trail_undirected.test.cpp
documentation_of: graph/eulerian_trail.cpp
layout: document
redirect_from:
- /library/graph/eulerian_trail.cpp
- /library/graph/eulerian_trail.cpp.html
title: "\u30AA\u30A4\u30E9\u30FC\u8DEF(Eulerian Trail)"
---
---
layout: post
title: Eulerian Trail
date: 2026-03-08
category: グラフ
tags: グラフ
---

## 説明
有向グラフまたは無向グラフの Eulerian trail / circuit を 1 つ構成する。
辺をちょうど 1 回ずつ通る頂点列と辺番号列を返す。

## できること
- `EulerianTrail<false> g(n)`
  頂点数 `n` の無向グラフを作る
- `EulerianTrail<true> g(n)`
  頂点数 `n` の有向グラフを作る
- `int add_edge(int from, int to)`
  辺を追加し、辺番号を返す
- `Result solve()`
  Eulerian trail が存在すれば構成を返す。存在しないとき `exists == false`

`Result` は次を持つ。

- `bool exists`
  Eulerian trail が存在するか
- `vector<int> vertices`
  通る頂点列。長さは `M + 1`
- `vector<int> edge_ids`
  通る辺番号列。長さは `M`

## 使い方
全辺を `add_edge` で追加し、`solve()` を呼ぶ。
`vertices[i] -> vertices[i + 1]` に対応する辺番号が `edge_ids[i]` に入る。

## 実装上の補足
Hierholzer 法で構成する。
計算量は `O(N + M)`。
