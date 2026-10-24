---
title: 特性多項式
documentation_of: //math/characteristic_polynomial.cpp
---

## 説明
正方行列 $A$ の特性多項式 $\det(xI-A)$ を求める。

## できること
- `vector<T> characteristic_polynomial(vector<vector<T>> a)`
  行列の次数を $N$ として、特性多項式の係数を定数項から順に $N+1$ 要素で返す。最高次の係数は `1`。時間 $O(N^3)$、補助領域 $O(N^2)$

## 使い方
`T` には非零要素で除算できる体の型を使う。例えば素数を法とする `modint` を指定できる。

```cpp
vector<vector<mint>> a = { {1, 2}, {3, 4} };
auto p = characteristic_polynomial(a);
```

この例では $x^2-5x-2$ の係数が返る。
空行列の特性多項式は $1$ とする。

## 実装上の補足
相似変換で上 Hessenberg 形にし、先頭主小行列の特性多項式を順に計算する。
副対角が零になった位置で、それより前の多項式からの寄与を打ち切る。上三角・対角行列では全体が $O(N^2)$ 時間となる。
整数 $1,\ldots,N$ による除算は使わず、標数が $N$ 以下の体にも対応する。
