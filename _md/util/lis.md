---
title: 最長増加部分列の復元
documentation_of: //util/lis.cpp
---

## 説明
最長増加部分列を元の配列の添字列として復元する。
時間 $O(N\log N)$、追加領域 $O(N)$。

## できること
- `lis_indices(a, strict = true)` : 狭義単調増加な最長部分列の添字を昇順で返す。`false` なら非減少部分列を返す
- 空配列には空列を返す。最適解が複数ある場合は任意の1つを返す

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さは `indices.size()` で得られる。
要素型には大小比較 `<` だけを使い、数値の番兵や座標圧縮は不要。
