---
title: Mo's Algorithm
documentation_of: //util/mo.cpp
date: 2026-03-25
category: クエリ
tags: クエリ
---

## 説明
区間のマージは高速にできないが、区間を 1 つ広げる/縮めることが $O(p(N))$ でできれば、$Q$ 個のクエリをまとめて処理できる。

## できること
- `Query(l, r, no)`
  半開区間 `[l, r)` のクエリを作る
- `mo_solve(n, queries, add_left, add_right, erase_left, erase_right, output, bucket_size = 0)`
  クエリを並べ替えて左右端を移動し、各回答時に `output(no)` を呼ぶ。各追加・削除 callback には要素の添字を渡す。入力クエリ列と `Query::bucket_size` は変更しない
- `Query::B`
  手動で `sort` するときのバケット幅。`Query::bucket_size` の別名
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる

## 使い方
`mo_solve` に渡すクエリは `0 <= l <= r <= n` を満たすものとし、callback 側の集計は空区間から始める。
左右の追加・削除を別々に指定できるため、転倒数など順序に依存する集計にも使える。
回答は元のクエリ ID で保存する。空クエリ列では callback を呼ばず、空区間のクエリにも対応する。
`bucket_size` が正なら指定値を使い、省略または `0` 以下なら $\max(1, \lfloor N/\sqrt{Q}\rfloor)$ を使う。
利用側では `<algorithm>`、`<cmath>`、`<vector>` を読み込む。

```cpp
mo_solve(n, qs, add_left, add_right, erase_left, erase_right,
         [&](int no) { ans[no] = current_answer; });
```

比較だけを使いたい場合は、従来どおり `Query::bucket_size` を設定して `sort(qs.begin(), qs.end())` を呼べる。

## 実装上の補足
- `mo_solve` のソートは $O(Q\log Q)$、作業領域はクエリ列のコピーに $O(Q)$
- 典型的な計算量評価は、左端の移動が $O(QB)$、右端の移動が $O(N^2 / B)$ なので、1 回の追加・削除が $O(p(N))$ なら合計は
$$
O\left(\left(QB + \frac{N^2}{B}\right) p(N)\right)
$$
  になる
- これを最小化する目安が
$$
B \approx \frac{N}{\sqrt{Q}}
$$
  なので、まずはこの値を目安に `Query::bucket_size` を決め、必要なら定数倍を見ながら手で調整するとよい
- `Q` と `N` が同程度なら $B \approx \sqrt{N}$ と見てよい
