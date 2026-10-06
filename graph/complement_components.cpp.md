---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_complement_components.test.cpp
    title: test/yosupo_aplusb_complement_components.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_connected_components_of_complement_graph.test.cpp
    title: test/yosupo_connected_components_of_complement_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u88DC\u30B0\u30E9\u30D5\u306E\u9023\u7D50\u6210\u5206"
    links: []
  bundledCode: "#line 1 \"graph/complement_components.cpp\"\nvector<vector<int>> complement_components(const\
    \ vector<vector<int>> &g) {\n    int n = g.size();\n    vector<int> next(n + 1),\
    \ marked(n, -1);\n    for(int v = 0; v < n; ++v) next[v] = v + 1;\n    next[n]\
    \ = 0;\n    vector<vector<int>> components;\n    while(next[n] != n) {\n     \
    \   int start = next[n];\n        next[n] = next[start];\n        components.push_back({start});\n\
    \        auto &component = components.back();\n        for(size_t i = 0; i < component.size();\
    \ ++i) {\n            int v = component[i];\n            for(int u : g[v]) marked[u]\
    \ = v;\n            int prev = n;\n            while(next[prev] != n) {\n    \
    \            int u = next[prev];\n                if(marked[u] == v) {\n     \
    \               prev = u;\n                } else {\n                    next[prev]\
    \ = next[u];\n                    component.push_back(u);\n                }\n\
    \            }\n        }\n    }\n    return components;\n}\n\n/**\n * @brief\
    \ \u88DC\u30B0\u30E9\u30D5\u306E\u9023\u7D50\u6210\u5206\n */\n"
  code: "vector<vector<int>> complement_components(const vector<vector<int>> &g) {\n\
    \    int n = g.size();\n    vector<int> next(n + 1), marked(n, -1);\n    for(int\
    \ v = 0; v < n; ++v) next[v] = v + 1;\n    next[n] = 0;\n    vector<vector<int>>\
    \ components;\n    while(next[n] != n) {\n        int start = next[n];\n     \
    \   next[n] = next[start];\n        components.push_back({start});\n        auto\
    \ &component = components.back();\n        for(size_t i = 0; i < component.size();\
    \ ++i) {\n            int v = component[i];\n            for(int u : g[v]) marked[u]\
    \ = v;\n            int prev = n;\n            while(next[prev] != n) {\n    \
    \            int u = next[prev];\n                if(marked[u] == v) {\n     \
    \               prev = u;\n                } else {\n                    next[prev]\
    \ = next[u];\n                    component.push_back(u);\n                }\n\
    \            }\n        }\n    }\n    return components;\n}\n\n/**\n * @brief\
    \ \u88DC\u30B0\u30E9\u30D5\u306E\u9023\u7D50\u6210\u5206\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/complement_components.cpp
  requiredBy: []
  timestamp: '2026-10-07 00:51:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_connected_components_of_complement_graph.test.cpp
  - test/yosupo_aplusb_complement_components.test.cpp
documentation_of: graph/complement_components.cpp
layout: document
title: "\u88DC\u30B0\u30E9\u30D5\u306E\u9023\u7D50\u6210\u5206"
---

## 説明
単純無向グラフの補グラフについて、連結成分を列挙する。
補グラフの隣接リストを作らず、時間 $O(N+M)$、入力・出力を除く作業領域 $O(N)$ で求める。

## できること
- `vector<vector<int>> complement_components(const vector<vector<int>>& g)`
  補グラフの各連結成分を頂点列として返す。空グラフなら空の配列

## 使い方
`g` は頂点番号 `0` から `n-1` の対称な隣接リストとし、自己ループ・平行辺を含めない。

```cpp
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);
auto components = complement_components(g);
```

入力は変更しない。各頂点は結果にちょうど1回現れる。
成分の順序と、成分内の頂点の順序は保証しない。

## 実装上の補足
未訪問頂点を連結リストで管理し、元のグラフで隣接していない頂点を取り出して探索する。
取り出す処理は各頂点に1回だけで、取り出さずに通過する処理は元の辺に対応する。
