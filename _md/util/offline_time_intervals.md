---
title: 追加・削除クエリのオフライン処理
documentation_of: //util/offline_time_intervals.cpp
date: 2026-10-14
category: クエリ
tags: クエリ
---

## 説明
辺の追加・削除を含むグラフの連結性判定などを、rollback 可能なデータ構造でオフラインに処理する。
例えば、クエリ `l` で追加し、クエリ `r` で削除する辺は、区間 `[l,r)` で有効なイベントとして登録する。
各クエリへの回答時には、その時点で有効なイベントだけが適用された状態になる。

イベントの適用順序が変わってもクエリの答えが変わらない操作を扱う。

## できること
- `OfflineTimeIntervals tm(q)`
  `q` 個のクエリを処理する。追加・削除もクエリ数に含める
- `tm.add_interval(l, r, event_id)`
  半開区間 `[l,r)` で有効なイベント ID を登録する。空区間は無視し、同じ ID の複数区間も別々に適用する
- `tm.run(snapshot, apply, rollback, answer)`
  登録した区間を処理し、`answer(t)` をクエリ番号順に呼ぶ。終了時には開始時の状態へ戻す。同じ登録内容で再実行できる

## 使い方
イベント本体は利用側の配列で保持する。区間は `0 <= l <= r <= q` とする。
`tm.run` は区間をセグメント木に分け、各ノードで `snapshot()` により状態を記録してから `apply(id)` でイベントを適用する。
そのノード内の処理が終わると `rollback(state)` で記録した状態へ戻す。
葉では `answer(t)` でクエリに答える。`answer` は状態の意味を変更せず、回答が不要なクエリでは何もしなくてよい。

```cpp
tm.add_interval(l, r, id);
tm.run([&] { return uf.get_state(); },
       [&](int id) { uf.unite(edges[id].u, edges[id].v, edges[id].w); },
       [&](int state) { uf.rollback(state); },
       [&](int t) { answer[t] = uf.consistent(); });
```

`q=0` では callback を呼ばない。登録後に別途 build や reserve を呼ぶ必要はない。

## 実装上の補足
登録する区間数を $K$、クエリ数を $Q$ とする。

- `tm.add_interval` は1回あたり償却 $O(1)$。登録内容の保持に $O(K)$ の領域を使う
- `tm.run` は callback を除いて $O(Q+K\log Q)$ 時間、作業領域も $O(Q+K\log Q)$

`tm.run` は `snapshot` と `rollback` をそれぞれ $O(Q)$ 回、`apply` を $O(K\log Q)$ 回、`answer` を $Q$ 回呼ぶ。
`rollback` が操作を1つずつ取り消す実装なら、取り消す操作の総数は `apply` の呼び出し回数と同じとなる。
