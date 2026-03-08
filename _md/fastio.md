---
layout: post
title: Fast IO
date: 2026-03-08
category: ユーティリティ
tags: ユーティリティ
---

## 説明
verify 用の小さい高速入出力。
`fread` / `fwrite` を使って整数や文字列を読む。

## できること
- `Scanner in`
  入力を読む
- `in.read(T& x)`
  整数 `x` を読む
- `in.read(a, b, c, ...)`
  複数の値を続けて読む
- `in.read(char& c)`
  空白を飛ばして 1 文字読む
- `in.read(string& s)`
  空白区切り文字列を読む
- `Printer out`
  出力をためる
- `out.write(x)`
  整数、`char`、`string`、文字列リテラルを出力する
- `out.writeln(x)`
  `write(x)` の後に改行する
- `out.writeln(a, b, c, ...)`
  空白区切りで複数の値を出力して改行する
- `out.writeln()`
  改行だけ出力する

## 使い方
テストコードで `#include "../util/fastio.cpp"` して使う。

```cpp
Scanner in;
Printer out;

int n, q;
in.read(n);
in.read(q);
while (q--) {
    int t, u, v;
    in.read(t, u, v);
    out.writeln(t, u, v);
}
```
