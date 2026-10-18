---
title: HL分解(HL Decomposition)
documentation_of: //tree/hld.cpp
date: 2019-10-10
category: 木
tags: 木
---

## 説明
根つき木を Euler Tour 順の連続区間へ写し、パスや部分木を少数個の区間に分解する。
パスクエリ・パス更新は $O(log^2 N)$、部分木クエリは $O(f(N))$ で扱える。

## できること
- `HeavyLightDecomposition hld(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(vector<int> roots = {0})`
  前処理をする。森にも対応する
- `int lca(int u, int v)`
  最近共通祖先を返す
- `int parent(int v)`
  親を返す。根なら `-1`
- `int ancestor(int v, int k)`
  `k` 個上の祖先を返す。存在しなければ `-1`
- `int distance(int u, int v)`
  木上距離を返す
- `pair<int, int> subtree(int v, bool edge = false)`
  部分木に対応する半開区間 `[l, r)` を返す
- `void rerooted_subtree(int v, int root, F f) const`
  `root` を根とした場合の `v` の部分木に対応する区間へ `f(l, r)` を呼ぶ。空でない半開区間を `id` の昇順で高々2つ渡す。区間の取得は $O(\log N)$ 時間、$O(1)$ 作業領域
- `int rerooted_lca(int u, int v, int root) const`
  `root` を根とした場合の `u, v` の最近共通祖先を $O(\log N)$ 時間、$O(1)$ 作業領域で返す
- `void path(int u, int v, F f, bool edge = false)`
  パスを被覆する各区間へ `f(l, r)` を呼ぶ
- `void path_ordered(int u, int v, F f, bool edge = false) const`
  `u -> v` の順に `f(l, r, reversed)` を呼ぶ。空でない半開区間を渡し、`reversed = true` なら区間内を `r-1 -> l`、それ以外は `l -> r-1` の順に進む
- `T path_query(int u, int v, T e, Q q, F f, bool edge = false)`
  可換向けパスクエリ
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f, bool edge = false)`
  非可換向け順序付きパスクエリ
- `void apply_subtree(int v, F f, bool edge = false)`
  部分木区間へ `f(l, r)` を呼ぶ
- `subtree_query(int v, Q q, bool edge = false)`
  `v` の部分木クエリ。戻り値の型は `q` から推論する

## 使い方
`id[v]` を頂点 `v` の 1 次元位置としてセグ木や BIT に載せる。
部分木は `subtree(v)` の区間 1 本で取れる。
パスは `path` / `path_ordered` / `path_query` / `path_query_ordered` を使う。
両端点は同じ連結成分に属することを前提とする。

`rerooted_subtree` と `rerooted_lca` は、問い合わせごとに根を指定できる。
前処理時の根や `id` は変更されない。引数の頂点は同じ連結成分に属することを前提とする。
`rerooted_subtree` が扱うのは頂点集合で、森ではその成分内の区間だけを渡す。

```cpp
HeavyLightDecomposition hld(n);
hld.add_edge(u, v);
hld.build();

auto [l, r] = hld.subtree(v);
auto sub = seg.query(l, r);

auto ans = hld.path_query_ordered(a, b, Monoid::e(), ql, qr, Monoid::f, false);
```

`path_ordered` で先頭から等差数列を加算する例を示す。`values` は `id` 順に並べる。

```cpp
long long offset = 0;
hld.path_ordered(u, v, [&](int l, int r, bool reversed) {
    for (int i = l; i < r; ++i) {
        long long k = offset + (reversed ? r - 1 - i : i - l);
        values[i] += first + step * k;
    }
    offset += r - l;
});
```

文字列結合も同様に、区間を指定された向きに読み、callback の呼び出し順に連結する。

## 実装上の補足
`edge = true` にすると、LCA 側の頂点を除いた辺クエリ区間になる。
`path_query_ordered` は `u -> v` の向きを保つ。
`path_ordered` の区間数と列挙時間は $O(\log N)$。callback の処理時間は含まない。
後半の区間をスタック領域の固定長配列に保存し、逆順に取り出す。light edge の数は `int` のビット数未満なので、その幅を配列の上限とし、heap 確保は行わない。
頂点モードの `u = v` は1要素、辺モードは空パスとなり callback を呼ばない。
前処理は $O(N)$ 時間・領域で、再帰を使わない。森では各連結成分の根を `roots` に1つずつ渡す。
