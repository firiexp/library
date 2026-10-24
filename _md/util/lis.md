---
title: 最長増加部分列
documentation_of: //util/lis.cpp
---

## 説明
最長増加部分列の長さを求め、必要なら元の配列の添字列として復元する。

## できること
入力列の長さを $N$、最長増加部分列の長さを $L$ とする。
どちらも `strict = false` なら非減少部分列を求める。

- `int lis_length(a, strict = true)` : 狭義単調増加な最長部分列の長さを返す。空配列には `0` を返す。時間 $O(N\log N)$、追加領域 $O(L)$
- `vector<int> lis_indices(a, strict = true)` : 最長部分列の添字を昇順で返す。空配列には空列を返す。最適解が複数なら任意の1つを返す。時間 $O(N\log N)$、追加領域 $O(N)$

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さだけが必要なら `int length = lis_length(a);` とする。
要素の大小比較には `<` を使う。
`lis_length` は要素のコピー構築・コピー代入も必要とする。`lis_indices` は要素をコピーしない。
