---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_many_aplusb_tree_center.test.cpp
    title: test/yosupo_many_aplusb_tree_center.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u306E\u4E2D\u5FC3(Tree Center)"
    links: []
  bundledCode: "#line 1 \"tree/tree_center.cpp\"\npair<int, vector<int>> tree_center(const\
    \ vector<vector<int>> &G) {\n    int n = G.size();\n    if (n == 0) return {0,\
    \ {}};\n\n    auto bfs = [&](int s, vector<int> &par) {\n        vector<int> dist(n,\
    \ -1);\n        queue<int> q;\n        dist[s] = 0;\n        par.assign(n, -1);\n\
    \        q.push(s);\n        int far = s;\n        while (!q.empty()) {\n    \
    \        int v = q.front();\n            q.pop();\n            if (dist[far] <\
    \ dist[v]) far = v;\n            for (auto &&to : G[v]) {\n                if\
    \ (dist[to] != -1) continue;\n                dist[to] = dist[v] + 1;\n      \
    \          par[to] = v;\n                q.push(to);\n            }\n        }\n\
    \        return pair<int, vector<int>>(far, dist);\n    };\n\n    vector<int>\
    \ par;\n    int s = bfs(0, par).first;\n    auto [t, dist] = bfs(s, par);\n\n\
    \    vector<int> path;\n    for (int v = t; v != -1; v = par[v]) path.push_back(v);\n\
    \    reverse(path.begin(), path.end());\n\n    int diam = dist[t];\n    vector<int>\
    \ centers;\n    centers.push_back(path[diam / 2]);\n    if (diam & 1) centers.push_back(path[diam\
    \ / 2 + 1]);\n    return {(diam + 1) / 2, centers};\n}\n\n/**\n * @brief \u6728\
    \u306E\u4E2D\u5FC3(Tree Center)\n */\n"
  code: "pair<int, vector<int>> tree_center(const vector<vector<int>> &G) {\n    int\
    \ n = G.size();\n    if (n == 0) return {0, {}};\n\n    auto bfs = [&](int s,\
    \ vector<int> &par) {\n        vector<int> dist(n, -1);\n        queue<int> q;\n\
    \        dist[s] = 0;\n        par.assign(n, -1);\n        q.push(s);\n      \
    \  int far = s;\n        while (!q.empty()) {\n            int v = q.front();\n\
    \            q.pop();\n            if (dist[far] < dist[v]) far = v;\n       \
    \     for (auto &&to : G[v]) {\n                if (dist[to] != -1) continue;\n\
    \                dist[to] = dist[v] + 1;\n                par[to] = v;\n     \
    \           q.push(to);\n            }\n        }\n        return pair<int, vector<int>>(far,\
    \ dist);\n    };\n\n    vector<int> par;\n    int s = bfs(0, par).first;\n   \
    \ auto [t, dist] = bfs(s, par);\n\n    vector<int> path;\n    for (int v = t;\
    \ v != -1; v = par[v]) path.push_back(v);\n    reverse(path.begin(), path.end());\n\
    \n    int diam = dist[t];\n    vector<int> centers;\n    centers.push_back(path[diam\
    \ / 2]);\n    if (diam & 1) centers.push_back(path[diam / 2 + 1]);\n    return\
    \ {(diam + 1) / 2, centers};\n}\n\n/**\n * @brief \u6728\u306E\u4E2D\u5FC3(Tree\
    \ Center)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/tree_center.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_many_aplusb_tree_center.test.cpp
date: 2026-03-08
documentation_of: tree/tree_center.cpp
layout: document
tags: "\u6728"
title: Tree Center
---

## 説明
重みなし木の中心と半径を `O(N)` で求める。
中心は 1 頂点または隣接する 2 頂点になる。

## できること
- `pair<int, vector<int>> tree_center(const vector<vector<int>>& g)`
  木の半径と中心頂点列を返す
- 戻り値の `first`
  半径
- 戻り値の `second`
  中心頂点を 1 個または 2 個持つ

## 使い方
隣接リストを `vector<vector<int>>` で持って `tree_center(g)` を呼ぶ。

```cpp
auto [radius, centers] = tree_center(g);
```

## 実装上の補足
直径の両端点を BFS 2 回で求め、直径パスの中央を中心とする。
直径長が偶数なら中心は 1 個、奇数なら中心は 2 個になる。
