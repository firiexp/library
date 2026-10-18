---
title: Offline Dynamic Connectivity
documentation_of: //graph/offlinedynamicconnectivity.cpp
date: 2020-02-26
category: グラフ
tags: グラフ
---

## 説明
辺の追加・削除と、その時点の連結成分に関する問い合わせをオフラインで処理する。
各辺の生存区間を時間セグメント木に乗せ、DFS 中の状態を rollback 可能なデータ構造で持つ。
生存区間数を $K$ とすると、時間木の構築・列挙は $O(q+K\log(q+1))$ 時間、領域は $O(n+q+K\log(q+1))$。
辺の登録には別途 map の操作ごとに $O(\log(K+1))$、`run` には各イベントの unite / undo と callback の費用がかかる。

## できること
- `OfflineDynamicConnectivity dc(n, q)`
  頂点数 `n`、クエリ数 `q` の時間セグメント木を作る
- `void insert(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を追加する
- `void erase(int t, int u, int v)`
  時刻 `t` で辺 `u` - `v` を削除する
- `void build()`
  登録済みの追加・削除から各辺の生存区間を構築する。同じ登録内容で再実行できる
- `void run(F f)`
  内部の `UndoableUnionFind` を使って DFS し、各時刻で `f(t)` または `f(t, uf)` を呼ぶ
- `void dfs(Enter enter, Leave leave, Leaf leaf)`
  時間セグメント木を直接 DFS する。`enter(k, edges)` でノード進入、`leave(k, edges)` で離脱、`leaf(t)` で時刻 `t` を昇順に処理する

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

`dfs` は辺以外の rollback 付き状態も一緒に載せたいときに使う。
たとえば頂点加算や成分和のように、別の時間セグメント木を同じ DFS で重ねて処理できる。

## 実装上の補足
時間木のイベントは辺の組を1本の配列へ詰め、ノードごとの offset で参照する。
`dfs` の `edges` は range-for と `size()` を使える読み取り専用の `EdgeRange` であり、vector ではない。
従来の `const vector<pair<int,int>>&` を明記した callback は `const auto&` または `const OfflineDynamicConnectivity::EdgeRange&` に変更する。
view は次の `build` まで有効。DFS 中には登録内容を変更しない。
`q=0` では葉の callback を呼ばない。
