---
title: 固定長正方行列(mint専用)
documentation_of: //math/squarematrix_mint.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
`mint` 専用の固定長正方行列。
積で `mint.value()` を使う整数演算に寄せ、`MOD` と accumulator 幅に応じたチャンク分割で行列累乗の定数倍を削る。
汎用版と分け、性能重視の特殊版として置いている。

## できること
- `SquareMatrixMint<SIZE> A`
  `SIZE × SIZE` 行列を 0 初期化で作る
- `SquareMatrixMint<SIZE>::I()`
  単位行列を返す
- `SquareMatrixMint<SIZE>::I(n)`
  左上 `n × n` だけを使う単位行列を返す
- `SquareMatrixMint<SIZE>::PreparedMul prepared`
  転置済み右辺を保持する
- `A += B`, `A -= B`, `A *= B`
  加減算、行列積を行う
- `A.pow(k)`
  $A^k$ を返す
- `A.pow(k, n)`
  左上 `n × n` だけを使って $A^k$ を返す
- `x * A`
  長さ `SIZE` の行ベクトルに右から掛ける
- `A.mul_vec(x, n)`, `A.mul_vec_assign(x, n)`
  左上 `n × n` だけを使って行ベクトル積を行う
- `A.prepare_mul(prepared, n)`
  左上 `n × n` の転置済み右辺を作る
- `A.mul_assign_prepared(prepared, scratch, n)`
  転置済み右辺を再利用して行列積を行う
- `A.mul_vec_prepared(x, prepared, scratch, n)`
  行列積と同じ転置済み右辺を再利用して行ベクトル積を行う

## 使い方
要素が `mint` に固定でよいときに使う。
`Pow of Matrix` のようにサイズ固定で累乗回数が多いケースを想定している。
実際に使うサイズが `SIZE` 未満で、行ベクトル積も合わせて回したいときは `mul_vec(x, n)` を使う。
同じ行列を右辺に何度も使うなら `PreparedMul` を 1 つ作って `prepare_mul` し、行列積と行ベクトル積の両方で共有すると無駄が少ない。

汎用の半環版が必要なら `SquareMatrix<H, SIZE>` を使う。
