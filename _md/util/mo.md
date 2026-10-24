---
title: Mo's Algorithm
documentation_of: //util/mo.cpp
date: 2026-03-25
category: クエリ
tags: クエリ
---

## 説明
区間の両端への要素追加・削除で答えを更新できるとき、クエリを並べ替えてまとめて処理する。

## できること
配列長を $N$、クエリ数を $Q$、バケット幅を $B$ とする。

- `Query(l, r, no)`
  半開区間 `[l, r)` のクエリを作る。`no` はクエリ番号。$O(1)$
- `mo_solve(n, queries, add_left, add_right, erase_left, erase_right, output, bucket_size = 0)`
  クエリを並べ替えて左右端を移動し、各回答時に `output(no)` を呼ぶ。要素の追加・削除は合計 $O(QB+N^2/B)$ 回、ソートは $O(Q\log Q)$ 時間、作業領域は $O(Q)$
- `Query::B`
  手動で `sort` するときのバケット幅。`Query::bucket_size` の別名
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる。$O(Q\log Q)$

## 使い方
`mo_solve` に渡すクエリは `0 <= l <= r <= n` を満たすものとし、callback 側の集計は空区間から始める。
`add_left(i)`、`add_right(i)` は添字 `i` の要素を左端・右端に加え、`erase_left(i)`、`erase_right(i)` はその要素を除く。
左右を別々に指定できるため、転倒数など順序に依存する集計にも使える。
回答は `output(no)` で元のクエリ番号に対応させて保存する。

```cpp
mo_solve(n, qs, add_left, add_right, erase_left, erase_right,
         [&](int no) { ans[no] = current_answer; });
```

クエリ列が空なら callback を呼ばずに終了する。
クエリがある場合、`bucket_size` が正なら指定値を使い、省略または `0` 以下なら $\max(1, \lfloor N/\sqrt{Q}\rfloor)$ を使う。
$B \approx N/\sqrt{Q}$ が移動回数を抑える目安で、$N$ と $Q$ が同程度なら $B \approx \sqrt{N}$ となる。
追加・削除の処理時間に合わせて手で調整してもよい。
比較だけを使う場合は、`Query::bucket_size` を設定して `sort(qs.begin(), qs.end())` を呼ぶ。

## 実装上の補足
`mo_solve` は左端のブロック番号と右端の蛇行順をキーに変換してからソートする。
整数除算はキーの作成時に各クエリで1回だけ行う。同じブロック・右端を持つクエリの順序は未指定。
