---
title: 行列
documentation_of: //math/matrix.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
一般サイズの行列に対して加算、減算、積、累乗を扱う。

## できること
- `matrix<H> A(n, m)`
  `n × m` 行列を作る
- `matrix<H> A(n)`
  `n × n` 行列を作る
- `matrix<H>::I(n)`
  `n × n` 単位行列を返す
- `A += B`, `A -= B`, `A *= B`
  同じサイズの加減算、または行列積を行う
- `A.pow(k)`
  正方行列の非負整数 $k$ 乗を返す。`k = 0` なら単位行列、`k = 1` なら入力のコピー。どちらも $O(n^2)$、$k \ge 2$ で $O(n^3 \log k)$
- `A.pow_sum(k)`
  正方行列と非負整数 `k` に対し、$(A^k, I+A+\cdots+A^{k-1})$ の pair を返す。`k = 0` なら単位行列と零行列
- `A.pow_apply(k, v)`
  正方行列の冪を列ベクトルに適用し、$A^k v$ を `vector<T>` で返す。`k` は非負、`v.size() == A.width()` とする。`k = 0` なら `v` のコピー

## 使い方
`H` に `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を定義して使う。
可変サイズの行列を素直に扱いたいときに使う。
`auto [power, sum] = A.pow_sum(k);` で冪と累積和を同時に求める。減算や逆元は使わないため、一般の半環でも使える。
`auto result = A.pow_apply(k, v);` は全状態の遷移を `k` 回進めたいときに使う。
1回の適用は $\mathrm{result}_i=\sum_j A_{ij}v_j$ で、係数の積が非可換でもこの順序を保つ。

## 実装上の補足
`pow` は最初の単位行列との積をコピーに置き換え、正の指数では行列積を1回省く。
`pow_sum` は $P(2a)=P(a)^2$、$S(2a)=S(a)+P(a)S(a)$ で倍増する。時間 $O(n^2+n^3\log(k+1))$、作業領域 $O(n^2)$。
固定幅整数を使う場合は、冪・累積和とその途中演算が係数型の範囲に収まることを前提とする。
`pow_apply` は指数の各1ビットでベクトルだけを更新する。時間は `k = 0` で $O(n)$、`k = 1` で $O(n^2)$、`k \ge 2` で $O(n^3\log k+n^2\operatorname{popcount}(k))$。
作業領域は `k <= 1` で $O(n)$、それ以外で $O(n^2)$、返却値は $O(n)$。行列の二乗・ベクトル積・累積加算の途中値も係数型に収める。min-plus の到達不能値は `H::mul` 側で保護する。
