---
title: modint(任意MOD)
documentation_of: //util/modint_arbitrary.cpp
date: 2026-03-14
category: 数学
tags: 数学
---

## 説明
実行時に MOD を設定する剰余整数を扱う。
固定 MOD 版と同じ演算を持ち、`set_mod` だけが追加で必要になる。

## できること
- `mint::set_mod(mod)`
  MOD を設定する。使う前に 1 回以上呼ぶ
- `modint x`, `mint x`
  現在の MOD 上の値を作る。負数もそのまま渡せる
- `modint::raw(v)`
  `0 <= v < MOD` を仮定してそのまま作る
- `modint::get_mod()`, `modint::M()`
  現在の MOD を返す
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
先に `mint::set_mod(mod);` を呼んでから値を作る。
`/` と `inv()` は現在の MOD が素数で、対象が `0` でない状況を前提にしている。
