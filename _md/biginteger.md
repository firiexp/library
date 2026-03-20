---
title: 多倍長整数(BigInteger)
documentation_of: //util/biginteger.cpp
date: 2026-03-20
category: 数学
tags: 数学
---

## 説明
符号付き多倍長整数を扱う。
内部表現は $2^{32}$ 基数の little endian limb 列で、加減算・比較・シフト・短整数演算と長除算を持つ。

## できること
- `BigInteger()`
  `0` を作る
- `BigInteger(long long x)`
  `x` から作る
- `BigInteger(const string& s, int base = 10)`
  `s` から作る。`base` は `10` または `16` を想定する
- `x.is_zero()`
  `x == 0` なら `true`
- `x.to_string(int base = 10)`
  `base` 表記の文字列にする。`16` のときは小文字で返す
- `x += y`, `x -= y`, `x *= y`, `x /= y`, `x %= y`
  四則演算と余りを計算する。`/` は床除算、`%` は divisor と同符号の余りを返す
- `x << k`, `x >> k`
  2 の冪でのシフトを行う
- `x < y`, `x <= y`, `x > y`, `x >= y`, `x == y`, `x != y`
  比較する
- `divmod(x, y)`
  商と余りを同時に返す

## 使い方
`BigInteger a(s);` のように作って使う。
文字列入力が decimal ならそのまま、hex なら `BigInteger(s, 16)` と `to_string(16)` を使う。

## 実装上の補足
- 加減算と比較は符号付き絶対値で処理する
- 乗算は小さいとき schoolbook、大きいときは畳み込みに切り替える
- 除算は正規化付き long division を使う
