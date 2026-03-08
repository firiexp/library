---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_diameter_unweighted.test.cpp
    title: test/yosupo_many_aplusb_diameter_unweighted.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u306E\u76F4\u5F84(Tree Diameter)"
    links: []
  bundledCode: "#line 1 \"tree/diameter.cpp\"\npair<int, pair<int, int>> tree_diameter(const\
    \ vector<vector<int>> &G) {\n    int n = G.size();\n    if (n == 0) return {0,\
    \ {-1, -1}};\n\n    vector<int> dist(n);\n    int far = 0;\n    auto dfs = [&](int\
    \ v, int p, auto &&f) -> void {\n        for (auto &&to : G[v]) {\n          \
    \  if (to == p) continue;\n            dist[to] = dist[v] + 1;\n            if\
    \ (dist[far] < dist[to]) far = to;\n            f(to, v, f);\n        }\n    };\n\
    \n    dist[0] = 0;\n    dfs(0, -1, dfs);\n    int s = far;\n    dist[s] = 0;\n\
    \    dfs(s, -1, dfs);\n    return {dist[far], {s, far}};\n}\n\nint diameter(const\
    \ vector<vector<int>> &G) {\n    return tree_diameter(G).first;\n}\n\n/**\n *\
    \ @brief \u6728\u306E\u76F4\u5F84(Tree Diameter)\n */\n"
  code: "pair<int, pair<int, int>> tree_diameter(const vector<vector<int>> &G) {\n\
    \    int n = G.size();\n    if (n == 0) return {0, {-1, -1}};\n\n    vector<int>\
    \ dist(n);\n    int far = 0;\n    auto dfs = [&](int v, int p, auto &&f) -> void\
    \ {\n        for (auto &&to : G[v]) {\n            if (to == p) continue;\n  \
    \          dist[to] = dist[v] + 1;\n            if (dist[far] < dist[to]) far\
    \ = to;\n            f(to, v, f);\n        }\n    };\n\n    dist[0] = 0;\n   \
    \ dfs(0, -1, dfs);\n    int s = far;\n    dist[s] = 0;\n    dfs(s, -1, dfs);\n\
    \    return {dist[far], {s, far}};\n}\n\nint diameter(const vector<vector<int>>\
    \ &G) {\n    return tree_diameter(G).first;\n}\n\n/**\n * @brief \u6728\u306E\u76F4\
    \u5F84(Tree Diameter)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/diameter.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_diameter_unweighted.test.cpp
documentation_of: tree/diameter.cpp
layout: document
title: "\u6728\u306E\u76F4\u5F84(Tree Diameter)"
---
## 説明
重みなし木の直径長とその両端点を `O(N)` で求める。

## できること
- `pair<int, pair<int, int>> tree_diameter(const vector<vector<int>> &g)`
  直径を返す。戻り値の `first` は辺数としての直径長、`second.first` と `second.second` は両端点
- `int diameter(const vector<vector<int>> &g)`
  直径長だけを返す

## 使い方
隣接リストを `vector<vector<int>>` で持ち、`tree_diameter(g)` を呼ぶ。

```cpp
vector<vector<int>> g(n);
g[u].push_back(v);
g[v].push_back(u);

auto [dist, ends] = tree_diameter(g);
int s = ends.first;
int t = ends.second;
```

直径長だけ欲しいなら `diameter(g)` を使えばよい。
重み付き木には `diameter_weighted.cpp` の `tree_diameter_weighted` を使う。

## 実装上の補足
任意の頂点から最遠点 `s` を取り、さらに `s` から最遠点を取る 2 回 DFS で求める。
木を仮定しているので、連結で閉路のないグラフに対して使う。
