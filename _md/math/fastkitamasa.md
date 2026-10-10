---
title: 多項式剰余の冪計算(高速Kitamasa法)
documentation_of: //math/fastkitamasa.cpp
date: 2018-04-28
category: 数学
tags: 数学
---

## 説明
多項式 $f(x)$ に対する $x^K \bmod f(x)$ の係数列を求める。
次数を $N \ge 1$ として、前処理は $O(N \log(N+1))$、冪計算は $O(N \log(N+1)\log(K+2))$、作業領域は $O(N)$。

## できること
- `Fast_Kitamasa solver(coefficients)`
  `vector<mint>` の係数列から構築する。`coefficients[i]` は $x^i$ の係数で、末尾は非零とする
- `Fast_Kitamasa solver(coefficients, mod)`
  既存の `vector<int>` 入力を受け付ける。`mod` は使用する `mint::get_mod()` と一致させる。省略時も同じ法を使う
- `poly kitamasa(long long k) const`
  $x^k \bmod f(x)$ を低次から長さ $N$ で返す。`k >= 0` を前提とし、指数0では定数1を返す
- `void multiply_mod(poly &a, const poly &b) const`
  `a` を $ab \bmod f(x)$ にする。両入力の長さは $N$ 以下とする。空入力は零として扱う

## 使い方
先に `math/ntt.cpp` または `math/fft.cpp` のいずれかを include し、続けて `math/fastkitamasa.cpp` を include する。
NTT 版は法998244353、任意 mod 版は利用側で設定した素数 `MOD` を使う。両方の `poly` は同時に include しない。

```cpp
vector<mint> f = {-1, -1, 1};
Fast_Kitamasa solver(f);
poly remainder = solver.kitamasa(10);
```

$f(x)=x^2-x-1$ に対し、結果は $34+55x$、係数列は `{34, 55}` となる。
返り値の順序は現在の `poly` と同じ低次からの順である。
線形漸化式の値だけが必要なら `fps/linear_recurrence.cpp` を使い、剰余の全係数を再利用する場合はこのクラスを使う。

## 実装上の補足
反転した $f$ の逆多項式を前計算し、積の高次部分から商を求めて剰余を計算する。
定数項が0の多項式や非モニック多項式にも対応する。法は実行時には切り替えず、係数演算と畳み込みは選択した `mint` / `poly` に従う。
