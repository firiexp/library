---
title: 最長増加部分列
documentation_of: //util/lis.cpp
---

## 説明
最長増加部分列の長さ、添字列の復元、最適な添字列の個数を求める。

## できること
入力列の長さを $N$、最長増加部分列の長さを $L$ とする。
いずれも `strict = false` なら非減少部分列を求める。

- `int lis_length(a, strict = true)` : 狭義単調増加な最長部分列の長さを返す。空配列には `0` を返す。時間 $O(N\log N)$、追加領域 $O(L)$
- `vector<int> lis_indices(a, strict = true)` : 最長部分列の添字を昇順で返す。空配列には空列を返す。最適解が複数なら任意の1つを返す。時間 $O(N\log N)$、追加領域 $O(N)$
- `pair<int, Count> lis_count<Count>(a, strict = true)` : 最長部分列の長さと個数を返す。元の添字列が異なれば別に数え、空配列には `{0, 1}` を返す。時間 $O(N\log N)$、追加領域 $O(N)$

## 使い方
`auto indices = lis_indices(a);` とし、`a[indices[i]]` で各要素を取得する。
長さだけが必要なら `int length = lis_length(a);` とする。
要素の大小比較には `<` を使う。
`lis_length` は要素のコピー構築・コピー代入も必要とする。`lis_indices` と `lis_count` は要素をコピーしない。
個数も必要なら `auto [length, count] = lis_count<mint>(a);` とする。
`Count` には `0`・`1` からの構築、コピーと `+=` が必要で、整数型や modint を使える。
整数型では途中の個数も型の範囲に収める。modint の個数が法で0になっても長さは保持する。

## 実装上の補足
`lis_count` は値を座標圧縮し、長さが大きい側を採用し、同じ長さなら個数を足す集約を BIT で扱う。
長さ0の集約は個数0とし、新しい部分列を開始するときだけ1通りを与える。
長さだけ・復元だけの関数は個数計算を行わない。
