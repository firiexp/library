---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_minimum_steiner_tree.test.cpp
    title: test/yosupo_aplusb_minimum_steiner_tree.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_minimum_steiner_tree.test.cpp
    title: test/yosupo_minimum_steiner_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\u6728"
    links: []
  bundledCode: "#line 1 \"graph/minimum_steiner_tree.cpp\"\n\n\n\ntemplate <class\
    \ T>\nclass MinimumSteinerTree {\n    struct Edge { int u, v; T cost; };\n\n \
    \   int n;\n    vector<Edge> edges;\n    vector<vector<int>> graph;\n    vector<vector<T>>\
    \ dp;\n    vector<vector<int>> trace;\n\npublic:\n    explicit MinimumSteinerTree(int\
    \ n) : n(n), graph(n) {\n        assert(n > 0);\n    }\n\n    int add_edge(int\
    \ u, int v, T weight) {\n        assert(0 <= u && u < n && 0 <= v && v < n &&\
    \ weight >= 0);\n        int id = (int)edges.size();\n        edges.push_back({u,\
    \ v, weight});\n        graph[u].push_back(id);\n        graph[v].push_back(id);\n\
    \        return id;\n    }\n\n    void build(const vector<int> &terminals) {\n\
    \        int k = (int)terminals.size();\n        vector<char> used(n);\n     \
    \   for (int v : terminals) {\n            assert(0 <= v && v < n && !used[v]);\n\
    \            used[v] = true;\n        }\n        int states = 1 << k;\n      \
    \  dp.assign(states, vector<T>(n, INF<T>));\n        trace.assign(states, vector<int>(n,\
    \ -1));\n        for (int i = 0; i < k; ++i) dp[1 << i][terminals[i]] = 0;\n \
    \       for (int mask = 1; mask < states; ++mask) {\n            auto &dist =\
    \ dp[mask];\n            for (int sub = (mask - 1) & mask; sub; sub = (sub - 1)\
    \ & mask) {\n                int other = mask ^ sub;\n                if (sub\
    \ < other) continue;\n                for (int v = 0; v < n; ++v) {\n        \
    \            if (dp[sub][v] >= INF<T> - dp[other][v]) continue;\n            \
    \        T next = dp[sub][v] + dp[other][v];\n                    if (next >=\
    \ dist[v]) continue;\n                    dist[v] = next;\n                  \
    \  trace[mask][v] = sub;\n                }\n            }\n            priority_queue<pair<T,\
    \ int>, vector<pair<T, int>>, greater<>> queue;\n            for (int v = 0; v\
    \ < n; ++v) {\n                if (dist[v] != INF<T>) queue.emplace(dist[v], v);\n\
    \            }\n            while (!queue.empty()) {\n                auto [value,\
    \ v] = queue.top();\n                queue.pop();\n                if (value !=\
    \ dist[v]) continue;\n                for (int id : graph[v]) {\n            \
    \        const auto &e = edges[id];\n                    int u = e.u ^ e.v ^ v;\n\
    \                    if (e.cost >= INF<T> - value) continue;\n               \
    \     T next = value + e.cost;\n                    if (next >= dist[u]) continue;\n\
    \                    dist[u] = next;\n                    trace[mask][u] = -id\
    \ - 2;\n                    queue.emplace(next, u);\n                }\n     \
    \       }\n        }\n    }\n\n    T cost(int v) const {\n        return dp.back()[v];\n\
    \    }\n\n    vector<int> restore(int v) const {\n        if (cost(v) == INF<T>)\
    \ return {};\n        vector<int> result, parent(n, -1);\n        auto root =\
    \ [&](auto &&self, int u) -> int {\n            return parent[u] < 0 ? u : parent[u]\
    \ = self(self, parent[u]);\n        };\n        vector<pair<int, int>> pending{\
    \ { (int)dp.size() - 1, v } };\n        while (!pending.empty()) {\n         \
    \   auto [mask, u] = pending.back();\n            pending.pop_back();\n      \
    \      int step = trace[mask][u];\n            if (step == -1) continue;\n   \
    \         if (step >= 0) {\n                pending.emplace_back(step, u);\n \
    \               pending.emplace_back(mask ^ step, u);\n            } else {\n\
    \                int id = -step - 2;\n                const auto &e = edges[id];\n\
    \                pending.emplace_back(mask, e.u ^ e.v ^ u);\n                int\
    \ a = root(root, e.u), b = root(root, e.v);\n                if (a == b) continue;\n\
    \                if (parent[a] > parent[b]) swap(a, b);\n                parent[a]\
    \ += parent[b];\n                parent[b] = a;\n                result.push_back(id);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n\n\n/**\n * @brief\
    \ \u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\u6728\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_MINIMUM_STEINER_TREE_CPP\n#define FIRIEXP_LIBRARY_GRAPH_MINIMUM_STEINER_TREE_CPP\n\
    \ntemplate <class T>\nclass MinimumSteinerTree {\n    struct Edge { int u, v;\
    \ T cost; };\n\n    int n;\n    vector<Edge> edges;\n    vector<vector<int>> graph;\n\
    \    vector<vector<T>> dp;\n    vector<vector<int>> trace;\n\npublic:\n    explicit\
    \ MinimumSteinerTree(int n) : n(n), graph(n) {\n        assert(n > 0);\n    }\n\
    \n    int add_edge(int u, int v, T weight) {\n        assert(0 <= u && u < n &&\
    \ 0 <= v && v < n && weight >= 0);\n        int id = (int)edges.size();\n    \
    \    edges.push_back({u, v, weight});\n        graph[u].push_back(id);\n     \
    \   graph[v].push_back(id);\n        return id;\n    }\n\n    void build(const\
    \ vector<int> &terminals) {\n        int k = (int)terminals.size();\n        vector<char>\
    \ used(n);\n        for (int v : terminals) {\n            assert(0 <= v && v\
    \ < n && !used[v]);\n            used[v] = true;\n        }\n        int states\
    \ = 1 << k;\n        dp.assign(states, vector<T>(n, INF<T>));\n        trace.assign(states,\
    \ vector<int>(n, -1));\n        for (int i = 0; i < k; ++i) dp[1 << i][terminals[i]]\
    \ = 0;\n        for (int mask = 1; mask < states; ++mask) {\n            auto\
    \ &dist = dp[mask];\n            for (int sub = (mask - 1) & mask; sub; sub =\
    \ (sub - 1) & mask) {\n                int other = mask ^ sub;\n             \
    \   if (sub < other) continue;\n                for (int v = 0; v < n; ++v) {\n\
    \                    if (dp[sub][v] >= INF<T> - dp[other][v]) continue;\n    \
    \                T next = dp[sub][v] + dp[other][v];\n                    if (next\
    \ >= dist[v]) continue;\n                    dist[v] = next;\n               \
    \     trace[mask][v] = sub;\n                }\n            }\n            priority_queue<pair<T,\
    \ int>, vector<pair<T, int>>, greater<>> queue;\n            for (int v = 0; v\
    \ < n; ++v) {\n                if (dist[v] != INF<T>) queue.emplace(dist[v], v);\n\
    \            }\n            while (!queue.empty()) {\n                auto [value,\
    \ v] = queue.top();\n                queue.pop();\n                if (value !=\
    \ dist[v]) continue;\n                for (int id : graph[v]) {\n            \
    \        const auto &e = edges[id];\n                    int u = e.u ^ e.v ^ v;\n\
    \                    if (e.cost >= INF<T> - value) continue;\n               \
    \     T next = value + e.cost;\n                    if (next >= dist[u]) continue;\n\
    \                    dist[u] = next;\n                    trace[mask][u] = -id\
    \ - 2;\n                    queue.emplace(next, u);\n                }\n     \
    \       }\n        }\n    }\n\n    T cost(int v) const {\n        return dp.back()[v];\n\
    \    }\n\n    vector<int> restore(int v) const {\n        if (cost(v) == INF<T>)\
    \ return {};\n        vector<int> result, parent(n, -1);\n        auto root =\
    \ [&](auto &&self, int u) -> int {\n            return parent[u] < 0 ? u : parent[u]\
    \ = self(self, parent[u]);\n        };\n        vector<pair<int, int>> pending{\
    \ { (int)dp.size() - 1, v } };\n        while (!pending.empty()) {\n         \
    \   auto [mask, u] = pending.back();\n            pending.pop_back();\n      \
    \      int step = trace[mask][u];\n            if (step == -1) continue;\n   \
    \         if (step >= 0) {\n                pending.emplace_back(step, u);\n \
    \               pending.emplace_back(mask ^ step, u);\n            } else {\n\
    \                int id = -step - 2;\n                const auto &e = edges[id];\n\
    \                pending.emplace_back(mask, e.u ^ e.v ^ u);\n                int\
    \ a = root(root, e.u), b = root(root, e.v);\n                if (a == b) continue;\n\
    \                if (parent[a] > parent[b]) swap(a, b);\n                parent[a]\
    \ += parent[b];\n                parent[b] = a;\n                result.push_back(id);\n\
    \            }\n        }\n        return result;\n    }\n};\n\n#endif\n\n/**\n\
    \ * @brief \u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\u6728\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/minimum_steiner_tree.cpp
  requiredBy: []
  timestamp: '2026-10-17 02:52:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_minimum_steiner_tree.test.cpp
  - test/yosupo_aplusb_minimum_steiner_tree.test.cpp
documentation_of: graph/minimum_steiner_tree.cpp
layout: document
title: "\u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\u6728"
---

## 説明
非負重みの無向グラフで、指定された頂点集合を連結にする最小コストと採用辺を求める。
`build(terminals)` で前計算し、`cost(v)` で `terminals` に `v` を加えた場合の最小コストを取得する。
非連結グラフ、多重辺、自己ループ、重み0の辺に対応する。

## できること
指定頂点数を $K$、頂点数を $N$、辺数を $M$ とする。

- `MinimumSteinerTree<T> st(n)`
  `n` 頂点のグラフを作る。`n >= 1`
- `int add_edge(int u, int v, T weight)`
  無向辺を追加し、0から始まる入力順の辺IDを返す。最初の `build` より前に呼ぶ
- `void build(const vector<int>& terminals)`
  指定頂点集合について前計算する。再呼び出しで以前のDPと復元情報を置き換える
  時間 $O(3^K N + 2^K (N+M)\log(N+M+1))$、保持領域 $O(2^K N+M)$
- `T cost(int v) const`
  `terminals` と `v` を連結にする最小コストを返す。連結にできなければ `INF<T>`。時間 $O(1)$
- `vector<int> restore(int v) const`
  `cost(v)` を達成する木の辺IDを重複なく返す。連結にできなければ空。空解とは `cost(v)` で区別する
  時間 $O(KN\alpha(N))$、追加領域 $O(N+K)$

## 使い方
頂点は0-indexed、`terminals` は相異なる有効な頂点の非空列とする。
`T` は整数型（通常は `long long`）、辺重みは非負、有限の答えは `INF<T>` 未満とする。

```cpp
MinimumSteinerTree<long long> st(n);
for (auto [u, v, w] : edges) st.add_edge(u, v, w);
st.build(terminals);
auto answer = st.cost(terminals[0]);
auto ids = st.restore(terminals[0]);
for (int v = 0; v < n; ++v) {
    auto with_v = st.cost(v);
}
```

## 実装上の補足
部分集合DPの分割遷移と、各集合に対する多始点Dijkstra法を使う。
復元は再帰でグラフをたどらず、Union-Findで重複辺と重み0の閉路を除く。
最適解の一意性や辺IDの順序は保証しない。
