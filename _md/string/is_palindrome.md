---
title: 回文判定
documentation_of: //string/is_palindrome.cpp
date: 2018-04-28
category: 文字列
tags: 文字列
---

## 説明
ワイルドカードを任意の文字に置き換えて、文字列を回文にできるかを判定する。

## できること
- `is_palindrome(s, c = '?')` : 文字列 `s` の文字 `c` をそれぞれ任意の文字に置き換えて回文にできるなら `true`、そうでなければ `false`。$O(|s|)$

## 使い方
既定のワイルドカードは `'?'`。`is_palindrome("a?")` は `true` を返す。
ワイルドカードを使わずに判定する場合は、`s` に含まれない文字を第2引数に指定する。
空文字列は `true` を返す。
