---
title: 第二種Stirling数の列
documentation_of: //math/combinatorics/stirling_second_row.cpp
date: 2026-10-30
category: 数学
tags: 数学
---

## 説明
$N$ 個の区別できる要素を $k$ 個の空でないグループへ分割する第二種 Stirling 数 $S(N,k)$ を、$k=0,\ldots,K$ について求める。
グループの順序を区別する場合は $k!$ 倍する。

## できること
- `vector<mint> stirling_second_row(long long n, int k)`
  $S(N,0),\ldots,S(N,K)$ を `998244353` で割った余りの列を返す。$S(0,0)=1$、$j>N$ の要素は0とする。時間 $O(K(\log K+\log N))$、領域 $O(K)$

## 使い方
$0\leq N\leq\mathrm{LLONG\_MAX}$ と $0\leq K<2^{22}$ を渡す。
法は素数 `998244353` に固定し、階乗が可逆で、畳み込みの変換長が $2^{23}$ 以下に収まる範囲を使う。

```cpp
auto row = stirling_second_row(4, 6);
```

返り値は `{0, 1, 7, 6, 1, 0, 0}`。
$N$ は法以上でもよいが、整数としての指数をそのまま渡す。

## 実装上の補足
$N>0$ では `powk_all` と `Factorial` で次の2列を作り、既存の NTT で畳み込む。

$$
a_j=\frac{j^N}{j!},\qquad b_j=\frac{(-1)^j}{j!},\qquad S(N,k)=(a*b)_k
$$

$N=0$ は直接処理し、$0^0$ の定義に依存しない。
$K>N$ のときは $N$ まで計算し、残りを0で埋める。
