---
title: HL分解(辺クエリ)
documentation_of: //tree/hld_edge.cpp
---

## 説明
辺を子頂点側の位置に載せる重軽分解である。
根の位置には辺がないので、`edge_index(root)` は `-1` を返す。

## できること
頂点数を $N$ とする。区間を渡す API の計算量には callback の処理を含めない。
集約 API は区間集約 `q`・`ql`・`qr` が $O(\log N)$、結合演算 `f` が $O(1)$ の場合を示す。

- `HeavyLightDecompositionEdge hld(n)`
  頂点数 `n` の木を作る。$O(N)$
- `HeavyLightDecompositionEdge hld(g)`
  隣接リスト `const vector<vector<int>>& g` から木を作る。$O(N)$
- `void add_edge(int u, int v)`
  木辺を張る。償却 $O(1)$
- `void build(vector<int> roots = {0})`
  前処理をする。森では各成分の根を `roots` に1つずつ指定する。時間・領域 $O(N)$
- `int lca(int u, int v) const`
  `u` と `v` の最近共通祖先を返す。$O(\log N)$
- `int parent(int v) const`
  `v` の親を返す。根なら `-1`。$O(1)$
- `int ancestor(int v, int k) const`
  `v` から根へ `k` 辺進んだ頂点を返す。存在しない場合は `-1`。$O(\log N)$
- `int distance(int u, int v) const`
  `u` と `v` の間の辺数を返す。$O(\log N)$
- `int jump(int u, int v, int k) const`
  `u` から `v` へ `k` 辺進んだ頂点を返す。`u` と `v` が別の木に属する場合、または `k` が負かパスの辺数を超える場合は `-1`。$O(\log N)$
- `int edge_index(int v) const`
  `parent(v) - v` の辺が載る位置を返す。根なら `-1`。$O(1)$
- `pair<int, int> subtree(int v) const`
  部分木の辺集合に対応する半開区間 `[l, r)` を返す。$O(1)$
- `void path(int u, int v, F f) const`
  `u - v` パス上の辺を被覆する $O(\log N)$ 個の区間へ `f(l, r)` を呼ぶ。$O(\log N)$
- `void path_ordered(int u, int v, F f) const`
  `u -> v` の順に、辺を被覆する $O(\log N)$ 個の空でない半開区間 `[l, r)` とその向きを `f` に渡す。$O(\log N)$
- `T path_query(int u, int v, T e, Q q, F f) const`
  パス上の辺の値を `q` で集約し、`f` で結合して返す。結合は可換とする。$O(\log^2 N)$
- `T path_query_ordered(int u, int v, T e, QL ql, QR qr, F f) const`
  `u -> v` の順に `ql`・`qr` の辺の区間集約を `f` で結合して返す。$O(\log^2 N)$
- `void apply_subtree(int v, F f) const`
  部分木の辺区間へ `f(l, r)` を1回呼ぶ。$O(1)$
- `subtree_query(int v, Q q) const`
  `v` の部分木の辺クエリ。返り値の型は `q` から推論する。$O(\log N)$

## 使い方
木を構成して `build()` を呼んだあと、各辺の値を子頂点側に置く。
`parent(v) - v` の辺を更新したいときは `edge_index(v)` を使う。
パス順序付きの集約には `path_query_ordered`、区間ごとの処理には `path_ordered` を使う。
`lca`・`distance` およびパス操作は両端点が同じ連結成分に属することを前提とする。
集約の `e` は単位元、`f(a, b)` は結合演算とする。
`q(l, r)` と `ql(l, r)` は区間 `[l, r)` を添字の昇順、`qr(l, r)` は降順に集約する。

`path_ordered` の `f` は `int l, int r, bool reversed` を引数に取る関数として定義する。
`reversed` は HLD が区間ごとに決めて第3引数に渡す値で、`true` なら `r-1 -> l`、`false` なら `l -> r-1` の順に進む。

次は区間和を返す `seg.query(l, r)` と組み合わせる例。

```cpp
HeavyLightDecompositionEdge hld(n);
hld.add_edge(u, v);
hld.build();

int p = hld.edge_index(v);
seg.update(p, x);

auto ans = hld.path_query(a, b, 0LL,
    [&](int l, int r) { return seg.query(l, r); },
    [](long long x, long long y) { return x + y; });
```

## 実装上の補足
内部では `HeavyLightDecomposition` の `edge = true` を使っている。
`subtree(v)` は `v` 自身へ入る辺を含まないので、根の部分木では木全体の辺区間になる。
`path_ordered` は空区間を渡さないが、`path`・`path_query`・`path_query_ordered`・`apply_subtree`・`subtree_query` は空区間 `[l, l)` を渡しうる。
