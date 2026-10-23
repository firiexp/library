---
title: Z-Algorithm
documentation_of: //string/z-algorithm.cpp
date: 2026-03-08
category: 文字列
tags: 文字列
---

## 説明
文字列 `s` の各位置 `i` について、`s` と `s[i, |s|)` の最長共通接頭辞長を $O(|s|)$ で求める。
`res[i]` は `s[0..)` と `s[i..)` の LCP 長になる。
別の列 `pattern` と `text` の各 suffix の LCP も、区切り文字や連結なしで求められる。

## できること
- `vector<int> Z_algorithm(const string& s)`
  Z 配列を返す。`res[0] = |s|`。空文字列なら空 vector を返す
- `vector<int> z_match(pattern, text)`
  `LCP(pattern, text[i..))` を各位置について返す。引数は `string` 同士、または同じ要素型の `vector<T>` 同士
- `z_match` の返却長は常に `text.size()`。空の `pattern` なら全要素 `0`、空の `text` なら空列を返す

## 使い方
`auto z = Z_algorithm(s);` として使う。
部分文字列検索には `z_match(pattern, text)` を使う。

```cpp
string pattern = "aba", text = "abacaba";
auto common = z_match(pattern, text);
vector<int> positions;
for (int i = 0; i < (int)text.size(); ++i) {
    if (common[i] == (int)pattern.size()) positions.push_back(i);
}
```

## 実装上の補足
- 一致判定だけでなく、各 suffix と先頭の一致長をまとめて取りたいときに向く
- 返る配列は 0-indexed
- `z_match` は等値比較だけを使い、NUL や `0xff` も通常の要素として扱う。入力は変更しない
- $M=|\mathrm{pattern}|$, $N=|\mathrm{text}|$ として、時間 $O(M+N)$、返却列を含む追加領域 $O(M+N)$
- 空の `pattern` でも位置 $N$ の要素は返さない。空列の一致位置を列挙する場合の末尾は別に扱う
