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
- `Query::bucket_size`
  左端を分けるバケット幅。`sort` 前に利用側で設定する
- `sort(qs.begin(), qs.end())`
  左端のブロック順、右端の蛇行順でクエリを並べる

## 使い方
クエリを読み込んだら `Query::bucket_size = B;` を設定し、`sort(qs.begin(), qs.end())` で並べ替える。
あとは区間の左右端を少しずつ動かしながら答えを更新する。

## 実装上の補足
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
