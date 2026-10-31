---
title: AND畳み込み(Bitwise AND Convolution)
documentation_of: //math/convolution/and_convolution.cpp
date: 2026-03-10
category: 数学
tags: 数学
---

## 説明
bitwise AND 畳み込みを計算する。
`c[S] = Σ_{A & B = S} a[A] b[B]` を返す。

## できること
$N$ を2冪に拡張した後の配列長とする。

- `void superset_zeta_transform(vector<T>& v)`
  superset zeta transform をその場適用する。$O(N\log N)$
- `void superset_mobius_transform(vector<T>& v)`
  superset zeta transform の逆変換をその場適用する。$O(N\log N)$
- `vector<T> and_convolution(vector<T> a, vector<T> b)`
  AND 畳み込みを返す。長さは大きい方に合わせて 2 冪へ拡張する。$O(N\log N)$

## 使い方
`T` には `+`, `-`, `*`, `+=`, `-=`, `*=` が必要。
AND 畳み込み以外にも superset zeta / mobius transform を単体で使える。
