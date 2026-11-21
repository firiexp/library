---
title: MOD逆元(拡張ユークリッド互除法)
documentation_of: //math/modular/modinv.cpp
---

## 説明
法 $M$ における整数 $x$ の逆元を求める。$x$ は負でも $M$ 以上でもよい。

## できること
- `T mod_inv(T x, T M)`
  $0 \le r < M$ かつ $xr \equiv 1 \pmod{M}$ を満たす $r$ を返す。$M = 1$ のときは `0`。$O(\log M)$

## 使い方
$M \ge 1$ かつ $\gcd(x, M) = 1$ を前提とする。
