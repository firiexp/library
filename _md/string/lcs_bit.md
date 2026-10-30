---
title: LCS(bitset)
documentation_of: //string/lcs_bit.cpp
---
## 説明
bitset を使って 2 文字列の LCS 長を求める。

## できること
長い方の文字列長を $N$、短い方を $M$ とする。

- `int LCS_bit(const string& s, const string& t)`
  `s` と `t` の最長共通部分列の長さを返す。$O(N\lceil M/64\rceil)$

## 使い方
```cpp
const string s = "abc", t = "ac";
int len = LCS_bit(s, t);
```

この例では `len` は `2` になる。入力は変更せず、一時文字列も渡せる。

## 実装上の補足
文字は byte 単位で扱う。
短い方の文字列を bitset にし、入力は変更しない。
GCC 系の x86_64 環境では CPU を実行時に判定し、AVX2 + POPCNT で4 word、さらに AVX512F があれば8 word ずつ更新する。
利用側の pragma や CPU 指定は不要。短い bitset、非対応 CPU・環境、端数 word は scalar で処理する。
領域計算量は $O(256\lceil M/64\rceil)$。
