---
title: XOR基底(Linear Basis)
documentation_of: //math/xor_basis.cpp
date: 2026-03-12
category: 数学
tags: 数学
---

## 説明
整数列から xor 基底を構築する。
基底の本数を $k$ とすると、表現できる値の個数は $2^k$。

## できること
- `XorBasis<T> xb`
  空の xor 基底を作る
- `int size()`
  基底の本数を返す
- `bool empty()`
  基底が空なら `true`
- `bool add(T x)`
  `x` を基底に追加する。独立なら `true`、追加されなければ `false`
- `bool contains(T x)`
  `x` を基底で表せるなら `true`、表せなければ `false`
- `T get_min(T x = 0)`
  `x xor y` を最小にする `y` を基底の生成する空間から選んだ結果を返す
- `T get_max(T x = 0)`
  `x xor y` を最大にする `y` を基底の生成する空間から選んだ結果を返す
- `void merge(const XorBasis<T>& other)`
  `other` の基底を併合する

## 使い方
`add` で値を順に入れて使う。
`contains(x)` で表現可能性を判定でき、`get_min(x)` と `get_max(x)` で
$$
\min_{y \in \langle S \rangle} (x \oplus y), \quad \max_{y \in \langle S \rangle} (x \oplus y)
$$
を求められる。

## 実装上の補足
- `T` は整数型を想定する
- 返り値は `x xor y` そのものを返す
