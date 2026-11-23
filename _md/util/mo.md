---
title: Mo's Algorithm
documentation_of: //util/mo.cpp
---

## 説明
区間の両端への要素追加・削除で答えを更新できるとき、クエリを並べ替えてまとめて処理する。

## できること
配列長を $N$、クエリ数を $Q$、バケット幅を $B$ とする。

- `Query(l, r, no)`
  半開区間 `[l, r)` のクエリを作る。`no` はクエリ番号。$O(1)$
- `mo_solve(n, queries, add, erase, output, bucket_size = 0)`
  左右共通の `add(i)`・`erase(i)` でクエリを並べ替えて処理し、各回答時に `output(no)` を呼ぶ。要素の追加・削除は合計 $O(QB+N^2/B)$ 回、ソートは $O(Q\log Q)$ 時間、作業領域は $O(Q)$
- `mo_solve(n, queries, add_left, add_right, erase_left, erase_right, output, bucket_size = 0)`
  左端と右端で別々の追加・削除操作を指定して処理する。要素の追加・削除は合計 $O(QB+N^2/B)$ 回、ソートは $O(Q\log Q)$ 時間、作業領域は $O(Q)$
- `Query::B`
  手動で `sort` するときのバケット幅。`Query::bucket_size` の別名
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる。$O(Q\log Q)$

## 使い方
`mo_solve` に渡すクエリは `0 <= l <= r <= n` を満たすものとし、callback 側の集計は空区間から始める。
左右共通でよければ `add(i)`・`erase(i)` を渡し、転倒数など順序に依存する集計では `add_left`・`add_right`・`erase_left`・`erase_right` を別々に指定する。
回答は `output(no)` で元のクエリ番号に対応させて保存する。

```cpp
vector<int> a = {4, 1, 5};
vector<Query> qs = { {1, 3, 0}, {0, 2, 1} };
vector<long long> ans(qs.size());
long long sum = 0;
mo_solve(a.size(), qs,
         [&](int i) { sum += a[i]; },
         [&](int i) { sum -= a[i]; },
         [&](int no) { ans[no] = sum; }); // ans = {6, 5}
```

`bucket_size` が正なら指定値を使い、省略または `0` 以下なら $\max(1, \lfloor N/\sqrt{Q}\rfloor)$ を使う。
$B \approx N/\sqrt{Q}$ が移動回数を抑える目安で、$N$ と $Q$ が同程度なら $B \approx \sqrt{N}$ となる。
追加・削除の処理時間に合わせて手で調整してもよい。
比較だけを使う場合は、`Query::bucket_size` を設定して `sort(qs.begin(), qs.end())` を呼ぶ。

## 実装上の補足
`mo_solve` は左端のブロック番号と右端の蛇行順をキーに変換してからソートする。
整数除算はキーの作成時に各クエリで1回だけ行う。同じブロック・右端を持つクエリの順序は未指定。
