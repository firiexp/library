---
title: Mo's algorithm
documentation_of: //util/mo.cpp
date: 2020-02-17
category: クエリ
tags: クエリ
---

## 説明
区間のマージは高速にできないが、区間を 1 つ広げる/縮めることが $O(p(N))$ でできれば、$Q$ 個のクエリを $O(N \sqrt{Qp(N)})$ で処理できる。
ブロックサイズ $B$ を適切に設定して使う。

## 使い方
クエリを並べ替え、区間の左右端を少しずつ動かしながら答えを更新する。
