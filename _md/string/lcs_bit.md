---
title: LCS(bitset)
documentation_of: //string/lcs_bit.cpp
---
## 説明
bitset を使って 2 文字列の LCS 長を求める。

## できること
長い方の文字列長を $N$、短い方を $M$ とする。

- `int LCS_bit(string& s, string& t)`
  `s` と `t` の最長共通部分列の長さを返す。$O(N\lceil M/64\rceil)$

## 使い方
```cpp
string s, t;
int len = LCS_bit(s, t);
```

## 実装上の補足
文字は byte 単位で扱う。
