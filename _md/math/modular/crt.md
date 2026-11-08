---
title: 中国剰余定理(Chinese Remainder Theorem)
documentation_of: //math/modular/crt.cpp
date: 2019-08-18
category: 数学
tags: 数学
---

## 説明

$$
x \equiv a_i \pmod{M_i} \quad (1 \le i \le N)
$$

という情報から、$\operatorname{lcm}(M_1, M_2, \dots, M_N)$ を法とする $x$ を復元する。

## できること
- `CRT(a)` : 合同式の列 `a` をまとめ、解があれば `(r, M)`、解がなければ `(0, 0)` を返す。空列には `(0, 1)` を返す。合同式の数を $N$、各法の最大値を $B$ として $O(N\log B)$

## 使い方
`a[i] = (a_i, M_i)` を渡す。
各 $M_i$ は正とし、余り $a_i$ が負数や $M_i$ 以上の場合には内部で正規化する。
戻り値 `(r, M)` は $x \equiv r \pmod{M}$、$0 \le r < M$ を満たす。
各法の最小公倍数が `long long` に収まる範囲で使う。中間積は `__int128` で計算する。
余りには `LLONG_MIN` を含む任意の `long long` を渡せる。
最小公倍数が上限を超える入力は対象外であり、`(0, 0)` は合同式の矛盾だけを表す。
