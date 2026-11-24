---
title: modint(固定MOD)
documentation_of: //math/modular/modint.cpp
---

## 説明
テンプレート引数で MOD を固定した剰余整数を扱う。
`+ - * /`、累乗、逆元、インクリメントを持ち、合成数の MOD にも対応する。

## できること
- `modint<MOD> x`, `mint x`
  `MOD` 上の値を作る。負数もそのまま渡せる。$O(1)$
- `modint<MOD>::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る。$O(1)$
- `modint<MOD>::get_mod()`, `modint<MOD>::M()`
  MOD を返す。$O(1)$
- `x.value()`, `x.val`
  保持している値を返す。$O(1)$
- `++x`, `--x`, `x + y`, `x - y`, `x * y`, `x += y`, `x -= y`, `x *= y`
  加減算・乗算を行う。$O(1)$
- `x / y`, `x /= y`
  `x` を `y` で割る。`y` と `MOD` が互いに素である必要がある。$O(\log \mathrm{MOD})$
- `x.pow(n)`
  $x^n$ を返す。`n >= 0` が必要。$O(\log n)$
- `x.inv()`
  逆元を返す。`x` と `MOD` が互いに素である必要がある。$O(\log \mathrm{MOD})$
- `x == y`, `x != y`
  値を比較する。$O(1)$

## 使い方
事前に `MOD` を定義した上で、`mint` か `modint<MOD>` を使う（テンプレートの `snippets/template.cpp` では `MOD = 998244353` が定義済み）。
加減算を含む各演算は $1 \le \mathrm{MOD} \le 2^{31}$ で使う。
