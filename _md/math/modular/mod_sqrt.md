---
title: 平方根(mod p)
documentation_of: //math/modular/mod_sqrt.cpp
---

## 説明
素数 $p$ を法として整数 $a$ の平方根を求める。

## できること
- `long long mod_sqrt(long long a, long long p)`
  $x^2 \equiv a \pmod p$ を満たす $0 \le x < p$ を1つ返す。解がなければ `-1`。期待 $O(\log^2 p)$

## 使い方
`p` は $2 \le p < 2^{63}$ の素数、`a` は負数も含む任意の `long long` を指定できる。

## 実装上の補足
$p \equiv 1 \pmod 4$ では Tonelli-Shanks 法を使う。
直近の素数 $p$ に対する前処理結果をスレッドごとに保持し、同じ $p$ の呼び出しで再利用する。
