---
category: "\u6728"
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/aoj_grl_5_a_rerooting.test.cpp
    title: test/aoj_grl_5_a_rerooting.test.cpp
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "ReRooting(\u5168\u65B9\u4F4D\u6728DP)"
    links: []
  bundledCode: "#line 1 \"tree/rerooting.cpp\"\nusing namespace std;\n\ntemplate <typename\
    \ M>\nclass ReRooting {\npublic:\n    using T = typename M::T;\n    using U =\
    \ typename M::U;\n\n    struct Node {\n        int to, rev;\n        U val;\n\n\
    \        Node(int to, int rev, U val) : to(to), rev(rev), val(val) {}\n    };\n\
    \n    int n;\n    vector<vector<Node>> G;\n    vector<vector<T>> dpl, dpr;\n \
    \   vector<int> l, r;\n\n    explicit ReRooting(int n) : n(n), G(n), dpl(n), dpr(n),\
    \ l(n), r(n) {}\n\n    void add_edge(int u, int v, const U &x) {\n        G[u].emplace_back(v,\
    \ (int)G[v].size(), x);\n        G[v].emplace_back(u, (int)G[u].size() - 1, x);\n\
    \    }\n\n    void add_edge(int u, int v, const U &x, const U &y) {\n        G[u].emplace_back(v,\
    \ (int)G[v].size(), x);\n        G[v].emplace_back(u, (int)G[u].size() - 1, y);\n\
    \    }\n\n    T dfs(int i, int par) {\n        while (l[i] != par && l[i] < (int)G[i].size())\
    \ {\n            auto &e = G[i][l[i]];\n            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]],\
    \ M::g(dfs(e.to, e.rev), e.val));\n            ++l[i];\n        }\n        while\
    \ (r[i] != par && r[i] >= 0) {\n            auto &e = G[i][r[i]];\n          \
    \  dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));\n   \
    \         --r[i];\n        }\n        if (par < 0) return dpr[i].front();\n  \
    \      return M::f(dpl[i][par], dpr[i][par + 1]);\n    }\n\n    vector<T> solve()\
    \ {\n        for (int i = 0; i < n; ++i) {\n            dpl[i].assign(G[i].size()\
    \ + 1, M::e());\n            dpr[i].assign(G[i].size() + 1, M::e());\n       \
    \     l[i] = 0;\n            r[i] = (int)G[i].size() - 1;\n        }\n       \
    \ vector<T> ans(n);\n        for (int i = 0; i < n; ++i) ans[i] = dfs(i, -1);\n\
    \        return ans;\n    }\n};\n\n/**\n * @brief ReRooting(\u5168\u65B9\u4F4D\
    \u6728DP)\n */\n"
  code: "using namespace std;\n\ntemplate <typename M>\nclass ReRooting {\npublic:\n\
    \    using T = typename M::T;\n    using U = typename M::U;\n\n    struct Node\
    \ {\n        int to, rev;\n        U val;\n\n        Node(int to, int rev, U val)\
    \ : to(to), rev(rev), val(val) {}\n    };\n\n    int n;\n    vector<vector<Node>>\
    \ G;\n    vector<vector<T>> dpl, dpr;\n    vector<int> l, r;\n\n    explicit ReRooting(int\
    \ n) : n(n), G(n), dpl(n), dpr(n), l(n), r(n) {}\n\n    void add_edge(int u, int\
    \ v, const U &x) {\n        G[u].emplace_back(v, (int)G[v].size(), x);\n     \
    \   G[v].emplace_back(u, (int)G[u].size() - 1, x);\n    }\n\n    void add_edge(int\
    \ u, int v, const U &x, const U &y) {\n        G[u].emplace_back(v, (int)G[v].size(),\
    \ x);\n        G[v].emplace_back(u, (int)G[u].size() - 1, y);\n    }\n\n    T\
    \ dfs(int i, int par) {\n        while (l[i] != par && l[i] < (int)G[i].size())\
    \ {\n            auto &e = G[i][l[i]];\n            dpl[i][l[i] + 1] = M::f(dpl[i][l[i]],\
    \ M::g(dfs(e.to, e.rev), e.val));\n            ++l[i];\n        }\n        while\
    \ (r[i] != par && r[i] >= 0) {\n            auto &e = G[i][r[i]];\n          \
    \  dpr[i][r[i]] = M::f(dpr[i][r[i] + 1], M::g(dfs(e.to, e.rev), e.val));\n   \
    \         --r[i];\n        }\n        if (par < 0) return dpr[i].front();\n  \
    \      return M::f(dpl[i][par], dpr[i][par + 1]);\n    }\n\n    vector<T> solve()\
    \ {\n        for (int i = 0; i < n; ++i) {\n            dpl[i].assign(G[i].size()\
    \ + 1, M::e());\n            dpr[i].assign(G[i].size() + 1, M::e());\n       \
    \     l[i] = 0;\n            r[i] = (int)G[i].size() - 1;\n        }\n       \
    \ vector<T> ans(n);\n        for (int i = 0; i < n; ++i) ans[i] = dfs(i, -1);\n\
    \        return ans;\n    }\n};\n\n/**\n * @brief ReRooting(\u5168\u65B9\u4F4D\
    \u6728DP)\n */\n"
  dependsOn: []
  isVerificationFile: false
  path: tree/rerooting.cpp
  requiredBy: []
  timestamp: '2026-03-12 00:49:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/aoj_grl_5_a_rerooting.test.cpp
date: 2026-03-12
documentation_of: tree/rerooting.cpp
layout: document
tags: "\u6728"
title: "ReRooting(\u5168\u65B9\u4F4D\u6728DP)"
---

## 説明
木上の各頂点を根とみなした DP 値をまとめて求める。
辺ごとの遷移 `g` と、部分木結果のマージ `f` を与えると、全頂点の答えを計算する。

## できること
- `ReRooting<M> rr(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v, const U& x)`
  無向辺を追加する。両方向に同じ辺データ `x` を持たせる
- `void add_edge(int u, int v, const U& x, const U& y)`
  無向辺を追加する。`u -> v` に `x`、`v -> u` に `y` を持たせる
- `vector<T> solve()`
  各頂点を根にした DP 値を返す

## 使い方
`M` は次を持てばよい。

```cpp
struct Monoid {
    using T = ...;
    using U = ...;
    static T f(T a, T b);
    static T g(T child, U edge);
    static T e();
};
```

`f` は兄弟部分木のマージ、`g` は子側の結果を親へ渡す変換である。

```cpp
struct M {
    using T = long long;
    using U = long long;
    static T f(T a, T b) { return max(a, b); }
    static T g(T a, U w) { return a + w; }
    static T e() { return 0; }
};

ReRooting<M> rr(n);
rr.add_edge(u, v, w);
auto dp = rr.solve();
```

## 実装上の補足
各有向辺に対する DP を左右累積で 1 回ずつ計算するので全体は $O(N)$。
再帰実装なので、深い木で使うときはスタック深さに注意する。
