---
title: 多倍長整数(BigInteger)
documentation_of: //util/biginteger.cpp
date: 2026-03-20
category: 数学
tags: 数学
---

## 説明
符号付き多倍長整数を扱う。
`BigInteger` は $10^{16}$ 基数の little endian limb 列を唯一の内部表現として持つ。
16 進入出力を中心に使う場合は、同じ API を $2^{60}$ 基数で実装した `HexBigInteger` を使う。

## できること
- `BigInteger()`
  `0` を作る
- `BigInteger(long long x)`
  `x` から作る
- `BigInteger(const string& s, int base = 10)`
  `s` から作る。`base` は $2$ 以上 $36$ 以下。不正な文字列なら assertion failure
- `x.assign(const string& s, int base = 10)`
  `s` を代入する。成功なら `true`、不正な文字列なら `false`
- `HexBigInteger(const string& s)`
  16 進文字列から作る
- `x.is_zero()`
  `x == 0` なら `true`
- `x.to_string(int base = 10)`
  `base` 表記の文字列にする。英字は小文字で返す
- `x += y`, `x -= y`, `x *= y`, `x /= y`, `x %= y`
  四則演算と余りを計算する。`/` は 0 方向に切り捨て、`%` は dividend と同符号の余りを返す。0 除算は assertion failure
- `x << k`, `x >> k`
  2 の冪でのシフトを行う
- `x < y`, `x <= y`, `x > y`, `x >= y`, `x == y`, `x != y`
  比較する
- `divmod(x, y)`
  `/` と `%` の結果を同時に返す。0 除算は assertion failure
- `floor_divmod(x, y)`
  商を負の無限大方向に丸め、divisor と同符号の余りを返す。0 除算は assertion failure

## 使い方
`Scanner` と `Printer` から直接入出力できる。

```cpp
BigInteger a, b;
sc.read(a, b);
auto [q, r] = divmod(a, b);
pr.println(q, r);
```

10 進中心なら `BigInteger`、16 進中心なら `HexBigInteger` を使う。
異なる基数の文字列も扱えるが、主基数以外の変換には追加コストがかかる。

## 実装上の補足

乗算は小さい入力で筆算、大きい入力で exact NTT を使う。
除算は商が短い入力で Knuth 法、それ以外の大きい入力で Newton 法による逆数計算を使う。
