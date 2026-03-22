---
title: Fast IO
documentation_of: //util/fastio.cpp
date: 2026-03-14
category: ユーティリティ
tags: ユーティリティ
---

## 説明
verify 用の小さい高速入出力。
通常は `fread` / `fwrite` ベースで動き、標準入出力が TTY のときは interactive 用の挙動に切り替わる。

## できること
- `Scanner in`
  入力を読む
- `in.read(T& x)`
  整数 `x` を読む
- `in.read(a, b, c, ...)`
  複数の値を続けて読む
- `in.read(pair<T, U>& p)`
  `p.first`, `p.second` を順に読む
- `in.read(Range& a)`
  `string` 以外の range を先頭から順に読む
- `in.read(char& c)`
  空白を飛ばして 1 文字読む
- `in.read(string& s)`
  空白区切り文字列を読む
- `in >> x`
  `in.read(x)` の別名
- `Printer out`
  出力をためる
- `out.print(x)`
  整数、`bool`、`char`、`string`、文字列リテラルを出力する
- `out.print(Range const& a)`
  `string` 以外の range を空白区切りで出力する
- `out.println(x)`
  `print(x)` の後に改行する
- `out.println(a, b, c, ...)`
  空白区切りで複数の値を出力して改行する
- `out.println()`
  改行だけ出力する
- `out << x`
  `out.print(x)` の別名

## 使い方
テストコードで `#include "../util/fastio.cpp"` して使う。

```cpp
Scanner in;
Printer out;

int n;
pair<int, int> p;
in.read(n);
in.read(p);

vector<int> a(n);
in.read(a);

out.println(a);
out.println(p.first, p.second);
```

## 実装上の補足
- interactive 問題では、`Scanner` は行入力ベースで詰まらないように読み、`Printer` は改行ごとに flush する
- range の入出力は `string` を除く `begin()` / `end()` を持つ型が対象
