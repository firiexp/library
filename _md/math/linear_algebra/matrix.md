---
title: 行列
documentation_of: //math/linear_algebra/matrix.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
一般サイズの行列に対して加算、減算、積、累乗を扱う。

## できること
- `matrix<H> A(n, m)`
  `n × m` 行列を加法単位元で初期化する。$O(nm)$
- `matrix<H> A(n)`
  `n × n` 行列を加法単位元で初期化する。$O(n^2)$
- `matrix<H>::I(n)`
  `n × n` 単位行列を返す。$O(n^2)$
- `A += B`
  同じサイズの行列を加える。$n$ 行 $m$ 列に対して $O(nm)$
- `A -= B`
  同じサイズの行列を引く。$n$ 行 $m$ 列に対して $O(nm)$
- `A *= B`
  `A` を行列積に置き換える。`A` が $n$ 行 $p$ 列、`B` が $p$ 行 $m$ 列なら $O(npm)$
- `A.pow(k)`
  正方行列の非負整数 $k$ 乗を返す。`k = 0` なら単位行列、`k = 1` なら入力のコピー。どちらも $O(n^2)$、$k \ge 2$ で $O(n^3 \log k)$
- `A.pow_sum(k)`
  正方行列と非負整数 `k` に対し、$(A^k, I+A+\cdots+A^{k-1})$ の pair を返す。`k = 0` なら単位行列と零行列。$n$ を行列の次数として、時間 $O(n^3\log k)$、作業領域 $O(n^2)$
- `A.pow_apply(k, v)`
  正方行列の冪を列ベクトルに適用し、$A^k v$ を `vector<T>` で返す。`k` は非負、`v.size() == A.width()` とする。`k = 0` なら `v` のコピー。行列の次数を $n$ として、`k = 0` は $O(n)$、`k = 1` は $O(n^2)$、`k >= 2` は $O(n^3\log k)$

## 使い方
`H` に `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を定義して使う。
可変サイズの行列を素直に扱いたいときに使う。
`auto [power, sum] = A.pow_sum(k);` で冪と累積和を同時に求める。減算や逆元は使わないため、一般の半環でも使える。
`auto result = A.pow_apply(k, v);` は全状態の遷移を `k` 回進めたいときに使う。
1回の適用は $\mathrm{result}_i=\sum_j A_{ij}v_j$ で、係数の積が非可換でもこの順序を保つ。

## 例
`mint` の通常の加算と乗算を使う場合は、次のように演算を定義する。

```cpp
struct Ring {
    using T = mint;
    static T mul(T a, T b) { return a * b; }
    static void add(T& a, T b) { a += b; }
    static T one() { return 1; }
    static T zero() { return 0; }
};
matrix<Ring> a(2);
a[0][1] = a[1][0] = a[1][1] = 1;
auto power = a.pow(10);
```

## 実装上の補足
`pow` は最初の単位行列との積をコピーに置き換え、正の指数では行列積を1回省く。
`pow_sum` は $P(2a)=P(a)^2$、$S(2a)=S(a)+P(a)S(a)$ で倍増する。
固定幅整数を使う場合は、冪・累積和とその途中演算が係数型の範囲に収まることを前提とする。
`pow_apply` は指数の各1ビットでベクトルだけを更新する。
作業領域は `k <= 1` で $O(n)$、それ以外で $O(n^2)$、返却値は $O(n)$。行列の二乗・ベクトル積・累積加算の途中値も係数型に収める。min-plus の到達不能値は `H::mul` 側で保護する。
