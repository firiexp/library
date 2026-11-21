---
title: 相異なる部分列の個数
documentation_of: //string/count_distinct_subsequences.cpp
---

## 説明
文字列または配列から要素を順に選び、得られる非空部分列の種類数を求める。
同じ列になる添字の選び方は1度だけ数える。連続する部分文字列の個数とは異なる。

## できること
入力の長さを $N$ とする。

- `Count count_distinct_subsequences<Count>(string_view s)`
  `string` または `string_view` の非空部分列数を返す。空入力なら `0`。時間 $O(N)$、作業領域 $O(1)$
- `Count count_distinct_subsequences<Count>(const vector<T>& a)`
  配列の非空部分列数を返す。空入力なら `0`。期待時間 $O(N)$、作業領域 $O(N)$

## 使い方
`Count` は `0`・`1` からの構築、コピー、`+`・`-` に対応する型を指定する。mod を取る場合は `mint` などを使う。
配列版では `std::hash<T>` と `==` に対応する要素型を使う。
固定幅整数で数える場合は、空部分列を含む個数の2倍など、中間値もその型に収まることを前提とする。

```cpp
const string s = "aba";
long long count = count_distinct_subsequences<long long>(s);
mint count_mod = count_distinct_subsequences<mint>(s);
vector<long long> a = {1000000000000LL, -5, 1000000000000LL};
long long array_count = count_distinct_subsequences<long long>(a);  // 6
```

文字列 `"aba"` では `a, b, aa, ab, ba, aba` の6種類を数える。連続する部分文字列に限ると `aa` は含まれない。
`string_view` の部分範囲もそのまま渡せる。

## 実装上の補足
空部分列を含む現在の個数を $D$、要素 $c$ の前回追加直前の個数を $L_c$ とする。
要素 $c$ を追加すると $D'=2D-L_c$ となる。文字列では256要素の配列、配列ではハッシュ表に $L_c$ を記録し、最後に空部分列の1通りを引く。
