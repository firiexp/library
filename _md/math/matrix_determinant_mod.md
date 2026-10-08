---
title: 任意 mod の行列式
documentation_of: //math/matrix_determinant_mod.cpp
date: 2026-10-08
category: 数学
tags: 数学
---

## 説明
合成数を含む任意 mod で正方行列の行列式を求める。
逆元を使わず、整数商による行の加減算と交換で上三角化する。
時間は $O(N^3\log m)$、入力コピーを含む領域は $O(N^2)$。

## できること
- `ll matrix_determinant_mod(vector<vector<ll>> A, int mod)`
  入力を保持して行列式を `[0, mod)` に正規化して返す。空行列は `1 % mod`、mod 1 では常に0
- `Mint matrix_determinant_mod(const vector<vector<Mint>>& A)`
  `modint` 行列の行列式を同じ型で返す。mod は `Mint::get_mod()` から取得し、入力は保持する

## 使い方
正方行列 `A` と $1 \le \mathrm{mod} \le \mathrm{INT\_MAX}$ を渡す。
要素は負の値を含む `long long` の全範囲を受け取る。
整数行列では mod を第2引数に渡す。
`modint` 行列では `matrix_determinant_mod(A)` とする。固定 mod 版と実行時 mod 版の両方に対応する。
実行時 mod 版は行列を作る前に `Mint::set_mod(mod)` を呼ぶ。対応する mod の範囲は整数行列と同じとする。
`Mint` には `get_mod()`、`value()`、整数からの構築を使い、逆元や除算は要求しない。

素数 mod では $O(N^3)$ の `math/matrix_determinant.cpp` も使える。

## 例
`Mint` を `modint<6>` とした場合も、そのまま計算できる。

```cpp
using Mint = modint<6>;
vector<vector<Mint>> A = { {2, 1}, {3, 2} };
Mint det = matrix_determinant_mod(A);
Mint doubled = det * 2;
```

`det` は1、`doubled` は2になる。
