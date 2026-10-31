---
title: 固定長正方行列(mint専用)
documentation_of: //math/linear_algebra/squarematrix_mint.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
`mint` 専用の固定長正方行列。
通常の加算と乗算による行列積と累乗を扱う。

## できること
- `SquareMatrixMint<SIZE> A`
  `SIZE × SIZE` 行列を 0 初期化で作る。$O(SIZE^2)$
- `SquareMatrixMint<SIZE>::I()`
  単位行列を返す。$O(SIZE^2)$
- `SquareMatrixMint<SIZE>::I(n)`
  左上 `n × n` だけを使う単位行列を返す。$O(SIZE^2)$
- `SquareMatrixMint<SIZE>::PreparedMul prepared`
  転置済み右辺を保持する
- `A += B`
  `B` を加える。$O(SIZE^2)$
- `A -= B`
  `B` を引く。$O(SIZE^2)$
- `A *= B`
  `A` を行列積に置き換える。$O(SIZE^3)$
- `A.pow(k)`
  非負整数 `k` に対して $A^k$ を返す。$O(SIZE^3\log k)$
- `A.pow(k, n)`
  左上 `n × n` だけを使って $A^k$ を返す。時間 $O((SIZE^2+n^3)\log k)$
- `A.pow_sum(k, n = SIZE)`
  非負整数 `k` に対し、左上 `n × n` の $(A^k, I+A+\cdots+A^{k-1})$ を返す。`k = 0` は単位行列と零行列。返り値の未使用領域は0。時間 $O((SIZE^2+n^3)\log k)$、作業領域 $O(SIZE^2)$
- `x * A`
  長さ `SIZE` の行ベクトルに右から掛ける。$O(SIZE^2)$
- `A.mul_vec(x, n)`
  左上 `n × n` と行ベクトル `x` の積を返す。$O(SIZE+n^2)$
- `A.mul_vec_assign(x, n)`
  左上 `n × n` と行ベクトル `x` の積を `x` に代入する。$O(SIZE+n^2)$
- `A.prepare_mul(prepared, n)`
  `A` の左上 `n × n` の転置を `prepared` に格納する。$O(n^2)$
- `A.mul_assign_prepared(prepared, scratch, n)`
  `prepared` に格納した右辺との積を `A` に代入する。`scratch` は `MatrixMulScratch` 型の作業領域とする。$O(SIZE^2+n^3)$
- `A.mul_vec_prepared(x, prepared, scratch, n)`
  `prepared` に格納した右辺と行ベクトル `x` の積を返す。`scratch` は `VecMulScratch` 型の作業領域とする。$O(SIZE+n^2)$

## 使い方
要素が `mint` に固定でよいときに使う。
実際に使うサイズが `SIZE` 未満で、行ベクトル積も合わせて回したいときは `mul_vec(x, n)` を使う。
同じ行列を右辺に何度も使うなら `PreparedMul` を 1 つ作って `prepare_mul` し、行列積と行ベクトル積の両方で共有すると無駄が少ない。

汎用の半環版が必要なら `SquareMatrix<H, SIZE>` を使う。

## 実装上の補足
`pow` の指数が8未満のときは二分累乗を使い、最初の単位行列との積を有効領域のコピーに置き換える。この経路の未使用領域は0で、指数0・1の時間は $O(SIZE^2)$。
`auto [power, sum] = A.pow_sum(k);` で冪と累積和を同時に求める。逆元は使わず、$A-I$ が特異でもよい。
`pow_sum` は二分累乗と既存の行列積を組み合わせ、元の行列の転置を再利用する。`pow` の sliding window 法とは別の処理を使う。
