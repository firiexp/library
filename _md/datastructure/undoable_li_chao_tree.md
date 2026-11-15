---
title: ロールバック可能な Li Chao Tree
documentation_of: //datastructure/undoable_li_chao_tree.cpp
---

## 説明
直線を追加し、登録済みの座標で最小値と直線IDを求める。
追加前の状態へ戻せるため、木の分岐ごとに候補が変わるDPや、直線の追加・削除をオフラインで処理する場合に使える。

## できること
構築時に渡す座標数を $K$ とする。値の比較・評価は $O(1)$ とする。

- `UndoableLiChaoTree<T> tree(vector<T> xs)`：クエリを行う座標を登録する。順序は任意で、重複は内部で除く。$O(K\log K)$
- `void add_line(T a, T b, int id)`：直線 $y=ax+b$ を追加する。`id` は非負とし、同じ値なら小さいIDを選ぶ。償却 $O(\log K)$
- `pair<T, int> query_with_id(T x) const`：`{最小値, ID}` を返す。直線がない場合や未登録の座標では `{T{}, -1}`。$O(\log K)$
- `Snapshot snapshot() const`：現在の履歴位置を返す。`Snapshot` は `size_t`。$O(1)$
- `void rollback(Snapshot state)`：`snapshot()` で保存した状態に戻す。戻す変更数に比例する時間。

履歴の最大保持件数を $H$ とすると、領域は $O(K+H)$。1回の追加で記録する変更は $O(\log K)$ 件で、rollback後は履歴領域を再利用する。

## 使い方
`T` には `long long` や `__int128` を使う。直線の評価 `a * x + b` の中間値も `T` に収まる必要がある。
IDは追加順とは独立して指定できる。元の直線番号を使えば、追加する順序が変わっても同値時の選択は変わらない。

```cpp
UndoableLiChaoTree<long long> tree({-2, 0, 3});
tree.add_line(2, 1, 10);
auto state = tree.snapshot();
tree.add_line(-1, 0, 4);
auto best = tree.query_with_id(3); // {最小値 -3, ID 4}
tree.rollback(state);
auto restored = tree.query_with_id(3); // {最小値 7, ID 10}
```

snapshotは入れ子にできる。rollbackには同じインスタンスで取得し、まだ取り消していない履歴上の位置を渡す。
過去へ戻った後に別の直線を追加した場合、取り消した側のsnapshotは再利用しない。

直線の有効期間が半開区間 `[l, r)` で分かっている場合は、`OfflineTimeIntervals` に直線番号を登録する。
`lines[id]` に係数 `{a, b}`、`query_x[t]` に時刻 `t` のクエリ座標を持たせると、次のように接続できる。クエリ座標はすべて構築時に登録しておく。

```cpp
times.run([&] { return tree.snapshot(); },
    [&](int id) {
        auto [a, b] = lines[id];
        tree.add_line(a, b, id);
    },
    [&](auto state) { tree.rollback(state); },
    [&](int t) { answers[t] = tree.query_with_id(query_x[t]); });
```

`run` の終了後は呼び出し前の直線集合へ戻る。
