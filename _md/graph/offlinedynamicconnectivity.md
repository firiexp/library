---
title: Offline Dynamic Connectivity
documentation_of: //graph/offlinedynamicconnectivity.cpp
date: 2020-02-26
category: グラフ
tags: グラフ
---

## 説明
辺の追加・削除と、その時点の連結成分に関するクエリをオフラインで処理する。
各辺の生存区間を時間セグメント木に乗せ、DFS 中の状態を rollback 可能なデータ構造で持つ。

## できること
頂点数を $N$、時刻数を $Q$、辺の生存区間数を $K$、登録する異なる辺の数を $M$ とする。

- `OfflineDynamicConnectivity dc(n, q)`
  頂点数 `n`、時刻数 `q` で初期化する。$O(N+\log Q)$
- `void insert(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を追加する。$O(\log M)$
- `void erase(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を削除する。償却 $O(\log M)$
- `void build()`
  登録済みの追加・削除から各辺の生存区間を構築する。時間 $O(Q+K\log Q)$、領域 $O(N+Q+K\log Q)$
- `void run(F f)`
  内部の `UndoableUnionFind` を使って DFS し、各時刻で `f(t)` または `f(t, uf)` を呼ぶ。コールバックを除き $O(Q+K\log Q\log N)$
- `void dfs(Enter enter, Leave leave, Leaf leaf)`
  時間セグメント木を直接 DFS する。`enter(k, edges)` でノード進入、`leave(k, edges)` で離脱、`leaf(t)` で時刻 `t` を昇順に処理する。コールバックを除き $O(Q)$、列挙する辺は合計 $O(K\log Q)$ 個

## 使い方
単に連結判定だけをしたいなら `insert` / `erase` を全て登録して `build()` し、`run` で葉を処理する。
時刻は `0 <= t < q` とし、操作を時刻順に登録する。同じ辺を複数回追加すると参照数を持ち、最後の削除まで有効となる。
削除は追加済みの辺に限る。削除しなかった辺は時刻 `q` の直前まで有効となる。
`run` の callback は UF の状態を変更しないこと。終了時には開始時の UF の状態へ戻る。

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

`dfs` の `k` は時間セグメント木のノード番号、`edges` はそのノードの時間区間全体で有効な辺の列を表す。
辺以外の rollback 付き状態も一緒に処理したいときに使う。
たとえば頂点加算や成分和のように、別の時間セグメント木を同じ DFS で重ねて処理できる。

## 実装上の補足
時間木のイベントは辺の組を1本の配列へ詰め、ノードごとの offset で参照する。
`dfs` の `edges` は range-for と `size()` を使える読み取り専用の `EdgeRange` であり、vector ではない。
コールバックの `edges` は `const auto&` または `const OfflineDynamicConnectivity::EdgeRange&` で受け取る。
view は次の `build` まで有効。DFS 中には登録内容を変更しない。
`q=0` では葉の callback を呼ばない。
