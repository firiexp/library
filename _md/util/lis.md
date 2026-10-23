---
title: 最長増加部分列
documentation_of: //util/lis.cpp
---

## 説明
最長増加部分列の長さを求め、必要なら元の配列の添字列として復元する。
時間はどちらも $O(N\log N)$。長さを $L$ として、長さ取得の追加領域は $O(L)$、復元は $O(N)$。

## できること
- `int lis_length(a, strict = true)` : 狭義単調増加な最長部分列の長さを返す。空配列には `0` を返す
- `vector<int> lis_indices(a, strict = true)` : 最長部分列の添字を昇順で返す。空配列には空列を返す。最適解が複数なら任意の1つを返す
- どちらも `strict = false` なら非減少部分列を求める。入力は変更しない

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さだけが必要なら `int length = lis_length(a);` とする。復元用の配列は作らない。
要素型には大小比較 `<` だけを使い、数値の番兵や座標圧縮は不要。
`lis_length` は要素のコピー構築・コピー代入も必要とする。`lis_indices` は要素をコピーしない。
