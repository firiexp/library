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
  `MOD` 上の値を作る。負数もそのまま渡せる
- `modint<MOD>::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る
- `modint<MOD>::get_mod()`, `modint<MOD>::M()`
  MOD を返す
- `x.value()`, `x.val`
  保持している値を返す
- `++x`, `--x`, `x += y`, `x -= y`, `x *= y`, `x /= y`
  各演算を行う
- `x.pow(n)`
  $x^n$ を返す
- `x.inv()`
  逆元を返す。逆元が存在しない場合は壊れる
- `x == y`, `x != y`
  値を比較する

## 使い方
`MOD` を定義してから `#include "../util/modint.cpp"` し、`mint` か `modint<MOD>` を使う。
`/` と `inv()` は `MOD` が素数で、対象が `0` でない状況を前提にしている。
