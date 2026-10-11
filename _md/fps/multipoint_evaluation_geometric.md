---
title: 等比数列上の多点評価
documentation_of: //fps/multipoint_evaluation_geometric.cpp
date: 2026-10-11
category: FPS
tags: FPS
---

## 説明
多項式 $f$ を等比数列 $a,ar,\ldots,ar^{M-1}$ 上で評価する。
Chirp Z 変換により1回の畳み込みへ帰着する。

## できること
- `vector<mint> multipoint_evaluation_geometric(const poly& f, mint a, mint r, int m)`
  `f(a * r^i)` を `i = 0..m-1` の順に返す。空多項式は全て `0`、`m = 0` は空列。係数数を $N$ として時間 $O((N+M)\log(N+M))$、領域 $O(N+M)$

## 使い方
`fps/multipoint_evaluation_geometric.cpp` を読み込み、法 `998244353` の `poly` と開始点・公比・評価点数を渡す。
`m >= 0` を前提とし、入力多項式は変更しない。
`a = 0`、`r = 0, 1` や評価点の重複も扱う。

```cpp
poly f(vector<mint>{1, 2, 3});
auto values = multipoint_evaluation_geometric(f, mint(2), mint(3), 3);
```

返り値は `f(2), f(6), f(18)`。

## 実装上の補足
$ij=\binom{i+j}{2}-\binom{i}{2}-\binom{j}{2}$ を用いて係数を重み付けする。
三角数乗は乗算で順に生成し、小さい片側には Horner 法を使う。
畳み込み経路では $2N+M-2$ 以上の最小の2冪が NTT の上限 $2^{23}$ 以下であることを前提とする。
