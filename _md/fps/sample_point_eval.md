---
title: 連続標本点からの1点評価
documentation_of: //fps/sample_point_eval.cpp
date: 2026-10-11
category: FPS
tags: FPS
---

## 説明
次数 $N$ 未満の多項式の値 $f(0),\ldots,f(N-1)$ から、任意の1点 $f(x)$ を Lagrange 補間で求める。

## できること
- `Mint sample_point_eval(const vector<Mint>& ys, Mint x)`
  `ys[i] = f(i)` として `f(x)` を返す。空の値列は `0`、既知点ならその値を返す。時間・作業領域は $O(N)$、既知点への評価は $O(1)$

## 使い方
`fps/sample_point_eval.cpp` を読み込み、値列と評価点を同じ `modint<P>` 型で渡す。
`P` は $2^{31}$ 未満の固定素数、$N\leq P$ を前提とする。
法 `998244353` と `1000000007` のどちらも使える。

```cpp
vector<mint> ys = {1, 4, 9};
mint value = sample_point_eval(ys, mint(5));
```

この例の返り値は `36`。
階乗逆元は `Factorial<Mint>` の共有キャッシュを内部で用意して再利用する。
