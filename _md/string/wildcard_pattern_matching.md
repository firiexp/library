---
title: ワイルドカード付きパターン照合
documentation_of: //string/wildcard_pattern_matching.cpp
---

## 説明
文字列とパターンの両方にワイルドカードを含むパターン照合を行う。
ワイルドカードは任意の1文字に一致する。
文字列の長さを $N$、パターンの長さを $M$ として、時間は $O((N+M)\log(N+M+1))$、領域は $O(N+M)$。

## できること
- `vector<int> wildcard_pattern_matching(const string& text, const string& pattern, char wildcard = '*')`
  `text` の開始位置 $0,1,\ldots,N-M$ それぞれについて、`pattern` と一致すれば $1$、一致しなければ $0$ を返す

## 使い方
```cpp
auto matches = wildcard_pattern_matching("ab*aba", "a*");
```

この例では `{1, 0, 1, 1, 0}` を返す。
`pattern` が `text` より長い場合は空列を返す。空の `pattern` は全 $N+1$ 箇所で一致する。
任意の byte 列を扱えるが、`wildcard` に指定した文字は通常文字として使えない。

## 実装上の補足
$1\le M\le N$ の場合、$N+M-1\le 2^{21}$ が必要。
ワイルドカードを $0$、通常文字を byte 値 $+1$ に変換し、不一致の指標 $\sum ab(a-b)^2$ を3回の整数畳み込みで求める。
2つの法から整数値を復元するため、剰余の衝突による誤一致はない。
