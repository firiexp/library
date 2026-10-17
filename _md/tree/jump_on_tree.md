---
title: Jump on Tree
documentation_of: //tree/jump_on_tree.cpp
date: 2026-03-08
category: 木
tags: 木
---

## 説明
木上の `k` 個先の頂点、LCA、祖先を doubling で求める。
根からの最大深さを $D$ として、前処理時間・祖先表の領域は $O(N\log(D+2))$、各クエリは $O(\log(D+2))$。

## できること
- `JumpOnTree jt(n)`
  頂点数 `n` の木を作る
- `void add_edge(int u, int v)`
  木辺を張る
- `void build(int root = 0)`
  根 `root` で前処理する
- `int ancestor(int v, int k)`
  `v` の `k` 個上の祖先を返す。存在しなければ `-1`
- `int lca(int u, int v)`
  `u` と `v` の最近共通祖先を返す
- `int dist(int u, int v)`
  `u` と `v` の距離を返す
- `int jump(int s, int t, int k)`
  `s` から `t` への最短路の `k` 番目の頂点を返す。存在しなければ `-1`

## 使い方
辺を張って `build(root)` を 1 回呼び、その後に `jump(s, t, k)` や `lca(u, v)` を使う。

```cpp
JumpOnTree jt(n);
for (auto [u, v] : edges) {
    jt.add_edge(u, v);
}
jt.build(0);

int x = jt.jump(s, t, k);
```

## 実装上の補足
親と深さを求めてから祖先表の段数を決める。最大深さが $0$ なら1段、それ以外は $\lfloor\log_2 D\rfloor+1$ 段を使う。
星や平衡木では段数が減る。パスでは最悪計算量は従来どおり前処理 $O(N\log N)$、各クエリ $O(\log N)$ となる。
`jump(s, t, k)` は `s -> lca(s, t)` 側と `lca(s, t) -> t` 側を分けて処理する。
