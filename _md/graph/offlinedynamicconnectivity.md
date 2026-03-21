---
title: Dynamic Connectivity (オフライン)
documentation_of: //graph/offlinedynamicconnectivity.cpp
date: 2020-02-26
category: グラフ
tags: グラフ
---

## 説明
辺の追加・削除と、その時点の連結成分に関する問い合わせをオフラインで処理する。
各辺の生存区間を時間セグメント木に乗せ、DFS 中の状態を rollback 可能なデータ構造で持つ。
辺の登録全体は $O(q \log q)$、DFS 中の各操作は使う rollback 構造に依存する。

## できること
- `OfflineDynamicConnectivity dc(n, q)`
  頂点数 `n`、クエリ数 `q` の時間セグメント木を作る
- `void insert(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を追加する
- `void erase(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を削除する
- `void build()`
  登録済みの追加・削除から各辺の生存区間を構築する
- `void run(F f)`
  内部の `UndoableUnionFind` を使って DFS し、各時刻で `f(t)` または `f(t, uf)` を呼ぶ
- `void dfs(Enter enter, Leave leave, Leaf leaf)`
  時間セグメント木を直接 DFS する。`enter(k, seg[k])` でノード進入、`leave(k, seg[k])` で離脱、`leaf(t)` で時刻 `t` を処理する

## 使い方
単に連結判定だけをしたいなら `insert` / `erase` を全て登録して `build()` し、`run` で葉を処理する。

```cpp
OfflineDynamicConnectivity dc(n, q);
for (int t = 0; t < q; ++t) {
    if (add_query) dc.insert(t, u, v);
    if (erase_query) dc.erase(t, u, v);
}
dc.build();
dc.run([&](int t, UndoableUnionFind &uf) {
    answer[t] = uf.same(s[t], target[t]);
});
```

`dfs` は辺以外の rollback 付き状態も一緒に載せたいときに使う。
たとえば頂点加算や成分和のように、別の時間セグメント木を同じ DFS で重ねて処理できる。
