---
title: 任意の法の行列式
documentation_of: //math/matrix_determinant_mod.cpp
date: 2026-10-08
category: 数学
tags: 数学
---

## 説明
合成数を含む任意の法で正方行列の行列式を求める。
逆元を使わず、整数商による行の加減算と交換で上三角化する。
時間は $O(N^3(1+\log m))$、入力コピーを含む領域は $O(N^2)$。

## できること
- `ll matrix_determinant_mod(vector<vector<ll>> A, int mod)`
  入力を保持して行列式を `[0, mod)` に正規化して返す。空行列は `1 % mod`、法1では常に0

## 使い方
正方行列 `A` と $1 \le \mathrm{mod} \le \mathrm{INT\_MAX}$ を渡す。
要素は負の値を含む `long long` の全範囲を受け取る。
法の素因数分解や `modint` の設定は不要とする。
素数法では $O(N^3)$ の `math/matrix_determinant.cpp` も使える。
