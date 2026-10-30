---
title: ランレングス圧縮(RLE)
documentation_of: //util/rle.cpp
date: 2026-03-08
category: util
tags: util
---

## 説明
列を run-length encoding する。
連続する同じ値を `(値, 個数)` にまとめる。

## できること
- `vector<pair<T, int>> RLE(const vector<T>& a)`
  `a` を run-length encoding した列を返す。$O(|a|)$
- `vector<pair<char, int>> RLE(string_view s)`
  `string` または `string_view` を圧縮した列を返す。$O(|s|)$

いずれも空入力なら空列を返す。出力領域はラン数に比例する。

## 使い方
`T` には `==` が必要。
返り値の各要素は出現順に並ぶ。
入力長は `int` に収まることを前提とする。

```cpp
string s = "aaabbc";
auto runs = RLE(s);
auto middle = RLE(string_view(s).substr(2, 3));
```

`runs` は `('a', 3), ('b', 2), ('c', 1)`、`middle` は `('a', 1), ('b', 2)` となる。
