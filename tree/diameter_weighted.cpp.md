---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_5_a_diameter.test.cpp
    title: test/aoj_grl_5_a_diameter.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    _deprecated_at_docs: _md/diameter_weighted.md
    document_title: Tree Diameter (Weighted)
    links: []
  bundledCode: "#line 1 \"tree/diameter_weighted.cpp\"\ntemplate<class T>\npair<T,\
    \ pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int, T>>> &G)\
    \ {\n    int n = G.size();\n    if (n == 0) return {T(), {-1, -1}};\n\n    vector<T>\
    \ dist(n);\n    int far = 0;\n    auto dfs = [&](int v, int p, auto &&f) -> void\
    \ {\n        for (auto &&e : G[v]) {\n            int to = e.first;\n        \
    \    T cost = e.second;\n            if (to == p) continue;\n            dist[to]\
    \ = dist[v] + cost;\n            if (dist[far] < dist[to]) far = to;\n       \
    \     f(to, v, f);\n        }\n    };\n\n    dist[0] = T();\n    dfs(0, -1, dfs);\n\
    \    int s = far;\n    dist[s] = T();\n    dfs(s, -1, dfs);\n    return {dist[far],\
    \ {s, far}};\n}\n\n/**\n * @brief Tree Diameter (Weighted)\n * @docs _md/diameter_weighted.md\n\
    \ */\n"
  code: "template<class T>\npair<T, pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int,\
    \ T>>> &G) {\n    int n = G.size();\n    if (n == 0) return {T(), {-1, -1}};\n\
    \n    vector<T> dist(n);\n    int far = 0;\n    auto dfs = [&](int v, int p, auto\
    \ &&f) -> void {\n        for (auto &&e : G[v]) {\n            int to = e.first;\n\
    \            T cost = e.second;\n            if (to == p) continue;\n        \
    \    dist[to] = dist[v] + cost;\n            if (dist[far] < dist[to]) far = to;\n\
    \            f(to, v, f);\n        }\n    };\n\n    dist[0] = T();\n    dfs(0,\
    \ -1, dfs);\n    int s = far;\n    dist[s] = T();\n    dfs(s, -1, dfs);\n    return\
    \ {dist[far], {s, far}};\n}\n\n/**\n * @brief Tree Diameter (Weighted)\n * @docs\
    \ _md/diameter_weighted.md\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/diameter_weighted.cpp
  requiredBy: []
  timestamp: '2026-03-08 15:15:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_5_a_diameter.test.cpp
documentation_of: tree/diameter_weighted.cpp
layout: document
redirect_from:
- /library/tree/diameter_weighted.cpp
- /library/tree/diameter_weighted.cpp.html
title: Tree Diameter (Weighted)
---
## 説明
重み付き木の直径長とその両端点を `O(N)` で求める。

## できること
- `pair<T, pair<int, int>> tree_diameter_weighted(const vector<vector<pair<int, T>>> &g)`
  直径を返す。戻り値の `first` は重み和としての直径長、`second.first` と `second.second` は両端点

## 使い方
隣接リストを `vector<vector<pair<int, T>>>` で持ち、`tree_diameter_weighted(g)` を呼ぶ。

```cpp
vector<vector<pair<int, long long>>> g(n);
g[u].push_back({v, w});
g[v].push_back({u, w});

auto [dist, ends] = tree_diameter_weighted(g);
int s = ends.first;
int t = ends.second;
```

重みなし木には `diameter.cpp` の `tree_diameter` を使う。

## 実装上の補足
任意の頂点から最遠点 `s` を取り、さらに `s` から最遠点を取る 2 回 DFS で求める。
木を仮定しているので、連結で閉路のないグラフに対して使う。
