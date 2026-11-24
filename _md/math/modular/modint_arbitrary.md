---
title: modint(任意MOD)
documentation_of: //math/modular/modint_arbitrary.cpp
---

## 説明
実行時に MOD を設定する剰余整数を扱う。
固定 MOD 版と同じ演算を持ち、合成数の MOD にも対応する。利用前に `set_mod` で MOD を設定する。

## できること
- `mint::set_mod(mod)`
  MOD を設定する（`mod >= 1`）。使う前に呼ぶ。$O(1)$
- `modint x`, `mint x`
  現在の MOD 上の値を作る。負数もそのまま渡せる。$O(1)$
- `modint::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る。$O(1)$
- `modint::get_mod()`, `modint::M()`
  現在の MOD を返す。$O(1)$
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
先に `mint::set_mod(mod);` を呼んでから値を作る。
加減算を含む各演算は $1 \le \mathrm{MOD} \le 2^{31}$ で使う。MOD を変更した後は値を作り直す。

## 実装上の補足
乗算は `set_mod` で計算した 64 bit の逆数と `unsigned __int128` による Barrett reduction を使う。逆元は拡張ユークリッド互除法で求める。MOD 1 も扱い、`val` は通常の剰余表現のまま保持する。
