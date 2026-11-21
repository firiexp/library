---
title: 高速入出力(Fast IO)
documentation_of: //util/fastio.cpp
---

## 説明
整数・文字列・配列などを読み書きする高速入出力。
interactive 問題のプログラムを端末で直接起動し、手入力で試す場合は、行単位でやり取りする挙動に自動で切り替わる。

## できること

### Scanner

- `in.read(T& x)`
  整数 `x` を読む
- `in.read(double& x)`
  浮動小数点数を読む
- `in.read(a, b, c, ...)`
  複数の値を続けて読む
- `in.read(pair<T, U>& p)`
  `p.first`, `p.second` を順に読む
- `in.read(Range& a)`
  range の各要素に先頭から順に読み込む
- `in.read(char& c)`
  空白を飛ばして 1 文字読む
- `in.read(string& s)`
  空白区切り文字列を読む
- `in.read(T& x)` (`x.value()` を持つ型)
  整数を読み `T(v)` で代入する（`modint` など）
- `in.read(T& x)` (`x.assign(string)` を持つ型)
  文字列を読んで `assign` する
- `in >> x`
  `in.read(x)` の別名

### Printer

- `out.print(x)`
  整数、`bool`、`char`、`string`、文字列リテラルを出力する。`double` は小数点以下15桁で出力する
- `out.print(string_view s)`
  ビューが参照する `s.size()` バイトをそのまま出力する。途中のヌル文字も出力する
- `out.print_fixed(double x, int precision = 15)`
  `double` を小数点以下 `precision` 桁で出力する。
- `out.print(x)` (`x.value()` を持つ型)
  `x.value()` の値を出力する（`modint` など）
- `out.print(x)` (`x.to_string()` を持つ型)
  `to_string()` の結果を出力する
- `out.print(Range const& a)`
  range の各要素を空白区切りで出力する。`string_view` の配列では各ビューの間に空白を1つ入れる
- `out.println(x)`
  `print(x)` の後に改行する
- `out.println(a, b, c, ...)`
  空白区切りで複数の値を出力して改行する
- `out.println_fixed(double x, int precision = 15)`
  `out.print_fixed(x, precision)` の後に改行する
- `out.println()`
  改行だけ出力する
- `out.flush()`
  出力バッファを即時 flush する（pipe 接続のインタラクティブ問題で必要）
- `out << x`
  `out.print(x)` の別名

## 使い方

```cpp
Scanner in;
Printer out;

int n;
double x;
pair<int, int> p;
in.read(n);
in.read(x);
in.read(p);

vector<int> a(n);
in.read(a);

out.println(a);
out.println(p.first, p.second);
out.println(x);
out.println_fixed(x, 8);
```

## 実装上の補足
通常は `fread` / `fwrite` で入出力し、`double` の読み取りには `from_chars` を使う。

- interactive 用の自動切り替えは、標準入力・標準出力がそれぞれ端末（TTY）に接続されている場合に行う。入力側では `Scanner` が行単位で読み、空行も読み飛ばす。出力側では `Printer` が文字列中の改行も含めて改行ごとに flush する
- ファイルからのリダイレクトや、judge と pipe で接続する実行では自動切り替えされない
- range の入出力は `string` と `string_view` を除く `begin()` / `end()` を持つ型が対象
