---
title: 相異なる部分列の個数
documentation_of: //string/count_distinct_subsequences.cpp
---

## 説明
文字列からいくつかの文字を順序を保って取り出した、内容の異なる非空部分列の個数を求める。
同じ列になる添字の選び方は一度だけ数える。連続する部分文字列の個数とは異なる。

## できること
- `T count_distinct_subsequences<T>(string_view s)`
  非空部分列数を `T` で返す。空入力なら `0`。`string` または `string_view` を渡せる。

長さを $N$ とすると、時間 $O(N)$、作業領域 $O(1)$。
`T` の構築・コピー・加減算を定数時間として数える。

## 使い方
`T` は `0`・`1` からの構築、コピー、`+`・`-` に対応する型を指定する。法を取る場合は `mint` などを使う。
固定幅整数で数える場合は、空部分列を含む個数の2倍など、中間値もその型に収まることを前提とする。

```cpp
const string s = "aba";
long long count = count_distinct_subsequences<long long>(s);
mint count_mod = count_distinct_subsequences<mint>(s);
```

この例では `a, b, aa, ab, ba, aba` の6種類を数える。連続する部分文字列に限ると `aa` は含まれない。
`string_view` の部分範囲もそのまま渡せる。

## 実装上の補足
空部分列を含む現在の個数を $D$、文字 $c$ の前回追加直前の個数を $L_c$ とする。
文字 $c$ を追加すると $D'=2D-L_c$ となる。$L_c$ を更新しながら走査し、最後に空部分列の1通りを引く。
