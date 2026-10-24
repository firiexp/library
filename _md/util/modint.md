---
title: modint(固定MOD)
documentation_of: //util/modint.cpp
date: 2026-03-14
category: 数学
tags: 数学
---
## 説明
テンプレート引数で MOD を固定した剰余整数を扱う。
`+ - * /`、累乗、逆元、インクリメントを持つ。

## できること
- `modint<MOD> x`, `mint x`
  `MOD` 上の値を作る。負数もそのまま渡せる。$O(1)$
- `modint<MOD>::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る。$O(1)$
- `modint<MOD>::get_mod()`, `modint<MOD>::M()`
  MOD を返す。$O(1)$
- `x.value()`, `x.val`
  保持している値を返す。$O(1)$
- `++x`, `--x`, `x += y`, `x -= y`, `x *= y`
  加減算・乗算を行う。$O(1)$
- `x /= y`
  `x` を `y` で割る。mod が素数で、`y != 0` が必要。$O(\log MOD)$
- `x.pow(n)`
  $x^n$ を返す。`n >= 0` が必要。$O(\log n)$
- `x.inv()`
  逆元を返す。mod が素数で、`x != 0` が必要。$O(\log MOD)$
- `x == y`, `x != y`
  値を比較する。$O(1)$

## 使い方
`MOD` を定義してから `#include "../util/modint.cpp"` し、`mint` か `modint<MOD>` を使う。
