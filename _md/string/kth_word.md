---
title: 有限オートマトンの辞書順k番目の文字列
documentation_of: //string/kth_word.cpp
---

## 説明
`DFA<W>` が受理する固定長の文字列から、辞書順で $k$ 番目を復元する。
文字の順序は $0,1,\ldots,W-1$ とし、先頭の $0$ も一文字として扱う。

## できること
状態数を $S$、文字列長を $N$、文字種数を $W$ とする。

- `optional<vector<int>> kth_word(const DFA<W>& a, int n, unsigned long long k)`
  長さ `n` の受理文字列のうち、0-indexed で `k` 番目の文字番号列を返す。範囲外なら `nullopt`。`n >= 0` が必要。時間 $O(NSW)$、領域 $O(NS)$

## 使い方
```cpp
auto a = avoid_patterns<2, 'a'>({"aa"});
auto word = kth_word(a, 3, 1);
string text;
if (word) for (int c : *word) text.push_back('a' + c);
```

この例では `text` は `"abb"` となる。
禁止語の例には `string/avoid_patterns.cpp` も include する。
手書きの遷移表や `intersect` の結果もそのまま渡せる。

## 実装上の補足
残り長さと状態ごとの受理個数を前計算し、各位置で文字順に候補の個数を引く。
個数は `__uint128_t` で保持し、$k+1$ で飽和させる。mod を取った個数では大小を判定しない。
`k == ULLONG_MAX` も指定できる。
`n == 0` では、空列を受理しかつ `k == 0` なら空の `vector<int>` を返す。それ以外は `nullopt`。
巨大な長さに対して個数だけを求める場合は `count_words` を使う。
