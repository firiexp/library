---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/kruskal.cpp
    title: "\u6700\u5C0F\u5168\u57DF\u6728(Kruskal\u6CD5)"
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_mst_sensitivity.test.cpp
    title: test/yosupo_aplusb_mst_sensitivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\u5225\u5236\u7D04\u30B3\
      \u30B9\u30C8"
    links: []
  bundledCode: "#line 1 \"graph/mst_sensitivity.cpp\"\n\n\n\n#line 1 \"graph/kruskal.cpp\"\
    \n\n\n\ntemplate <class T>\nstruct edge {\n    int from, to, idx;\n    T cost;\n\
    \n    edge(int from, int to, T cost, int idx = -1) : from(from), to(to), idx(idx),\
    \ cost(cost) {}\n};\n\nclass KruskalUnionFind {\n    vector<int> p;\n\npublic:\n\
    \    explicit KruskalUnionFind(int n) : p(n, -1) {}\n\n    int root(int x) {\n\
    \        if (p[x] < 0) return x;\n        return p[x] = root(p[x]);\n    }\n\n\
    \    bool unite(int a, int b) {\n        a = root(a);\n        b = root(b);\n\
    \        if (a == b) return false;\n        if (p[a] > p[b]) swap(a, b);\n   \
    \     p[a] += p[b];\n        p[b] = a;\n        return true;\n    }\n};\n\ntemplate\
    \ <class T>\nstruct KruskalResult {\n    bool exists;\n    T cost;\n    vector<int>\
    \ edge_id;\n};\n\ntemplate <class T>\nKruskalResult<T> kruskal(vector<edge<T>>\
    \ edges, int n) {\n    for (int i = 0; i < (int)edges.size(); ++i) {\n       \
    \ if (edges[i].idx == -1) edges[i].idx = i;\n    }\n    sort(edges.begin(), edges.end(),\
    \ [](const edge<T> &a, const edge<T> &b) {\n        if (a.cost != b.cost) return\
    \ a.cost < b.cost;\n        return a.idx < b.idx;\n    });\n\n    KruskalUnionFind\
    \ uf(n);\n    T cost = T(0);\n    vector<int> edge_id;\n    edge_id.reserve(max(0,\
    \ n - 1));\n    for (auto &&e : edges) {\n        if (!uf.unite(e.from, e.to))\
    \ continue;\n        cost += e.cost;\n        edge_id.push_back(e.idx);\n    }\n\
    \    if ((int)edge_id.size() != max(0, n - 1)) return {false, T(0), {}};\n   \
    \ return {true, cost, std::move(edge_id)};\n}\n\n\n\n/**\n * @brief \u6700\u5C0F\
    \u5168\u57DF\u6728(Kruskal\u6CD5)\n */\n#line 5 \"graph/mst_sensitivity.cpp\"\n\
    \nstruct MSTSensitivityResult {\n    bool exists;\n    long long cost;\n    vector<optional<long\
    \ long>> forced, forbidden;\n};\n\nMSTSensitivityResult mst_sensitivity(int n,\
    \ const vector<edge<long long>> &edges) {\n    assert(n >= 1);\n    int m = (int)edges.size();\n\
    \    auto indexed = edges;\n    for (int i = 0; i < m; ++i) indexed[i].idx = i;\n\
    \    auto mst = kruskal(std::move(indexed), n);\n    MSTSensitivityResult result{mst.exists,\
    \ mst.cost,\n                                vector<optional<long long>>(m), vector<optional<long\
    \ long>>(m)};\n    if (!mst.exists) return result;\n    vector<char> in_tree(m);\n\
    \    vector<vector<pair<int, int>>> tree(n);\n    for (int id : mst.edge_id) {\n\
    \        in_tree[id] = 1;\n        result.forced[id] = mst.cost;\n        const\
    \ auto &e = edges[id];\n        tree[e.from].emplace_back(e.to, id);\n       \
    \ tree[e.to].emplace_back(e.from, id);\n    }\n    int height = 1;\n    while\
    \ ((1LL << height) <= n) ++height;\n    vector<vector<int>> parent(height, vector<int>(n));\n\
    \    vector<vector<long long>> maximum(height, vector<long long>(n, LLONG_MIN));\n\
    \    vector<int> depth(n), parent_edge(n, -1), order{0};\n    for (int i = 0;\
    \ i < (int)order.size(); ++i) {\n        int v = order[i];\n        for (auto\
    \ [u, id] : tree[v]) {\n            if (u == parent[0][v]) continue;\n       \
    \     parent[0][u] = v;\n            parent_edge[u] = id;\n            maximum[0][u]\
    \ = edges[id].cost;\n            depth[u] = depth[v] + 1;\n            order.push_back(u);\n\
    \        }\n    }\n    for (int k = 1; k < height; ++k) {\n        for (int v\
    \ = 0; v < n; ++v) {\n            int u = parent[k - 1][v];\n            parent[k][v]\
    \ = parent[k - 1][u];\n            maximum[k][v] = max(maximum[k - 1][v], maximum[k\
    \ - 1][u]);\n        }\n    }\n    auto path = [&](int u, int v) {\n        long\
    \ long weight = LLONG_MIN;\n        if (depth[u] < depth[v]) swap(u, v);\n   \
    \     int difference = depth[u] - depth[v];\n        for (int k = 0; k < height;\
    \ ++k) {\n            if ((difference >> k) & 1) {\n                weight = max(weight,\
    \ maximum[k][u]);\n                u = parent[k][u];\n            }\n        }\n\
    \        if (u == v) return make_pair(u, weight);\n        for (int k = height\
    \ - 1; k >= 0; --k) {\n            if (parent[k][u] == parent[k][v]) continue;\n\
    \            weight = max({weight, maximum[k][u], maximum[k][v]});\n         \
    \   u = parent[k][u];\n            v = parent[k][v];\n        }\n        return\
    \ make_pair(parent[0][u], max({weight, maximum[0][u], maximum[0][v]}));\n    };\n\
    \    vector<int> non_tree;\n    for (int i = 0; i < m; ++i) {\n        if (in_tree[i])\
    \ continue;\n        result.forbidden[i] = mst.cost;\n        if (edges[i].from\
    \ != edges[i].to) non_tree.push_back(i);\n    }\n    sort(non_tree.begin(), non_tree.end(),\
    \ [&](int a, int b) { return edges[a].cost < edges[b].cost; });\n    KruskalUnionFind\
    \ skip(n);\n    vector<int> top(n);\n    iota(top.begin(), top.end(), 0);\n  \
    \  auto replace = [&](int v, int ancestor, long long weight) {\n        int representative\
    \ = skip.root(v), x = top[representative];\n        while (depth[x] > depth[ancestor])\
    \ {\n            int id = parent_edge[x];\n            result.forbidden[id] =\
    \ mst.cost + weight - edges[id].cost;\n            int highest = top[skip.root(parent[0][x])];\n\
    \            skip.unite(representative, parent[0][x]);\n            representative\
    \ = skip.root(representative);\n            top[representative] = highest;\n \
    \           x = highest;\n        }\n    };\n    for (int id : non_tree) {\n \
    \       const auto &e = edges[id];\n        auto [ancestor, weight] = path(e.from,\
    \ e.to);\n        result.forced[id] = mst.cost + e.cost - weight;\n        replace(e.from,\
    \ ancestor, e.cost);\n        replace(e.to, ancestor, e.cost);\n    }\n    return\
    \ result;\n}\n\n\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\u5225\
    \u5236\u7D04\u30B3\u30B9\u30C8\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_MST_SENSITIVITY_CPP\n#define FIRIEXP_LIBRARY_GRAPH_MST_SENSITIVITY_CPP\n\
    \n#include \"kruskal.cpp\"\n\nstruct MSTSensitivityResult {\n    bool exists;\n\
    \    long long cost;\n    vector<optional<long long>> forced, forbidden;\n};\n\
    \nMSTSensitivityResult mst_sensitivity(int n, const vector<edge<long long>> &edges)\
    \ {\n    assert(n >= 1);\n    int m = (int)edges.size();\n    auto indexed = edges;\n\
    \    for (int i = 0; i < m; ++i) indexed[i].idx = i;\n    auto mst = kruskal(std::move(indexed),\
    \ n);\n    MSTSensitivityResult result{mst.exists, mst.cost,\n               \
    \                 vector<optional<long long>>(m), vector<optional<long long>>(m)};\n\
    \    if (!mst.exists) return result;\n    vector<char> in_tree(m);\n    vector<vector<pair<int,\
    \ int>>> tree(n);\n    for (int id : mst.edge_id) {\n        in_tree[id] = 1;\n\
    \        result.forced[id] = mst.cost;\n        const auto &e = edges[id];\n \
    \       tree[e.from].emplace_back(e.to, id);\n        tree[e.to].emplace_back(e.from,\
    \ id);\n    }\n    int height = 1;\n    while ((1LL << height) <= n) ++height;\n\
    \    vector<vector<int>> parent(height, vector<int>(n));\n    vector<vector<long\
    \ long>> maximum(height, vector<long long>(n, LLONG_MIN));\n    vector<int> depth(n),\
    \ parent_edge(n, -1), order{0};\n    for (int i = 0; i < (int)order.size(); ++i)\
    \ {\n        int v = order[i];\n        for (auto [u, id] : tree[v]) {\n     \
    \       if (u == parent[0][v]) continue;\n            parent[0][u] = v;\n    \
    \        parent_edge[u] = id;\n            maximum[0][u] = edges[id].cost;\n \
    \           depth[u] = depth[v] + 1;\n            order.push_back(u);\n      \
    \  }\n    }\n    for (int k = 1; k < height; ++k) {\n        for (int v = 0; v\
    \ < n; ++v) {\n            int u = parent[k - 1][v];\n            parent[k][v]\
    \ = parent[k - 1][u];\n            maximum[k][v] = max(maximum[k - 1][v], maximum[k\
    \ - 1][u]);\n        }\n    }\n    auto path = [&](int u, int v) {\n        long\
    \ long weight = LLONG_MIN;\n        if (depth[u] < depth[v]) swap(u, v);\n   \
    \     int difference = depth[u] - depth[v];\n        for (int k = 0; k < height;\
    \ ++k) {\n            if ((difference >> k) & 1) {\n                weight = max(weight,\
    \ maximum[k][u]);\n                u = parent[k][u];\n            }\n        }\n\
    \        if (u == v) return make_pair(u, weight);\n        for (int k = height\
    \ - 1; k >= 0; --k) {\n            if (parent[k][u] == parent[k][v]) continue;\n\
    \            weight = max({weight, maximum[k][u], maximum[k][v]});\n         \
    \   u = parent[k][u];\n            v = parent[k][v];\n        }\n        return\
    \ make_pair(parent[0][u], max({weight, maximum[0][u], maximum[0][v]}));\n    };\n\
    \    vector<int> non_tree;\n    for (int i = 0; i < m; ++i) {\n        if (in_tree[i])\
    \ continue;\n        result.forbidden[i] = mst.cost;\n        if (edges[i].from\
    \ != edges[i].to) non_tree.push_back(i);\n    }\n    sort(non_tree.begin(), non_tree.end(),\
    \ [&](int a, int b) { return edges[a].cost < edges[b].cost; });\n    KruskalUnionFind\
    \ skip(n);\n    vector<int> top(n);\n    iota(top.begin(), top.end(), 0);\n  \
    \  auto replace = [&](int v, int ancestor, long long weight) {\n        int representative\
    \ = skip.root(v), x = top[representative];\n        while (depth[x] > depth[ancestor])\
    \ {\n            int id = parent_edge[x];\n            result.forbidden[id] =\
    \ mst.cost + weight - edges[id].cost;\n            int highest = top[skip.root(parent[0][x])];\n\
    \            skip.unite(representative, parent[0][x]);\n            representative\
    \ = skip.root(representative);\n            top[representative] = highest;\n \
    \           x = highest;\n        }\n    };\n    for (int id : non_tree) {\n \
    \       const auto &e = edges[id];\n        auto [ancestor, weight] = path(e.from,\
    \ e.to);\n        result.forced[id] = mst.cost + e.cost - weight;\n        replace(e.from,\
    \ ancestor, e.cost);\n        replace(e.to, ancestor, e.cost);\n    }\n    return\
    \ result;\n}\n\n#endif\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\
    \u5225\u5236\u7D04\u30B3\u30B9\u30C8\n */\n"
  dependsOn:
  - graph/kruskal.cpp
  isVerificationFile: false
  path: graph/mst_sensitivity.cpp
  requiredBy: []
  timestamp: '2026-10-15 00:51:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_mst_sensitivity.test.cpp
date: 2026-10-14
documentation_of: graph/mst_sensitivity.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u6700\u5C0F\u5168\u57DF\u6728\u306E\u8FBA\u5225\u5236\u7D04\u30B3\u30B9\u30C8"
---

## 説明
無向重み付きグラフの各辺について、その辺を必ず採用する場合・使用禁止にする場合の最小全域木コストをまとめて求める。
負重み、同重み、多重辺、自己ループを扱う。

## できること
- `mst_sensitivity(n, edges)`
  `MSTSensitivityResult` を返す。`edges` は Kruskal の `vector<edge<long long>>` とし、入力を変更しない
- `result.exists` / `result.cost`
  元グラフの全域木の存在と最小コスト。非連結なら `false` と `0`
- `result.forced[i]` / `result.forbidden[i]`
  入力順 `i` 番目の辺を必須／禁止にした最小コスト。実現不能なら `nullopt`

## 使い方
`n >= 1`、端点は `0..n-1` とする。返却配列の番号は `edge.idx` に依存しない。
元グラフが非連結なら、両配列は辺数個の `nullopt` となる。
自己ループの `forced` は `nullopt`、`forbidden` は元のコスト。1頂点の空の全域木はコスト0となる。

```cpp
auto result = mst_sensitivity(n, edges);
if (result.forced[i]) {
    bool can_belong_to_mst = *result.forced[i] == result.cost;
}
```

重みの加減算は中間値も含めて `long long` に収まる範囲で使う。
Kruskal 内の逐次加算と、交換式 `cost + added - removed` がこの条件を満たす必要がある。
条件ごとの木の復元は行わない。別途 LCA 構築や build は不要。

## 実装上の補足
Kruskal で木を1つ作り、非木辺の強制採用は、木上パスの最大重みの辺との交換で求める。
非木辺を重み順に処理し、パス上のまだ代替辺が決まっていない木辺へ最初の代替重みを設定する。
確定済みの辺は union-by-size と経路圧縮を持つ UnionFind で飛ばし、代表とは別に最上位頂点を保持する。
自己ループを除く非木辺の使用禁止は元のコストで、木辺の禁止はその代替辺との交換となる。

時間は $O(M\log(M)+(N+M)\log(N))$、入力・出力を含む領域は $O(M+N\log(N))$。
各木辺への代替設定は高々1回で、skip の総処理は $O((N+M)\alpha(N))$。
前処理の走査は反復処理とし、木の深さに依存する再帰は使わない。
