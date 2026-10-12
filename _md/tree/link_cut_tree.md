---
title: Link-Cut Tree
documentation_of: //tree/link_cut_tree.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
動的森に対して、辺の追加・削除、根の付け替え、パス上の集約を扱う。
各操作は償却 $O(log N)$。

## できること
- `LinkCutTree<M> lct(n)`
  頂点数 `n` の森を作る
- `bool link(int u, int v)`
  `u` と `v` の間に辺を張る。同じ連結成分なら `false`
- `bool cut(int u, int v)`
  `u` - `v` 間の辺を削除する。存在しなければ `false`
- `void evert(int v)`
  `v` を根にする
- `bool connected(int u, int v)`
  同じ木にあるかを返す
- `int get_root(int v)`
  `v` が属する木の根を返す
- `int lca(int u, int v)`
  現在の根に対する LCA を返す。非連結なら `-1`
- `int parent(int v)`
  現在の根に対する親を返す。根なら `-1`
- `void set(int v, T x)`
  頂点 `v` の値を `x` にする
- `T get(int v)`
  頂点 `v` の値を返す
- `T fold(int u, int v)`
  パス `u -> v` 上の値を順番通りに集約する
- `int dist(int u, int v)`
  パス長を返す
- `int jump(int u, int v, int k)`
  `u` から `v` へ `k` 辺進んだ頂点を返す。非連結の場合、または `k` が負かパス長を超える場合は `-1`

## 使い方
`LinkCutTree<M> lct(n);` を作り、`M` に `using T`、`static T f(T, T)`、`static T e()` を定義する。
頂点値は `set(v, x)` で更新し、`fold(u, v)` で `u` から `v` への順序付きパス集約を取る。
辺操作は `link(u, v)`、`cut(u, v)` を使う。
`jump(u, v, k)` は動的な辺変更の後でも呼べる。頂点番号は有効な範囲とする。
`k >= 0` のとき、失敗時も含めて `u` の木の根を `u` に変更する。`k < 0` では状態を変更しない。

`M` は次を持てばよい。

```cpp
struct Monoid {
    using T = ...;
    static T f(T a, T b);
    static T e();
};
```

`fold(u, v)` は順序を保つので、非可換モノイドでも使える。

## 実装上の補足
`jump` は補助木の部分木サイズで順位を探し、得た頂点を splay する。
追加の恒久データは不要で、モノイド演算を $O(1)$ として償却 $O(\log N)$。1回の最悪時間の保証ではない。
