---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_directedmst.test.cpp
    title: test/yosupo_directedmst.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6700\u5C0F\u5168\u57DF\u6709\u5411\u6728(Chu-Liu/Edmonds)"
    links: []
  bundledCode: "#line 1 \"graph/chu_liu_edmonds.cpp\"\ntemplate<class T>\nstruct ChuLiuEdmonds\
    \ {\n    struct Edge {\n        int from, to;\n        T cost;\n    };\n\n   \
    \ struct Result {\n        bool exists;\n        T cost;\n        vector<int>\
    \ parent;\n        vector<int> edge_id;\n    };\n\n    struct UnionFind {\n  \
    \      vector<int> p;\n\n        explicit UnionFind(int n) : p(n, -1) {}\n\n \
    \       int root(int x) {\n            if (p[x] < 0) return x;\n            return\
    \ p[x] = root(p[x]);\n        }\n\n        bool unite(int a, int b) {\n      \
    \      a = root(a);\n            b = root(b);\n            if (a == b) return\
    \ false;\n            if (p[a] > p[b]) swap(a, b);\n            p[a] += p[b];\n\
    \            p[b] = a;\n            return true;\n        }\n    };\n\n    struct\
    \ SkewHeapNode {\n        T key, lazy;\n        int idx;\n        SkewHeapNode\
    \ *l, *r;\n\n        SkewHeapNode(T key, int idx) : key(key), lazy(0), idx(idx),\
    \ l(nullptr), r(nullptr) {}\n    };\n\n    int n, root;\n    vector<Edge> edges;\n\
    \n    explicit ChuLiuEdmonds(int n, int root) : n(n), root(root) {}\n\n    int\
    \ add_edge(int from, int to, T cost) {\n        edges.push_back({from, to, cost});\n\
    \        return (int)edges.size() - 1;\n    }\n\n    static void push(SkewHeapNode\
    \ *node) {\n        if (node == nullptr || node->lazy == T(0)) return;\n     \
    \   if (node->l != nullptr) {\n            node->l->key += node->lazy;\n     \
    \       node->l->lazy += node->lazy;\n        }\n        if (node->r != nullptr)\
    \ {\n            node->r->key += node->lazy;\n            node->r->lazy += node->lazy;\n\
    \        }\n        node->lazy = T(0);\n    }\n\n    static SkewHeapNode* meld(SkewHeapNode\
    \ *a, SkewHeapNode *b) {\n        if (a == nullptr) return b;\n        if (b ==\
    \ nullptr) return a;\n        if (b->key < a->key) swap(a, b);\n        push(a);\n\
    \        a->r = meld(a->r, b);\n        swap(a->l, a->r);\n        return a;\n\
    \    }\n\n    static SkewHeapNode* pop(SkewHeapNode *a) {\n        push(a);\n\
    \        return meld(a->l, a->r);\n    }\n\n    Result solve() const {\n     \
    \   vector<SkewHeapNode> nodes;\n        nodes.reserve(edges.size());\n      \
    \  vector<SkewHeapNode*> come(n, nullptr);\n        for (int i = 0; i < (int)edges.size();\
    \ ++i) {\n            nodes.emplace_back(edges[i].cost, i);\n            come[edges[i].to]\
    \ = meld(come[edges[i].to], &nodes.back());\n        }\n\n        UnionFind uf(n);\n\
    \        vector<int> used(n, -1), from(n, -1), stem(n, -1);\n        vector<T>\
    \ from_cost(n, T(0));\n        vector<int> parent_edge(edges.size(), -1), order;\n\
    \        used[root] = root;\n        T total = T(0);\n\n        for (int start\
    \ = 0; start < n; ++start) {\n            if (used[start] != -1) continue;\n \
    \           int cur = start;\n            vector<int> child_edges;\n         \
    \   int cycle = 0;\n            while (used[cur] == -1 || used[cur] == start)\
    \ {\n                used[cur] = start;\n                while (come[cur] != nullptr\
    \ && uf.root(edges[come[cur]->idx].from) == cur) {\n                    come[cur]\
    \ = pop(come[cur]);\n                }\n                if (come[cur] == nullptr)\
    \ return {false, T(0), {}, {}};\n                int idx = come[cur]->idx;\n \
    \               int src = uf.root(edges[idx].from);\n                T cost =\
    \ come[cur]->key;\n                come[cur] = pop(come[cur]);\n\n           \
    \     from[cur] = src;\n                from_cost[cur] = cost;\n             \
    \   if (stem[cur] == -1) stem[cur] = idx;\n                total += cost;\n  \
    \              order.push_back(idx);\n                while (cycle) {\n      \
    \              parent_edge[child_edges.back()] = idx;\n                    child_edges.pop_back();\n\
    \                    --cycle;\n                }\n                child_edges.push_back(idx);\n\
    \n                if (used[src] == start) {\n                    int p = cur;\n\
    \                    do {\n                        if (come[p] != nullptr) {\n\
    \                            come[p]->key -= from_cost[p];\n                 \
    \           come[p]->lazy -= from_cost[p];\n                        }\n      \
    \                  if (p != cur) {\n                            int pv = p;\n\
    \                            int cv = cur;\n                            uf.unite(pv,\
    \ cv);\n                            cur = uf.root(cv);\n                     \
    \       come[cur] = meld(come[pv], come[cv]);\n                        }\n   \
    \                     p = uf.root(from[p]);\n                        ++cycle;\n\
    \                    } while (p != cur);\n                } else {\n         \
    \           cur = src;\n                }\n            }\n        }\n\n      \
    \  vector<int> used_edge(edges.size(), 0), edge_id(n, -1), parent(n, -1);\n  \
    \      parent[root] = root;\n        for (int i = (int)order.size() - 1; i >=\
    \ 0; --i) {\n            int idx = order[i];\n            if (used_edge[idx])\
    \ continue;\n            int v = edges[idx].to;\n            edge_id[v] = idx;\n\
    \            parent[v] = edges[idx].from;\n            int x = stem[v];\n    \
    \        while (x != idx) {\n                used_edge[x] = 1;\n             \
    \   x = parent_edge[x];\n            }\n        }\n        return {true, total,\
    \ parent, edge_id};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6709\
    \u5411\u6728(Chu-Liu/Edmonds)\n */\n"
  code: "template<class T>\nstruct ChuLiuEdmonds {\n    struct Edge {\n        int\
    \ from, to;\n        T cost;\n    };\n\n    struct Result {\n        bool exists;\n\
    \        T cost;\n        vector<int> parent;\n        vector<int> edge_id;\n\
    \    };\n\n    struct UnionFind {\n        vector<int> p;\n\n        explicit\
    \ UnionFind(int n) : p(n, -1) {}\n\n        int root(int x) {\n            if\
    \ (p[x] < 0) return x;\n            return p[x] = root(p[x]);\n        }\n\n \
    \       bool unite(int a, int b) {\n            a = root(a);\n            b =\
    \ root(b);\n            if (a == b) return false;\n            if (p[a] > p[b])\
    \ swap(a, b);\n            p[a] += p[b];\n            p[b] = a;\n            return\
    \ true;\n        }\n    };\n\n    struct SkewHeapNode {\n        T key, lazy;\n\
    \        int idx;\n        SkewHeapNode *l, *r;\n\n        SkewHeapNode(T key,\
    \ int idx) : key(key), lazy(0), idx(idx), l(nullptr), r(nullptr) {}\n    };\n\n\
    \    int n, root;\n    vector<Edge> edges;\n\n    explicit ChuLiuEdmonds(int n,\
    \ int root) : n(n), root(root) {}\n\n    int add_edge(int from, int to, T cost)\
    \ {\n        edges.push_back({from, to, cost});\n        return (int)edges.size()\
    \ - 1;\n    }\n\n    static void push(SkewHeapNode *node) {\n        if (node\
    \ == nullptr || node->lazy == T(0)) return;\n        if (node->l != nullptr) {\n\
    \            node->l->key += node->lazy;\n            node->l->lazy += node->lazy;\n\
    \        }\n        if (node->r != nullptr) {\n            node->r->key += node->lazy;\n\
    \            node->r->lazy += node->lazy;\n        }\n        node->lazy = T(0);\n\
    \    }\n\n    static SkewHeapNode* meld(SkewHeapNode *a, SkewHeapNode *b) {\n\
    \        if (a == nullptr) return b;\n        if (b == nullptr) return a;\n  \
    \      if (b->key < a->key) swap(a, b);\n        push(a);\n        a->r = meld(a->r,\
    \ b);\n        swap(a->l, a->r);\n        return a;\n    }\n\n    static SkewHeapNode*\
    \ pop(SkewHeapNode *a) {\n        push(a);\n        return meld(a->l, a->r);\n\
    \    }\n\n    Result solve() const {\n        vector<SkewHeapNode> nodes;\n  \
    \      nodes.reserve(edges.size());\n        vector<SkewHeapNode*> come(n, nullptr);\n\
    \        for (int i = 0; i < (int)edges.size(); ++i) {\n            nodes.emplace_back(edges[i].cost,\
    \ i);\n            come[edges[i].to] = meld(come[edges[i].to], &nodes.back());\n\
    \        }\n\n        UnionFind uf(n);\n        vector<int> used(n, -1), from(n,\
    \ -1), stem(n, -1);\n        vector<T> from_cost(n, T(0));\n        vector<int>\
    \ parent_edge(edges.size(), -1), order;\n        used[root] = root;\n        T\
    \ total = T(0);\n\n        for (int start = 0; start < n; ++start) {\n       \
    \     if (used[start] != -1) continue;\n            int cur = start;\n       \
    \     vector<int> child_edges;\n            int cycle = 0;\n            while\
    \ (used[cur] == -1 || used[cur] == start) {\n                used[cur] = start;\n\
    \                while (come[cur] != nullptr && uf.root(edges[come[cur]->idx].from)\
    \ == cur) {\n                    come[cur] = pop(come[cur]);\n               \
    \ }\n                if (come[cur] == nullptr) return {false, T(0), {}, {}};\n\
    \                int idx = come[cur]->idx;\n                int src = uf.root(edges[idx].from);\n\
    \                T cost = come[cur]->key;\n                come[cur] = pop(come[cur]);\n\
    \n                from[cur] = src;\n                from_cost[cur] = cost;\n \
    \               if (stem[cur] == -1) stem[cur] = idx;\n                total +=\
    \ cost;\n                order.push_back(idx);\n                while (cycle)\
    \ {\n                    parent_edge[child_edges.back()] = idx;\n            \
    \        child_edges.pop_back();\n                    --cycle;\n             \
    \   }\n                child_edges.push_back(idx);\n\n                if (used[src]\
    \ == start) {\n                    int p = cur;\n                    do {\n  \
    \                      if (come[p] != nullptr) {\n                           \
    \ come[p]->key -= from_cost[p];\n                            come[p]->lazy -=\
    \ from_cost[p];\n                        }\n                        if (p != cur)\
    \ {\n                            int pv = p;\n                            int\
    \ cv = cur;\n                            uf.unite(pv, cv);\n                 \
    \           cur = uf.root(cv);\n                            come[cur] = meld(come[pv],\
    \ come[cv]);\n                        }\n                        p = uf.root(from[p]);\n\
    \                        ++cycle;\n                    } while (p != cur);\n \
    \               } else {\n                    cur = src;\n                }\n\
    \            }\n        }\n\n        vector<int> used_edge(edges.size(), 0), edge_id(n,\
    \ -1), parent(n, -1);\n        parent[root] = root;\n        for (int i = (int)order.size()\
    \ - 1; i >= 0; --i) {\n            int idx = order[i];\n            if (used_edge[idx])\
    \ continue;\n            int v = edges[idx].to;\n            edge_id[v] = idx;\n\
    \            parent[v] = edges[idx].from;\n            int x = stem[v];\n    \
    \        while (x != idx) {\n                used_edge[x] = 1;\n             \
    \   x = parent_edge[x];\n            }\n        }\n        return {true, total,\
    \ parent, edge_id};\n    }\n};\n\n/**\n * @brief \u6700\u5C0F\u5168\u57DF\u6709\
    \u5411\u6728(Chu-Liu/Edmonds)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/chu_liu_edmonds.cpp
  requiredBy: []
  timestamp: '2026-03-08 22:25:54+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_directedmst.test.cpp
date: 2026-03-08
documentation_of: graph/chu_liu_edmonds.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: Chu-Liu Edmonds
---

## 説明
根付き有向グラフの最小全域有向木を求める。
各頂点へ入る辺から 1 本ずつ選び、根 `root` から全頂点へ到達できる最小コストの親配列を返す。

## できること
- `ChuLiuEdmonds<T> dmst(n, root)`
  頂点数 `n`、根 `root` のインスタンスを作る
- `int add_edge(int from, int to, T cost)`
  有向辺を追加し、その辺番号を返す
- `Result solve()`
  最小全域有向木を求める。存在しないとき `exists == false`

`Result` は次を持つ。

- `bool exists`
  最小全域有向木が存在するか
- `T cost`
  最小コスト。存在しないときは未定義
- `vector<int> parent`
  各頂点の親。根は `parent[root] = root`。存在しないときは空
- `vector<int> edge_id`
  採用した辺番号。根は `-1`

## 使い方
`add_edge` で全辺を追加してから `solve()` を呼ぶ。
戻り値の `parent[v]` が `v` の親、`edge_id[v]` が対応する採用辺番号になる。

## 実装上の補足
Skew heap + Union-Find による Chu-Liu/Edmonds 法。
計算量は償却 $O(M log N)$。
