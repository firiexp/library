---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: datastructure/undoableunionfind.cpp
    title: Undoable Union Find
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
    title: test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: Offline Dynamic Connectivity
    links: []
  bundledCode: "#line 1 \"graph/offlinedynamicconnectivity.cpp\"\nusing namespace\
    \ std;\n\n#line 1 \"datastructure/undoableunionfind.cpp\"\nclass UndoableUnionFind\
    \ {\n    stack<pair<int, int>> hist;\n    int forest_size;\n    int snap;\n\n\
    public:\n    vector<int> uni;\n\n    explicit UndoableUnionFind(int sz) : forest_size(sz),\
    \ snap(0), uni(sz, -1) {}\n\n    int root(int a) {\n        if (uni[a] < 0) return\
    \ a;\n        return root(uni[a]);\n    }\n\n    bool same(int a, int b) {\n \
    \       return root(a) == root(b);\n    }\n\n    bool unite(int a, int b) {\n\
    \        a = root(a);\n        b = root(b);\n        hist.emplace(a, uni[a]);\n\
    \        hist.emplace(b, uni[b]);\n        if (a == b) return false;\n       \
    \ if (uni[a] > uni[b]) swap(a, b);\n        uni[a] += uni[b];\n        uni[b]\
    \ = a;\n        forest_size--;\n        return true;\n    }\n\n    int size()\
    \ { return forest_size; }\n    int size(int i) { return -uni[root(i)]; }\n\n \
    \   int get_state() const {\n        return int(hist.size() >> 1);\n    }\n\n\
    \    void undo() {\n        int a = hist.top().first;\n        int ua = hist.top().second;\n\
    \        hist.pop();\n        int b = hist.top().first;\n        int ub = hist.top().second;\n\
    \        hist.pop();\n        if (a != b) forest_size++;\n        uni[a] = ua;\n\
    \        uni[b] = ub;\n    }\n\n    void snapshot() {\n        snap = get_state();\n\
    \    }\n\n    void rollback(int state = -1) {\n        if (state == -1) state\
    \ = snap;\n        while (get_state() > state) undo();\n    }\n};\n\n/**\n * @brief\
    \ Undoable Union Find\n */\n#line 4 \"graph/offlinedynamicconnectivity.cpp\"\n\
    \nstruct OfflineDynamicConnectivity {\n    int n, q, sz;\n    UndoableUnionFind\
    \ uf;\n    vector<vector<pair<int, int>>> seg;\n    vector<pair<pair<int, int>,\
    \ pair<int, int>>> pend;\n    map<pair<int, int>, int> cnt, appear;\n\n    explicit\
    \ OfflineDynamicConnectivity(int n, int q) : n(n), q(q), uf(n) {\n        sz =\
    \ 1;\n        while (sz < q) sz <<= 1;\n        seg.resize(2 * sz);\n    }\n\n\
    \    void add_segment(int l, int r, const pair<int, int> &e) {\n        for (l\
    \ += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) seg[l++].push_back(e);\n\
    \            if (r & 1) seg[--r].push_back(e);\n        }\n    }\n\n    void insert(int\
    \ t, int a, int b) {\n        auto e = minmax(a, b);\n        if (cnt[e]++ ==\
    \ 0) appear[e] = t;\n    }\n\n    void erase(int t, int a, int b) {\n        auto\
    \ e = minmax(a, b);\n        if (--cnt[e] == 0) {\n            pend.emplace_back(make_pair(appear[e],\
    \ t), e);\n            appear.erase(e);\n        }\n    }\n\n    void build()\
    \ {\n        for (auto &&[e, c] : cnt) {\n            if (!c) continue;\n    \
    \        pend.emplace_back(make_pair(appear[e], q), e);\n        }\n        for\
    \ (auto &&[range, e] : pend) add_segment(range.first, range.second, e);\n    }\n\
    \n    template <class Enter, class Leave, class Leaf>\n    void dfs(const Enter\
    \ &enter, const Leave &leave, const Leaf &leaf, int k = 1) {\n        enter(k,\
    \ seg[k]);\n        if (k < sz) {\n            dfs(enter, leave, leaf, k << 1);\n\
    \            dfs(enter, leave, leaf, k << 1 | 1);\n        } else if (k - sz <\
    \ q) {\n            leaf(k - sz);\n        }\n        leave(k, seg[k]);\n    }\n\
    \n    template <class F>\n    void run(const F &f) {\n        dfs(\n         \
    \   [&](int, const vector<pair<int, int>> &edges) {\n                for (auto\
    \ &&[u, v] : edges) uf.unite(u, v);\n            },\n            [&](int, const\
    \ vector<pair<int, int>> &edges) {\n                for (int i = 0; i < (int)edges.size();\
    \ ++i) uf.undo();\n            },\n            [&](int t) {\n                if\
    \ constexpr (is_invocable_v<F, int, UndoableUnionFind &>) {\n                \
    \    f(t, uf);\n                } else {\n                    f(t);\n        \
    \        }\n            }\n        );\n    }\n};\n\n/**\n * @brief Offline Dynamic\
    \ Connectivity\n */\n"
  code: "using namespace std;\n\n#include \"../datastructure/undoableunionfind.cpp\"\
    \n\nstruct OfflineDynamicConnectivity {\n    int n, q, sz;\n    UndoableUnionFind\
    \ uf;\n    vector<vector<pair<int, int>>> seg;\n    vector<pair<pair<int, int>,\
    \ pair<int, int>>> pend;\n    map<pair<int, int>, int> cnt, appear;\n\n    explicit\
    \ OfflineDynamicConnectivity(int n, int q) : n(n), q(q), uf(n) {\n        sz =\
    \ 1;\n        while (sz < q) sz <<= 1;\n        seg.resize(2 * sz);\n    }\n\n\
    \    void add_segment(int l, int r, const pair<int, int> &e) {\n        for (l\
    \ += sz, r += sz; l < r; l >>= 1, r >>= 1) {\n            if (l & 1) seg[l++].push_back(e);\n\
    \            if (r & 1) seg[--r].push_back(e);\n        }\n    }\n\n    void insert(int\
    \ t, int a, int b) {\n        auto e = minmax(a, b);\n        if (cnt[e]++ ==\
    \ 0) appear[e] = t;\n    }\n\n    void erase(int t, int a, int b) {\n        auto\
    \ e = minmax(a, b);\n        if (--cnt[e] == 0) {\n            pend.emplace_back(make_pair(appear[e],\
    \ t), e);\n            appear.erase(e);\n        }\n    }\n\n    void build()\
    \ {\n        for (auto &&[e, c] : cnt) {\n            if (!c) continue;\n    \
    \        pend.emplace_back(make_pair(appear[e], q), e);\n        }\n        for\
    \ (auto &&[range, e] : pend) add_segment(range.first, range.second, e);\n    }\n\
    \n    template <class Enter, class Leave, class Leaf>\n    void dfs(const Enter\
    \ &enter, const Leave &leave, const Leaf &leaf, int k = 1) {\n        enter(k,\
    \ seg[k]);\n        if (k < sz) {\n            dfs(enter, leave, leaf, k << 1);\n\
    \            dfs(enter, leave, leaf, k << 1 | 1);\n        } else if (k - sz <\
    \ q) {\n            leaf(k - sz);\n        }\n        leave(k, seg[k]);\n    }\n\
    \n    template <class F>\n    void run(const F &f) {\n        dfs(\n         \
    \   [&](int, const vector<pair<int, int>> &edges) {\n                for (auto\
    \ &&[u, v] : edges) uf.unite(u, v);\n            },\n            [&](int, const\
    \ vector<pair<int, int>> &edges) {\n                for (int i = 0; i < (int)edges.size();\
    \ ++i) uf.undo();\n            },\n            [&](int t) {\n                if\
    \ constexpr (is_invocable_v<F, int, UndoableUnionFind &>) {\n                \
    \    f(t, uf);\n                } else {\n                    f(t);\n        \
    \        }\n            }\n        );\n    }\n};\n\n/**\n * @brief Offline Dynamic\
    \ Connectivity\n */\n"
  dependsOn:
  - datastructure/undoableunionfind.cpp
  isVerificationFile: false
  path: graph/offlinedynamicconnectivity.cpp
  requiredBy: []
  timestamp: '2026-03-23 22:54:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_dynamic_graph_vertex_add_component_sum_offlinedynamicconnectivity.test.cpp
date: 2020-02-26
documentation_of: graph/offlinedynamicconnectivity.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "Dynamic Connectivity (\u30AA\u30D5\u30E9\u30A4\u30F3)"
---

## 説明
辺の追加・削除と、その時点の連結成分に関する問い合わせをオフラインで処理する。
各辺の生存区間を時間セグメント木に乗せ、DFS 中の状態を rollback 可能なデータ構造で持つ。
辺の登録全体は $O(q \log q)$、DFS 中の各操作は使う rollback 構造に依存する。

## できること
- `OfflineDynamicConnectivity dc(n, q)`
  頂点数 `n`、クエリ数 `q` の時間セグメント木を作る
- `void insert(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を追加する
- `void erase(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を削除する
- `void build()`
  登録済みの追加・削除から各辺の生存区間を構築する
- `void run(F f)`
  内部の `UndoableUnionFind` を使って DFS し、各時刻で `f(t)` または `f(t, uf)` を呼ぶ
- `void dfs(Enter enter, Leave leave, Leaf leaf)`
  時間セグメント木を直接 DFS する。`enter(k, seg[k])` でノード進入、`leave(k, seg[k])` で離脱、`leaf(t)` で時刻 `t` を処理する

## 使い方
単に連結判定だけをしたいなら `insert` / `erase` を全て登録して `build()` し、`run` で葉を処理する。

```cpp
OfflineDynamicConnectivity dc(n, q);
for (int t = 0; t < q; ++t) {
    if (add_query) dc.insert(t, u, v);
    if (erase_query) dc.erase(t, u, v);
}
dc.build();
dc.run([&](int t, UndoableUnionFind &uf) {
    answer[t] = uf.same(s[t], target[t]);
});
```

`dfs` は辺以外の rollback 付き状態も一緒に載せたいときに使う。
たとえば頂点加算や成分和のように、別の時間セグメント木を同じ DFS で重ねて処理できる。
