---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj0294.test.cpp
    title: test/aoj0294.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_dominator_queries.test.cpp
    title: test/yosupo_aplusb_dominator_queries.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dominator_tree.test.cpp
    title: test/yosupo_dominator_tree.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Dominator Tree
    links: []
  bundledCode: "#line 1 \"graph/dominatortree.cpp\"\nclass DominatorTree {\n    struct\
    \ CSR {\n        vector<int> start, elist;\n\n        CSR() = default;\n\n   \
    \     CSR(int n, const vector<pair<int, int>> &edges, bool rev) : start(n + 1),\
    \ elist(edges.size()) {\n            for (auto &&[a, b] : edges) {\n         \
    \       ++start[(rev ? b : a) + 1];\n            }\n            for (int i = 0;\
    \ i < n; ++i) start[i + 1] += start[i];\n            auto counter = start;\n \
    \           for (auto &&[a, b] : edges) {\n                int from = rev ? b\
    \ : a;\n                int to = rev ? a : b;\n                elist[counter[from]++]\
    \ = to;\n            }\n        }\n    };\n\n    int n;\n    vector<pair<int,\
    \ int>> edges;\n    vector<int> tin, tout;\n    void unite(int x, int y){\n  \
    \      uf_par[y] = x;\n    }\n\n    int compress(int x){\n        if(uf_par[x]\
    \ == x) return x;\n        int r = compress(uf_par[x]);\n        if(semi[m[x]]\
    \ > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];\n        return uf_par[x] = r;\n\
    \    }\n\n    int eval(int x){\n        compress(x);\n        return m[x];\n \
    \   }\npublic:\n    DominatorTree(int n) : n(n), tin(n, -1), tout(n, -1), semi(n),\
    \ ord(n), par(n), uf_par(n), m(n), U(n), idom(n), bucket_head(n), bucket_next(n)\
    \ {}\n\n    vector<int> semi, ord, par, uf_par, m, U, idom;\n    vector<int> bucket_head,\
    \ bucket_next;\n\n    void add_edge(int a, int b){\n        edges.emplace_back(a,\
    \ b);\n    }\n\n    bool reachable(int v) const {\n        return tin[v] != -1;\n\
    \    }\n\n    bool dominates(int u, int v) const {\n        return reachable(u)\
    \ && reachable(v) && tin[u] <= tin[v] && tin[v] < tout[u];\n    }\n\n    bool\
    \ reachable_without_vertex(int target, int removed) const {\n        return reachable(target)\
    \ && !dominates(removed, target);\n    }\n\n    void build(int root){\n      \
    \  CSR G(n, edges, false), Grev(n, edges, true);\n        for (int i = 0; i <\
    \ n; ++i) {\n            uf_par[i] = i;\n            m[i] = i;\n            semi[i]\
    \ = -1;\n            idom[i] = -1;\n            par[i] = -1;\n            bucket_head[i]\
    \ = -1;\n            bucket_next[i] = -1;\n            tin[i] = tout[i] = -1;\n\
    \        }\n        int cur = 0;\n        auto dfs = [&](auto &&self, int x) ->\
    \ void {\n            semi[x] = cur;\n            ord[cur++] = x;\n          \
    \  for (int ei = G.start[x]; ei < G.start[x + 1]; ++ei) {\n                int\
    \ to = G.elist[ei];\n                if(!~semi[to]){\n                    par[to]\
    \ = x;\n                    self(self, to);\n                }\n            }\n\
    \        };\n        par[root] = root;\n        dfs(dfs, root);\n        for (int\
    \ i = cur-1; i >= 0; --i) {\n            int a = ord[i];\n            for (int\
    \ ei = Grev.start[a]; ei < Grev.start[a + 1]; ++ei) {\n                int b =\
    \ Grev.elist[ei];\n                if(~semi[b]){\n                    int c =\
    \ eval(b);\n                    semi[a] = min(semi[a], semi[c]);\n           \
    \     }\n            }\n            bucket_next[a] = bucket_head[ord[semi[a]]];\n\
    \            bucket_head[ord[semi[a]]] = a;\n            int p = par[a];\n   \
    \         for (int b = bucket_head[p]; b != -1; b = bucket_next[b]) {\n      \
    \          U[b] = eval(b);\n            }\n            bucket_head[p] = -1;\n\
    \            unite(p, a);\n        }\n        for (int i = 1; i < cur; ++i) {\n\
    \            int a = ord[i], b = U[a];\n            if(semi[a] == semi[b]) idom[a]\
    \ = semi[a];\n            else idom[a] = idom[b];\n        }\n        for (int\
    \ i = 1; i < cur; ++i) {\n            int a = ord[i];\n            idom[a] = ord[idom[a]];\n\
    \        }\n        idom[root] = -1;\n        fill(bucket_head.begin(), bucket_head.end(),\
    \ -1);\n        for (int i = 1; i < cur; ++i) {\n            int v = ord[i];\n\
    \            bucket_next[v] = bucket_head[idom[v]];\n            bucket_head[idom[v]]\
    \ = v;\n        }\n        vector<int> stack;\n        stack.reserve(cur);\n \
    \       stack.push_back(root);\n        int timer = 0;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      if (v < 0) {\n                tout[~v] = timer;\n                continue;\n\
    \            }\n            tin[v] = timer++;\n            stack.push_back(~v);\n\
    \            for (int to = bucket_head[v]; to != -1; to = bucket_next[to]) stack.push_back(to);\n\
    \        }\n    }\n\n};\n\n\n/**\n * @brief Dominator Tree\n */\n"
  code: "class DominatorTree {\n    struct CSR {\n        vector<int> start, elist;\n\
    \n        CSR() = default;\n\n        CSR(int n, const vector<pair<int, int>>\
    \ &edges, bool rev) : start(n + 1), elist(edges.size()) {\n            for (auto\
    \ &&[a, b] : edges) {\n                ++start[(rev ? b : a) + 1];\n         \
    \   }\n            for (int i = 0; i < n; ++i) start[i + 1] += start[i];\n   \
    \         auto counter = start;\n            for (auto &&[a, b] : edges) {\n \
    \               int from = rev ? b : a;\n                int to = rev ? a : b;\n\
    \                elist[counter[from]++] = to;\n            }\n        }\n    };\n\
    \n    int n;\n    vector<pair<int, int>> edges;\n    vector<int> tin, tout;\n\
    \    void unite(int x, int y){\n        uf_par[y] = x;\n    }\n\n    int compress(int\
    \ x){\n        if(uf_par[x] == x) return x;\n        int r = compress(uf_par[x]);\n\
    \        if(semi[m[x]] > semi[m[uf_par[x]]]) m[x] = m[uf_par[x]];\n        return\
    \ uf_par[x] = r;\n    }\n\n    int eval(int x){\n        compress(x);\n      \
    \  return m[x];\n    }\npublic:\n    DominatorTree(int n) : n(n), tin(n, -1),\
    \ tout(n, -1), semi(n), ord(n), par(n), uf_par(n), m(n), U(n), idom(n), bucket_head(n),\
    \ bucket_next(n) {}\n\n    vector<int> semi, ord, par, uf_par, m, U, idom;\n \
    \   vector<int> bucket_head, bucket_next;\n\n    void add_edge(int a, int b){\n\
    \        edges.emplace_back(a, b);\n    }\n\n    bool reachable(int v) const {\n\
    \        return tin[v] != -1;\n    }\n\n    bool dominates(int u, int v) const\
    \ {\n        return reachable(u) && reachable(v) && tin[u] <= tin[v] && tin[v]\
    \ < tout[u];\n    }\n\n    bool reachable_without_vertex(int target, int removed)\
    \ const {\n        return reachable(target) && !dominates(removed, target);\n\
    \    }\n\n    void build(int root){\n        CSR G(n, edges, false), Grev(n, edges,\
    \ true);\n        for (int i = 0; i < n; ++i) {\n            uf_par[i] = i;\n\
    \            m[i] = i;\n            semi[i] = -1;\n            idom[i] = -1;\n\
    \            par[i] = -1;\n            bucket_head[i] = -1;\n            bucket_next[i]\
    \ = -1;\n            tin[i] = tout[i] = -1;\n        }\n        int cur = 0;\n\
    \        auto dfs = [&](auto &&self, int x) -> void {\n            semi[x] = cur;\n\
    \            ord[cur++] = x;\n            for (int ei = G.start[x]; ei < G.start[x\
    \ + 1]; ++ei) {\n                int to = G.elist[ei];\n                if(!~semi[to]){\n\
    \                    par[to] = x;\n                    self(self, to);\n     \
    \           }\n            }\n        };\n        par[root] = root;\n        dfs(dfs,\
    \ root);\n        for (int i = cur-1; i >= 0; --i) {\n            int a = ord[i];\n\
    \            for (int ei = Grev.start[a]; ei < Grev.start[a + 1]; ++ei) {\n  \
    \              int b = Grev.elist[ei];\n                if(~semi[b]){\n      \
    \              int c = eval(b);\n                    semi[a] = min(semi[a], semi[c]);\n\
    \                }\n            }\n            bucket_next[a] = bucket_head[ord[semi[a]]];\n\
    \            bucket_head[ord[semi[a]]] = a;\n            int p = par[a];\n   \
    \         for (int b = bucket_head[p]; b != -1; b = bucket_next[b]) {\n      \
    \          U[b] = eval(b);\n            }\n            bucket_head[p] = -1;\n\
    \            unite(p, a);\n        }\n        for (int i = 1; i < cur; ++i) {\n\
    \            int a = ord[i], b = U[a];\n            if(semi[a] == semi[b]) idom[a]\
    \ = semi[a];\n            else idom[a] = idom[b];\n        }\n        for (int\
    \ i = 1; i < cur; ++i) {\n            int a = ord[i];\n            idom[a] = ord[idom[a]];\n\
    \        }\n        idom[root] = -1;\n        fill(bucket_head.begin(), bucket_head.end(),\
    \ -1);\n        for (int i = 1; i < cur; ++i) {\n            int v = ord[i];\n\
    \            bucket_next[v] = bucket_head[idom[v]];\n            bucket_head[idom[v]]\
    \ = v;\n        }\n        vector<int> stack;\n        stack.reserve(cur);\n \
    \       stack.push_back(root);\n        int timer = 0;\n        while (!stack.empty())\
    \ {\n            int v = stack.back();\n            stack.pop_back();\n      \
    \      if (v < 0) {\n                tout[~v] = timer;\n                continue;\n\
    \            }\n            tin[v] = timer++;\n            stack.push_back(~v);\n\
    \            for (int to = bucket_head[v]; to != -1; to = bucket_next[to]) stack.push_back(to);\n\
    \        }\n    }\n\n};\n\n\n/**\n * @brief Dominator Tree\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/dominatortree.cpp
  requiredBy: []
  timestamp: '2026-10-18 09:38:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj0294.test.cpp
  - test/yosupo_aplusb_dominator_queries.test.cpp
  - test/yosupo_dominator_tree.test.cpp
documentation_of: graph/dominatortree.cpp
layout: document
title: Dominator Tree
---

## 説明
有向グラフの始点 `root` から到達可能な頂点について Dominator Tree を構築する。
`u` が `v` を支配するとは、始点から `v` へのすべての経路が `u` を通ることを表す。

## できること
- `void add_edge(int a, int b)`
  有向辺 `a -> b` を追加する。自己ループ・多重辺も扱う
- `void build(int root)`
  `root` を始点に Dominator Tree を構築する
- `idom[v]`
  `v` 自身を除く `v` の支配頂点のうち、他のすべてに支配される頂点（immediate dominator）。Dominator Tree では `v` の親にあたる。根と未到達頂点は `-1`
- `bool reachable(int v) const`
  始点から `v` へ到達可能かを返す
- `bool dominates(int u, int v) const`
  `u` が `v` を支配するかを返す。どちらかが未到達なら `false`。到達可能な頂点は自分自身を支配する
- `bool reachable_without_vertex(int target, int removed) const`
  `removed` を削除しても始点から `target` へ到達可能かを返す。始点や `target` 自身を削除した場合、または元から未到達なら `false`

## 使い方
`DominatorTree dt(n)` に辺を追加し、`dt.build(root)` の後でクエリを処理する。
頂点番号は `[0, n)` とする。辺の追加や始点の変更後は再度 `build` を呼ぶ。
未到達の頂点を削除しても、元から到達可能な頂点への到達性は変わらない。

## 実装上の補足
Dominator Tree の構築後、祖先判定の前処理を $O(N)$ 時間・追加領域で行う。各クエリは $O(1)$。
削除後の到達性は、元から到達可能で、削除頂点に支配されないことと同値である。
