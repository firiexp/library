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
頂点数を $N$ とし、`f` と `g` の計算は $O(1)$ とする。

- `ReRooting<M> rr(n)`
  頂点数 `n` の木を作る。$O(N)$
- `void add_edge(int u, int v, const U& x)`
  無向辺を追加する。両方向に同じ辺データ `x` を持たせる。償却 $O(1)$
- `void add_edge(int u, int v, const U& x, const U& y)`
  無向辺を追加する。`u -> v` に `x`、`v -> u` に `y` を持たせる。償却 $O(1)$
- `vector<T> solve()`
  各頂点を根にした DP 値を返す。呼ぶたびに現在の辺データから再計算する。時間・領域 $O(N)$

## 使い方
`M` に頂点の DP 値の型 `T`、辺データの型 `U`、演算 `f`・`g`・`e` を定義する。
`f` は兄弟部分木のマージ、`g` は子側の結果を親へ渡す変換である。
`f` は結合則を満たし、`e()` はその単位元とする。マージは各頂点の隣接リスト `G[v]` の順に行う。
次は非負の辺重みを持つ木で、各頂点から最も遠い頂点までの距離を求める例。

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
親から子への順序を作り、逆順で子側の DP、順方向で親側の DP と全根の答えを計算する。
各方向の辺に対する `g` は1回ずつ評価し、左右累積で隣接リスト順を保ってマージする。
左右累積はそれぞれ 1 本の連続配列に保持し、頂点ごとの確保を避ける。空でない木では各配列の要素数は $3N-2$、作業領域全体は $O(N)$。
内部配列 `dpl` / `dpr` は `vector<T>` で、頂点 `v` の累積値は `offset[v]` から始まる。
走査順と親辺の番号も配列に保持する。再帰を使わないため、深い木でも入力サイズに応じたネイティブスタックの調整は不要。
