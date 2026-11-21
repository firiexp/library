---
title: 1点更新付きMo
documentation_of: //util/mo_with_updates.cpp
---

## 説明

配列の1点更新を挟む区間クエリをオフラインで処理する。区間の両端を動かしながら更新を適用したり取り消したりして、各クエリの時刻での答えを求める。

## できること

- `MoUpdateQuery(l, r, t, no)` は先頭から `t` 件の更新を適用した時点の半開区間 `[l, r)` を表す。`no` は回答を識別する番号。$O(1)$。
- `void mo_with_updates_solve(n, queries, add_left, add_right, erase_left, erase_right, apply, undo, output, bucket_size = 0)` はクエリを並べ替え、各クエリに対して `output(no)` を1回呼ぶ。回答を入力順で使う場合は `no` を添字にして保存する。クエリが空ならコールバックを呼ばない。

配列長を $N$、クエリ数を $Q$、クエリの最大時刻を $T$ とする。左右の端点に共通のブロック幅 $B$ を使う。`bucket_size` が正なら指定値を使う。省略時や0以下のときは $N^{2/3}$ を目安に `max(1, (int)cbrt((double)n * n))` で幅を決める。

ブロック数を $K=\lfloor N/B\rfloor+1$ とすると、端点の追加・削除は合計 $O(QB+NK)$ 回、更新の適用・取り消しは合計 $O(T\min(Q,K^2))$ 回。ソートは $O(Q\log Q)$ 時間、全体の作業領域は $O(Q)$。$N,Q,T$ が同程度で各コールバックが $O(1)$ なら、既定の幅で全体の時間は $O(N^{5/3})$ となる。

## 使い方

配列と集計を更新前の時刻0、空区間 `[0, 0)` から始める。クエリは `0 <= l <= r <= n` を満たし、`t` は0以上、用意した更新の件数以下とする。

- `add_left(i)` と `add_right(i)` は添字 `i` の要素をそれぞれ左端と右端に加える。`erase_left(i)` と `erase_right(i)` はそれぞれの端から除く。
- `apply(k, l, r)` は0始まりで `k` 番目の更新を適用し、`undo(k, l, r)` はその更新の直前の値に戻す。どちらも配列の値を書き換え、更新位置が現在の区間 `[l, r)` に入っているときだけ集計も直す。

次の例では配列の値と更新値を交換する。同じ更新を取り消すときにもう一度交換すると、直前の値に戻る。

```cpp
vector<int> a{2, 5, 1};
vector<pair<int, int>> updates = { {1, 8}, {1, 3} };
vector<MoUpdateQuery> queries = { {0, 2, 1, 0}, {1, 3, 2, 1} };
vector<long long> ans(queries.size());
long long sum = 0;
auto add = [&](int i) { sum += a[i]; };
auto erase = [&](int i) { sum -= a[i]; };
auto change = [&](int k, int l, int r) {
    auto &[pos, value] = updates[k];
    if (l <= pos && pos < r) sum += (long long)value - a[pos];
    swap(a[pos], value);
};
mo_with_updates_solve(a.size(), queries, add, add, erase, erase, change, change,
                      [&](int no) { ans[no] = sum; });  // ans = {10, 4}
```

## 実装上の補足

左端のブロック、右端のブロック、時刻の順でクエリをソートする。右端のブロックと時刻は蛇行順にたどる。各クエリでは時刻を合わせてから両端を動かす。処理後の配列と集計は、最後に処理したクエリの状態になる。
