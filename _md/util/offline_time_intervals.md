---
title: 生存区間のオフライン処理
documentation_of: //util/offline_time_intervals.cpp
date: 2026-10-14
category: クエリ
tags: クエリ
---

## 説明
イベントの生存区間を時間軸のセグメント木へ載せ、rollback 可能な状態を使って各時刻の問い合わせを処理する。
イベントの適用順序が変わっても問い合わせの意味が変わらない操作を扱う。一般の時系列代入には使えない。

## できること
- `OfflineTimeIntervals tm(q)`
  時刻 `0..q-1` を用意する
- `tm.add_interval(l, r, event_id)`
  半開区間 `[l,r)` で有効なイベント ID を登録する。空区間は無視し、同じ ID の複数区間も別々に適用する
- `tm.run(snapshot, apply, rollback, answer)`
  内部構築と走査を行い、`answer(t)` を時刻順に呼ぶ。終了時には開始時の状態へ戻す。同じ登録内容で再実行できる

## 使い方
イベント本体は利用側の配列で保持する。`0 <= l <= r <= q` とし、各 callback は次の役割を持つ。

- `snapshot()` は現在の状態を表す値を返す
- `apply(id)` はイベントを適用する
- `rollback(state)` は snapshot 時点へ状態を戻す
- `answer(t)` は時刻 `t` の回答を保存する。状態の意味を変更しない

```cpp
tm.run([&] { return uf.get_state(); },
       [&](int id) { uf.unite(edges[id].u, edges[id].v, edges[id].w); },
       [&](int state) { uf.rollback(state); },
       [&](int t) { answer[t] = uf.consistent(); });
```

`q=0` では callback を呼ばない。登録後に別途 build や reserve を呼ぶ必要はない。

## 実装上の補足
区間数を $K$、時刻数を $Q$ とする。登録は vector の拡張を含め償却 $O(1)$、登録内容の保持は $O(K)$。
run 内の構築は $O(Q+K\log(Q+1))$。イベント列は offset と連続配列で持つ。
snapshot が $O(1)$、適用が $A$、1イベントの取消が $U$、回答が $F$ なら、run は $O(Q+K\log(Q+1)(A+U)+QF)$、作業領域は $O(Q+K\log(Q+1))$。
状態側が償却保証ならその区別を引き継ぐ。再帰の深さは $O(\log(Q+1))$。
