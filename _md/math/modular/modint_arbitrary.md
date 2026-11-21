---
title: modint(任意MOD)
documentation_of: //math/modular/modint_arbitrary.cpp
---

## 説明
実行時に MOD を設定する剰余整数を扱う。
固定 MOD 版と同じ演算を持ち、`set_mod` だけが追加で必要になる。

## できること
合成数を法とする場合も逆元や商を求められる。逆元を求める値（除算では除数）は `MOD` と互いに素である必要がある。`assert` が有効なときはこの条件を検査する。`MOD = 1` では逆元も商も0になる。

- `mint::set_mod(mod)`
  正の `uint` を法として設定する。使う前に呼ぶ。$O(1)$
- `modint x`, `mint x`
  現在の MOD 上の値を作る。負数もそのまま渡せる。$O(1)$
- `modint::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る。$O(1)$
- `modint::get_mod()`, `modint::M()`
  現在の MOD を返す。$O(1)$
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
先に `mint::set_mod(mod);` を呼んでから値を作る。
加減算も使う場合は $1 \le MOD \le 2^{31}$ の範囲で法を選ぶ。mod を変更した後は値を作り直す。

## 実装上の補足
乗算は `set_mod` で計算した64 bitの逆数と `unsigned __int128` による Barrett reduction を使う。法1も扱い、`val` は通常の剰余表現のまま保持する。
