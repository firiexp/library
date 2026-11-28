---
title: 任意MOD畳み込み(3 NTT + Garner)
documentation_of: //fps/fft.cpp
---

## 説明
指定した `MOD` (合成数含む) で多項式の積と形式的べき級数の逆数を求める。 も使える。

## できること
$N$ を入力の係数数とする。
長さ $n,m$ の列を NTT で掛けるには、出力長 $n+m-1$ が $2^{24}$ 以下である必要がある。

- `vector<unsigned int> ArbitraryConvolution::convolution_mod(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  各係数を $0$ 以上 $\mathrm{MOD}$ 未満の剰余で渡すと、`MOD` 上の畳み込みを返す。$O(N\log N)$
- `poly operator*(const poly& a, const poly& b)`
  多項式の積を返す。$O(N\log N)$
- `poly inv() const`
  $a(x)b(x) \equiv 1 \pmod{x^N}$ を満たす $N$ 項の $b(x)$ を返す。定数項は `MOD` と互いに素とする。 $O(N\log N)$

## 使い方
$1 \le \mathrm{MOD} \le 2^{31}$ の整数定数 `MOD` を定義してから読み込む。
`poly` の `a[i]` には $x^i$ の係数を入れる。負の係数もそのまま代入できる。
整数値を保った畳み込みは `math/convolution/integer_convolution.cpp` を使う。

## 実装上の補足
NTT では $167772161, 469762049, 1224736769$ の 3 素数を使い、Garner で結果を復元する。
`convolution_mod` に剰余を取らずに係数を渡す場合も、整数としての各出力係数がこの 3 素数の積未満なら正しく復元できる。
