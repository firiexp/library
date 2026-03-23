---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
    title: test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Dynamic Graph Vertex Add Component Sum
    links: []
  bundledCode: "#line 1 \"graph/dynamic_graph_vertex_add_component_sum.cpp\"\nusing\
    \ namespace std;\n\nstruct RollbackUnionFindComponentSum {\n    struct History\
    \ {\n        int child, parent;\n        int parent_size, child_size;\n      \
    \  long long parent_sum, child_sum;\n    };\n\n    vector<int> parent_or_size;\n\
    \    vector<long long> comp_sum;\n    vector<History> history;\n\n    explicit\
    \ RollbackUnionFindComponentSum(int n, const vector<long long> &a)\n        :\
    \ parent_or_size(n, -1), comp_sum(a) {}\n\n    int root(int v) const {\n     \
    \   while (parent_or_size[v] >= 0) v = parent_or_size[v];\n        return v;\n\
    \    }\n\n    int snapshot() const {\n        return (int)history.size();\n  \
    \  }\n\n    void rollback(int snap) {\n        while ((int)history.size() > snap)\
    \ {\n            auto h = history.back();\n            history.pop_back();\n \
    \           if (h.parent == -1) continue;\n            parent_or_size[h.parent]\
    \ = h.parent_size;\n            parent_or_size[h.child] = h.child_size;\n    \
    \        comp_sum[h.parent] = h.parent_sum;\n            comp_sum[h.child] = h.child_sum;\n\
    \        }\n    }\n\n    void unite(int a, int b) {\n        a = root(a), b =\
    \ root(b);\n        if (a == b) {\n            history.push_back({-1, -1, 0, 0,\
    \ 0, 0});\n            return;\n        }\n        if (parent_or_size[a] > parent_or_size[b])\
    \ swap(a, b);\n        history.push_back({b, a, parent_or_size[a], parent_or_size[b],\
    \ comp_sum[a], comp_sum[b]});\n        parent_or_size[a] += parent_or_size[b];\n\
    \        parent_or_size[b] = a;\n        comp_sum[a] += comp_sum[b];\n    }\n\n\
    \    void add_value(int v, long long x) {\n        int r = root(v);\n        history.push_back({r,\
    \ r, parent_or_size[r], parent_or_size[r], comp_sum[r], comp_sum[r]});\n     \
    \   comp_sum[r] += x;\n    }\n\n    long long get_sum(int v) const {\n       \
    \ return comp_sum[root(v)];\n    }\n};\n\nstruct DynamicGraphVertexAddComponentSum\
    \ {\n    struct Query {\n        int type, u, v;\n        long long x;\n    };\n\
    \    struct EdgeEvent {\n        int u, v;\n    };\n    struct AddEvent {\n  \
    \      int v;\n        long long x;\n    };\n\n    int n, q, sz;\n    vector<Query>\
    \ queries;\n    vector<vector<EdgeEvent>> seg_edges;\n    vector<vector<AddEvent>>\
    \ seg_adds;\n    vector<long long> initial;\n\n    DynamicGraphVertexAddComponentSum(const\
    \ vector<long long> &a, int q)\n        : n((int)a.size()), q(q), initial(a) {\n\
    \        sz = 1;\n        while (sz < q) sz <<= 1;\n        seg_edges.resize(2\
    \ * sz);\n        seg_adds.resize(2 * sz);\n        queries.reserve(q);\n    }\n\
    \n    void add_edge(int u, int v) {\n        queries.push_back({0, u, v, 0});\n\
    \    }\n\n    void erase_edge(int u, int v) {\n        queries.push_back({1, u,\
    \ v, 0});\n    }\n\n    void add_vertex(int v, long long x) {\n        queries.push_back({2,\
    \ v, 0, x});\n    }\n\n    void add_component_query(int v) {\n        queries.push_back({3,\
    \ v, 0, 0});\n    }\n\n    template<class T>\n    void add_segment(vector<vector<T>>\
    \ &seg, int l, int r, const T &event) {\n        for (l += sz, r += sz; l < r;\
    \ l >>= 1, r >>= 1) {\n            if (l & 1) seg[l++].push_back(event);\n   \
    \         if (r & 1) seg[--r].push_back(event);\n        }\n    }\n\n    vector<long\
    \ long> solve() {\n        map<pair<int, int>, int> appear;\n        for (int\
    \ t = 0; t < q; ++t) {\n            auto query = queries[t];\n            if (query.type\
    \ == 0) {\n                appear[minmax(query.u, query.v)] = t;\n           \
    \ } else if (query.type == 1) {\n                auto e = minmax(query.u, query.v);\n\
    \                add_segment(seg_edges, appear[e], t, {e.first, e.second});\n\
    \                appear.erase(e);\n            } else if (query.type == 2) {\n\
    \                add_segment(seg_adds, t, q, {query.u, query.x});\n          \
    \  }\n        }\n        for (auto &&[e, l] : appear) add_segment(seg_edges, l,\
    \ q, {e.first, e.second});\n\n        RollbackUnionFindComponentSum uf(n, initial);\n\
    \        vector<long long> ans;\n        ans.reserve(q);\n        auto dfs = [&](auto\
    \ &&self, int k) -> void {\n            int snap = uf.snapshot();\n          \
    \  for (auto &&e : seg_edges[k]) uf.unite(e.u, e.v);\n            for (auto &&a\
    \ : seg_adds[k]) uf.add_value(a.v, a.x);\n            if (k < sz) {\n        \
    \        self(self, k << 1);\n                self(self, k << 1 | 1);\n      \
    \      } else {\n                int t = k - sz;\n                if (t < q &&\
    \ queries[t].type == 3) ans.push_back(uf.get_sum(queries[t].u));\n           \
    \ }\n            uf.rollback(snap);\n        };\n        dfs(dfs, 1);\n      \
    \  return ans;\n    }\n};\n\n/**\n * @brief Dynamic Graph Vertex Add Component\
    \ Sum\n */\n"
  code: "using namespace std;\n\nstruct RollbackUnionFindComponentSum {\n    struct\
    \ History {\n        int child, parent;\n        int parent_size, child_size;\n\
    \        long long parent_sum, child_sum;\n    };\n\n    vector<int> parent_or_size;\n\
    \    vector<long long> comp_sum;\n    vector<History> history;\n\n    explicit\
    \ RollbackUnionFindComponentSum(int n, const vector<long long> &a)\n        :\
    \ parent_or_size(n, -1), comp_sum(a) {}\n\n    int root(int v) const {\n     \
    \   while (parent_or_size[v] >= 0) v = parent_or_size[v];\n        return v;\n\
    \    }\n\n    int snapshot() const {\n        return (int)history.size();\n  \
    \  }\n\n    void rollback(int snap) {\n        while ((int)history.size() > snap)\
    \ {\n            auto h = history.back();\n            history.pop_back();\n \
    \           if (h.parent == -1) continue;\n            parent_or_size[h.parent]\
    \ = h.parent_size;\n            parent_or_size[h.child] = h.child_size;\n    \
    \        comp_sum[h.parent] = h.parent_sum;\n            comp_sum[h.child] = h.child_sum;\n\
    \        }\n    }\n\n    void unite(int a, int b) {\n        a = root(a), b =\
    \ root(b);\n        if (a == b) {\n            history.push_back({-1, -1, 0, 0,\
    \ 0, 0});\n            return;\n        }\n        if (parent_or_size[a] > parent_or_size[b])\
    \ swap(a, b);\n        history.push_back({b, a, parent_or_size[a], parent_or_size[b],\
    \ comp_sum[a], comp_sum[b]});\n        parent_or_size[a] += parent_or_size[b];\n\
    \        parent_or_size[b] = a;\n        comp_sum[a] += comp_sum[b];\n    }\n\n\
    \    void add_value(int v, long long x) {\n        int r = root(v);\n        history.push_back({r,\
    \ r, parent_or_size[r], parent_or_size[r], comp_sum[r], comp_sum[r]});\n     \
    \   comp_sum[r] += x;\n    }\n\n    long long get_sum(int v) const {\n       \
    \ return comp_sum[root(v)];\n    }\n};\n\nstruct DynamicGraphVertexAddComponentSum\
    \ {\n    struct Query {\n        int type, u, v;\n        long long x;\n    };\n\
    \    struct EdgeEvent {\n        int u, v;\n    };\n    struct AddEvent {\n  \
    \      int v;\n        long long x;\n    };\n\n    int n, q, sz;\n    vector<Query>\
    \ queries;\n    vector<vector<EdgeEvent>> seg_edges;\n    vector<vector<AddEvent>>\
    \ seg_adds;\n    vector<long long> initial;\n\n    DynamicGraphVertexAddComponentSum(const\
    \ vector<long long> &a, int q)\n        : n((int)a.size()), q(q), initial(a) {\n\
    \        sz = 1;\n        while (sz < q) sz <<= 1;\n        seg_edges.resize(2\
    \ * sz);\n        seg_adds.resize(2 * sz);\n        queries.reserve(q);\n    }\n\
    \n    void add_edge(int u, int v) {\n        queries.push_back({0, u, v, 0});\n\
    \    }\n\n    void erase_edge(int u, int v) {\n        queries.push_back({1, u,\
    \ v, 0});\n    }\n\n    void add_vertex(int v, long long x) {\n        queries.push_back({2,\
    \ v, 0, x});\n    }\n\n    void add_component_query(int v) {\n        queries.push_back({3,\
    \ v, 0, 0});\n    }\n\n    template<class T>\n    void add_segment(vector<vector<T>>\
    \ &seg, int l, int r, const T &event) {\n        for (l += sz, r += sz; l < r;\
    \ l >>= 1, r >>= 1) {\n            if (l & 1) seg[l++].push_back(event);\n   \
    \         if (r & 1) seg[--r].push_back(event);\n        }\n    }\n\n    vector<long\
    \ long> solve() {\n        map<pair<int, int>, int> appear;\n        for (int\
    \ t = 0; t < q; ++t) {\n            auto query = queries[t];\n            if (query.type\
    \ == 0) {\n                appear[minmax(query.u, query.v)] = t;\n           \
    \ } else if (query.type == 1) {\n                auto e = minmax(query.u, query.v);\n\
    \                add_segment(seg_edges, appear[e], t, {e.first, e.second});\n\
    \                appear.erase(e);\n            } else if (query.type == 2) {\n\
    \                add_segment(seg_adds, t, q, {query.u, query.x});\n          \
    \  }\n        }\n        for (auto &&[e, l] : appear) add_segment(seg_edges, l,\
    \ q, {e.first, e.second});\n\n        RollbackUnionFindComponentSum uf(n, initial);\n\
    \        vector<long long> ans;\n        ans.reserve(q);\n        auto dfs = [&](auto\
    \ &&self, int k) -> void {\n            int snap = uf.snapshot();\n          \
    \  for (auto &&e : seg_edges[k]) uf.unite(e.u, e.v);\n            for (auto &&a\
    \ : seg_adds[k]) uf.add_value(a.v, a.x);\n            if (k < sz) {\n        \
    \        self(self, k << 1);\n                self(self, k << 1 | 1);\n      \
    \      } else {\n                int t = k - sz;\n                if (t < q &&\
    \ queries[t].type == 3) ans.push_back(uf.get_sum(queries[t].u));\n           \
    \ }\n            uf.rollback(snap);\n        };\n        dfs(dfs, 1);\n      \
    \  return ans;\n    }\n};\n\n/**\n * @brief Dynamic Graph Vertex Add Component\
    \ Sum\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/dynamic_graph_vertex_add_component_sum.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_dynamic_graph_vertex_add_component_sum.test.cpp
date: 2026-03-11
documentation_of: graph/dynamic_graph_vertex_add_component_sum.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u52D5\u7684\u30B0\u30E9\u30D5\u9023\u7D50\u6210\u5206\u548C(Dynamic Graph\
  \ Vertex Add Component Sum)"
---

## 説明
辺の追加・削除、頂点加算、連結成分和取得を offline で処理する。
時間区間セグメント木と rollback Union-Find を使う。

## できること
- `DynamicGraphVertexAddComponentSum(const vector<long long>& a, int q)`
  初期頂点値 `a` とクエリ数 `q` を受け取って solver を作る
- `void add_edge(int u, int v)`
  辺追加クエリを積む
- `void erase_edge(int u, int v)`
  辺削除クエリを積む
- `void add_vertex(int v, long long x)`
  頂点 `v` に `x` を足すクエリを積む
- `void add_component_query(int v)`
  頂点 `v` が属する連結成分の総和クエリを積む
- `vector<long long> solve()`
  クエリ順に各総和クエリの答えを返す

## 使い方
クエリを時系列順に積み、最後に `solve()` を呼ぶ。
計算量は $O((N + Q) log Q log^* N)$ 相当で、rollback により経路圧縮は使わない。
