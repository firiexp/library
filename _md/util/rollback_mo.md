---
title: Rollbackを使うMo
documentation_of: //util/rollback_mo.cpp
category: その他
tags: その他
---

## 説明
要素の追加と状態の保存・復元を使って、静的配列の区間クエリを処理する。
区間内で同じ値を取る2要素の最大距離など、要素を削除した後の集計値を更新しにくい場合に使う。

## できること
配列長を $N$、クエリ数を $Q$、ブロック幅を $B$ とする。

- `rollback_mo_solve(n, queries, state, bucket_size = 0)`
  長さ `n` の配列について、`Query(l, r, no)` の半開区間 `[l,r)` を `state` で集計し、`state.output(no)` で回答を保存する。
  `bucket_size` には左端を分けるブロックの幅を指定する。0以下なら $B=\max(1,\lfloor N/\sqrt Q\rfloor)$ に設定する。

## 使い方
配列・集計値・履歴を持つ構造体を定義し、そのオブジェクトを `state` として渡す。
次のメンバ関数を実装する。`snapshot()` が返した値を `rollback(saved)` に渡して状態を復元する。

- `reset()`：集計値と履歴を空状態に戻す。
- `add_left(i)`：現在の区間の左端に添字 `i` の要素を追加する。
- `add_right(i)`：現在の区間の右端に添字 `i` の要素を追加する。
- `snapshot()`：現在の状態を復元するための値を返す。
- `rollback(saved)`：`snapshot()` の時点の集計値・履歴へ戻す。
- `output(no)`：集計値から求めた答えをクエリ番号 `no` の回答として保存する。集計値と履歴は変更しない。

例えば区間最大値なら、保存・復元する状態は最大値1つでよい。

```cpp
struct RangeMax {
    const vector<int> &a;
    vector<int> answers;
    int best = numeric_limits<int>::lowest();

    void reset() { best = numeric_limits<int>::lowest(); }
    void add_left(int i) { best = max(best, a[i]); }
    void add_right(int i) { add_left(i); }
    int snapshot() const { return best; }
    void rollback(int saved) { best = saved; }
    void output(int no) { answers[no] = best; }
};

RangeMax state{a, vector<int>(queries.size())};
rollback_mo_solve(a.size(), queries, state);
```

## 実装上の補足
左端を幅 $B$ のブロックに分け、ブロック内では右端を昇順に処理する。
短い区間は空状態から一時追加する。ブロックをまたぐ区間は右側を延ばし、snapshot 後に左側を一時追加する。
回答後に rollback して、一時追加した要素を取り消す。

要素1個の追加・取り消しが $O(F)$、snapshot・output が $O(1)$ とする。
reset・rollback が $O(1)$、または履歴を1件ずつ取り消す実装なら、全体の時間は $O(Q\log Q+(N^2/B+QB)F)$。
補助領域は `state` の領域を除いて $O(Q)$。
