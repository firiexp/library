---
title: 整数畳み込み(2/3 NTT)
documentation_of: //math/convolution/integer_convolution.cpp
---

## 説明
非負整数列の畳み込みを整数値のまま求める。

## できること
入力列が空でないとき、出力長 $N$ は長さ $n,m$ の列の畳み込みで $n+m-1$、長さ $n$ の列の自己畳み込みで $2n-1$ となる。入力列のいずれかが空なら空配列を返す。

| 名前空間 | 対応する出力長 $N$ | 各出力係数の条件 |
| --- | --- | --- |
| `ArbitraryConvolution` | $2^{24}$ 以下 | `unsigned long long` に収まる |
| `BoundedConvolution` | $2^{21}$ 以下 | $998244353 \times 1004535809$ 未満 |

- `vector<unsigned long long> ArbitraryConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  `a` と `b` の畳み込みを返す。$O(N\log N)$
- `vector<unsigned long long> ArbitraryConvolution::square_u64(const vector<unsigned int>& a)`
  `a` の自己畳み込みを返す。$O(N\log N)$
- `vector<unsigned long long> BoundedConvolution::convolution_u64(const vector<unsigned int>& a, const vector<unsigned int>& b)`
  `a` と `b` の畳み込みを返す。$O(N\log N)$
- `vector<unsigned long long> BoundedConvolution::square_u64(const vector<unsigned int>& a)`
  `a` の自己畳み込みを返す。$O(N\log N)$

## 使い方
通常は `ArbitraryConvolution` を使う。`BoundedConvolution` を選ぶときは、出力係数の上限を呼び出し側で確かめる。

## 実装上の補足
`ArbitraryConvolution` は小さい入力では直接積を求め、それ以外は 3 素数の NTT と中国剰余定理を使う。`BoundedConvolution` は 2 素数で畳み込む。
NTT を使うとき、`square_u64` の順変換は各素数につき 1 回で済む。
