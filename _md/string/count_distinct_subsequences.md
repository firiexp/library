---
title: 相異なる部分列の個数
documentation_of: //string/count_distinct_subsequences.cpp
---

## 説明
文字列または配列から要素を順に選び、得られる非空部分列の種類を数える。
同じ列になる添字の選び方は一度だけ数える。連続する部分文字列の個数とは異なる。

## できること
どちらの関数も空入力なら `0` を返す。入力の長さを $N$、異なる要素の数を $K$ とする。

- `Count count_distinct_subsequences<Count>(string_view s)`
  `string` または `string_view` の非空部分列数を返す。時間 $O(N)$、作業領域 $O(1)$。
- `Count count_distinct_subsequences<Count>(const vector<T>& a)`
  配列の非空部分列数を返す。要素型 `T` はコピーでき、`==` で等しい要素に `std::hash<T>` が同じ値を返すことが必要。期待時間 $O(N)$、ハッシュの衝突が集中した場合は最悪 $O(N^2)$。作業領域は $O(K)$。

個数の型 `Count` の構築・コピー・加減算と、要素のコピー・比較・ハッシュ値の計算は定数時間とする。

## 使い方
`Count` は `0`・`1` からの構築、コピー、`+`・`-` に対応する型を指定する。法を取る場合は `mint` などを使う。
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
空部分列を含む現在の個数を $D$、要素 $c$ を前回追加する直前の個数を $L_c$ とする。初めて現れる要素では $L_c=0$ とする。
要素 $c$ を追加すると $D'=2D-L_c$ となる。文字列では256要素の表、配列ではハッシュ表に $L_c$ を記録し、最後に空部分列の1通りを引く。
