---
title: 1点更新付きMo
documentation_of: //util/mo_with_updates.cpp
---

## 説明
1点更新を含む配列への区間クエリをオフラインで処理する。

## できること
配列長を $N$、クエリ数を $Q$、最大時刻を $T$、ブロック幅を $B$ とする。

- `MoUpdateQuery(l, r, t, no)`
  先頭から `t` 件の更新を適用した時点の半開区間 `[l, r)` のクエリを作る。`no` はクエリ番号。$O(1)$
- `void mo_with_updates_solve(n, queries, add_left, add_right, erase_left, erase_right, apply, undo, output, bucket_size = 0)`
  クエリを並べ替えて区間と時刻を移動し、各回答時に `output(no)` を呼ぶ。端点の追加・削除は合計 $O(QB + N^2/B)$ 回、更新の適用・取り消しは合計 $O(TN^2/B^2)$ 回、ソートは $O(Q\log Q)$。既定の $B \approx N^{2/3}$ で $N, Q, T$ が同程度かつ各操作が $O(1)$ なら $O(N^{5/3})$

## 使い方
配列と集計は更新前の時刻 `0`、空区間 `[0, 0)` から始める。各クエリは `0 <= l <= r <= n`、`t >= 0` を満たすものとする。

- `add_left(i)`・`add_right(i)`：添字 `i` の要素を左端・右端に追加する。
- `erase_left(i)`・`erase_right(i)`：添字 `i` の要素を左端・右端から削除する。
- `apply(k, l, r)`・`undo(k, l, r)`：0始まりの `k` 番目の更新を適用・取り消し、配列を更新する。更新位置が現在の区間 `[l, r)` に含まれる場合は集計も更新する。
- `output(no)`：現在の集計結果をクエリ番号 `no` の回答として保存する。

`bucket_size` が正ならその値をブロック幅に使い、省略または `0` 以下なら $N^{2/3}$ を目安に設定する。

配列の値と更新値を `swap` しておくと、`apply` と `undo` を同じ処理で書ける。

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
左端のブロック、右端のブロック、時刻の順でクエリをソートし、右端のブロックと時刻は蛇行順にたどる。各クエリでは時刻を合わせてから両端を動かす。
