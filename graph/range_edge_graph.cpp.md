---
category: "\u30B0\u30E9\u30D5"
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/edge.cpp
    title: graph/edge.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/yosupo_aplusb_range_edge_graph.test.cpp
    title: test/yosupo_aplusb_range_edge_graph.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u533A\u9593\u3078\u306E\u8FBA\u3092\u5727\u7E2E\u3059\u308B\u30B0\
      \u30E9\u30D5"
    links: []
  bundledCode: "#line 1 \"graph/range_edge_graph.cpp\"\n\n\n\n#line 1 \"graph/edge.cpp\"\
    \n\n\n\ntemplate <typename T>\nstruct edge {\n    int from, to;\n    T cost;\n\
    \n    edge(int to, T cost) : from(-1), to(to), cost(cost) {}\n    edge(int from,\
    \ int to, T cost) : from(from), to(to), cost(cost) {}\n\n    explicit operator\
    \ int() const { return to; }\n};\n\n\n#line 5 \"graph/range_edge_graph.cpp\"\n\
    \ntemplate<class T>\nclass RangeEdgeGraph {\n    int n;\n    vector<vector<edge<T>>>\
    \ g;\n\n    int down(int v) const { return v >= n ? v - n : n + v - 1; }\n   \
    \ int up(int v) const { return v >= n ? v - n : 2 * n + v - 2; }\n\n    void connect(int\
    \ l, int r, int v, const T &w, bool to_range) {\n        auto add = [&](int node)\
    \ {\n            int from = to_range ? v : up(node), to = to_range ? down(node)\
    \ : v;\n            g[from].emplace_back(from, to, w);\n        };\n        for\
    \ (l += n, r += n; l < r; l /= 2, r /= 2) {\n            if (l & 1) add(l++);\n\
    \            if (r & 1) add(--r);\n        }\n    }\n\n    void check_range(int\
    \ l, int r) const { assert(0 <= l && l <= r && r <= n); }\n\npublic:\n    explicit\
    \ RangeEdgeGraph(int n) : n(n) {\n        assert(0 <= n && n <= INT_MAX / 3);\n\
    \        g.resize(n == 0 ? 0 : 3 * n - 2);\n        for (int v = 1; v < n; ++v)\
    \ {\n            for (int child : {2 * v, 2 * v + 1}) {\n                g[down(v)].emplace_back(down(v),\
    \ down(child), T(0));\n                g[up(child)].emplace_back(up(child), up(v),\
    \ T(0));\n            }\n        }\n    }\n\n    void add_edge(int u, int v, const\
    \ T &w) {\n        assert(0 <= u && u < n && 0 <= v && v < n);\n        g[u].emplace_back(u,\
    \ v, w);\n    }\n\n    void add_to_range(int u, int l, int r, const T &w) {\n\
    \        assert(0 <= u && u < n);\n        check_range(l, r);\n        connect(l,\
    \ r, u, w, true);\n    }\n\n    void add_from_range(int l, int r, int v, const\
    \ T &w) {\n        check_range(l, r);\n        assert(0 <= v && v < n);\n    \
    \    connect(l, r, v, w, false);\n    }\n\n    void add_range_to_range(int l1,\
    \ int r1, int l2, int r2, const T &w) {\n        check_range(l1, r1);\n      \
    \  check_range(l2, r2);\n        if (l1 == r1 || l2 == r2) return;\n        assert(g.size()\
    \ < (size_t)INT_MAX);\n        int v = (int)g.size();\n        g.emplace_back();\n\
    \        connect(l1, r1, v, T(0), false);\n        connect(l2, r2, v, w, true);\n\
    \    }\n\n    const vector<vector<edge<T>>> &graph() const { return g; }\n};\n\
    \n\n\n/**\n * @brief \u533A\u9593\u3078\u306E\u8FBA\u3092\u5727\u7E2E\u3059\u308B\
    \u30B0\u30E9\u30D5\n */\n"
  code: "#ifndef FIRIEXP_LIBRARY_GRAPH_RANGE_EDGE_GRAPH_CPP\n#define FIRIEXP_LIBRARY_GRAPH_RANGE_EDGE_GRAPH_CPP\n\
    \n#include \"edge.cpp\"\n\ntemplate<class T>\nclass RangeEdgeGraph {\n    int\
    \ n;\n    vector<vector<edge<T>>> g;\n\n    int down(int v) const { return v >=\
    \ n ? v - n : n + v - 1; }\n    int up(int v) const { return v >= n ? v - n :\
    \ 2 * n + v - 2; }\n\n    void connect(int l, int r, int v, const T &w, bool to_range)\
    \ {\n        auto add = [&](int node) {\n            int from = to_range ? v :\
    \ up(node), to = to_range ? down(node) : v;\n            g[from].emplace_back(from,\
    \ to, w);\n        };\n        for (l += n, r += n; l < r; l /= 2, r /= 2) {\n\
    \            if (l & 1) add(l++);\n            if (r & 1) add(--r);\n        }\n\
    \    }\n\n    void check_range(int l, int r) const { assert(0 <= l && l <= r &&\
    \ r <= n); }\n\npublic:\n    explicit RangeEdgeGraph(int n) : n(n) {\n       \
    \ assert(0 <= n && n <= INT_MAX / 3);\n        g.resize(n == 0 ? 0 : 3 * n - 2);\n\
    \        for (int v = 1; v < n; ++v) {\n            for (int child : {2 * v, 2\
    \ * v + 1}) {\n                g[down(v)].emplace_back(down(v), down(child), T(0));\n\
    \                g[up(child)].emplace_back(up(child), up(v), T(0));\n        \
    \    }\n        }\n    }\n\n    void add_edge(int u, int v, const T &w) {\n  \
    \      assert(0 <= u && u < n && 0 <= v && v < n);\n        g[u].emplace_back(u,\
    \ v, w);\n    }\n\n    void add_to_range(int u, int l, int r, const T &w) {\n\
    \        assert(0 <= u && u < n);\n        check_range(l, r);\n        connect(l,\
    \ r, u, w, true);\n    }\n\n    void add_from_range(int l, int r, int v, const\
    \ T &w) {\n        check_range(l, r);\n        assert(0 <= v && v < n);\n    \
    \    connect(l, r, v, w, false);\n    }\n\n    void add_range_to_range(int l1,\
    \ int r1, int l2, int r2, const T &w) {\n        check_range(l1, r1);\n      \
    \  check_range(l2, r2);\n        if (l1 == r1 || l2 == r2) return;\n        assert(g.size()\
    \ < (size_t)INT_MAX);\n        int v = (int)g.size();\n        g.emplace_back();\n\
    \        connect(l1, r1, v, T(0), false);\n        connect(l2, r2, v, w, true);\n\
    \    }\n\n    const vector<vector<edge<T>>> &graph() const { return g; }\n};\n\
    \n#endif\n\n/**\n * @brief \u533A\u9593\u3078\u306E\u8FBA\u3092\u5727\u7E2E\u3059\
    \u308B\u30B0\u30E9\u30D5\n */\n"
  dependsOn:
  - graph/edge.cpp
  isVerificationFile: false
  path: graph/range_edge_graph.cpp
  requiredBy: []
  timestamp: '2026-10-14 23:14:26+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/yosupo_aplusb_range_edge_graph.test.cpp
date: 2026-10-14
documentation_of: graph/range_edge_graph.cpp
layout: document
tags: "\u30B0\u30E9\u30D5"
title: "\u533A\u9593\u3078\u306E\u8FBA\u3092\u5727\u7E2E\u3059\u308B\u30B0\u30E9\u30D5"
---

## 説明
頂点から区間、区間から頂点、区間から区間への有向辺を、補助頂点を使って圧縮する。
元の頂点番号 `0..n-1` を保ち、既存の最短路ライブラリに渡せる隣接リストを返す。
初期状態は $N>0$ のとき $3N-2$ 頂点、$4(N-1)$ 辺となる。
$Q$ 回の辺追加後は $O(N+Q)$ 頂点、$O(N+Q\log N)$ 辺となる。

## できること
- `RangeEdgeGraph<T> rg(n)`
  元頂点数 `n` のグラフを作る
- `rg.add_edge(u, v, w)`
  重み `w` の有向辺 `u -> v` を追加する
- `rg.add_to_range(u, l, r, w)` / `rg.add_from_range(l, r, v, w)`
  頂点から区間内の全頂点、または区間内の全頂点から頂点へ同じ重みの辺を追加する
- `rg.add_range_to_range(l1, r1, l2, r2, w)`
  2区間の直積の全有向辺を重み `w` で追加する。補助頂点を1個追加する
- `rg.graph()`
  `const vector<vector<edge<T>>>&` を返す。補助頂点も含む

## 使い方
区間は `0 <= l <= r <= n` の半開区間とし、空区間の追加は何もしない。
`T` は重みと `T(0)` を表せる型を使う。重複辺、自己辺、重なる区間も扱う。
追加される全頂点の番号が `int` に収まり、グラフを確保できる範囲で使う。

```cpp
RangeEdgeGraph<long long> rg(n);
rg.add_to_range(0, l, r, 5);
rg.add_range_to_range(l1, r1, l2, r2, 7);
auto dist = dijkstra(0, rg.graph());
```

最短路計算の前提は選ぶアルゴリズムに従う。Dijkstra 法なら非負重みと、距離がその `INF<T>` 未満に収まることが必要となる。
結果の先頭 `n` 要素が元頂点への距離となる。別途 build や reserve は不要。

## 実装上の補足
上下2方向のセグメント木の葉を元頂点として共有する。区間から区間への追加には中継点を1個使う。
初期構築は $O(N)$、通常辺追加は償却 $O(1)$、区間追加は償却 $O(\log N)$。
最短路処理の計算量は、生成されたグラフの頂点数・辺数と使うアルゴリズムによる。
