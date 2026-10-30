---
title: 式パーサ(Parse)
documentation_of: //util/parse.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明
整数と `()+-*/` からなる式を再帰下降で評価する。
空白や単項演算子は扱わない。

## できること
- `int parse_expression(string_view s)`
  式全体を評価する。`const string`、一時文字列、部分 `string_view` を渡せる。入力は変更しない。長さ $N$ に対し時間・作業領域 $O(N)$

以下の低水準入口は、読み進める文字数に比例する時間で評価し、`cur` を読み取り後の位置へ進める。

- `int expr(state& cur)`
  式全体を評価する。`+` と `-` を扱う
- `int addsub(state& cur)`
  加減算を評価する
- `int muldiv(state& cur)`
  乗除算を評価する
- `int factor(state& cur)`
  数値または括弧付き式を評価する
- `int num(state& cur)`
  連続する数字を読み取って整数にする。数字で始まらなければ未定義

## 使い方
`parse_expression` に式をそのまま渡す。停止文字の追加は不要。

```cpp
const string s = "2*(3+4)";
int value = parse_expression(s);
int inner = parse_expression(string_view(s).substr(3, 3));
```

この例では `value` は14、`inner` は7になる。
空白・単項演算子・NUL を含まない、空でない有効な式を渡す。
数値リテラルと演算の途中値は `int` に収まり、除数は0でないことを前提とする。

## 実装上の補足
`parse_expression` は内部で文字列をコピーして停止用 NUL を追加し、既存の再帰下降処理を呼ぶ。
低水準入口を直接使う場合は、従来どおり停止文字を含む文字列と、その先頭を指す `state` を用意する。
再帰の深さは括弧の入れ子に比例する。
乗除算は加減算より優先し、同じ優先順位の演算は左から結合する。除算は C++ の整数除算を使う。
不正入力の検出は行わない。
