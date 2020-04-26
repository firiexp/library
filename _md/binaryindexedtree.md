---
layout: post
title: BIT(BinaryIndexedTree)
date: 2019-10-15
category: データ構造
tags: データ構造
---

## 説明
可換群(逆元が存在する群)について、区間和を$O(\log N)$で求め、更新を$O(\log N)$で行う。<br>
可換でなくても$[0, x)$について演算した結果だけを求めたいのであれば、使うことができる。(例: LIS)

## 操作
- $\mathrm{add}(k, x)$ : $k$番目の要素に$x$を加算する。
- $\mathrm{sum}(k)$ : 閉区間$[0, k]$の和を求める。

{% include a.html code="binaryindexedtree.cpp" %}