---
title: 前計算付きの辞書順k番目の受理文字列
documentation_of: //string/dfa_kth_word.cpp
---

## 説明
同じ `DFA<W>` に対して、長さや順位を変えながら辞書順 $k$ 番目の受理文字列を求める。
照会する長さは `max_length` 以下、0-indexed の順位は `max_rank` 以下として前計算する。
1回だけ求める場合は `string/kth_word.cpp` の `kth_word` を使う。

## できること

- `DFAKthWord index(a, max_length, max_rank = ULLONG_MAX)` : 各長さ・状態から受理できる文字列数を前計算する
- `index.kth(n, k)` : 長さ `n` の受理文字列のうち、0-indexed で `k` 番目を `optional<vector<int>>` で返す。受理語が不足すれば `nullopt`

状態数を $S$、文字種数を $W$、`max_length` を $N$ とする。
前計算は $O(NSW)$ 時間、保持領域は $O(NS+SW)$。長さ $n$ の復元は $O(nW)$ 時間。
個数表は `16 * (N+1) * S` バイトを使う。

## 使い方

```cpp
auto a = avoid_patterns<2, 'a'>({"aa"});
DFAKthWord index(a, 100, 1000);
auto first = index.kth(3, 0);
auto second = index.kth(3, 1);
auto longer = index.kth(100, 1000);
```

長さ100以下、順位1000以下の照会で同じ表を使う。
`first` は `"aba"` に対応する `{0, 1, 0}`、`second` は `"abb"` に対応する `{0, 1, 1}` となる。
禁止語の例には `string/avoid_patterns.cpp` も include する。

## 実装上の補足
個数は `__uint128_t` で保持し、`max_rank + 1` で飽和させる。
扱う順位が小さいなら `max_rank` を指定すると、前計算で走査する遷移を減らせる。
`max_rank == ULLONG_MAX` も指定できる。
