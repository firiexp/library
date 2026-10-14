---
title: 二項係数（合成数mod）
documentation_of: //math/binom_mod.cpp
---

## 説明
二項係数 $\binom{n}{k}\bmod m$ を求める。法 $m$ を素因数分解し、素数冪ごとのテーブルと CRT の併合係数を前計算する。
$1\le m\le10^6$、$0\le n\le10^{18}$ を扱う。

## できること
- `BinomMod(m)`：法 $m$ 用のテーブルを構築する
- `ll C(ll n, ll k) const`：$\binom{n}{k}\bmod m$ を返す。$m=1$、$k<0$、$k>n$ なら $0$
- `ll modulus() const`：法を返す

## 使い方
```cpp
BinomMod binom(12);
auto value = binom.C(10, 3);
```

この例の結果は $0$。素数冪だけを扱う場合は `BinomModPrimePower` も引き続き使える。

## 実装上の補足
$m=\prod_i p_i^{q_i}$ として、構築時間は $O(\sqrt m+\sum_i p_i^{q_i})$、保持領域は $O(1+\sum_i p_i^{q_i})$。
1クエリは $O(1+\sum_i(\log_{p_i}(n+1)+\log(p_i^{q_i})))$。
CRT 用の配列確保や併合係数の逆数計算はクエリ中に行わない。素数冪ごとの階乗比の逆数計算は必要。
