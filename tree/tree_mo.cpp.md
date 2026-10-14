---
category: "\u6728"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: util/mo.cpp
    title: Mo's Algorithm
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_tree_mo.test.cpp
    title: test/yosupo_aplusb_tree_mo.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u6728\u4E0A\u30D1\u30B9\u306EMo"
    links: []
  bundledCode: "#line 1 \"tree/tree_mo.cpp\"\n\n\n\n#line 1 \"util/mo.cpp\"\n\n\n\n\
    struct Query {\n    static inline int bucket_size = 1;\n    static inline int\
    \ &B = bucket_size;\n    int l, r, no;\n    Query(int l, int r, int no) : l(l),\
    \ r(r), no(no) {}\n    Query() : l(0), r(0), no(0) {}\n    bool operator<(const\
    \ Query &a) const {\n        int ablock = this->l / bucket_size, bblock = a.l\
    \ / bucket_size;\n        if(ablock != bblock) return ablock < bblock;\n     \
    \   if(ablock & 1) return this->r < a.r;\n        else return this->r > a.r;\n\
    \    }\n};\n\ntemplate<class AddLeft, class AddRight, class EraseLeft, class EraseRight,\
    \ class Output>\nvoid mo_solve(int n, const vector<Query>& queries, AddLeft add_left,\
    \ AddRight add_right,\n              EraseLeft erase_left, EraseRight erase_right,\
    \ Output output, int bucket_size = 0) {\n    if (queries.empty()) return;\n  \
    \  if (bucket_size <= 0) bucket_size = max(1, (int)(n / sqrt((double)queries.size())));\n\
    \    vector<Query> qs = queries;\n    sort(qs.begin(), qs.end(), [&](const Query&\
    \ a, const Query& b) {\n        int ablock = a.l / bucket_size, bblock = b.l /\
    \ bucket_size;\n        if (ablock != bblock) return ablock < bblock;\n      \
    \  return ablock & 1 ? a.r < b.r : a.r > b.r;\n    });\n    int l = 0, r = 0;\n\
    \    for (const auto& q : qs) {\n        while (q.l < l) add_left(--l);\n    \
    \    while (r < q.r) add_right(r++);\n        while (l < q.l) erase_left(l++);\n\
    \        while (q.r < r) erase_right(--r);\n        output(q.no);\n    }\n}\n\n\
    \n\n/**\n * @brief Mo's Algorithm\n */\n#line 5 \"tree/tree_mo.cpp\"\n\ntemplate<class\
    \ Add, class Erase, class Output>\nvoid tree_mo_solve(const vector<vector<int>>\
    \ &g, const vector<pair<int, int>> &paths,\n                   Add add, Erase\
    \ erase, Output output, int root = 0) {\n    if (paths.empty()) return;\n    int\
    \ n = (int)g.size();\n    assert(0 <= root && root < n);\n    vector<int> tin(n),\
    \ parent(n, -1), tour, stack{root};\n    tour.reserve(2 * n - 1);\n    while (!stack.empty())\
    \ {\n        int v = stack.back();\n        stack.pop_back();\n        if (v <\
    \ 0) {\n            if (parent[~v] != -1) tour.push_back(parent[~v]);\n      \
    \  } else {\n            tin[v] = (int)tour.size();\n            tour.push_back(v);\n\
    \            stack.push_back(~v);\n            for (int i = (int)g[v].size() -\
    \ 1; i >= 0; --i) {\n                int u = g[v][i];\n                if (u !=\
    \ parent[v]) {\n                    parent[u] = v;\n                    stack.push_back(u);\n\
    \                }\n            }\n        }\n    }\n    vector<Query> queries;\n\
    \    queries.reserve(paths.size());\n    for (int i = 0; i < (int)paths.size();\
    \ ++i) {\n        auto [u, v] = paths[i];\n        assert(0 <= u && u < n && 0\
    \ <= v && v < n);\n        if (tin[u] > tin[v]) swap(u, v);\n        queries.emplace_back(tin[u],\
    \ tin[v], i);\n    }\n    vector<char> active(n);\n    auto move = [&](int from,\
    \ int to) {\n        if (active[to]) {\n            erase(from);\n           \
    \ active[from] = 0;\n        } else {\n            add(to);\n            active[to]\
    \ = 1;\n        }\n    };\n    auto forward = [&](int i) { move(tour[i], tour[i\
    \ + 1]); };\n    auto backward = [&](int i) { move(tour[i + 1], tour[i]); };\n\
    \    add(root);\n    active[root] = 1;\n    mo_solve((int)tour.size(), queries,\
    \ backward, forward, forward, backward, output);\n    for (int v = 0; v < n; ++v)\
    \ {\n        if (active[v]) erase(v);\n    }\n}\n\n\n\n/**\n * @brief \u6728\u4E0A\
    \u30D1\u30B9\u306EMo\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_TREE_TREE_MO_CPP\n#define FIRIEXP_LIBRARY_TREE_TREE_MO_CPP\n\
    \n#include \"../util/mo.cpp\"\n\ntemplate<class Add, class Erase, class Output>\n\
    void tree_mo_solve(const vector<vector<int>> &g, const vector<pair<int, int>>\
    \ &paths,\n                   Add add, Erase erase, Output output, int root =\
    \ 0) {\n    if (paths.empty()) return;\n    int n = (int)g.size();\n    assert(0\
    \ <= root && root < n);\n    vector<int> tin(n), parent(n, -1), tour, stack{root};\n\
    \    tour.reserve(2 * n - 1);\n    while (!stack.empty()) {\n        int v = stack.back();\n\
    \        stack.pop_back();\n        if (v < 0) {\n            if (parent[~v] !=\
    \ -1) tour.push_back(parent[~v]);\n        } else {\n            tin[v] = (int)tour.size();\n\
    \            tour.push_back(v);\n            stack.push_back(~v);\n          \
    \  for (int i = (int)g[v].size() - 1; i >= 0; --i) {\n                int u =\
    \ g[v][i];\n                if (u != parent[v]) {\n                    parent[u]\
    \ = v;\n                    stack.push_back(u);\n                }\n         \
    \   }\n        }\n    }\n    vector<Query> queries;\n    queries.reserve(paths.size());\n\
    \    for (int i = 0; i < (int)paths.size(); ++i) {\n        auto [u, v] = paths[i];\n\
    \        assert(0 <= u && u < n && 0 <= v && v < n);\n        if (tin[u] > tin[v])\
    \ swap(u, v);\n        queries.emplace_back(tin[u], tin[v], i);\n    }\n    vector<char>\
    \ active(n);\n    auto move = [&](int from, int to) {\n        if (active[to])\
    \ {\n            erase(from);\n            active[from] = 0;\n        } else {\n\
    \            add(to);\n            active[to] = 1;\n        }\n    };\n    auto\
    \ forward = [&](int i) { move(tour[i], tour[i + 1]); };\n    auto backward = [&](int\
    \ i) { move(tour[i + 1], tour[i]); };\n    add(root);\n    active[root] = 1;\n\
    \    mo_solve((int)tour.size(), queries, backward, forward, forward, backward,\
    \ output);\n    for (int v = 0; v < n; ++v) {\n        if (active[v]) erase(v);\n\
    \    }\n}\n\n#endif\n\n/**\n * @brief \u6728\u4E0A\u30D1\u30B9\u306EMo\n */\n"
  dependsOn:
  - util/mo.cpp
  isVerificationFile: false
  path: tree/tree_mo.cpp
  requiredBy: []
  timestamp: '2026-10-15 00:51:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_tree_mo.test.cpp
date: 2026-10-14
documentation_of: tree/tree_mo.cpp
layout: document
tags: "\u6728"
title: "\u6728\u4E0A\u30D1\u30B9\u306EMo"
---

## 説明
静的な連結木のパスに対するクエリを Mo でまとめて処理する。
頂点1個の追加・削除で答えを更新できる、順序に依存しない集計を扱う。色の種類数などに使える。

## できること
- `tree_mo_solve(g, paths, add, erase, output, root=0)`
  `paths` の各 `(u,v)` について、パス上の全頂点を1回ずつ有効にして `output(id)` を呼ぶ。`id` は入力クエリ番号
- `add(v)` / `erase(v)`
  元の頂点番号 `v` を追加・削除する。状態は空集合から始め、終了時も空集合に戻る

## 使い方
`g` は `vector<vector<int>>` の無向木、`paths` は `vector<pair<int,int>>` とする。
root と各端点は有効な頂点番号を指定する。入力の木とクエリ列は変更しない。
Euler Tour とバケット幅は内部で管理する。
同一端点や祖先関係のあるパスもそのまま渡せる。空クエリ列では callback を呼ばず、空グラフでもよい。

```cpp
tree_mo_solve(g, paths,
    [&](int v) { if (frequency[color[v]]++ == 0) ++distinct; },
    [&](int v) { if (--frequency[color[v]] == 0) --distinct; },
    [&](int id) { answer[id] = distinct; });
```

`output` は現在の集計状態を変更しない。呼び出し順はクエリ順とは限らない。

## 実装上の補足
辺を往復する長さ $2N-1$ の Euler Tour を作り、パスの両端を隣接頂点へ動かす。
移動先が現在のパス内なら元の端点を削除し、パス外なら移動先を追加する。
これによりパス上の頂点集合を保てる。木の走査は反復処理なので、深い木でも stack 設定の変更は不要。

準備は $O(N+Q)$、ソートは $O(Q\log Q)$、領域は $O(N+Q)$。
バケット幅は $B=\max(1,\lfloor (2N-1)/\sqrt Q\rfloor)$ を内部で選ぶ。
頂点の追加・削除は合計 $O(QB+N^2/B+N)$ 回、`output` は $Q$ 回呼ぶ。
パスの向きに沿った順序付き集約には使えない。
