---
title: 固定長正方行列(Square Matrix)
documentation_of: //math/squarematrix.cpp
date: 2026-03-15
category: データ構造
tags: データ構造
---

## 説明
サイズ固定になる代わりに `array` を使う正方行列。
`H` が定める加法と乗法で演算する。

## できること
- `SquareMatrix<H, SIZE> A`
  `SIZE × SIZE` 行列を 0 初期化で作る
- `SquareMatrix<H, SIZE>::I()`
  単位行列を返す
- `SquareMatrix<H, SIZE>::I(n)`
  左上 `n × n` だけを使う単位行列を返す
- `A += B`, `A -= B`, `A *= B`
  加減算、行列積を行う
- `A.pow(k)`
  $A^k$ を返す
- `A.pow(k, n)`
  左上 `n × n` だけを使って $A^k$ を返す
- `x * A`
  長さ `SIZE` の行ベクトルに右から掛ける

## 使い方
サイズが固定で、累乗や遷移行列を繰り返し回すときに使う。
実際に使うサイズが `SIZE` 未満なら `pow(k, n)` を使うと未使用領域を回さずに済む。
`H` は `using T`、`static T mul(T, T)`、`static void add(T&, T)`、`static T one()`、`static T zero()` を持てばよい。

## 例
普通の行列積を `mint` で使う場合。

```cpp
struct Ring {
    using T = mint;
    static T mul(T a, T b) { return a * b; }
    static void add(T &a, T b) { a += b; }
    static T one() { return 1; }
    static T zero() { return 0; }
};

using Mat = SquareMatrix<Ring, 50>;
```

min-plus 行列積を使う場合。

```cpp
struct MinPlus {
    using T = ll;
    static T mul(T a, T b) {
        if (a == INF<ll> || b == INF<ll>) return INF<ll>;
        return a + b;
    }
    static void add(T &a, T b) { a = min(a, b); }
    static T one() { return 0; }
    static T zero() { return INF<ll>; }
};

using Mat = SquareMatrix<MinPlus, 100>;
```

max-plus 行列積も同じ形で書ける。

```cpp
struct MaxPlus {
    using T = ll;
    static T mul(T a, T b) {
        if (a == -INF<ll> || b == -INF<ll>) return -INF<ll>;
        return a + b;
    }
    static void add(T &a, T b) { a = max(a, b); }
    static T one() { return 0; }
    static T zero() { return -INF<ll>; }
};
```