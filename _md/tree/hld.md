---
title: HL分解(HL Decomposition)
documentation_of: //tree/hld.cpp
---

## 説明
根つき木を Euler Tour 順の連続区間へ写し、パスや部分木を少数個の区間に分解する。

## できること
頂点数を $N$ とする。区間を渡す API の計算量には callback の処理を含めない。
集約 API は区間集約 `q`・`ql`・`qr` が $O(\log N)$、結合演算 `f` が $O(1)$ の場合を示す。

- `HeavyLightDecomposition hld(n)`
  頂点数 `n` の木を作る。$O(N)$
- `HeavyLightDecomposition hld(g)`
  隣接リスト `const vector<vector<int>>& g` から木を作る。$O(N)$
- `void add_edge(int u, int v)`
  木辺を張る。償却 $O(1)$
- `void build(vector<int> roots = {0})`
  前処理をする。森では各成分の根を `roots` に1つずつ指定する。時間・領域 $O(N)$
- `int lca(int u, int v) const`
  最近共通祖先を返す。$O(\log N)$
- `int parent(int v) const`
  親を返す。根なら `-1`。$O(1)$
- `int ancestor(int v, int k) const`
  `v` から根へ `k` 辺進んだ頂点を返す。存在しない場合は `-1`。$O(\log N)$
- `int distance(int u, int v) const`
  木上距離を返す。$O(\log N)$
- `int jump(int u, int v, int k) const`
  `u` から `v` へ `k` 辺進んだ頂点を返す。存在しない場合は `-1`。$O(\log N)$
- `pair<int, int> path_intersection(int a, int b, int c, int d) const`
  頂点パス `a -> b` と `c -> d` の共通部分を、`a -> b` の順に端点の組で返す。空、または4頂点が同じ木に属さなければ `{-1, -1}`。1頂点だけなら両端点が同じになる。$O(\log N)$
- `pair<int, int> subtree(int v, bool edge = false) const`
  部分木に対応する半開区間 `[l, r)` を返す。$O(1)$
- `void rerooted_subtree(int v, int root, F f) const`
  `root` を根とした場合の `v` の部分木に対応する区間へ `f(l, r)` を呼ぶ。空でない半開区間を `id` の昇順で高々2つ渡す。$O(\log N)$
- `int rerooted_lca(int u, int v, int root) const`
  `root` を根とした場合の `u`, `v` の最近共通祖先を返す。$O(\log N)$
- `void path(int u, int v, F f, bool edge = false) const`
  パスを被覆する $O(\log N)$ 個の区間へ `f(l, r)` を呼ぶ。$O(\log N)$
- `void path_ordered(int u, int v, F f, bool edge = false) const`
  `u -> v` の順に、パスを被覆する $O(\log N)$ 個の空でない半開区間 `[l, r)` とその向きを `f` に渡す。$O(\log N)$
- `T path_query(int u, int v, T e, Q q, F f, bool edge = false) const`
  パス上の値を `q` で集約し、`f` で結合して返す。結合は可換とする。$O(\log^2 N)$
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f, bool edge = false) const`
  `u -> v` の順に `ql`・`qr` の区間集約を `f` で結合して返す。$O(\log^2 N)$
- `void apply_subtree(int v, F f, bool edge = false) const`
  部分木区間へ `f(l, r)` を1回呼ぶ。$O(1)$
- `subtree_query(int v, Q q, bool edge = false) const`
  `v` の部分木クエリ。返り値の型は `q` から推論する。$O(\log N)$

## 使い方
木を構成して `build()` を呼んだあと、`id[v]` を頂点 `v` の 1 次元位置としてセグメント木や BIT に載せる。
部分木は `subtree(v)` の区間 1 本で取れる。
パスは `path` / `path_ordered` / `path_query` / `path_query_ordered` を使う。
`lca`・`distance` およびパス操作は両端点が同じ連結成分に属することを前提とする。
集約の `e` は単位元、`f(a, b)` は結合演算とする。
`q(l, r)` と `ql(l, r)` は区間 `[l, r)` を添字の昇順、`qr(l, r)` は降順に集約する。

`path_ordered` の `f` は `int l, int r, bool reversed` を引数に取る関数として定義する。
`reversed` は HLD が区間ごとに決めて第3引数に渡す値で、`true` なら `r-1 -> l`、`false` なら `l -> r-1` の順に進む。

`rerooted_subtree` と `rerooted_lca` はクエリごとに根を指定できる。
前処理時の根や `id` は変更されない。引数の頂点は同じ連結成分に属することを前提とする。
`rerooted_subtree` が扱うのは頂点集合で、森ではその成分内の区間だけを渡す。

次は区間和を返す `seg.query(l, r)` と組み合わせる例。

```cpp
HeavyLightDecomposition hld(n);
hld.add_edge(u, v);
hld.build();

auto [l, r] = hld.subtree(v);
auto sub = seg.query(l, r);

auto ans = hld.path_query(a, b, 0LL,
    [&](int l, int r) { return seg.query(l, r); },
    [](long long x, long long y) { return x + y; });
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

2本のパスの共通部分も既存のパス API に渡せる。
共通する**頂点集合**を扱う。
端点だけの接触も1頂点のパスとして返る。

```cpp
auto [x, y] = hld.path_intersection(a, b, c, d);
if (x != -1) {
    hld.path(x, y, [&](int l, int r) { seg.update(l, r, value); });
}
```

## 実装上の補足
`edge = true` にすると、LCA 側の頂点を除いた辺クエリ区間になる。
`path_ordered` は空区間を渡さず、`edge = true` で `u == v` のときは callback を呼ばないが、`path`・`path_query`・`path_query_ordered`・`apply_subtree`・`subtree_query` は `edge = true` で空区間 `[l, l)` を渡しうる。
前処理は非再帰で行い、`path_ordered` は後半の区間を固定長配列に積むため動的確保を行わない。
