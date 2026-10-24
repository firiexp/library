---
title: Link-Cut Tree
documentation_of: //tree/link_cut_tree.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
動的森に対して、辺の追加・削除、根の付け替え、パス上の集約を扱う。

## できること
頂点数を $N$ とし、モノイド演算は $O(1)$ とする。

- `LinkCutTree<M> lct(n)`
  頂点数 `n` の森を作る。$O(N)$
- `bool link(int u, int v)`
  `u` と `v` の間に辺を張る。同じ連結成分なら `false`。償却 $O(\log N)$
- `bool cut(int u, int v)`
  `u` - `v` 間の辺を削除する。存在しなければ `false`。償却 $O(\log N)$
- `void evert(int v)`
  `v` を根にする。償却 $O(\log N)$
- `bool connected(int u, int v)`
  同じ木にあるかを返す。償却 $O(\log N)$
- `int get_root(int v)`
  `v` が属する木の根を返す。償却 $O(\log N)$
- `int lca(int u, int v)`
  現在の根に対する LCA を返す。非連結なら `-1`。償却 $O(\log N)$
- `int parent(int v)`
  現在の根に対する親を返す。根なら `-1`。償却 $O(\log N)$
- `void set(int v, T x)`
  頂点 `v` の値を `x` にする。償却 $O(\log N)$
- `T get(int v) const`
  頂点 `v` の値を返す。$O(1)$
- `T fold(int u, int v)`
  パス `u -> v` 上の値を順番通りに集約する。両端点は連結とする。償却 $O(\log N)$
- `int dist(int u, int v)`
  パスの辺数を返す。両端点は連結とする。償却 $O(\log N)$
- `int jump(int u, int v, int k)`
  `u` から `v` へ `k` 辺進んだ頂点を返す。非連結の場合、または `k` が負かパス長を超える場合は `-1`。償却 $O(\log N)$

## 使い方
`LinkCutTree<M> lct(n);` を作り、`M` に `using T`、`static T f(T, T)`、`static T e()` を定義する。
頂点値は `set(v, x)` で更新し、`fold(u, v)` で `u` から `v` への順序付きパス集約を取る。
辺操作は `link(u, v)`、`cut(u, v)` を使う。
`jump(u, v, k)` は動的な辺変更の後でも呼べる。頂点番号は有効な範囲とする。
`k >= 0` のとき、失敗時も含めて `u` の木の根を `u` に変更する。`k < 0` では状態を変更しない。

頂点値の和を求めるモノイドは次のように定義する。

```cpp
struct SumMonoid {
    using T = long long;
    static T f(T a, T b) { return a + b; }
    static T e() { return 0; }
};

LinkCutTree<SumMonoid> lct(3);
lct.set(0, 2);
lct.set(1, 5);
lct.link(0, 1);
long long sum = lct.fold(0, 1);
```

`f` は結合則を満たし、`e()` は単位元とする。
`fold(u, v)` は順序を保つので、非可換モノイドでも使える。
`cut`・`fold`・`dist` は処理の前に `u` を根にする。`cut` が失敗した場合も根は変わる。
`link` は `u` を根にしてから `v` 側の木につなぐ。同じ木で失敗した場合も `u` が根になる。

## 実装上の補足
遅延するのは左右の反転だけで、頂点値への遅延作用はない。
`set` は対象を補助木の根へ splay して集約を更新する。`get` と `set` は表現している木の根を変更しない。
`jump` は補助木の部分木サイズで順位を探し、得た頂点を splay する。
