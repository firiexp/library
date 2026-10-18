---
category: "\u6728"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/tree_center.cpp
    title: "\u6728\u306E\u4E2D\u5FC3(Tree Center)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_tree_isomorphism.test.cpp
    title: test/yosupo_aplusb_tree_isomorphism.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u306E\u540C\u578B\u5224\u5B9A\u3068\u9802\u70B9\u5BFE\u5FDC"
    links: []
  bundledCode: "#line 1 \"tree/tree_isomorphism.cpp\"\n\n\n\n#line 1 \"tree/tree_center.cpp\"\
    \n\n\n\npair<int, vector<int>> tree_center(const vector<vector<int>> &G) {\n \
    \   int n = G.size();\n    if (n == 0) return {0, {}};\n\n    vector<int> dist(n),\
    \ par(n), q(n);\n    auto bfs = [&](int s, bool record_parent) {\n        fill(dist.begin(),\
    \ dist.end(), -1);\n        dist[s] = 0;\n        if (record_parent) par[s] =\
    \ -1;\n        int head = 0, tail = 0;\n        q[tail++] = s;\n        int far\
    \ = s;\n        while (head < tail) {\n            int v = q[head++];\n      \
    \      if (dist[far] < dist[v]) far = v;\n            for (auto &&to : G[v]) {\n\
    \                if (dist[to] != -1) continue;\n                dist[to] = dist[v]\
    \ + 1;\n                if (record_parent) par[to] = v;\n                q[tail++]\
    \ = to;\n            }\n        }\n        return far;\n    };\n\n    int s =\
    \ bfs(0, false);\n    int t = bfs(s, true);\n\n    int diam = dist[t];\n    int\
    \ v = t;\n    for (int i = 0; i < diam / 2; ++i) v = par[v];\n    if (diam & 1)\
    \ return {(diam + 1) / 2, vector<int>{par[v], v}};\n    return {diam / 2, vector<int>{v}};\n\
    }\n\n/**\n * @brief \u6728\u306E\u4E2D\u5FC3(Tree Center)\n */\n\n\n#line 5 \"\
    tree/tree_isomorphism.cpp\"\n\nstruct TreeIsomorphismResult {\n    bool exists;\n\
    \    vector<int> mapping;\n};\n\nnamespace tree_isomorphism_detail {\nstruct RootedTree\
    \ {\n    vector<vector<int>> children;\n    vector<int> order, label;\n\n    RootedTree(const\
    \ vector<vector<int>> &g, int root, map<vector<int>, int> &ids)\n        : children(g.size()),\
    \ label(g.size()) {\n        int n = g.size();\n        vector<int> parent(n,\
    \ -1);\n        order.reserve(n);\n        order.push_back(root);\n        for\
    \ (int i = 0; i < n; ++i) {\n            int v = order[i];\n            for (int\
    \ to : g[v]) if (to != parent[v]) {\n                parent[to] = v;\n       \
    \         children[v].push_back(to);\n                order.push_back(to);\n \
    \           }\n        }\n        for (int i = n - 1; i >= 0; --i) {\n       \
    \     int v = order[i];\n            auto &ch = children[v];\n            sort(ch.begin(),\
    \ ch.end(), [&](int a, int b) { return label[a] < label[b]; });\n            vector<int>\
    \ key;\n            key.reserve(ch.size());\n            for (int to : ch) key.push_back(label[to]);\n\
    \            label[v] = ids.try_emplace(std::move(key), (int)ids.size()).first->second;\n\
    \        }\n    }\n};\n}\n\nTreeIsomorphismResult rooted_tree_isomorphism(const\
    \ vector<vector<int>> &g,\n        const vector<vector<int>> &h, int root_g, int\
    \ root_h) {\n    if (g.size() != h.size()) return {false, {}};\n    if (g.empty())\
    \ return {true, {}};\n    map<vector<int>, int> ids;\n    tree_isomorphism_detail::RootedTree\
    \ a(g, root_g, ids), b(h, root_h, ids);\n    if (a.label[root_g] != b.label[root_h])\
    \ return {false, {}};\n    vector<int> mapping(g.size());\n    mapping[root_g]\
    \ = root_h;\n    for (int v : a.order) {\n        int w = mapping[v];\n      \
    \  for (int i = 0; i < (int)a.children[v].size(); ++i) {\n            mapping[a.children[v][i]]\
    \ = b.children[w][i];\n        }\n    }\n    return {true, std::move(mapping)};\n\
    }\n\nTreeIsomorphismResult tree_isomorphism(const vector<vector<int>> &g,\n  \
    \      const vector<vector<int>> &h) {\n    if (g.size() != h.size()) return {false,\
    \ {}};\n    if (g.empty()) return {true, {}};\n    auto centers_g = tree_center(g).second;\n\
    \    auto centers_h = tree_center(h).second;\n    if (centers_g.size() != centers_h.size())\
    \ return {false, {}};\n    for (int root_h : centers_h) {\n        auto result\
    \ = rooted_tree_isomorphism(g, h, centers_g[0], root_h);\n        if (result.exists)\
    \ return result;\n    }\n    return {false, {}};\n}\n\n\n\n/**\n * @brief \u6728\
    \u306E\u540C\u578B\u5224\u5B9A\u3068\u9802\u70B9\u5BFE\u5FDC\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_TREE_TREE_ISOMORPHISM_CPP\n#define FIRIEXP_LIBRARY_TREE_TREE_ISOMORPHISM_CPP\n\
    \n#include \"tree_center.cpp\"\n\nstruct TreeIsomorphismResult {\n    bool exists;\n\
    \    vector<int> mapping;\n};\n\nnamespace tree_isomorphism_detail {\nstruct RootedTree\
    \ {\n    vector<vector<int>> children;\n    vector<int> order, label;\n\n    RootedTree(const\
    \ vector<vector<int>> &g, int root, map<vector<int>, int> &ids)\n        : children(g.size()),\
    \ label(g.size()) {\n        int n = g.size();\n        vector<int> parent(n,\
    \ -1);\n        order.reserve(n);\n        order.push_back(root);\n        for\
    \ (int i = 0; i < n; ++i) {\n            int v = order[i];\n            for (int\
    \ to : g[v]) if (to != parent[v]) {\n                parent[to] = v;\n       \
    \         children[v].push_back(to);\n                order.push_back(to);\n \
    \           }\n        }\n        for (int i = n - 1; i >= 0; --i) {\n       \
    \     int v = order[i];\n            auto &ch = children[v];\n            sort(ch.begin(),\
    \ ch.end(), [&](int a, int b) { return label[a] < label[b]; });\n            vector<int>\
    \ key;\n            key.reserve(ch.size());\n            for (int to : ch) key.push_back(label[to]);\n\
    \            label[v] = ids.try_emplace(std::move(key), (int)ids.size()).first->second;\n\
    \        }\n    }\n};\n}\n\nTreeIsomorphismResult rooted_tree_isomorphism(const\
    \ vector<vector<int>> &g,\n        const vector<vector<int>> &h, int root_g, int\
    \ root_h) {\n    if (g.size() != h.size()) return {false, {}};\n    if (g.empty())\
    \ return {true, {}};\n    map<vector<int>, int> ids;\n    tree_isomorphism_detail::RootedTree\
    \ a(g, root_g, ids), b(h, root_h, ids);\n    if (a.label[root_g] != b.label[root_h])\
    \ return {false, {}};\n    vector<int> mapping(g.size());\n    mapping[root_g]\
    \ = root_h;\n    for (int v : a.order) {\n        int w = mapping[v];\n      \
    \  for (int i = 0; i < (int)a.children[v].size(); ++i) {\n            mapping[a.children[v][i]]\
    \ = b.children[w][i];\n        }\n    }\n    return {true, std::move(mapping)};\n\
    }\n\nTreeIsomorphismResult tree_isomorphism(const vector<vector<int>> &g,\n  \
    \      const vector<vector<int>> &h) {\n    if (g.size() != h.size()) return {false,\
    \ {}};\n    if (g.empty()) return {true, {}};\n    auto centers_g = tree_center(g).second;\n\
    \    auto centers_h = tree_center(h).second;\n    if (centers_g.size() != centers_h.size())\
    \ return {false, {}};\n    for (int root_h : centers_h) {\n        auto result\
    \ = rooted_tree_isomorphism(g, h, centers_g[0], root_h);\n        if (result.exists)\
    \ return result;\n    }\n    return {false, {}};\n}\n\n#endif\n\n/**\n * @brief\
    \ \u6728\u306E\u540C\u578B\u5224\u5B9A\u3068\u9802\u70B9\u5BFE\u5FDC\n */\n"
  dependsOn:
  - tree/tree_center.cpp
  isVerificationFile: false
  path: tree/tree_isomorphism.cpp
  requiredBy: []
  timestamp: '2026-10-18 09:39:49+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_tree_isomorphism.test.cpp
date: 2026-10-18
documentation_of: tree/tree_isomorphism.cpp
layout: document
tags: "\u6728"
title: "\u6728\u306E\u540C\u578B\u5224\u5B9A\u3068\u9802\u70B9\u5BFE\u5FDC"
---

## 説明
2本の木が同型かを判定し、同型なら頂点の対応を返す。
2本の木を通じて、同じ構造の部分木に同じ id を割り当てて比較する。ハッシュ衝突による誤判定はない。
以下の計算量では、2本の木の頂点数の大きい方を $N$ とする。

## できること
- `TreeIsomorphismResult tree_isomorphism(g, h)`
  根を指定せずに同型性を判定する。時間 $O(N\log N)$、追加領域 $O(N)$
- `TreeIsomorphismResult rooted_tree_isomorphism(g, h, root_g, root_h)`
  指定した根同士を対応させる同型写像を求める。時間 $O(N\log N)$、追加領域 $O(N)$
- `result.exists`
  同型なら `true`。頂点数が異なる場合や非同型なら `false`。参照は $O(1)$
- `result.mapping[v]`
  1本目の頂点 `v` に対応する2本目の頂点番号。成功時の参照は $O(1)$。失敗時は配列全体が空

## 使い方
単純な無向木の隣接リストを `vector<vector<int>>` で渡す。入力は変更しない。
非空の木では根を有効な頂点番号で指定する。空の木同士は根の指定を使わず、`exists = true` と空の対応を返す。

```cpp
auto result = tree_isomorphism(g, h);
if (result.exists) {
    int matched_vertex = result.mapping[v];
}
```

対応は全単射で、すべての辺を保つ。複数の対応がある場合はそのうち1つを返し、辞書順最小性は保証しない。
頂点・辺のラベルは扱わない。

## 実装上の補足
2本の木の部分木を、1つの `map<vector<int>, int>` で分類する。
ソートした子の同型類の id 列をキーにし、同じ列には同じ id を割り当てる。
根の同型類が一致したら、同じ同型類の子同士を対応させる。
根なし版は `tree_center` で中心を求め、1本目の中心を1つ固定して2本目の中心を高々2通り試す。
構築・復元ともに再帰を使わない。既存の `TreeHash` の id は別々の `build` 間で比較できないため、2本の比較にはこの関数を使う。
