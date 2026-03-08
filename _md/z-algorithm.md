---
title: Z-algorithm
documentation_of: //string/z-algorithm.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明
文字列 `s` の各位置 `i` について、`s` と `s[i, |s|)` の最長共通接頭辞長を `O(|s|)` で求める。
`res[i]` は `s[0..)` と `s[i..)` の LCP 長になる。

## できること
- `vector<int> Z_algorithm(const string& s)`
  Z 配列を返す。`res[0] = |s|`。空文字列なら空 vector を返す

## 使い方
`auto z = Z_algorithm(s);` として使う。
部分文字列検索では `pattern + '$' + text` のように連結し、`z[i] == pattern.size()` になる位置を拾えばよい。

```cpp
string t = pattern + '$' + text;
auto z = Z_algorithm(t);
for (int i = 0; i < (int)t.size(); ++i) {
    if (z[i] == (int)pattern.size()) {
        // pattern が一致
    }
}
```

## 実装上の補足
- 一致判定だけでなく、各 suffix と先頭の一致長をまとめて取りたいときに向く
- 返る配列は 0-indexed
- `'$'` のような区切り文字を使うときは、元の文字列に現れない文字を選ぶ
