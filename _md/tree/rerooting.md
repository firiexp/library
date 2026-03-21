---
title: ReRooting(全方位木DP)
documentation_of: //tree/rerooting.cpp
date: 2026-03-12
category: 木
tags: 木
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
