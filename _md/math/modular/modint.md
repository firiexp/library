---
title: modint(固定MOD)
documentation_of: //math/modular/modint.cpp
---
## 説明
テンプレート引数で MOD を固定した剰余整数を扱う。
`+ - * /`、累乗、逆元、インクリメントを持つ。

## できること
合成数を法とする場合も逆元や商を求められる。逆元を求める値（除算では除数）は `MOD` と互いに素である必要がある。`assert` が有効なときはこの条件を検査する。`MOD = 1` では逆元も商も0になる。

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
- `x / y`, `x /= y`
  `x` に `y` の逆元を掛けた値を返す。`/=` はその値で `x` を更新する。$O(\log MOD)$
- `x.pow(n)`
  $x^n$ を返す。`n >= 0` が必要。$O(\log n)$
- `x.inv()`
  `x` の乗法逆元を返す。$O(\log MOD)$
- `x == y`, `x != y`
  値を比較する。$O(1)$

## 使い方
事前に `MOD` を定義した上で、`mint` か `modint<MOD>` を使う（テンプレートの `snippets/template.cpp` では `MOD = 998244353` が定義済み）。
