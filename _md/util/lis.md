---
title: 最長増加部分列
documentation_of: //util/lis.cpp
---

## 説明
最長増加部分列の長さを求める。
元の配列の添字列として復元したり、最長増加部分列の個数を数えたりすることもできる。

## できること
入力列の長さを $N$、最長増加部分列の長さを $L$ とする。
いずれも `strict = false` なら非減少部分列を求める。
個数を数える型 `U` には `long long` や modint を指定する。

- `int lis_length(a, strict = true)` : 狭義単調増加な最長部分列の長さを返す。時間 $O(N\log N)$、追加領域 $O(L)$
- `vector<int> lis_indices(a, strict = true)` : 最長部分列の添字を昇順で返す。最適解が複数なら任意の1つを返す。時間 $O(N\log N)$、追加領域 $O(N)$
- `pair<int, U> lis_count<U>(a, strict = true)` : 最長部分列の長さと個数を返す。元の添字列が異なれば別に数える。時間 $O(N\log N)$、追加領域 $O(N)$

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さだけが必要なら `int length = lis_length(a);` とする。
要素の大小比較には `<` を使う。
個数も必要なら `auto [length, count] = lis_count<mint>(a);` とする。

## 実装上の補足
空配列に対しては、`lis_length` は `0`、`lis_indices` は空列、`lis_count` は `{0, 1}` を返す。
`lis_count` は値を座標圧縮し、長さが大きい側を採用し、同じ長さなら個数を足す集約を BIT で扱う。
